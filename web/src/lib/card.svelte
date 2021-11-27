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
</script>

<section>
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
    background-color: aliceblue;
    display: grid;
    grid: "image image" 300px "info actions" auto / 50% auto;
    gap: 1rem;
    border-radius: 18px;
    aspect-ratio: 6 / 6;
    padding: min(16px, 5%);
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
