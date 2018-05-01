let makeCls = x => Belt.List.reduce(x, "", (a, b) => a ++ " " ++ b);

let ste = ReasonReact.string;