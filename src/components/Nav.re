open Utils;

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

let component = ReasonReact.statelessComponent("Nav");

let make = _children => {
  ...component,
  render: _self =>
    <nav className="pa3 pa4-ns">
      <Link href="/" className=(makeCls(Styles.feedRoute))>
        ("Feed" |> ste)
      </Link>
      <Link href="drafts" className=(makeCls(Styles.draftsRoute))>
        ("Drafts" |> ste)
      </Link>
      <Link href="create" className=(makeCls(Styles.createRoute))>
        ("+ Create Draft" |> ste)
      </Link>
    </nav>,
};
/* type link = {name: string};

   let links = [
     {name: "Home"},
     {name: "RandomPage"},
     {name: "GqlReducer"},
     {name: "MutationPage"},
     {name: "QueryPage"},
   ];

   /* let tolc = (name: Link.t => string) => "/" ++ name |> String.lowercase; */
   let component = ReasonReact.statelessComponent("Nav");

   let make = _children => {
     ...component,
     render: _self =>
       <nav>
         <ul className="list">
           (
             List.map(
               link => {
                 let href = "/" ++ link.name |> String.lowercase;
                 Js.log(href);
                 <li className="listItem">
                   <Link href key=link.name> (link.name |> Utils.s) </Link>
                 </li>;
               },
               links,
             )
             |> Array.of_list
             |> ReasonReact.arrayToElement
           )
         </ul>
       </nav>,
   }; */
