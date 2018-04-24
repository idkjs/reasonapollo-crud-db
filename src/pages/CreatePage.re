type action =
  | ChangeTitle(string)
  | ChangeText(string)
  /* | AddNewPost */
  | CancelNewPost;

type state = {
  title: string,
  text: string,
};

/* reducer: (action, state) =>
       switch action {
       | ChangeName(name) => ReasonReact.Update({...state, name})
       | ChangeFavoriteAnimal(favoriteAnimal) =>
         ReasonReact.Update({...state, favoriteAnimal})
   }, */
let reducer = (action, state) =>
  switch (action) {
  | ChangeTitle(title) => ReasonReact.Update({...state, title})
  | ChangeText(text) => ReasonReact.Update({...state, text})
  | CancelNewPost => ReasonReact.Update({title: "", text: ""})
  };

let initialState = () => {title: "", text: ""};

let onTextInputChange = ({ReasonReact.send}, e) =>
  send(
    ChangeText(
      ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value,
    ),
  );

let onTitleInputChange = ({ReasonReact.send}, e) =>
  send(
    ChangeTitle(
      ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value,
    ),
  );

let component = ReasonReact.reducerComponent("CreatePost");

let make = _children => {
  ...component,
  reducer,
  initialState,
  render: self =>
    <div>
      <input value=self.state.title onChange=(onTitleInputChange(self)) />
      <input value=self.state.text onChange=(onTextInputChange(self)) />
      <CreatePostButton title=self.state.title text=self.state.text />
    </div>,
};
