# EM Studio ([exe file](https://github.com/carisio/emstudio/releases/))
EM Studio is a free Electromagnetic Field Simulation software for Windows based on the Finite Difference Time Domain (FDTD) method.

To use EM Studio, download and extract `emstudio.rar`. Then, run `EMStudio.exe`. You can also find the binaries files at https://github.com/carisio/emstudio/releases/ .

For a brief tutorial, see the samples projects section.

Cite this project as:
- Leandro Carísio Fernandes and Antonio José Martins Soares, *"Software Architecture for the Design of Electromagnetic Simulators [EM Programmer's Notebook]"*, IEEE Antennas and Propagation Magazine, Volume: 55, Issue: 1, Feb. 2013, DOI: [10.1109/MAP.2013.6474511][1].

## Samples projects

[1 - Monopole mounted on a conducting rectangular box](samples/monopole_mounted_on_a_conducting_box/README_monopole_mounted_on_a_conducting_box.md)

[2 - Line-fed rectangular microstrip antenna](samples/line_fed_rectangular_microstrip_antenna/README_line_fed_rectangular_microstrip_antenna.md)

[3 - Microstrip low-pass filter](samples/microstrip_low_pass_filter/README_microstrip_low_pass_filter.md)

[4 - Propagation delay through dieletric slab](samples/propagation_delay_through_dieletric_slab/README_propagation_delay_through_dieletric_slab.md)

## Compiling EM Studio
The source code of EM Studio is also available. This section shows how to compile it. It considers that you are running 64-bit version of Windows.

A brief description of the architecture of EM Studio can be found in:
- Leandro Carísio Fernandes and Antonio José Martins Soares, *"Software Architecture for the Design of Electromagnetic Simulators [EM Programmer's Notebook]"*, IEEE Antennas and Propagation Magazine, Volume: 55, Issue: 1, Feb. 2013, DOI: 10.1109/MAP.2013.6474511. https://doi.org/10.1109/MAP.2013.6474511

### Preparing to compile EM Studio (last instructions: 27 January 2023)
You will need a set of tools:

1. Download and install a compiler.
	- In this tutorial we will consider MinGW-64. You can download it at http://tdm-gcc.tdragon.net/download . Select the installer for TDM64 MinGW-w64 edition (current version: `tdm64-gcc-10.3.0-2.exe`)
	- After install, add the bin folder path to Windows `PATH` variable. If you use the default folder, its path is `C:\TDM-GCC-64\bin` . Note: during the installation, the default options already set it to the `PATH` variable.

2. EM Studio uses wxWidgets. It is necessary to download its source code and build it:
	- This version was tested with wxWidgets 3.2.1.
	- You can download it at https://www.wxwidgets.org/downloads/ . Download the source code (Windows zip file) and extract it to `c:\wxWidgets-3.2.1` .
	- To build, open a console Windows (`cmd`) and execute the following commands (this process can take some time):
		- `cd C:\wxWidgets-3.2.1\build\msw`
		- `mingw32-make -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 USE_OPENGL=1 CXXFLAGS=-std=gnu++11 -Wall`
		- `mingw32-make -f makefile.gcc BUILD=debug SHARED=0 UNICODE=1 USE_OPENGL=1 CXXFLAGS=-std=gnu++11 -Wall`

3. Configure OpenGL libraries:
	- Download freeglut 3.0.0 MinGW Package, available at http://www.transmissionzero.co.uk/software/freeglut-devel/ .
	- The file `freeglut-MinGW-3.0.0-1.mp.zip` has three folders: `freeglut\bin`, `freeglut\include`, and `freeglut\lib`.
		- Copy the `GL` folder of `freeglut\include` to `c:\TDM-GCC-64\include`;
		- Copy the files of `freeglut\lib\x64` to `C:\TDM-GCC-64\lib\gcc\x86_64-w64-mingw32\10.3.0`;
		- Copy the `freeglut.dll` file of `freeglut\bin\x64` to `c:\windows\system32`.
			You will need to register this dll. Open the console (`cmd`) and type `regsvr32 freeglut.dll`.

4. Download an IDE
	- In this tutorial we will consider the Eclipse IDE for C/C++ developers, available at https://www.eclipse.org/downloads/eclipse-packages/ .
	- After download it, you just need to extract the zip file and run the file `eclipse.exe`to open it.

### Compiling EM Studio
To compile EM Studio, follow these steps:
1.  Download or clone this repository. The EMStudio folder contains the Eclipse project for EM Studio.

2. In Eclipse, click `File` > `Import` > `General` > `Existing Projects into Workspace`. Select the folder that you extract or cloned this repository.
	- Note: The project is configured considering the instalation of wxWidgets in `C:\wxWidgets-3.2.1`. If you are using a previous version of wxWidgets or if it is installed in other folder, you will need to open the project properties (right click on the project, select `Properties`). In C/C++ Build, change the variable `WX_PATH` to point to your wxWidgets folder;

3. All bitmap files are stored in a resource file. You will need to compile it before compile/link EM Studio. Open a console window (`cmd`), and run:
	- `cd EMS_FOLDER\src\emstudio\util\resources` . Note: replace  EMS_FOLDER for the location where you extract the EM Studio project;
	- `windres -iresource.rc -oresource.o -IC:\wxWidgets-3.2.1\include`

4. In Eclipse, select your project, click in menu `Project` > `Build Project`.

5.  After the building process, depending on the build configuration (debug or release), the `EMStudio.exe` file will be at `EMS_FOLDER\release` or `EMS_FOLDER\debug`.
  - Note: In the step 3 of the last section, if you didn't register `freeglut.dll`, you will need to copy this file to the same folder that `EMStudio.exe` is.



[1]: https://doi.org/10.1109/MAP.2013.6474511