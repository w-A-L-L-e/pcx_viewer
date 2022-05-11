## About
Tiny program to view pcx files easily on a modern mac (or windows if you recompile it).
This uses sdl2 libraries to do the heavy lifting. 

![PCX viewer screenshot](screenshot/pcx_viewer_screenshot.png?raw=true "pcx_viewer running")

## Installation and compiling
```
brew install sdl2
make
```


## Running
Just running the executable shows usage:
```
./pcx_viewer
Usage ./pcx_viewer[-fs] <pcx file>

pcx file is mandatory
optional -fs opens in full screen mode
```

When you give a valid pcx file path it opens and displays the PCX image in the original size.
Pressing 'f' will toggle the window fullscreen. And pressing 'q' or the close button on the window exits.

```
./pcx_viewer examples/sample_640×426.pcx
```

