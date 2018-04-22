open Aliases;

module GetFeed = [%graphql
  {|
       query getFeed {
        drafts {
          id
          text
          title
          isPublished
        }
       }
   |}
];

module GetFeedQuery = ReasonApollo.CreateQuery(GetFeed);

let component = ReasonReact.statelessComponent("DraftsPage");

let make = _children => {
  ...component,
  render: _self => {
    let getFeedQuery = GetFeed.make();
    <GetFeedQuery variables=getFeedQuery##variables>
      ...(
           ({result}) =>
             <div>
               <h1> ("Drafts: " |> ste) </h1>
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
                        <PostItem
                          key=(index |> string_of_int)
                          id=draft##id
                          title=draft##title
                          isDraft=draft##isPublished
                          draft
                        />
                      )
                   |> ReasonReact.arrayToElement
                 }
               )
             </div>
         )
    </GetFeedQuery>;
  },
};