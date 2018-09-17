/* State declaration */
type state = {
  date: string,
  topics: list(Topic.topic),
};

/* Action declaration */
type action =
  | Title(int, string)
  | Url(int, string)
  | Date(string)
  | Add;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

let blankTopic = (): Topic.topic => {
  title: "",
  url: "",
  id: Random.int(10000),
};

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {date: "", topics: [blankTopic()]},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Title(id, title) =>
      let topics =
        List.map(
          t => Topic.(t.id) == id ? {...t, Topic.title} : t,
          state.topics,
        );
      ReasonReact.Update({...state, topics});
    | Url(id, url) =>
      let topics =
        List.map(
          t => Topic.(t.id) == id ? {...t, Topic.url} : t,
          state.topics,
        );
      ReasonReact.Update({...state, topics});
    | Date(date) => ReasonReact.Update({...state, date})
    | Add =>
      ReasonReact.Update({
        ...state,
        topics: List.append([blankTopic()], state.topics),
      })
    },
  render: self => {
    let topics =
      List.map(
        topic =>
          <div key={string_of_int(Topic.(topic.id))} className="columns">
            <div className="column">
              <label className="label"> {ReasonReact.string("Title")} </label>
              <input
                type_="text"
                className="input"
                placeholder="Title"
                value=Topic.(topic.title)
                onChange={
                  event =>
                    self.send(
                      Title(
                        Topic.(topic.id),
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                }
              />
            </div>
            <div className="column">
              <label className="label"> {ReasonReact.string("URL")} </label>
              <input
                type_="text"
                className="input"
                placeholder="URL"
                onChange={
                  event =>
                    self.send(
                      Url(
                        Topic.(topic.id),
                        ReactEvent.Form.target(event)##value,
                      ),
                    )
                }
              />
            </div>
          </div>,
        self.state.topics,
      );
    let titles = StringHelpers.mergeTitles(self.state.topics);

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
        <label className="label"> {ReasonReact.string("Date")} </label>
        <input
          className="input"
          type_="date"
          onChange={
            event => self.send(Date(ReactEvent.Form.target(event)##value))
          }
          value={self.state.date}
        />
        {ReasonReact.array(Array.of_list(topics))}
        <p> {ReasonReact.string("# Code Quality Meeting")} </p>
        <br />
        <p>
          {
            ReasonReact.string(
              StringHelpers.constructDateString(self.state.date),
            )
          }
        </p>
        <br />
        <p> {ReasonReact.string("## Agenda")} </p>
        <br />
        <div> {ReasonReact.array(Array.of_list(titles))} </div>
        <button
          onClick={_event => self.send(Add)} className="button is-primary">
          {ReasonReact.string("Add new topic")}
        </button>
      </div>
    </div>;
  },
};
