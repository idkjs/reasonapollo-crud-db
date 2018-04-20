let component = ReasonReact.statelessComponent("App");

let ste = ReasonReact.stringToElement;

let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b);

module Styles = {
  let nav = ["pa3", "pa4-ns"];
  let feedRoute = ["link", "dim", "black", "b", "f6", "f5-ns", "dib", "mr3"];
  let draftsRoute = ["link", "dim", "f6", "f5-ns", "dib", "mr3", "black"];
  let createRoute = [
    "f6",
    "link",
    "dim",
    "br1",
    "ba",
    "ph3",
    "pv2",
    "fr",
    "mb2",
    "dib",
    "black",
  ];
};

let make = _children => {
  ...component,
  render: _self =>
    <Router.Container>
      ...(
           (~currentRoute) =>
             <div className=(makeCls(Styles.nav))>
               <ul>
                 <Router.Link route=FeedPage>
                   <li className=(makeCls(Styles.feedRoute))>
                     ("Blog" |> ste)
                   </li>
                 </Router.Link>
                 <Router.Link route=FeedPage>
                   <li className=(makeCls(Styles.feedRoute))>
                     ("Feed" |> ste)
                   </li>
                 </Router.Link>
                 <Router.Link route=DraftsPage>
                   <li className=(makeCls(Styles.draftsRoute))>
                     ("Drafts" |> ste)
                   </li>
                 </Router.Link>
                 <Router.Link route=CreatePage>
                   <li className=(makeCls(Styles.createRoute))>
                     ("+ Create Draft" |> ste)
                   </li>
                 </Router.Link>
               </ul>
               /* <h3> (ReasonReact.stringToElement("Menu")) </h3> */
               (
                 switch (currentRoute) {
                 | FeedPage => <FeedPage />
                 | DetailPage => <DetailPage />
                 | DraftsPage => <DraftsPage />
                 | CreatePage => <CreatePage />
                 }
               )
             </div>
         )
    </Router.Container>,
};