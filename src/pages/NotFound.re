open Utils;

let loading = ["flex w-100 h-100 items-center justify-center pt7"];

let component = ReasonReact.statelessComponent("NotFound");

let make = _children => {
  ...component,
  render: _self =>
    <div className=(makeCls(loading))>
      <div> ("Page Not Found ..." |> ste) </div>
    </div>,
};
