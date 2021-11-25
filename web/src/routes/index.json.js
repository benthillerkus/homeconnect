import { supabase } from "$lib/_db.js"

/** @type {import('@sveltejs/kit').RequestHandler} */
export async function get({ params }) {
  const res = await supabase.storage.from("images").list("", {
    sortBy: { column: "created_at", order: "desc" }
  })

  console.log(res)

  return {
    status: res.status,
    body: JSON.stringify(res)
  }
}
