open Aliases;

module GetFeed = [%graphql
  {|
       query getFeed {
        feed{
          id
          isPublished
          title
          text
        }
       }
   |}
];

module GetFeedQuery = ReasonApollo.CreateQuery(GetFeed);

module Error = {
  module Styles = {
    let error = ["flex w-100 h-100 items-center justify-center pt7"];
  };
  let component = ReasonReact.statelessComponent("Error");
  let make = _children => {
    ...component,
    render: _self =>
      <div className=(makeCls(Styles.error))>
        <div> ("An unexpected error occured." |> ste) </div>
      </div>,
  };
};

let component = ReasonReact.statelessComponent("FeedPage");

let make = _children => {
  ...component,
  render: _self => {
    let getFeedQuery = GetFeed.make();
    <GetFeedQuery variables=getFeedQuery##variables>
      ...(
           ({result}) =>
             <div>
               <h1> ("Feed: " |> ste) </h1>
               (
                 switch (result) {
                 | NoData => "No Data" |> ste
                 | Error(e) =>
                   Js.log(e);
                   <Error />;
                 | Loading => <Loading />
                 | Data(response) =>
                   response##feed
                   |> Array.mapi((index, post) =>
                        <PostItem
                          key=(index |> string_of_int)
                          id=post##id
                          title=post##title
                          post
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