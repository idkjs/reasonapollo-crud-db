type t = {
  id: option(string),
  title: option(string),
  text: option(string),
  isPublished: option(bool),
};

/*
   type Post {
   id: ID! @unique
   isPublished: Boolean!
   title: String!
   text: String!
 }
   */
/*
 We’re differentiating between a field being “optional” - that
 is, it may or may not be fetched, which is true of all
 fields - and “nullable” - that the field may or may not be null.
 Type safety FTW!
 */
/* let decode = json =>
   Json.Decode.{
     id: optional(field("id", string)),
     title: optional(field("name", string)),
     rating: optional(field("rating", nullable(string))),
     runTime: optional(field("runTime", nullable(int))),
   }; */
/* bs-json’s optional wrapper tells the decoder to not worry
   if that field is not a part of the JSON, so it accommodates
   our use case where a query response won’t include certain
   fields quite nicely. And nullable handles the fields we’ve
   defined as… nullable. One thing that’s a little annoying is
   all the nested function calls needed, but not to worry!
   Here are some helpers that’ll come in handy:
      */
let optionalField = (fieldName, decoder) =>
  Json.Decode.(optional(field(fieldName, decoder)));

let optionalNullableField = (fieldName, decoder) =>
  Json.Decode.(optional(field(fieldName, nullable(decoder))));

/* Now we can re-write our decoder like so: */
let decode = json =>
  Json.Decode.{
    id: json |> optionalField("id", string),
    title: json |> optionalField("title", string),
    isPublished: json |> optionalField("isPublished", bool),
    text: json |> optionalField("text", string),
  };