<script context="module">
</script>

<script>
  import Heart from "$lib/heart.svelte"
  import { onMount } from "svelte"

  export let data

  let canvas
  let ctx
  let width
  let height
  let img

  function draw() {
    const aspect = width / height
    const aspectImage = img.naturalWidth / img.naturalHeight

    if (aspect > aspectImage) {
      const newHeight = width / aspectImage
      ctx.drawImage(img, 0, (height - newHeight) / 2, width, newHeight)
    } else {
      const newWidth = height * aspectImage
      ctx.drawImage(img, (width - newWidth) / 2, 0, newWidth, height)
    }
  }

  onMount(async () => {
    ctx = canvas.getContext("2d")
    canvas.width = canvas.clientWidth
    canvas.height = canvas.clientHeight
    img = new Image()
    img.onload = draw
    img.src = data.url
  })

  let card

  function handleMousemove(event) {
    const rect = card.getBoundingClientRect()
    let x = (event.clientX - rect.left) / rect.width - 0.5
    let y = (event.clientY - rect.top) / rect.height - 0.5

    window.requestAnimationFrame(timespamp => {
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
    grid: "image image" 300px "info actions" auto / 50% auto;
    gap: 1rem;
    border-radius: 18px;
    aspect-ratio: 6 / 6;
    padding: min(16px, 5%);
    transition: transform 0.3s ease-out;
    box-shadow: 0 3px 4px rgba(0, 0, 0, 0.041), 0 1px 3px rgba(0, 0, 0, 0.055);
    transform: perspective(30cm) translateZ(0px);
    background: radial-gradient(
        at calc((var(--mouse-x, 0) + 0.5) * 100%) calc((var(--mouse-y, 0) + 0.5) * 100%),
        rgb(245, 243, 238),
        rgb(230, 226, 220)
      )
      no-repeat 0 0;
    background-blend-mode: screen;
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
  @media (hover: hover) and (pointer: fine), only screen {
    section:hover {
      transform: perspective(30cm) translateZ(calc(var(--intrusion) * 16px))
        rotateX(calc(var(--mouse-y) * 30deg)) rotateY(calc(var(--mouse-x) * -30deg));
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
    background-color: beige;
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
