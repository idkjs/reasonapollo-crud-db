open Utils;

let component = ReasonReact.statelessComponent("Post");

/* let make = (~title, ~isDraft: Js.boolean, ~post, _children) => { */
let make = (~isDraft, ~post, _children) => {
  ...component,
  render: _self => {
    let title =
      isDraft == Js.true_ ?
        post##title |> ste : post##title ++ " (Draft)" |> ste;
    Js.log(title);
    <Link className="no-underline ma1" href=("/post/" ++ post##id)>
      <h2 className="f3 black-80 fw4 lh-solid"> title </h2>
      <p className="black-80 fw3"> (post##text |> ste) </p>
    </Link>;
  },
};