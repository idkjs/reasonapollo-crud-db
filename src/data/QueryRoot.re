open PostT;

/* We need a way to parse the root of the query,
   which for our example we’ll assume looks like this: */
type t = {
  posts: option(Js.null(list(PostT.t))),
  post: option(Js.null(PostT.t)),
};

let decode = json =>
  Json.Decode.{
    posts: json |> optionalNullableField("posts", list(PostT.decode)),
    post: json |> optionalNullableField("post", PostT.decode),
  };