let component = ReasonReact.statelessComponent("PostItem");

/* let make = (~title, ~isDraft: Js.boolean, ~post, _children) => { */
let make = (~title, ~isDraft, ~post, ~id, _children) => {
  ...component,
  render: _self => {
    let title =
      isDraft == Js.true_ ?
        title |> Aliases.ste : title ++ " (Draft)" |> Aliases.ste;
    Js.log(title);
    <div>
      <Link className="no-underline ma1" href=("/post/" ++ id)>
        <h2 className="f3 black-80 fw4 lh-solid"> title </h2>
        <p className="black-80 fw3"> (post##text |> Aliases.ste) </p>
      </Link>
    </div>;
  },
};