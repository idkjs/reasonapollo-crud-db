/* module Styles = {
     let loading = ["flex w-100 h-100 items-center justify-center pt7"];
     let title = ["f3 black-80 fw4 lh-solid"];
     let text = ["black-80 fw"];
   };

   let ste = ReasonReact.stringToElement;

   let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b); */
/* type post = {
     id: string,
     isPublished: Js.boolean,
     text: string,
     title: string,
   }; */
let component = ReasonReact.statelessComponent("PostItem");

let make = (~post, _children) => {
  ...component,
  render: _self => {
    let title = ! post##isPublished ? post##title ++ "Draft" : post##title;
    <div>
      <Link className="no-underline ma1" href=("/detailpage/" ++ post##id)>
        <h2 className="f3 black-80 fw4 lh-solid"> (title |> Aliases.ste) </h2>
        /* (post##title |> Aliases.ste) */
        <p className="black-80 fw3"> (post##text |> Aliases.ste) </p>
      </Link>
    </div>;
  },
};