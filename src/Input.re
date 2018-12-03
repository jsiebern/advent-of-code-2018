module Styles = {
  open Emotion;

  let container =
    css([
      width(100.->pct),
      select("& textarea", [width(100.->pct), marginBottom(30->px)]),
    ]);
};

let intToDay = day => "day" ++ day->string_of_int;
let fromStorage = day =>
  (Dom.Storage.localStorage |> Dom.Storage.getItem(day->intToDay))
  ->Belt.Option.getWithDefault("");
let toStorage = (day, value) =>
  Dom.Storage.localStorage |> Dom.Storage.setItem(day->intToDay, value);

let component = React.reducerComponent(__MODULE__);

let make = (~day: int, children) => {
  ...component,
  initialState: () => fromStorage(day),
  reducer: (action: string, _state) =>
    React.UpdateWithSideEffects(action, _ => toStorage(day, action)),
  render: ({state, send}) =>
    <div className=Styles.container>
      <textarea
        value=state
        onChange={event => send(event->ReactEvent.Form.target##value)}
        placeholder="Input"
        rows=5
      />
      {children(state)}
    </div>,
};