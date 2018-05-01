open Utils;

module GetDrafts = [%graphql
  {|
    query DraftsQuery {
      drafts {
        id
        text
        title
        isPublished
      }
    }
   |}
];

module GetDraftsQuery = ReasonApollo.CreateQuery(GetDrafts);

let component = ReasonReact.statelessComponent("DraftsPage");

let make = _children => {
  ...component,
  render: _self => {
    let getDraftsQuery = GetDrafts.make();
    <GetDraftsQuery variables=getDraftsQuery##variables>
      ...(
           ({result}) =>
             <div>
               <div className="flex justify-between items-center">
                 <h1> ("Drafts" |> ste) </h1>
               </div>
               (
                 switch (result) {
                 | NoData => "No Data" |> ste
                 | Error(e) =>
                   Js.log(e);
                   <Error />;
                 | Loading => <Loading />
                 | Data(response) =>
                   response##drafts
                   |> Array.mapi((index, draft) =>
                        <Post
                          key=(index |> string_of_int)
                          isDraft=draft##isPublished
                          post=draft
                        />
                      )
                   |> ReasonReact.array
                 }
               )
             </div>
         )
    </GetDraftsQuery>;
  },
};
