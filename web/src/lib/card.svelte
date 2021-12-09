<script context="module">
  export const ssr = false
</script>

<script>
  import Heart from "$lib/heart.svelte"
  import Share from "$lib/share.svelte"
  import { onMount } from "svelte"
  import { fade } from "svelte/transition"

  export let data

  let canvas
  let ctx
  const width = 356
  const height = 300
  let img
  let loaded = false

  let currentFilterDrawOffsetAtAnimationStart = 0
  let oldId = 1
  let currentId = 0

  const filters = [
    ctx => {
      ctx.globalCompositeOperation = "soft-light"
      ctx.globalAlpha = 0.8
      const gradient = ctx.createLinearGradient(0, 0, 0, height)
      gradient.addColorStop(0, "pink")
      gradient.addColorStop(1, "lightblue")
      ctx.fillStyle = gradient
    },
    ctx => {
      ctx.globalCompositeOperation = "overlay"
      ctx.globalAlpha = 0.5
      ctx.fillStyle = "red"
    },
    ctx => {
      ctx.globalCompositeOperation = "screen"
      ctx.globalAlpha = 0.4
      ctx.fillStyle = "blue"
    }
  ]

  function drawImage() {
    loaded = true

    ctx.globalCompositeOperation = "source-over"
    ctx.globalAlpha = 1
    ctx.fillStyle = "black"
    ctx.clearRect(0, 0, width, height)

    const aspect = width / height
    const aspectImage = img.naturalWidth / img.naturalHeight
    if (aspect > aspectImage) {
      const newHeight = width / aspectImage
      ctx.drawImage(img, 0, (height - newHeight) / 2, width, newHeight)
    } else {
      const newWidth = height * aspectImage
      ctx.drawImage(img, (width - newWidth) / 2, 0, newWidth, height)
    }

    // color correction
    ctx.fillStyle = "A6FF00"
    ctx.globalCompositeOperation = "divide"
    ctx.globalAlpha = 0.17
    ctx.fillRect(0, 0, width, height)

    console.log(
      currentFilterDrawOffsetAtAnimationStart - width,
      currentFilterDrawOffsetAtAnimationStart + width * (oldId < currentId ? 1 : -1)
    )

    // filter
    filters[currentId](ctx)
    ctx.fillRect(currentFilterDrawOffsetAtAnimationStart, 0, width, height)
    filters[oldId](ctx)
    ctx.fillRect(getOldFilterDrawOffset(), 0, width, height)
  }

  onMount(async () => {
    canvas.width = width
    canvas.height = height

    const io = new IntersectionObserver((entries, observer) => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          ctx = canvas.getContext("2d")
          img = new Image()
          img.crossOrigin = "Anonymous"
          img.onload = drawImage
          img.src = data.url
          observer.disconnect()
        }
      })
    })

    io.observe(canvas)
  })

  let card

  function handleMousemove(event) {
    window.requestAnimationFrame(timespamp => {
      const rect = card.getBoundingClientRect()
      let x = (event.clientX - rect.left) / rect.width - 0.5
      let y = (event.clientY - rect.top) / rect.height - 0.5
      card.style.setProperty("--mouse-x", x)
      card.style.setProperty("--mouse-y", y)
      card.style.setProperty("--intrusion", 2 - Math.abs(x) - Math.abs(y))
    })
  }

  async function handleShare() {
    const blob = await (await fetch(canvas.toDataURL())).blob()
    navigator.share({
      title: "Homeconnect",
      text: "Image from Homeconnect",
      url: window.location.origin,
      files: [
        new File([blob], "homeconnect.png", {
          type: blob.type,
          lastModified: new Date().getTime()
        })
      ]
    })
  }

  let liked
  let lastTouch = 0
  function handleDoubletap(event) {
    if (event.pointerType === "touch") {
      const now = Date.now()
      if (now - lastTouch < 500) {
        event.preventDefault()
        navigator.vibrate([75, 25, 50])
        liked = !liked
      } else {
        lastTouch = now
      }
    }
  }

  let currentFilterDrawOffsetAtAnimationEnd = 0
  let swipeAnimationRunning = false
  function animateSwipe() {
    swipeAnimationRunning = true
    currentFilterDrawOffsetAtAnimationStart +=
      (currentFilterDrawOffsetAtAnimationEnd - currentFilterDrawOffsetAtAnimationStart) * 0.1
    if (
      Math.abs(currentFilterDrawOffsetAtAnimationStart - currentFilterDrawOffsetAtAnimationEnd) >
      0.5
    ) {
      window.requestAnimationFrame(animateSwipe)
    } else {
      currentFilterDrawOffsetAtAnimationStart = currentFilterDrawOffsetAtAnimationEnd
      swipeAnimationRunning = false
    }
    window.requestAnimationFrame(drawImage)
  }

  function getOldFilterDrawOffset() {
    return currentFilterDrawOffsetAtAnimationStart + width * (oldId > currentId ? 1 : -1)
  }

  function changeFilter(id) {
    if (id === currentId || id < 0 || id >= filters.length) return
    oldId = currentId
    currentId = id
    currentFilterDrawOffsetAtAnimationStart = oldId < currentId ? width : -width
    currentFilterDrawOffsetAtAnimationEnd = 0

    if (!swipeAnimationRunning) {
      animateSwipe()
    }
  }
</script>

<section bind:this={card} on:mousemove={handleMousemove} on:pointerdown={handleDoubletap}>
  <canvas bind:this={canvas} {height} {width} />
  {#if !loaded}
    <div transition:fade={{ duration: 2500 }} id="overlay" />
  {:else}
    <div id="filter">
      <button class="arrow" on:click={() => changeFilter(currentId - 1)}>◀</button>
      <div>
        {#each filters as filter, id}
          <input
            type="radio"
            value={id}
            class="dot"
            bind:group={currentId}
            on:click={() => changeFilter(id)}
          />
        {/each}
      </div>
      <button on:click={() => changeFilter(currentId + 1)}>▶</button>
    </div>
  {/if}
  <div id="info">
    <span>{width}x{height}</span>
  </div>
  <div id="actions">
    <Share onclick={handleShare} />
    <Heart {liked} />
  </div>
</section>

<style>
  section {
    --outer-border-radius: 18px;
    --inner-border-radius: 8px;
    display: grid;
    grid: "image image" auto "info actions" 40px / 50% auto;
    min-width: 388px;
    gap: 1rem;
    border-radius: var(--outer-border-radius);
    aspect-ratio: 6 / 6;
    padding: min(16px, 5%);
    transition: transform 0.6s cubic-bezier(0.175, 0.885, 0.32, 1.275);
    box-shadow: 0 3px 4px rgba(0, 0, 0, 0.041), 0 1px 3px rgba(0, 0, 0, 0.055);
    transform: perspective(30cm) translateZ(0px);
    background: rgb(230, 226, 220);
  }

  section::after {
    content: "";
    position: absolute;
    z-index: -3;
    width: 100%;
    height: 100%;
    border-radius: var(--outer-border-radius);
    box-shadow: 0 0 60px rgba(0, 0, 0, 0.144);
    opacity: 0;
    transition: opacity 0.3s ease-out;
  }

  @media (hover: hover) and (pointer: fine) and (prefers-reduced-motion: no-preference) {
    section:hover {
      transform: perspective(30cm) translateZ(calc(var(--intrusion) * 16px))
        rotateX(calc(var(--mouse-y) * 30deg)) rotateY(calc(var(--mouse-x) * -30deg));

      background: radial-gradient(
          at calc((var(--mouse-x, 0) + 0.5) * 100%) calc((var(--mouse-y, 0) + 0.5) * 100%),
          rgb(245, 243, 238),
          rgb(230, 226, 220)
        )
        no-repeat 0 0;
    }

    section:hover::after {
      opacity: 1;
    }
  }

  canvas {
    grid-area: image;
    display: block;
    width: 100%;
    height: 100%;
    border-radius: var(--inner-border-radius);
    background-color: black;
    user-select: none;
  }

  #overlay {
    grid-area: image;
    position: absolute;
    left: 0;
    top: 0;
    width: 100%;
    height: 100%;
    border-radius: var(--inner-border-radius);
    background: black;
  }

  #filter {
    grid-area: image;
    position: absolute;
    left: 0;
    top: 0;
    width: 100%;
    height: 100%;
    display: flex;
    flex-direction: row;
    justify-content: space-between;
    align-items: center;
    border-radius: var(--inner-border-radius);
    box-shadow: inset 0 0 3px 1px rgba(0, 0, 0, 0.103), inset 0 0 10px 5px rgba(0, 0, 0, 0.089);
  }

  #filter > * {
    opacity: 0;
    transition: opacity 0.2s ease;
  }

  #filter:hover > * {
    opacity: 1;
  }

  #filter > button {
    border: none;
    border-radius: 20px;
    margin: 8px;
    padding-inline: 16px;
    padding-block: 2px;
    color: white;
    background: rgba(255, 255, 255, 0.185);
  }

  #filter > div {
    display: flex;
    justify-content: center;
    align-items: flex-end;
    width: 100%;
    height: 90%;
    gap: 5px;
  }

  .dot {
    margin: 0;
    border: none;
    border-radius: 20px;
    height: 9px;
    width: 9px;
    background: rgba(255, 255, 255, 0.185);
  }

  #filter > div > input:checked {
    background: rgba(255, 255, 255, 0.5);
  }

  #filter > div > input:focus {
    outline: none;
  }

  #info {
    grid-area: info;
  }

  #actions {
    grid-area: actions;
    display: flex;
    flex-direction: row;
    align-items: center;
    justify-content: flex-end;
    gap: 0.3rem;
  }
</style>
