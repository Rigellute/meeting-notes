/* State declaration */
type state = {
  title: string,
  url: string,
};

/* Action declaration */
type action =
  | Title(string)
  | Url(string);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {title: "", url: ""},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Title(title) => ReasonReact.Update({...state, title})
    | Url(url) => ReasonReact.Update({...state, url})
    },
  render: self =>
    <div>
      <section className="hero is-primary">
        <div className="hero-body">
          <div className="container">
            <h1 className="title">
              {ReasonReact.string("Meeting Minutes")}
            </h1>
            <h2 className="subtitle">
              {ReasonReact.string("Generate markdown")}
            </h2>
          </div>
        </div>
      </section>
      <div className="container is-fluid">
        <div className="columns">
          <div className="column">
            <label className="label"> {ReasonReact.string("Title")} </label>
            <input
              type_="text"
              className="input"
              placeholder="Title"
              value={self.state.title}
              onChange={
                event =>
                  self.send(Title(ReactEvent.Form.target(event)##value))
              }
            />
          </div>
          <div className="column">
            <label className="label"> {ReasonReact.string("URL")} </label>
            <input
              type_="text"
              className="input"
              placeholder="URL"
              value={self.state.url}
              onChange={
                event =>
                  self.send(Url(ReactEvent.Form.target(event)##value))
              }
            />
          </div>
        </div>
        <code>
          {
            ReasonReact.string(
              "["
              ++ self.state.title
              ++ "]"
              ++ "("
              ++ StringHelpers.anchor(self.state.title)
              ++ ")"
              ++ " "
              ++ "["
              ++ StringHelpers.urlToIssueNumber(self.state.url)
              ++ "]"
              ++ "("
              ++ self.state.url
              ++ ")",
            )
          }
        </code>
      </div>
    </div>,
};
