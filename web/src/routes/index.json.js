import { supabase } from "$lib/_db.js"

const bucket = "images"

/** @type {import('@sveltejs/kit').RequestHandler} */
export async function get({ params }) {
  const res = await supabase.storage.from(bucket).list("", {
    sortBy: { column: "created_at", order: "desc" }
  })

  res.data?.forEach(image => {
    // image.url = supabase.storage.from("images").getPublicUrl(image.id).publicURL
    image.url = `${import.meta.env.VITE_PUBLIC_SUPABASE_URL}/storage/v1/object/public/${bucket}/${
      image.name
    }`
  })

  return {
    status: res.status,
    body: JSON.stringify(res)
  }
}
