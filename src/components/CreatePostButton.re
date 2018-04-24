/* open Utils; */
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
             <input
               className="pa3 bg-black-10"
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
               )
               value="Create"
               _type="submit"
             />
         )
    </CreatePostMutation>;
  },
};
/*

 <input
                   className={`pa3 bg-black-10 bn ${this.state.text &&
                     this.state.title &&
                     'dim pointer'}`}
                   disabled={!this.state.text || !this.state.title}
                   type="submit"
                   value="Create"


 */
