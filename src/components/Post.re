module Styles = {
  let loading = ["flex w-100 h-100 items-center justify-center pt7"];
  let title = ["f3 black-80 fw4 lh-solid"];
  let text = ["black-80 fw"];
};

let ste = ReasonReact.stringToElement;

let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b);

let component = ReasonReact.statelessComponent("Post");

let make = (~title, ~post, ~isDraft, ~id, _children) => {
  ...component,
  render: _self =>

    <div className=(makeCls(Styles.loading))>
      <h1> ("Some Post ..." |> ste) </h1>
      <Router.Link to={`/post/${this.props.post.id}`}>
      <a (makeCls(Styles.loading))>
        <h2 className=(makeCls(Styles.title))>(title|> ste)</h2>
        <p className=(makeCls(Styles.text))>(text |> ste)</p>
      </a>
        </Router.Link>
    </div>,
};