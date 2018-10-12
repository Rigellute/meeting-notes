/* State declaration */
type state = {
  date: string,
  topics: list(Topic.topic),
  markdownRef: ref(option(Dom.element)),
};

/* Action declaration */
type action =
  | Title(int, string)
  | Url(int, string)
  | UpdateNotes(int, string)
  | Date(string)
  | NewAction(int, int, string)
  | AddEmptyAction(int)
  | CopyMarkdownToClipboard
  | Add;

let setMarkdownRef = (theRef, {ReasonReact.state}) =>
  state.markdownRef := Js.Nullable.toOption(theRef);
/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

let blankTopic = (): Topic.topic => {
  title: "",
  url: "",
  id: Random.int(10000),
  notes: "",
  actions: [""],
};

/* `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {
    date: "",
    topics: [blankTopic()],
    markdownRef: ref(None),
  },
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
    | UpdateNotes(id, notes) =>
      let topics =
        List.map(
          t => Topic.(t.id) == id ? {...t, Topic.notes} : t,
          state.topics,
        );
      ReasonReact.Update({...state, topics});
    | Date(date) => ReasonReact.Update({...state, date})
    | Add =>
      ReasonReact.Update({
        ...state,
        topics: List.rev_append([blankTopic()], state.topics),
      })
    | NewAction(id, index, action) =>
      let topics =
        List.map(
          t =>
            Topic.(t.id) == id ?
              {
                ...t,
                actions:
                  List.mapi(
                    (i, a) => index == i ? action : a,
                    Topic.(t.actions),
                  ),
              } :
              t,
          state.topics,
        );

      ReasonReact.Update({...state, topics});
    | AddEmptyAction(id) =>
      let topics =
        List.map(
          t =>
            Topic.(t.id) == id ?
              {...t, actions: List.rev_append(Topic.(t.actions), [""])} : t,
          state.topics,
        );

      ReasonReact.Update({...state, topics});
    | CopyMarkdownToClipboard =>
/* TODO: copy the markdown to clipboard */
      /* let ref = */
      /*   switch (state.markdownRef^) { */
      /*   | None => "" */
      /*   | Some(r) => r.innerText */        
      /*   }; */
ReasonReact.NoUpdate;
    },
  render: self => {
    let topics =
      List.map(
        topic =>
          <div className="field">
            <div className="field">
              <div key={string_of_int(Topic.(topic.id))} className="columns">
                <div className="column">
                  <label className="label">
                    {ReasonReact.string("Title")}
                  </label>
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
                  <label className="label">
                    {ReasonReact.string("URL")}
                  </label>
                  <input
                    type_="text"
                    className="input"
                    value=Topic.(topic.url)
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
              </div>
              <div className="columns">
                <div className="column">
                  <label className="label">
                    {ReasonReact.string("Notes")}
                  </label>
                  <textarea
                    className="textarea"
                    value=Topic.(topic.notes)
                    onChange={
                      event =>
                        self.send(
                          UpdateNotes(
                            Topic.(topic.id),
                            ReactEvent.Form.target(event)##value,
                          ),
                        )
                    }
                    placeholder="Type notes here"
                  />
                </div>
                <div className="column">
                  <label className="label">
                    {ReasonReact.string("Actions")}
                  </label>
                  {
                    List.mapi(
                      (index, action) =>
                        <p className="field">
                          <input
                            key={string_of_int(index)}
                            type_="text"
                            className="input"
                            placeholder="Action"
                            value=action
                            onChange={
                              event =>
                                self.send(
                                  NewAction(
                                    Topic.(topic.id),
                                    index,
                                    ReactEvent.Form.target(event)##value,
                                  ),
                                )
                            }
                          />
                        </p>,
                      Topic.(topic.actions),
                    )
                    |> Array.of_list
                    |> ReasonReact.array
                  }
                  <button
                    onClick={
                      _event => self.send(AddEmptyAction(Topic.(topic.id)))
                    }
                    className="button is-primary">
                    {ReasonReact.string("Add Action")}
                  </button>
                </div>
              </div>
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
        <br />
        <label className="label"> {ReasonReact.string("Date")} </label>
        <input
          className="input field"
          type_="date"
          onChange={
            event => self.send(Date(ReactEvent.Form.target(event)##value))
          }
          value={self.state.date}
        />
        <h1 className="title"> {ReasonReact.string("Topics")} </h1>
        {ReasonReact.array(Array.of_list(topics))}
        <button
          onClick={_event => self.send(Add)} className="button is-primary">
          {ReasonReact.string("Add new topic")}
        </button>
        <section className="field">
          <hr className="hr" />
          <h1 className="title"> {ReasonReact.string("Markdown")} </h1>
          <button
            onClick={_event => self.send(CopyMarkdownToClipboard)}
            className="button is-primary">
            {ReasonReact.string("Copy to clipboard")}
          </button>
          <div
            className="box has-background-light"
            ref={self.handle(setMarkdownRef)}>
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
            <br />
            <p> {ReasonReact.string("## Discussion")} </p>
            <br />
            <p> {ReasonReact.string("## Actions Overview")} </p>
            <br />
            {
              List.map(topic => Topic.(topic.actions), self.state.topics)
              |> List.concat
              |> List.mapi((index, action) =>
                   <p key={string_of_int(index)}>
                     {ReasonReact.string("- " ++ action)}
                   </p>
                 )
              |> Array.of_list
              |> ReasonReact.array
            }
            <br />
            <div>
              {
                List.map(
                  topic =>
                    <div key={string_of_int(Topic.(topic.id))}>
                      <p>
                        {ReasonReact.string("### " ++ Topic.(topic.title))}
                      </p>
                      <p
                        style={
                          ReactDOMRe.Style.make(~whiteSpace="pre-wrap", ())
                        }>
                        {ReasonReact.string(Topic.(topic.notes))}
                      </p>
                      <br />
                      {
                        List.mapi(
                          (index, action) =>
                            <p key={string_of_int(index)}>
                              {ReasonReact.string("- " ++ action)}
                            </p>,
                          Topic.(topic.actions),
                        )
                        |> Array.of_list
                        |> ReasonReact.array
                      }
                      <br />
                    </div>,
                  self.state.topics,
                )
                |> Array.of_list
                |> ReasonReact.array
              }
            </div>
          </div>
        </section>
      </div>
    </div>;
  },
};
