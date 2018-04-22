open Aliases;

module GetDraft = [%graphql
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

module GetDraftQuery = ReasonApollo.CreateQuery(GetDraft);

let component = ReasonReact.statelessComponent("DraftsPage");

let make = _children => {
  ...component,
  render: _self => {
    let getDraftQuery = GetDraft.make();
    <GetDraftQuery variables=getDraftQuery##variables>
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
                   |> Array.mapi((index, post) =>
                        <PostItem
                          key=(index |> string_of_int)
                          id=post##id
                          title=post##title
                          isDraft=post##isPublished
                          post
                        />
                      )
                   |> ReasonReact.arrayToElement
                 }
               )
             </div>
         )
    </GetDraftQuery>;
  },
};