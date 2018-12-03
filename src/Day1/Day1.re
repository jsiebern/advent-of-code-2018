let component = React.statelessComponent(__MODULE__);

let parseInput = input =>
  (input |> Js.String.split("\n"))
  ->Belt.Array.map(v => {
      let operator = v |> Js.String.charAt(0);
      let v = v |> Js.String.substringToEnd(~from=1) |> int_of_string;
      operator === "-" ? v * (-1) : v;
    });

let day1 = (~frequencyStart=0, input: string) =>
  input->parseInput->Belt.Array.reduce(frequencyStart, (prev, v) => prev + v);

let day1P2 = (~frequencyStart=0, input: string) => {
  let frequencies = ref(Belt.Set.Int.empty);
  let values = input->parseInput;
  let currentFrequency = ref(frequencyStart);
  let i = ref(-1);
  let found = ref(false);

  while (! found^) {
    i :=
      (
        switch (values->Belt.Array.get(i^)) {
        | None => 0
        | Some(_) => i^
        }
      );
    currentFrequency := currentFrequency^ + values->Belt.Array.getUnsafe(i^);

    if ((frequencies^)->Belt.Set.Int.has(currentFrequency^)) {
      found := true;
    } else {
      frequencies := (frequencies^)->Belt.Set.Int.add(currentFrequency^);
    };

    i := i^ + 1;

    if (i^ > 5000) {
      found := true;
    };
  };

  currentFrequency^;
};

let make = _ => {
  ...component,
  render: _ =>
    <>
      <h3> "Day1"->React.string </h3>
      <br />
      <Input day=1>
        ...{
             value =>
               <div>
                 {day1(value)->string_of_int->React.string}
                 <br />
                 {day1P2(value)->string_of_int->React.string}
               </div>
           }
      </Input>
    </>,
};