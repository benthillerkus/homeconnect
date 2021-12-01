<script context="module">
  export const prerender = true
</script>

<script>
  import Card from "$lib/card.svelte"

  let data = {
    url: "kuhli-image-post.svg"
  }

  let code
</script>

<svelte:head>
  <title>Homeconnect</title>
</svelte:head>

<main>
  <section id="login">
    <form action={`/feed/${code}`}>
      <input id="code" bind:value={code} type="text" placeholder="Hast du einen Code?" />
      <label for="code">
        <span aria-hidden="false" style="display: none;">Hast du einen Code?</span>
      </label>
      <button>▶</button>
    </form>
  </section>
  <section id="copy">
    <hgroup>
      <h1>Ein soziales Netzwerk<br />für Kühlschränke</h1>
      <p><i>fridge storage management</i></p>
    </hgroup>
    <Card {data} />
  </section>
</main>

<style>
  main {
    display: flex;
    width: 100%;
    height: 100%;
    justify-content: center;
    flex-direction: column;
    align-items: center;
    gap: 20%;
  }

  #copy {
    display: flex;
    flex-direction: column-reverse;
    align-items: center;
    justify-content: center;
    flex-direction: column;
    gap: 2rem;
  }

  #login {
    position: absolute;
    bottom: 10%;
    width: 100%;
  }

  form {
    width: 100%;
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: stretch;
    --color: rgb(230, 226, 220);
  }

  input[type="text"] {
    width: 50%;
    font-size: 1.1rem;
    font-family: "Gill Sans", "Gill Sans MT", Calibri, "Trebuchet MS", sans-serif;
  }

  input,
  button {
    border-radius: 0px;
    border: solid 2px var(--color);
    padding: 0.5rem;
  }

  button {
    background: var(--color);
    color: white;
    cursor: pointer;
    height: 50px;
    aspect-ratio: 1;
  }

  hgroup {
    text-align: center;
    line-height: 2rem;
  }

  @media only screen and (min-width: 650px) {
    #copy {
      flex-direction: row;
    }

    hgroup {
      text-align: end;
    }
  }

  h1 {
    font-family: Cambria, Cochin, Georgia, Times, "Times New Roman", serif;
  }

  p {
    font-family: "Gill Sans", "Gill Sans MT", Calibri, "Trebuchet MS", sans-serif;
  }
</style>
