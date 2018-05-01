type route =
  | FeedPage
  | DetailPage(string)
  | DraftsPage
  | NotFound
  | CreatePage;

type state = {route};

type action =
  | ChangeRoute(route);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeRoute(route) => ReasonReact.Update({route: route})
  };

let routeFromUrl = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => FeedPage
  | ["/"] => FeedPage
  | ["post", id] => DetailPage(id)
  | ["drafts"] => DraftsPage
  | ["create"] => CreatePage
  | _ => NotFound
  };

let component = ReasonReact.reducerComponent("App");

let ste = ReasonReact.string;

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
    <div className="fl w-100 pl4 pr4">
      <Nav />
      (
        switch (self.state.route) {
        | FeedPage => <FeedPage />
        | DetailPage(id) => <DetailPage id />
        | DraftsPage => <DraftsPage />
        | NotFound => <NotFound />
        | CreatePage => <CreatePage />
        }
      )
    </div>,
};
