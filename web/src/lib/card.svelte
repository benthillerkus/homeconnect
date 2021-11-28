<script context="module">
  export const ssr = false
</script>

<script>
  import Heart from "$lib/heart.svelte"
  import { onMount } from "svelte"
  import "$lib/inset.js"

  export let data
  export const delay = 0

  let canvas
  let ctx
  let width
  let height
  let img

  function easeInOutQuad(x) {
    return x < 0.5 ? 2 * x * x : 1 - Math.pow(-2 * x + 2, 2) / 2
  }

  let start, previousTimeStamp
  const fadeLength = 2000 + delay
  function fadeImage(timestamp) {
    if (start === undefined) start = timestamp
    const elapsed = timestamp - start
    const progress = Math.min(elapsed / fadeLength, 1)
    const aspect = width / height
    const aspectImage = img.naturalWidth / img.naturalHeight

    ctx.clearRect(0, 0, width, height)

    if (aspect > aspectImage) {
      const newHeight = width / aspectImage
      ctx.drawImage(img, 0, (height - newHeight) / 2, width, newHeight)
    } else {
      const newWidth = height * aspectImage
      ctx.drawImage(img, (width - newWidth) / 2, 0, newWidth, height)
    }

    ctx.shadowInset = true
    ctx.shadowBlur = 3
    ctx.shadowColor = "#CCCCCE"
    ctx.globalCompositeOperation = "multiply"
    ctx.beginPath()
    let component = Math.pow(easeInOutQuad(progress), 0.8) * 255
    ctx.fillStyle = `rgb(${component} ${component} ${component})`
    ctx.rect(0, 0, width, height)
    ctx.fill()
    ctx.shadowBlur = 20
    ctx.shadowColor = "#EEEEF5"
    ctx.fillStyle = "white"
    ctx.rect(0, 0, width, height)
    ctx.fill()

    if (elapsed < fadeLength) {
      previousTimeStamp = timestamp
      window.requestAnimationFrame(fadeImage)
    }
  }

  onMount(async () => {
    ctx = canvas.getContext("2d")
    canvas.width = canvas.clientWidth
    canvas.height = canvas.clientHeight
    img = new Image()
    img.onload = () => window.requestAnimationFrame(fadeImage)
    img.src = data.url
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

  function handleMouseout() {
    if (isInsideCard()) {
      return false
    } else {
      card.style.transform = "perspective(30cm) translateZ(0px)"
      return true
    }
  }
</script>

<section bind:this={card} on:mousemove={handleMousemove}>
  <canvas bind:this={canvas} bind:clientHeight={height} bind:clientWidth={width} />
  <div id="info">
    <span>{data.created_at}</span>
  </div>
  <div id="actions">
    <Heart />
  </div>
</section>

<style>
  section {
    display: grid;
    grid: "image image" calc(min(300px, 70vw)) "info actions" auto / 50% auto;
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
    width: 100%;
    height: 100%;
    border-radius: 8px;
    background-color: black;
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
