Emotion.(
  global(
    "*",
    [
      margin(0->px),
      padding(0->px),
      boxSizing(`borderBox),
      fontFamily(
        "-apple-system, BlinkMacSystemFont, \"Segoe UI\", Roboto, \"Helvetica Neue\", Arial, sans-serif, \"Apple Color Emoji\", \"Segoe UI Emoji\", \"Segoe UI Symbol\"",
      ),
    ],
  )
);

module Styles = {
  open Emotion;

  let container =
    css([width(100.->pct), maxWidth(900->px), margin2(30->px, `auto)]);
};

module Layout = {
  let component = React.statelessComponent(__MODULE__);
  let make = _ => {
    ...component,
    render: _ =>
      <div className=Styles.container>
        <Day1 />
        <br />
        <hr />
        <br />
        <Day2 />
      </div>,
  };
};

ReactDOMRe.renderToElementWithId(<Layout />, "app");