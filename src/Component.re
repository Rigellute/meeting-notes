/* State declaration */
type state = {title: string};

/* Action declaration */
type action =
  | Title(string);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {title: ""},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Title(title) => ReasonReact.Update({...state, title})
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
        <label className="label"> {ReasonReact.string("Title")} </label>
        <input
          type_="text"
          className="input"
          placeholder="Title"
          value={self.state.title}
          onChange={
            event => self.send(Title(ReactEvent.Form.target(event)##value))
          }
        />
        <code>
          {
            ReasonReact.string(
              "["
              ++ self.state.title
              ++ "]"
              ++ "("
              ++ GenerateTitleLink.anchor(self.state.title)
              ++ ")",
            )
          }
        </code>
      </div>
    </div>,
};
