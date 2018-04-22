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

let component = ReasonReact.statelessComponent("FeedPage");

let make = _children => {
  ...component,
  render: _self => {
    let getFeedQuery = GetFeed.make();
    <GetFeedQuery variables=getFeedQuery##variables>
      ...(
           ({result}) =>
             <div>
               <div className="flex justify-between items-center">
                 <h1> ("Feed" |> ste) </h1>
               </div>
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
                          isDraft=post##isPublished
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