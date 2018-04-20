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