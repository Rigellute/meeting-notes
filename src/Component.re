module Topic = {
    type topic = {
        title: string,
        url: string,
        id: int,
    }; 
}
/* State declaration */
type state = {
    topics: list(Topic.topic)
};

/* Action declaration */
type action =
  | Title(int, string)
  | Url(int, string)
  | Add;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

let blankTopic = (): Topic.topic => {title: "", url: "", id: Random.int(10000)};

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => { topics: [blankTopic()]},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Title(id, title) => 
        let topics = List.map(t => Topic.(t.id) == id ? { ...t, Topic.title: title } : t, state.topics); 
        ReasonReact.Update({...state, topics: topics });
    | Url(id, url) => 
        let topics = List.map(t => Topic.(t.id) == id ? { ...t, Topic.url: url } : t, state.topics); 
        ReasonReact.Update({...state, topics: topics })
    | Add => ReasonReact.Update({ ...state, topics: List.append([blankTopic()], state.topics)})
    },
  render: self => {
    let topics = List.map(topic => 
        <div key=(string_of_int(Topic.(topic.id))) className="columns">
          <div className="column">
            <label className="label"> {ReasonReact.string("Title")} </label>
            <input
              type_="text"
              className="input"
              placeholder="Title"
              value={Topic.(topic.title)}
              onChange={
                event =>
                  self.send(Title(Topic.(topic.id), ReactEvent.Form.target(event)##value))
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
              StringHelpers.createTitle(
                ~title=self.state.title,
                ~url=self.state.url,
              ),
            )
          }
        </code>
      </div>
    </div>,
};
