// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE

import * as List from "bs-platform/lib/es6/list.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";

var anchor = (
    function (title) {
      return '#' + title.trim().toLowerCase().replace(/[^\w\- ]+/g, '').replace(/\s/g, '-').replace(/\-+$/, '');
    }
);

var urlToIssueNumber = (
    function (url) {
      return url.replace(/\D/g,'');
    }
  );

function createTitle(title, url) {
  var anchored = Curry._1(anchor, title);
  var issueNumber = Curry._1(urlToIssueNumber, url);
  return "\n  [" + (String(title) + ("](" + (String(anchored) + (") [" + (String(issueNumber) + ("](" + (String(url) + ")\n    ")))))));
}

function mergeTitles(topics) {
  return List.map((function (topic) {
                return React.createElement("p", {
                            key: String(topic[/* id */2])
                          }, "1." + createTitle(topic[/* title */0], topic[/* url */1]));
              }), topics);
}

function constructDateString(date) {
  var jsDate = new Date(date + "T00:0");
  var match = date.length;
  if (match !== 0) {
    return jsDate.toDateString();
  } else {
    return "";
  }
}

export {
  anchor ,
  urlToIssueNumber ,
  createTitle ,
  mergeTitles ,
  constructDateString ,
  
}
/* anchor Not a pure module */
