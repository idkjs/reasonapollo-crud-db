open Aliases;

let component = ReasonReact.statelessComponent("Error");

let make = _children => {
  ...component,
  render: _self =>
    <div className="flex w-100 h-100 items-center justify-center pt7">
      <div> ("An unexpected error occured." |> ste) </div>
    </div>,
};