# meeting-notes

## Run Project

```sh
yarn install
yarn start
# in another tab
yarn webpack
```

After you see the webpack compilation succeed (the `yarn webpack` step), open up `src/index.html` (**no server needed!**). Then modify whichever `.re` file in `src` and refresh the page to see the changes.

**For more elaborate ReasonReact examples**, please see https://github.com/reasonml-community/reason-react-example

## Build for Production

```sh
yarn build
yarn webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version.

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.

## Deploy to gh-pages
```sh
yarn deploy
```

## TODO
- [ ] Add link back to this repo on the webpage
- [ ] Complete the `copy to clipboard` functionality
- [ ] Reorder the form inputs so `url` comes first
- [ ] Make new topics appear at the end of the list, not at the front - use `List.rev_append`
- [ ] Add `#### Actions` title to topic actions list
