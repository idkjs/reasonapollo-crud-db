/*
 const DELETE_MUTATION = gql`
   mutation DeleteMutatoin($id: ID!) {
     deletePost(id: $id) {
       id
     }
   }

 */
module DeletePost = [%graphql
  {|
    query PostQuery($id: ID!) {
      post(id: $id) {
        id
        title
        text
        isPublished
      }
    }
   |}
];

let component = ReasonReact.statelessComponent("DeleteButton");

let deletePost = (_event, _self) => Js.log("clicked!");

let make = _children => {
  ...component,
  render: self =>
    <div>
      <div> ("Delete Button ..." |> Aliases.ste) </div>
      <a
        className="f6 dim br1 ba ph3 pv2 mb2 dib black pointer"
        onClick=(self.handle(deletePost))>
        ("Delete" |> Aliases.ste)
      </a>
    </div>,
};