# Khazad-dûm

Basic text adventure game written as part of the course *DD2387 Program System Construction using C++* at KTH Royal Institute of Technology.

## Building

The game requires GNU readline and uses QMake from Qt 5 as build system. It's recommended to build in a separate directory. Clone the repository into `khazad-dum`, then run

    $ mkdir khazad-dum-build
    $ cd khazad-dum-build
    $ qmake ../khazad-dum
    $ make

## Running

The game must be run from the build directory:

    $ cd khazad-dum-build
    $ ./khazad-dum

## Story

    ================================================
          Welcome to the Game of Khazad-dûm!
    ================================================
    You're trapped in the mines of Khazad-dûm. Your
    mission is to slay the evil Balrog guarding the
    exit in the northwestern parts of the mines.
    
    In your journey you may come across friendly
    Elves, Wizards and Dwarves that will help you
    along the way. Orcs and Goblins are evil and
    will try to stop you.
    ================================================

## License

See the LICENSE file.
