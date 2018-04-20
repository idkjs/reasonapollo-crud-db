let ste = ReasonReact.stringToElement;

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

let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b);

module Loading = {
  /* open Utils.React; */
  /* let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b); */
  module Styles = {
    let loading = ["flex w-100 h-100 items-center justify-center pt7"];
    let error = ["flex w-100 h-100 items-center justify-center pt7"];
    let link = ["link", "dim", "dark-gray"];
    let linkList = ["fr"];
  };
  /* <div className="flex w-100 h-100 items-center justify-center pt7">
       <div>Loading ...</div>
     </div> */
  let component = ReasonReact.statelessComponent("Loading");
  let make = _children => {
    ...component,
    render: _self =>
      <div className=(makeCls(Styles.loading))>
        <div> ("Loading ..." |> ste) </div>
      </div>,
  };
};

module Error = {
  /* open Utils.React; */
  /* let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b); */
  module Styles = {
    let error = ["flex w-100 h-100 items-center justify-center pt7"];
  };
  /* <div className="flex w-100 h-100 items-center justify-center pt7">
       <div>Loading ...</div>
     </div> */
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
                        <div key=(index |> string_of_int)>
                          (post##title |> ste)
                        </div>
                      )
                   |> ReasonReact.arrayToElement
                 }
               )
             </div>
         )
    </GetFeedQuery>;
  },
};