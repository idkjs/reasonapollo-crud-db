open Utils;

type action =
  | ChangeTitle(string)
  | ChangeText(string);

type state = {
  title: string,
  text: string,
};

let handleClick = (href, event) =>
  if (! ReactEventRe.Mouse.defaultPrevented(event)) {
    ReactEventRe.Mouse.preventDefault(event);
    ReasonReact.Router.push(href);
  };

let reducer = (action, state) =>
  switch (action) {
  | ChangeTitle(title) => ReasonReact.Update({...state, title})
  | ChangeText(text) => ReasonReact.Update({...state, text})
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
          autoFocus=true
          className="w-100 pa2 mv2 br2 b--black-20 bw1"
          placeholder="Title"
          _type="text"
          value=self.state.title
          onChange=(onTitleInputChange(self))
          required=true
        />
        <textarea
          className="db w-100 ba bw1 b--black-20 pa2 br2 mb2"
          cols=50
          rows=8
          value=self.state.text
          onChange=(onTextInputChange(self))
          placeholder="Content"
          _type="text"
          required=true
        />
        <CreatePostButton title=self.state.title text=self.state.text />
        <a className="f6 pointer" onClick=(event => handleClick("/", event))>
          (" or cancel" |> ste)
        </a>
      </form>
    </div>,
};
