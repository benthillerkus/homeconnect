<script context="module">
  export const prerender = true
</script>

<script>
  import Card from "$lib/card.svelte"

  let data = {
    url: "kuhli-image-post.svg"
  }
</script>

<svelte:head>
  <title>Homeconnect</title>
</svelte:head>

<main>
  <hgroup>
    <h1>Ein soziales Netzwerk<br />für Kühlschränke</h1>
    <p><i>fridge storage management</i></p>
  </hgroup>
  <Card {data} />
</main>

<style>
  main {
    display: flex;
    width: 100%;
    height: 100%;
    align-items: center;
    justify-content: center;
    flex-direction: column-reverse;
    gap: 2rem;
  }

  @media only screen and (min-width: 650px) {
    main {
      flex-direction: row;
    }
  }

  hgroup {
    text-align: end;
    line-height: 2rem;
  }

  h1 {
    font-family: Cambria, Cochin, Georgia, Times, "Times New Roman", serif;
  }

  p {
    font-family: "Gill Sans", "Gill Sans MT", Calibri, "Trebuchet MS", sans-serif;
  }
</style>
