Graphal
=======

About
-----

Graphal is an interpreter of a programming language that is mainly oriented to graph algorithms. There is a command line interpreter and a graphical integrated development environment. The IDE contains text editor for programmers, compilation and script output, advanced debugger and visualization window. The progress of the interpreted and debugged graph algorithm can be displayed in 3D scene.

![Screenshot of Graphal GUI](http://graphal.sourceforge.net/images/screenshots/graphal_gui_dfs_sm.png "Screenshot of Graphal GUI")

[http://graphal.sourceforge.net/](http://graphal.sourceforge.net/)


Main Features
-------------

- The script code looks very similar to C or Java language.
- Shared library and CLI application is written in C++ with STL.
- GUI application uses Qt library.
- There is no other dependency to any external library.
- Core library, CLI and GUI applications are separated.

- Null, bool, int, float, string, array, struct, set, vertex, edge and graph data types.
- Global and local variables.
- C/C++ like evaluation of expressions.
- If-else, for, while and foreach statements.
- Return, break and continue structured jumps.
- Built-in and user defined functions.
- Preprocessor includes and defines.

- Text editor for programmers with syntax highlighting.
- Window with compilation and script output.
- Interactive visualization Window with graph in 3D space.
- Advanced debugging of the scripts.

- Runnable on GNU/Linux and MS Windows, other operating systems are probably supported too.
- Core library licensed under GNU LGPL, applications under GNU GPL.


Dependencies
------------

- GNU Bison
- Perl
- Qt library


Installation
------------

To extract the downloaded archive:

```shell
tar -xzvf graphal-VERSION.tar.gz
cd graphal-VERSION
```

To compile the source codes (please see top level Makefile for possible options):

```shell
./configure
make
```

To install the application:

```shell
su
make install
```


Run
---

To execute Graphal CLI:

```shell
graphal_cli
```


To execute Graphal GUI:

```shell
graphal_gui
```


Contribute/Contact
------------------

Graphal is a free software, I would be very glad for any help with its improving. If you want to code, write documentation, maintain the website, package the software, publish a script you develop, or similar, please send me an email to mixalturek (at) users.sourceforge.net or WOQ (at) seznam.cz.

If you want something to be fixed or added to the applications or just to tell me that you are using Graphal and optionally how, contact me too, please. The developer is always happy to know that somebody uses his software.

Thank you very much in advance.

Michal Turek
