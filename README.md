# RPGMapper

RPG Role Playing Mapper for playing old-school RPGs and map dungeons and areas on a grid. 
The goal of this project is to have a tiny, nice tool at hand, which lets the user create
any dungeon-like map. The user should be capable of sharing these maps freely.


## Preamble

In  this project of mine, I try to adhere to the recent software engineering principles found
in such books as:

* Robert C. Martin, "Clean Code: A Handbook of Agile Software Craftsmanship"
* Stephan Roth, "Clean C++: Sustainable Software Development, and Best Practices 
with C++17"  

As for the latter, due to my target to support Debian, whose version number is - at the time
of writing - 9 and therefore ships with gcc-6.3, I'm locked at C++14. 

This is also a playground of mine to study, learn and experience new C++11, C++14 and C++17 
techniques.

Some more notes:
* The software is licensed under [GPL-3](http://gplv3.fsf.org).
* RPGMapper uses [Qt5](https://www.qt.io).
* [CMake](https://cmake.org)
* and [GoogleTest](https://github.com/google/googletest)

## Building

This is a CMake - Qt 5 - C++14 project. On a Ubuntu/Debian based operating 
system you'll need at least these packages:
* build-essential
* qtbase5-dev
* cmake

Maybe I missed some, sorry. The `cmake` step will tell you. Next, clone this 
repository as usual and then

```bash
$ mkdir build
$ cd build
$ cmake ..
```

You might check the output and install missing dependencies according to
your operating system.

Then:
```bash
$ make
```

If all went well, you'll find the rpgmapper executable:
```bash
$ bin/rpgmapper
```
within the `build` folder.


## Images

I'm still in desperate need of someone with a graphic skill to help me out drawing
icons and other images needed for the application. The icons and images I use here
are free. Some picked by KDE Plasma stock Breeze icon set other from Open Cliparts
and other from other various places, like: 

* https://www.freepik.com used under Creative Commons BY 3.0
* http://www.iconarchive.com/show/oxygen-icons-by-oxygen-icons.org.1.html

## Edit 1

Aaaarrrgghhh! I cannot stand it to _not_ comment my work. After some months of inactivity 
I myself find it hard to reflect upon this code.

Therefore: sorry, I will comment my code.

## Edit 2

Obviously, it is hard to find and figure out the software patterns and C++ idioms I use.
I will include them in the documentation too.

### Software Patterns and C/C++ Idioms in this project:

(in no particular order; sure some missing...)

- Model-View-Controller - https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller 
  Having model/controller classes defined in the library and view classes in the binary. 
- Null object pattern - https://en.wikipedia.org/wiki/Null_object_pattern
- Pimpl - https://en.wikipedia.org/wiki/Opaque_pointer
- Command - https://en.wikipedia.org/wiki/Command_pattern
- Factory - https://en.wikipedia.org/wiki/Factory_(object-oriented_programming)

---
Oliver Maurhart, <dyle71@gmail.com>  
