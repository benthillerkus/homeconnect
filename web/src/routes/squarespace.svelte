<form action="wp-login.php">
  <label>
    email address<br>
    <input type="text" placeholder="name@example.com" />
  </label>
  <label>
    password<br>
    <input type="password" placeholder="Password" />
  </label>
  <br>
  <button>LOG IN</button>
</form>

<style>

  label, button {
    font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
    font-variant-caps: small-caps;
    font-weight: 500;
    opacity: 0.4;
    font-size: medium;
    letter-spacing: 0.05em;
    width: 100%;
  }
  
  input {
    width: 100%;
    height: 3rem;
    font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;
    font-weight: initial;
    font-variant-caps: initial;
    border: none;
    border-bottom: 1.5px solid #ccc;
  }

  input:focus {
    outline: none;
    background: rgb(206, 206, 206);
    border-radius: 2px;
  }

  form {
    height: 100%;
    width: 100%;
    padding: 20%;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    gap: 1rem;
  }

  button {
    width: 100%;
    padding: 15px;
    background: #d4d4d4;
    color: rgb(88, 88, 88);
    border: none;
    border-radius: 0;
  }
</style>
