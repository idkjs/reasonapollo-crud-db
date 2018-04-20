module Config = {
  /** Declare routes. */
  type route =
    | FeedPage
    | DetailPage
    | DraftsPage
    | CreatePage;
  /** URL -> Route. */
  let routeFromUrl = (url: ReasonReact.Router.url) =>
    switch (url.path) {
    | [] => FeedPage
    | ["feedpage"] => FeedPage
    | ["detailpage"] => DetailPage
    | ["draftspage"] => DraftsPage
    | ["createpage"] => CreatePage
    | _ => FeedPage
    };
  /** Route -> URL. */
  let routeToUrl = (route: route) =>
    switch (route) {
    | FeedPage => "/feedpage"
    | DetailPage => "/detailPage"
    | DraftsPage => "/draftsPage"
    | CreatePage => "/createPage"
    };
};

/* pass config to ReRoute and call it Router.Container wrapper in root path */
include ReRoute.CreateRouter(Config);