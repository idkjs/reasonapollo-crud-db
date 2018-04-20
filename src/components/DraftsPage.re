let component = ReasonReact.statelessComponent("DraftPage");

let make = (~title: string="Draft Page", _children) => {
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