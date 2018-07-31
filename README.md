# Sierpinski triangle

A C [Sierpinski triangle](https://en.wikipedia.org/wiki/Sierpinski_triangle)
implementation based on [Cairo 2D graphical
library](https://www.cairographics.org/).

## Installation
As a first step, ensure Cairo is installed in your environment: [Cairo |
Download](https://www.cairographics.org/download/).

Once this dependency is done, run `make serpinskit` in your console to build the executable.

## Execution
```
serpinskit: <depth level>
```
The first argument to the executable is the number of iterations to carry out
on the initial canvas.

Image `.png` files are saved as `Serpinski[0-9]+.png` in
the same directory as the executable.

As an example `./sierpinski 8` will yield:

!["Eight levels of the Sierpinski process"][1]


[1]: ./Sierpinski8.png
