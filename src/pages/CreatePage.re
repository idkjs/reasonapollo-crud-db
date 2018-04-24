open Belt;

type action =
  | ChangeText(string)
  | AddNewPost
  | CancelNewPost
  | DeleteAll;

type state = {
  posts: list(PostItem.post),
  currentText: string,
};

let savePosts = posts => Storage.savePosts(posts);

let reducer = (action, state: state) =>
  switch (action) {
  | ChangeText(str) => ReasonReact.Update({...state, currentText: str})
  | AddNewPost =>
    switch (String.trim(state.currentText)) {
    | "" => ReasonReact.NoUpdate
    | title =>
      ReasonReact.UpdateWithSideEffects(
        {
          let newPost: PostItem.post = {
            /* id: Js.Date.(make() |> toISOString), */
            title,
            text,
          };
          let posts = [newPost] @ state.posts;
          {posts, currentText: ""};
        },
        (self => savePosts(self.state.posts)),
      )
    }
  | CancelNewPost => ReasonReact.Update({...state, currentText: ""})
  | DeleteAll =>
    ReasonReact.UpdateWithSideEffects(
      {...state, posts: []},
      (self => savePosts(self.state.posts)),
    )
  };

let initialState = () => {currentText: "", posts: Storage.loadPosts()};

let onInputChange = ({ReasonReact.send}, e) =>
  send(
    ChangeText(
      ReactDOMRe.domElementToObj(ReactEventRe.Form.target(e))##value,
    ),
  );

let onInputKeyDown = ({ReasonReact.send}, e) => {
  let key = ReactEventRe.Keyboard.key(e);
  switch (key) {
  | "Enter" =>
    e |> ReactEventRe.Keyboard.preventDefault;
    send(AddNewPost);
  | "Escape" =>
    e |> ReactEventRe.Keyboard.preventDefault;
    send(CancelNewPost);
  | _ => ()
  };
};

let onPostToggle = ({ReasonReact.send}, todo: PostItem.post) =>
  send(TogglePost(todo));

let onRemoveAllClick = ({ReasonReact.send}, _e) => send(DeleteAll);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState,
  render: self =>
    <div>
      <input
        value=self.state.currentText
        onChange=(onInputChange(self))
        onKeyDown=(onInputKeyDown(self))
      />
      <PostList
        posts=self.state.posts
        onToggle=(onPostToggle(self))
        onRemoveAll=(onRemoveAllClick(self))
      />
    </div>,
};