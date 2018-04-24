open Utils;

module DeletePost = [%graphql
  {|
    mutation DeletePost ($id: ID!){
      deletePost(id:$id){
        id
      }
    }
   |}
];

module DeletePostMutation = ReasonApollo.CreateMutation(DeletePost);

let component = ReasonReact.statelessComponent("DeleteButton");

let make = (~id, _children) => {
  ...component,
  render: _self => {
    let deletePostMutation = DeletePost.make(~id, ());
    <DeletePostMutation>
      ...(
           (mutation, _) =>
             <a
               className="f6 dim br1 ba ph3 pv2 mb2 dib black pointer"
               onClick=(
                 (_) => {
                   mutation(
                     ~variables=deletePostMutation##variables,
                     ~refetchQueries=[|"getDraftsQuery"|],
                     (),
                   )
                   |> ignore;
                   ReasonReact.Router.push("/");
                 }
               )>
               ("Delete" |> ste)
             </a>
         )
    </DeletePostMutation>;
  },
};
