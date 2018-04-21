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

type route =
  | FeedPage
  | DetailPage(int)
  | DraftsPage
  | RouteTestPage
  | NotFound
  | CreatePage;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

/** URL -> Route. */
let routeFromUrl = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => FeedPage
  | ["feedpage"] => FeedPage
  | ["detailpage", id] => DetailPage(int_of_string(id))
  | ["draftspage"] => DraftsPage
  | ["createpage"] => CreatePage
  | ["RouteTestPage"] => RouteTestPage
  | _ => NotFound
  };

let component = ReasonReact.reducerComponent("App");

let ste = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  reducer,
  initialState: () => {route: FeedPage},
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          self.send(ChangeRoute(url |> routeFromUrl))
        ),
      ReasonReact.Router.unwatchUrl,
    ),
  ],
  render: self =>
    <div>
      <Nav />
      (
        switch (self.state.route) {
        | FeedPage => <FeedPage />
        | DetailPage(id) => <DetailPage id />
        | DraftsPage => <DraftsPage />
        | RouteTestPage => <RouteTestPage />
        | NotFound => <NotFound />
        | CreatePage => <CreatePage />
        }
      )
    </div>,
};