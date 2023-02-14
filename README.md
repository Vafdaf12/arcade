# Arcade App
Following the Udemy course "Learning Programming by Making Games in C++, Volume 2"
by Serge Lansiquot, this project is an implementation of the content covered in the
course, with my own custom modifications to it.


## Currently implemented games
- [X] Breakout
- [X] Tetris
- [ ] MacPan (for obvious copyright reasons)
- [ ] Asteroids


# Plans for the Future
better suit my style of coding and 2) implement new features that could aid in future
games. Another convenient refactoring would be to seperate the "engine" code into its
own library, allowing easy re-use

## Potential Refactors
- [ ] Reduce function parameters for image rendering by offloading some parameters to structs
- [ ] Decouple all code from the central App class

## Planned Features
- [ ] Resizable/Fullscreen windows
- [ ] Add OpenGL backend to rendering code
- [ ] Event-based Tween animations
- [ ] Support for multi-threading to emphasize seperation of concerns (e.g. physics thread, graphics thread, etc.)


