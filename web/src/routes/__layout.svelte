<script>
  import { goto } from "$app/navigation"
  if (typeof document !== "undefined") {
    document.addEventListener("keyup", event => {
      if (event.key === "Escape") {
        goto("squarespace")
      }
    })
  }
</script>

<header>
  <h1>Homeconnect</h1>
</header>
<slot />
<footer>
  <small>
    <nav>
      <a href="/">about</a>
      <a href="https://github.com/benthillerkus/homeconnect">source</a>
      <a
        href="https://raw.githubusercontent.com/benthillerkus/homeconnect/main/web/static/3rd-party-licenses.txt"
        >licenses</a
      >
    </nav>
  </small>
</footer>

<style>
  /*
  Josh's Custom CSS Reset
  https://www.joshwcomeau.com/css/custom-css-reset/
  */
  :global(*),
  :global(*::before),
  :global(*::after) {
    box-sizing: border-box;
  }
  :global(*) {
    margin: 0;
  }
  :global(html),
  :global(body) {
    height: 100%;
  }
  :global(body) {
    line-height: calc(1em + 0.5rem);
    -webkit-font-smoothing: antialiased;
  }
  :global(img),
  :global(picture),
  :global(video),
  :global(canvas),
  :global(svg) {
    display: block;
    max-width: 100%;
  }
  :global(input),
  :global(button),
  :global(textarea),
  :global(select) {
    font: inherit;
  }
  :global(p),
  :global(h1),
  :global(h2),
  :global(h3),
  :global(h4),
  :global(h5),
  :global(h6) {
    overflow-wrap: break-word;
  }
  :root {
    color-scheme: light;
    font-family: sans-serif;
  }

  header {
    z-index: 1;
    position: absolute;
    width: 100%;
    text-align: center;
    background: linear-gradient(
      to bottom,
      hsl(0, 0%, 100%),
      hsla(0, 0%, 100%, 0.945) 7.9%,
      hsla(0, 0%, 100%, 0.883) 15.3%,
      hsla(0, 0%, 100%, 0.815) 22.2%,
      hsla(0, 0%, 100%, 0.743) 28.7%,
      hsla(0, 0%, 100%, 0.66692) 34.8%,
      hsla(0, 0%, 100%, 0.58891) 40.6%,
      hsla(0, 0%, 100%, 0.50925) 46.2%,
      hsla(0, 0%, 100%, 0.42866) 51.7%,
      hsla(0, 0%, 100%, 0.34817) 57.2%,
      hsla(0, 0%, 100%, 0.2693) 62.8%,
      hsla(0, 0%, 100%, 0.19309) 68.7%,
      hsla(0, 0%, 100%, 0.12126) 75.2%,
      hsla(0, 0%, 100%, 0.05882) 82.6%,
      hsla(0, 0%, 100%, 0.01457) 91.2%,
      hsla(0, 0%, 100%, 0)
    );
    height: 6%;
  }

  header > h1 {
    padding-top: 1%;
    font-size: 1.5rem;
  }
  footer {
    display: block;
    width: 100%;
    background: linear-gradient(
      to top,
      hsl(0, 0%, 100%),
      hsla(0, 0%, 100%, 0.945) 7.9%,
      hsla(0, 0%, 100%, 0.883) 15.3%,
      hsla(0, 0%, 100%, 0.815) 22.2%,
      hsla(0, 0%, 100%, 0.743) 28.7%,
      hsla(0, 0%, 100%, 0.66692) 34.8%,
      hsla(0, 0%, 100%, 0.58891) 40.6%,
      hsla(0, 0%, 100%, 0.50925) 46.2%,
      hsla(0, 0%, 100%, 0.42866) 51.7%,
      hsla(0, 0%, 100%, 0.34817) 57.2%,
      hsla(0, 0%, 100%, 0.2693) 62.8%,
      hsla(0, 0%, 100%, 0.19309) 68.7%,
      hsla(0, 0%, 100%, 0.12126) 75.2%,
      hsla(0, 0%, 100%, 0.05882) 82.6%,
      hsla(0, 0%, 100%, 0.01457) 91.2%,
      hsla(0, 0%, 100%, 0)
    );
  }

  footer small nav {
    display: flex;
    height: 100%;
    justify-content: center;
    align-items: center;
  }

  footer small nav a {
    padding: 0.2rem;
    opacity: 0.5;
    text-decoration: none;
    color: black;
  }

  @media only screen and (min-width: 500px) {
    footer {
      position: absolute;
      bottom: 0%;
      height: 50px;
    }
  }
</style>
