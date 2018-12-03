let component = React.statelessComponent(__MODULE__);

let parseInput = input => input |> Js.String.split("\n");

let analyzeId = id => {
  let members = id |> Js.String.split("");
  let counts =
    members->Belt.Array.reduce(Belt.Map.String.empty, (prev, v) =>
      prev->Belt.Map.String.set(
        v,
        prev->Belt.Map.String.getWithDefault(v, 0) + 1,
      )
    );
  counts->Belt.Map.String.reduce((0, 0), (prev, _, num) =>
    switch (num) {
    | 2 => (prev->fst + 1, prev->snd)
    | 3 => (prev->fst, prev->snd + 1)
    | _ => prev
    }
  );
};

let day2 = input => {
  let ids = input->parseInput;
  let result =
    ids
    ->Belt.Array.map(v => v->analyzeId)
    ->Belt.Array.reduce((0, 0), (prev, v) =>
        switch (v) {
        | (two, three) when two > 0 && three > 0 => (
            prev->fst + 1,
            prev->snd + 1,
          )
        | (two, _) when two > 0 => (prev->fst + 1, prev->snd)
        | (_, three) when three > 0 => (prev->fst, prev->snd + 1)
        | _ => prev
        }
      );
  result->fst * result->snd;
};

let day2P2 = input => {
  let ids = input->parseInput;
  let result =
    ids->Belt.Array.reduce(
      None,
      (prev, id) => {
        let idSplit = id |> Js.String.split("");
        switch (
          ids->Belt.Array.reduce(
            None,
            (prev, innerId) => {
              let innerIdSplit = innerId |> Js.String.split("");
              let differences =
                idSplit->Belt.Array.reduceWithIndex(0, (prev, char, i) =>
                  char === innerIdSplit->Belt.Array.getUnsafe(i) ?
                    prev : prev + 1
                );
              switch (differences) {
              | 1 =>
                Some(
                  idSplit->Belt.Array.reduceWithIndex("", (prev, char, i) =>
                    char === innerIdSplit->Belt.Array.getUnsafe(i) ?
                      prev ++ char : prev
                  ),
                )
              | _ => prev
              };
            },
          )
        ) {
        | Some(innerId) => Some(innerId)
        | None => prev
        };
      },
    );
  result->Belt.Option.getWithDefault("");
};

let make = _ => {
  ...component,
  render: _ =>
    <>
      <h3> "Day2"->React.string </h3>
      <br />
      <Input day=2>
        ...{
             value =>
               <div>
                 {value->day2->string_of_int->React.string}
                 <br />
                 {value->day2P2->React.string}
               </div>
           }
      </Input>
    </>,
};