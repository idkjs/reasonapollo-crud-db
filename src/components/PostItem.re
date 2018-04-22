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
      };

      //     let title = this.props.post.title
   //     if (this.props.isDraft) {
   //       title = `${title} (Draft)`
   //     }
      */
/* type isDraft =
   | IsDraft
   | IsNotDraft; */
let component = ReasonReact.statelessComponent("PostItem");

/* let make = (~title, ~isDraft: Js.boolean, ~post, _children) => { */
let make = (~title, ~isDraft, ~post, ~id, _children) => {
  ...component,
  render: _self => {
    /* let title =
       isDraft == Js.false_ ?
         title |> Aliases.ste : title ++ "Draft" |> Aliases.ste; */
    Js.log(isDraft);
    <div>
      <Link className="no-underline ma1" href=("/post/" ++ id)>
        <h2 className="f3 black-80 fw4 lh-solid"> title </h2>
        /* (post##title |> Aliases.ste) */
        <p className="black-80 fw3"> (post##text |> Aliases.ste) </p>
      </Link>
    </div>;
  },
  /* let title = isDraft == Js.true_ ? title ++ "Draft" : title; */
  /* let title = ! post##isPublished ? post##title ++ "Draft" : post##title; */
};