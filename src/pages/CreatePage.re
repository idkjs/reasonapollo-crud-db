/* type state = {
     title: string,
     text: string,
   }; */
let ste = Aliases.ste;

module CreateDraft = [%graphql
  {|
    mutation CreateDraftMutation($title: String!, $text: String!) {
      createDraft(title: $title, text: $text) {
        id
        title
        text
      }
    }
|}
];

let component = ReasonReact.statelessComponent("CreateDraft");

module CreateDraftMutation = ReasonApollo.CreateMutation(CreateDraft);

let make = _children => {
  ...component,
  render: _self => {
    let createDraftMutation =
      CreateDraft.make(~title="Delete this one", ~text="24", ());
    <CreateDraftMutation>
      ...(
           (mutation, _) =>
             <div className="pa4 flex justify-center bg-white">
               <h1> ("Create Draft" |> ste) </h1>
               <button
                 onClick=(
                   (_) => {
                     mutation(
                       ~variables=createDraftMutation##variables,
                       ~refetchQueries=[|"getFeedQuery"|],
                       (),
                     )
                     |> ignore;
                     ReasonReact.Router.push("/drafts");
                     Js.log("SEND");
                   }
                 )>
                 ("Create" |> ste)
               </button>
             </div>
         )
    </CreateDraftMutation>;
  },
};