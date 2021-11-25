<script context="module">
</script>

<script>
  import Heart from "$lib/heart.svelte";
</script>

<section>
  <canvas />
  <div id="info" />
  <div id="actions">
    <Heart />
  </div>
</section>

<style>
  section {
    background-color: aliceblue;
    display: grid;
    grid: "image image" 80% "info actions" auto / 50% auto;
    gap: 1rem;
    border-radius: 18px;
    width: min(350px, 80%);
    padding: min(18px, 5%);
    scroll-snap-align: start;
  }

  canvas {
    grid-area: image;
    width: 100%;
    height: 100%;
    border-radius: 12px;
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
