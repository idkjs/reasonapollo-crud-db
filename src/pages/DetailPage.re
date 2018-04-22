open Aliases;

module GetPost = [%graphql
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

module GetPostQuery = ReasonApollo.CreateQuery(GetPost);

let component = ReasonReact.statelessComponent("DetailPage");

let make = (~id, _children) => {
  ...component,
  render: _self => {
    let getPostQuery = GetPost.make(~id, ());
    <GetPostQuery variables=getPostQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => "No Data" |> ste
             | Error(e) =>
               Js.log(e);
               <Error />;
             | Loading => <Loading />
             | Data(response) =>
               switch (response##post) {
               | None => "No Person Data" |> ste
               | Some(post) =>
                 <div>
                   <h1 className="f3 black-80 fw4 lh-solid">
                     (post##title |> ste)
                   </h1>
                   <p className="black-80 fw3"> (post##text |> ste) </p>
                 </div>
               }
             }
         )
    </GetPostQuery>;
  },
};