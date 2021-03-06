open GraphqlHooks;

let memCache = Memcache.make();

let client =
  Client.make(
    ~url="https://api.graph.cool/simple/v1/cixmkt2ul01q00122mksg82pn",
    ~cache=memCache,
    (),
  );

ReactDOMRe.renderToElementWithId(
  <Provider client> <App /> </Provider>,
  "app",
);