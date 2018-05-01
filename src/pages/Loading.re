open Utils;

let component = ReasonReact.statelessComponent("Loading");

let make = _children => {
  ...component,
  render: _self =>
    <div className="flex w-100 h-100 items-center justify-center pt7">
      <div> ("Loading ..." |> ste) </div>
    </div>,
};
