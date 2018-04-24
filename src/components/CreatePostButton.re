open Aliases;

module CreatePost = [%graphql
  {|
  mutation CreatePostMutation ($text: String!, $title: String!) {
    createDraft(text: $text, title: $title) {
      id
      title
      text
    }
  }
|}
];

module CreatePostMutation = ReasonApollo.CreateMutation(CreatePost);

let component = ReasonReact.statelessComponent("CreatePostButton");

let make = (~text, ~title, _children) => {
  ...component,
  render: _self => {
    let createPostMutation = CreatePost.make(~title, ~text, ());
    <CreatePostMutation>
      ...(
           (mutation, _) =>
             <a
               className="f6 dim br1 ba ph3 pv2 mb2 dib black pointer"
               onClick=(
                 (_) => {
                   mutation(
                     ~variables=createPostMutation##variables,
                     ~refetchQueries=[|"getDraftsQuery"|],
                     (),
                   )
                   |> ignore;
                   ReasonReact.Router.push("/drafts");
                   Js.log("SEND");
                 }
               )>
               ("Create" |> ste)
             </a>
         )
    </CreatePostMutation>;
  },
};
