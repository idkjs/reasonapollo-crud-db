open Aliases;

/* const POST_QUERY = gql`
     query PostQuery($id: ID!) {
       post(id: $id) {
         id
         title
         text
         isPublished
       }
     }
   ` */
module GetPost = [%graphql
  {|
    query PostQuery($id: ID!) {
      post(id: $id) {
        id
        title
        text
        isPublished
      }
    }
   |}
];

/*
 <h1 className="f3 black-80 fw4 lh-solid">{data.post.title}</h1>
               <p className="black-80 fw3">{data.post.text}</p> */
module GetPostQuery = ReasonApollo.CreateQuery(GetPost);

let component = ReasonReact.statelessComponent("DetailPage");

let make = (~id, _children) => {
  ...component,
  render: _self => {
    let getPostQuery = GetPost.make(~id, ());
    <GetPostQuery variables=getPostQuery##variables>
      ...(
           ({result}) =>
             switch (result) {
             | NoData => "No Data" |> ste
             | Error(e) =>
               Js.log(e);
               <Error />;
             | Loading => <Loading />
             | Data(response) =>
               switch (response##post) {
               | None => "No Person Data" |> ste
               | Some(post) => <div> (post##title |> ste) </div>
               }
             }
         )
    </GetPostQuery>;
  },
};
/*
 let make = (~id, _children) => {
   ...component,
   render: _self => {
     let getPostQuery = GetPost.make(~id, ());
     <GetPostQuery query=getPostQuery>
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
                    response##post(
                      <div>
                        <h1 className="f3 black-80 fw4 lh-solid">
                          (post##title |> Aliases.ste)
                        </h1>
                        <p className="black-80 fw3">
                          (post##text |> Aliases.ste)
                        </p>
                      </div>,
                    )
                  }
                )
              </div>
          )
     </GetPostQuery>;
   },
 }; */