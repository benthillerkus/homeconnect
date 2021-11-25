/** @type {import('@sveltejs/kit').Handle} */
export async function handle( { request, resolve } ) {
  if ( request.method === "POST" ) {
    return {
      status: 202
    }
  }

  const response = await resolve( request )

  return {
    ...response
  }
}
