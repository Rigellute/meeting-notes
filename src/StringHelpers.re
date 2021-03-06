/* TODO: figure out how to do this with normal reason */
let anchor: string => string = [%bs.raw
  {|
    function (title) {
      return '#' + title.trim().toLowerCase().replace(/[^\w\- ]+/g, '').replace(/\s/g, '-').replace(/\-+$/, '');
    }
|}
];

let urlToIssueNumber: string => string = [%bs.raw
  {|
    function (url) {
      return url.replace(/\D/g,'');
    }
  |}
];

let createTitle = (~title: string, ~url: string) => {
  let anchored = anchor(title);
  let issueNumber = urlToIssueNumber(url);

  /* Interpolate the strings */
  {j|
  [$title]($anchored) [$issueNumber]($url)
    |j};
};

let mergeTitles = (topics: list(Topic.topic)) =>
  List.map(
    topic =>
      <p key={string_of_int(Topic.(topic.id))}>
        {
          ReasonReact.string(
            "1."
            ++ createTitle(~title=Topic.(topic.title), ~url=Topic.(topic.url)),
          )
        }
      </p>,
    topics,
  );

let constructDateString = (date: string) => {
  let jsDate = Js.Date.fromString(date ++ "T00:0");
  switch (Js.String.length(date)) {
  | 0 => ""
  | _ => Js.Date.toDateString(jsDate)
  };
};
