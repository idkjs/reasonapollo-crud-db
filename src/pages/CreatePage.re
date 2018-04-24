open Aliases;

type action =
  | ChangeTitle(string)
  | ChangeText(string)
  /* | AddNewPost */
  | CancelNewPost;

type state = {
  title: string,
  text: string,
};

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
    <div className="pa4 flex justify-center bg-white">
    <form>
      <h1> ("Create Draft" |> ste) </h1>
      <input
        autoFocus=Js.true_
        className="w-100 pa2 mv2 br2 b--black-20 bw1"
        placeholder="Title"
        _type="text"
        value=self.state.title
        onChange=(onTitleInputChange(self))
        required=Js.true_
      />
      <textarea
        className="db w-100 ba bw1 b--black-20 pa2 br2 mb2"
        cols=50
        value=self.state.text
        onChange=(onTextInputChange(self))
        placeholder="Title"
        _type="text"
        required=Js.true_
      />
      <CreatePostButton title=self.state.title text=self.state.text />
      <a className="f6 pointer" onClick=(_event => self.send(CancelNewPost))>
                  (" or cancel" |> ste)
                </a>
    </form>
      </div>,
};
