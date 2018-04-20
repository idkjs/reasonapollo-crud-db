let component = ReasonReact.statelessComponent("Detail Page");

let make = (~title: string="Detail Page", _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement(title)) </h2>
      </div>
      <p className="App-intro">
        (ReasonReact.stringToElement("To get started, edit"))
        <code> (ReasonReact.stringToElement(" src/app.re ")) </code>
        (ReasonReact.stringToElement("and save to reload."))
      </p>
    </div>,
};