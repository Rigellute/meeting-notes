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
