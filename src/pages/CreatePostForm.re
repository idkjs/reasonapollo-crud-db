module CreatePostForm = {
  type field =
    | Title
    | Text;
  type value = string;
  type state = {
    title: string,
    text: string,
  };
  type message = string;
  let get = (field, state) =>
    switch (field) {
    | Title => state.title
    | Text => state.text
    };
  let update = ((field, value), state) =>
    switch (field, value) {
    | (Title, value) => {...state, title: value}
    | (Text, value) => {...state, text: value}
    };
  let valueEmpty = Formality.emptyString;
  let strategy = Formality.Strategy.OnFirstSuccessOrFirstBlur;
  let debounceInterval = Formality.debounceInterval;
  module Validators =
    Formality.MakeValidators(
      {
        type t = field;
      },
    );
  type validators =
    Validators.t(Formality.validator(field, value, state, message));
  let validators =
    Formality.(
      Validators.empty
      |> Validators.add(
           Title,
           {
             strategy,
             dependents: None,
             validate: (value, _state) =>
               switch (value) {
               | "" => Invalid("Uh oh error")
               | _ => Valid
               },
           },
         )
      |> Validators.add(
           Text,
           {
             strategy,
             dependents: None,
             validate: (value, _state) =>
               switch (value) {
               | "" => Invalid("Uh oh error")
               | _ => Valid
               },
           },
         )
    );
};

module CreatePostFormContainer = Formality.Make(CreatePostForm);

module CreatePost = [%graphql
  {|
  mutation CreatePostMutation ($text: String!, $title: String!) {
    createDraft(text: $text, title: $title) {
      id
      title
      text
    }
  }
|}
];

module CreatePostMutation = ReasonApollo.CreateMutation(CreatePost);

let component = "CreatePostForm" |> ReasonReact.statelessComponent;

let make = (_) => {
  ...component,
  render: (_) =>
    <CreatePostFormContainer
      initialState={title: "", text: ""}
      onSubmit=(
        (state, {notifyOnSuccess, notifyOnFailure, reset}) => {
          let createPostMutation =
            CreatePost.make(~title=state.title, ~text=state.text, ());
          <CreatePostMutation>
            ...(
                 (mutation, _, _) => {
                   mutation(
                     ~variables=createPostMutation##variables,
                     ~refetchQueries=[|"getFeedQuery"|],
                     (),
                   )
                   |> ignore;
                   ReasonReact.Router.push("/");
                   Js.log("SEND");
                 }
               )
          </CreatePostMutation>;
          Js.log2("Called with:", state);
          Js.Global.setTimeout(
            () => {
              form.notifyOnSuccess(None);
              Js.Global.setTimeout(form.reset, 3000) |> ignore;
            },
            500,
          )
          |> ignore;
        }
      )>
      ...(
           form =>
             <form
               className="form"
               onSubmit=(form.submit |> Formality.Dom.preventDefault)>
               <div className="form-messages-area form-messages-area-lg" />
               <div className="form-content">
                 <h2 className="push-lg">
                   ("Signup" |> ReasonReact.stringToElement)
                 </h2>
                 <div className="form-row">
                   <label htmlFor="signup--email" className="label-lg">
                     ("Title" |> ReasonReact.stringToElement)
                   </label>
                   <input
                     id="signup--email"
                     value=form.state.title
                     disabled=form.submitting
                     onChange=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnChange
                         |> form.change(CreatePostForm.Title)
                     )
                     onBlur=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnBlur
                         |> form.blur(CreatePostForm.Title)
                     )
                   />
                   (
                     switch (
                       CreatePostForm.Title |> form.results,
                       CreatePostForm.Title |> form.validating,
                     ) {
                     | (_, true) =>
                       <div className="form-message">
                         ("Checking..." |> ReasonReact.stringToElement)
                       </div>
                     | (Some(Invalid(message)), false) =>
                       <div className=(Cn.make(["form-message", "failure"]))>
                         (message |> ReasonReact.stringToElement)
                       </div>
                     | (Some(Valid), false) =>
                       <div className=(Cn.make(["form-message", "success"]))>
                         ({j|✓|j} |> ReasonReact.stringToElement)
                       </div>
                     | (None, false) => ReasonReact.nullElement
                     }
                   )
                 </div>
                 <div className="form-row form-row-footer">
                   <div className="note push-lg">
                     (
                       "Hint: try `test@taken.title`"
                       |> ReasonReact.stringToElement
                     )
                   </div>
                 </div>
                 <div className="form-row">
                   <label htmlFor="signup--password" className="label-lg">
                     ("Text" |> ReasonReact.stringToElement)
                   </label>
                   <input
                     id="signup--password"
                     value=form.state.text
                     disabled=form.submitting
                     onChange=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnChange
                         |> form.change(CreatePostForm.Text)
                     )
                     onBlur=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnBlur
                         |> form.blur(CreatePostForm.Text)
                     )
                   />
                   (
                     switch (CreatePostForm.Text |> form.results) {
                     | Some(Invalid(message)) =>
                       <div className=(Cn.make(["form-message", "failure"]))>
                         (message |> ReasonReact.stringToElement)
                       </div>
                     | Some(Valid) =>
                       <div className=(Cn.make(["form-message", "success"]))>
                         ({j|✓|j} |> ReasonReact.stringToElement)
                       </div>
                     | None => ReasonReact.nullElement
                     }
                   )
                 </div>
                 <div className="form-row">
                   <label
                     htmlFor="signup--passwordConfirmation"
                     className="label-lg">
                     ("Confirmation" |> ReasonReact.stringToElement)
                   </label>
                   <input
                     id="signup--passwordConfirmation"
                     value=form.state.textConfirmation
                     disabled=form.submitting
                     onChange=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnChange
                         |> form.change(CreatePostForm.TextConfirmation)
                     )
                     onBlur=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnBlur
                         |> form.blur(CreatePostForm.TextConfirmation)
                     )
                   />
                   (
                     switch (CreatePostForm.TextConfirmation |> form.results) {
                     | Some(Invalid(message)) =>
                       <div className=(Cn.make(["form-message", "failure"]))>
                         (message |> ReasonReact.stringToElement)
                       </div>
                     | Some(Valid) =>
                       <div className=(Cn.make(["form-message", "success"]))>
                         ({j|✓|j} |> ReasonReact.stringToElement)
                       </div>
                     | None => ReasonReact.nullElement
                     }
                   )
                 </div>
                 <div className="form-row">
                   <button className="push-lg" disabled=form.submitting>
                     (
                       (form.submitting ? "Submitting..." : "Submit")
                       |> ReasonReact.stringToElement
                     )
                   </button>
                   (
                     switch (form.status) {
                     | Formality.FormStatus.Submitted =>
                       <div className=(Cn.make(["form-status", "success"]))>
                         ({j|✓ Signed Up|j} |> ReasonReact.stringToElement)
                       </div>
                     | _ => ReasonReact.nullElement
                     }
                   )
                 </div>
               </div>
             </form>
         )
    </CreatePostFormContainer>,
};
/* type state = {
     id: string,
     title: string,
     /* text: string, */
   };

   let ste = Aliases.ste;

   type state = {
     editText: string,
     /* editTitle: string, */
     editing: bool,
     editFieldRef: ref(option(Dom.element)),
   };
   /* these are the allowable action on this module so if you want to do
   something, you have to call one of these then define what it does */
   type action =
     | Edit
     | Submit
     | KeyDown(int)
     | Change(string);

   /* let valueFromEvent = event : string => (
                                            event
                                            |> ReactEventRe.Form.target
                                            |> ReactDOMRe.domElementToObj
                                          )##value; */

   /* let component = ReasonReact.statelessComponent("CreateDraft"); */
   let component = ReasonReact.reducerComponent("CreateDraft");

   let setEditFieldRef = (r, {ReasonReact.state}) => state.editFieldRef := Js.Nullable.toOption(r);

   let make = (~post, ~editing, ~onDestroy, ~onSave, ~onEdit, ~onCancel, _children) => {
     let submitHelper = state =>
       switch (String.trim(state.editText)) {
       | "" => ReasonReact.SideEffects((_self => onDestroy()))
       | nonEmptyValue => ReasonReact.UpdateWithSideEffects(
           {...state, editText: nonEmptyValue},
           (_self => onSave(nonEmptyValue)),
         )
       };
     {
     ...component,
     initialState: () => {
       editTitle: post.title,
       /* editText: post.text, */
       editFieldRef: ref(None),
       editing,
     },
     reducer: action =>
       switch action {
       | Edit => ( state => ReasonReact.Update({...state,
           editText: post.title
         }))
       | Submit => submitHelper
       | Change(text) => (
         state => editing ? ReasonReact.Update({...state, editText: text}): ReasonReact.NoUpdate
       )
       | KeyDown(27) => onCancel();
         (state => ReasonReact.Update({...state, editText: post.title}));
         | KeyDown(13) => submitHelper
         | KeyDown(_) => (_state = ReasonReact.NoUpdate)
       },
     willRecieveProps: ({state }) => {...state, editing},
     didUpdate: ({oldSelf, newSelf}) =>
       switch (oldSelf.state.editing, editing, newSelf.state.editFieldRef^) {
       | (false, true, Some(Field)) =>
         let node = ReactDOMRe.domElementToObj(field);
         ignore(node##focus());
         ignore(
           node##setSelectionRange(node##value##length, node##value##length),
         );
       | _ => ()
     },
     render: ({state, handle, send}) => {
       let className = editing ? "editing" : "";

       <div className="pa4 flex justify-center bg-white">
         <form
           name="post" action="/drafts/" className>
           <label htmlFor="name" className=style##label> (s("Title: ")) </label>
           <input
           ref=(handle(setEditFieldRef))
           className="edit"
           value=state.editText
           onBlur=(_event => send(Submit))
           onChange=(
             event =>
               send(
                 Change(
                   ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
                 ),
               )
           )
           onKeyDown=(
             event => send(KeyDown(ReactEventRe.Keyboard.which(event)))
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
       </div>;
     };
   }; */