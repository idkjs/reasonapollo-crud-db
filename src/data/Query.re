/* type response =
     | Loading
     | Error(string)
     | Loaded(QueryRoot.t);

   let component = ReasonReact.statelessComponent("Query");

   open ReactApollo;

   /* let data = ReactApollo.apolloData.t; */
   let make = (~query, children) => {
     ...component,
     render: _self =>
       <ReactApollo.Query query>
         ...(
              ({data, error, loading}: response) => {
                let r =
                  switch (loading, error, data) {
                  | (false, None, Some(data)) =>
                    Loading(data |> QueryRoot.decode)
                  };
                children(r);
              }
            )
       </ReactApollo.Query>,
   }; */