# Injector

A simple DLL injector for windows applications

### Usage

Just pass the process name and the DLL full path to the injector.

Ex. `injector.exe "notepad.exe" "c:\mydll.dll"` 

### Build steps

1. Download the [Mingw Compiler](https://osdn.net/projects/mingw/releases/), installing it and adding to PATH. It is also possile (and recommanded) to use the [scoop](https://scoop.sh/) package manager : `scoop install gcc make`
2. Make sure `gcc.exe` and `make` is in your PATH.
3. Clone this repo (`git clone https://gitlab.com/xdavidel/simple-dll-injector`)
4. Run `make` 

### Build with TCC

The Tiny C Compiler can produce smaller size apps and compiles faster most of the time.

1. Download the [Tiny C Compiler](http://download.savannah.gnu.org/releases/tinycc/tcc-0.9.27-win32-bin.zip) and add the [WinApi headers](http://download.savannah.gnu.org/releases/tinycc/winapi-full-for-0.9.27.zip).
2. Patch `tcc/lib/gdi32.def` to also include `SetDCPenColor` and `SetDCBrushColor`. 
3. Make sure `tcc.exe` is in your PATH.
4. Clone this repo (`git clone https://gitlab.com/xdavidel/simple-dll-injector`)
5. Run `maketcc.bat` 

### Credits

* [injector tutorial](https://guidedhacking.com/)

### License

This project is licensed under the GNU General Public License v3.0. See LICENSE for more details.