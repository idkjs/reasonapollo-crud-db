/* type state = {
     title: string,
     text: string,
   };

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

   let valueFromEvent = event : string => (
                                            event
                                            |> ReactEventRe.Form.target
                                            |> ReactDOMRe.domElementToObj
                                          )##value;

   let component = ReasonReact.reducerComponent("CreateDraft");

   module CreateDraftMutation = ReasonApollo.CreateMutation(CreateDraft);

   let make = _children => {
     ...component,
     initialState: () => {title: "", text: ""},
     render: _self => {
       let createDraftMutation =(state) =>
         CreateDraft.make(...state, ());
       <CreateDraftMutation>
         ...(
              (mutation, _) =>
                <div className="pa4 flex justify-center bg-white">
                  <form onClick=(
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
                  <input autoFocus=Js.true_
         className="w-100 pa2 mv2 br2 b--black-20 bw1"
         placeholder="Add a title"
         value=text
         _type="text"
         onChange=(update((event, {state: text}) => ReasonReact.Update(valueFromEvent(event))))
         onKeyDown=(
           update(
             (event, _) =>
               if (ReactEventRe.Keyboard.key(event) == "Enter") {
                 addTodo(text);
                 ReasonReact.Update("")
               } else {
                 ReasonReact.NoUpdate
               }
           )
         )
   />
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
                  </form>
                </div>
            )
       </CreateDraftMutation>;
     },
   }; */