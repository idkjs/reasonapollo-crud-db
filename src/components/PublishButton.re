open Utils;

module PublishPost = [%graphql
  {|
    mutation PublishMutation($id: ID!) {
      publish(id: $id) {
        id
        isPublished
      }
    }
   |}
];

module PublishPostMutation = ReasonApollo.CreateMutation(PublishPost);

let component = ReasonReact.statelessComponent("DeleteButton");

let make = (~id, _children) => {
  ...component,
  render: _self => {
    let publishPostMutation = PublishPost.make(~id, ());
    <PublishPostMutation>
      ...(
           (mutation, _) =>
             <a
               className="f6 dim br1 ba ph3 pv2 mb2 dib black pointer"
               onClick=(
                 (_) => {
                   mutation(
                     ~variables=publishPostMutation##variables,
                     ~refetchQueries=[|"getFeedQuery"|],
                     (),
                   )
                   |> ignore;
                   ReasonReact.Router.push("/");
                   Js.log("SEND");
                 }
               )>
               ("Publish" |> ste)
             </a>
         )
    </PublishPostMutation>;
  },
};
