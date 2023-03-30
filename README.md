# Mandelbrot Set Explorer

A Mandelbrot Set explorer I wrote in C.
![mandelbrot set](https://i.imgur.com/rwXt6PV.png)


## How to use

Click and drag to move. It will take a while to plot, while it's plotting you will see a text saying "loading..." in the bottom left corner.
Use the up and down arrow keys to zoom in/out.

## Command line parameters

``-iter [num]``
Will set the number of iterations for plotting each point. The more iterations the more detail you will find when zooming in. By default it's 256.

``-res [num]``
Sets the resolution of the plotting. The resolution has nothing to do with the window size, you will be able to maximize the window despite the resolution of the plotting which will be scaled accordingly.
By default it's 1024

``-col``
Inverts colors. Points that belong to the set will be drawn as white.
## Compiling
The code is currently only compilable on Windows.
Compiling requires [MinGW](https://sourceforge.net/projects/mingw/) installed and the SDL2 development libraries.
`SetupSDL.bat` is a script I wrote to make the process of installing the SDL2 libraries easier: all you need to do is run the script with administrator privileges and it will download and extract the libraries to `C:\SDL2-2.26.4-mingw`.
Once both SDL2 and MinGW are installed you can run `compile.bat` and `frac.exe` will be generated.

## Gallery
![img1](https://i.imgur.com/dvd4F0E.png)
![img2](https://i.imgur.com/MnrEUZM.png)
![img3](https://i.imgur.com/0YuN5Uz.png)
