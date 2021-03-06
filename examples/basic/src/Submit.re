open GraphqlHooksMutation;
open Util;

module CreatePost = [%graphql
  {|
    mutation createPost($title: String!, $url: String!) {
      createPost(title: $title, url: $url) {
        id
        title
        votes
        url
        createdAt
      }
    }
  |}
];

[@react.component]
let make = (~onSubmission: unit => unit) => {
  let (title, setTitle) = React.useState(_ => "");
  let (url, setUrl) = React.useState(_ => "");

  let request = CreatePost.make(~title, ~url, ());

  let ({loading}, createPost) = useMutation(~request, ());

  let reset = () => {
    setTitle(_ => "");
    setUrl(_ => "");
  };

  let handleSubmit = e => {
    e->ReactEvent.Form.preventDefault;
    reset();
    createPost()
    |> Js.Promise.then_(_result => onSubmission() |> Js.Promise.resolve)
    |> ignore;
  };

  <form onSubmit={e => handleSubmit(e)}>
    <h1> "Submit"->s </h1>
    <input
      placeholder="title"
      name="title"
      type_="text"
      value=title
      required=true
      onChange={e => e->ReactEvent.Form.target##value->setTitle}
    />
    <input
      placeholder="url"
      name="url"
      type_="url"
      value=url
      required=true
      onChange={e => e->ReactEvent.Form.target##value->setUrl}
    />
    <button type_="submit"> {loading ? "Loading..." : "Submit"}->s </button>
  </form>;
};