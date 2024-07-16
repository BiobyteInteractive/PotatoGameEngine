# try finch implementation

This is the code to build the https://finch.io/try wasm component.

### How to build

- Install emscripten sdk from https://emscripten.org/
- Make the emsdk available to your terminal/PATH 
	- for example:
    - `source ~/dev/emsdk/emsdk_env.sh`
- Run the emmake command to build
    - `emmake make`

That should be all. This builds a js + wasm file for the page.

### How does the page work?

The page is at `doc/site/try/template.html`.

It loads `finch_try.js` which loads `finch_try.wasm`.
The page uses emscripten API to call the `finch_compile` C function, found in `main.try.c`.
The page hooks up `printf` logging to the console for display.

### Notes

- The binaries land in `bin/finch_try.wasm` and `bin/finch_try.js` when building
- The default html output from emsripten is not used, `doc/site/try/template.html` is
- The finch_try.js and finch_try.wasm files are copied to `doc/site/static`
- The make project is a modified version of `projects/make`
- The code relies on code in `test/`
