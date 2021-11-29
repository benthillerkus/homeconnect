<script context="module">
  export const ssr = false
</script>

<script>
  import Heart from "$lib/heart.svelte"
  import { onMount } from "svelte"
  import { fade } from "svelte/transition"
  import "$lib/inset.js"

  export let data
  export let delay = 0

  let canvas
  let ctx
  let width
  let height
  let img
  let loaded = false

  function initImage() {
    loaded = true

    const aspect = width / height
    const aspectImage = img.naturalWidth / img.naturalHeight
    if (aspect > aspectImage) {
      const newHeight = width / aspectImage
      ctx.drawImage(img, 0, (height - newHeight) / 2, width, newHeight)
    } else {
      const newWidth = height * aspectImage
      ctx.drawImage(img, (width - newWidth) / 2, 0, newWidth, height)
    }

    ctx.beginPath()
    ctx.shadowInset = true
    ctx.shadowBlur = 5
    ctx.shadowColor = "#CCCCCE"
    ctx.globalCompositeOperation = "multiply"
    ctx.fillStyle = "white"
    ctx.rect(0, 0, width, height)
    ctx.fill()
    ctx.beginPath()
    ctx.shadowBlur = 20
    ctx.shadowColor = "#EEEEF5"
    ctx.rect(0, 0, width, height)
    ctx.fill()
  }

  onMount(async () => {
    const io = new IntersectionObserver((entries, observer) => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          ctx = canvas.getContext("2d")
          canvas.width = canvas.clientWidth
          canvas.height = canvas.clientHeight
          img = new Image()
          img.onload = initImage
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

  let liked
  let lastTouch = 0
  function handleDoubletap(event) {
    if (event.pointerType === "touch") {
      const now = Date.now()
      if (now - lastTouch < 500) {
        event.preventDefault()
        liked = !liked
      } else {
        lastTouch = now
      }
    }
  }
</script>

<section bind:this={card} on:mousemove={handleMousemove} on:pointerdown={handleDoubletap}>
  <canvas bind:this={canvas} bind:clientHeight={height} bind:clientWidth={width} />
  {#if !loaded}
    <div transition:fade={{ duration: 2500 }} id="overlay" />
  {/if}
  <div id="info">
    <span>{width}x{height}</span>
  </div>
  <div id="actions">
    <Heart {liked} />
  </div>
</section>

<style>
  section {
    display: grid;
    grid: "image image" auto "info actions" 40px / 50% auto;
    min-width: 388px;
    gap: 1rem;
    border-radius: 18px;
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
    border-radius: 18px;
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
    border-radius: 8px;
    background-color: black;
  }

  #overlay {
    grid-area: image;
    position: absolute;
    left: 0;
    top: 0;
    width: 100%;
    height: 100%;
    content: "";
    border-radius: 8px;
    background: black;
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
  }
</style>
