/* module Config = {
     /** Declare routes. */
     type route =
       | FeedPage
       | DetailPage(int)
       | DraftsPage
       | RouteTestPage
       | NotFound
       | CreatePage;
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
     /** Route -> URL. */
     let routeToUrl = (route: route) =>
       switch (route) {
       | FeedPage => "/feedpage"
       | DetailPage(id) => "/detailpage" ++ id
       | DraftsPage => "/draftspage"
       | CreatePage => "/createpage"
       | RouteTestPage => "/RouteTestPage"
       | NotFound => "/NotFound"
       };
   };

   /* pass config to ReRoute and call it Router.Container wrapper in root path */
   include ReRoute.CreateRouter(Config); */