module Styles = {
  let loading = ["flex w-100 h-100 items-center justify-center pt7"];
};

let ste = ReasonReact.stringToElement;

let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b);

let component = ReasonReact.statelessComponent("DraftsPage");

let make = _children => {
  ...component,
  render: _self =>
    <div className=(makeCls(Styles.loading))>
      <div> ("Draftspage ..." |> ste) </div>
    </div>,
};