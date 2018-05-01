open Utils;

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
               <div className="fl w-100 pl4 pr4">
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
                        <Post
                          key=(index |> string_of_int)
                          isDraft=post##isPublished
                          post
                        />
                      )
                   |> ReasonReact.array
                 }
               )
             </div>
         )
    </GetFeedQuery>;
  },
};
