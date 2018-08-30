// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");

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

exports.anchor = anchor;
exports.urlToIssueNumber = urlToIssueNumber;
exports.createTitle = createTitle;
/* anchor Not a pure module */
