#include <curses.h>
#include <stdexcept>

#include "textfield.h"

#define COLOUR_PAIR_BACKGROUND 1
#define COLOUR_PAIR_APPLICATION 2

void curse(void) {

  // initialise curses standard screen
  initscr();

  // turn off echoing of the user input in the terminal
  noecho();

  // turn off line-buffering
  cbreak();

  // enable translation of special keys into their names
  if (keypad(stdscr, true) == ERR) {
    throw std::runtime_error(
        "Could not initialise keypad function in ncurses. Please use a "
        "terminal emulator which supports this functionality");
  }

  // reduce cursor to small line if possible
  curs_set(1);

  // enable colors
  if (has_colors()) {
    start_color();
  }
  if (can_change_color()) {
    // The colors 0-7 are reserved for internal color constants (COLOR_...)
    // self defined colors will start at 8
    // # RGB values have to be set to integers from 0 to 1000 (last 3
    // parameters)

    // define the color #073642 (dark grey/blue)
    init_color(8, 28, 212, 264);
    // create the white-blue color pair as the global background color theme
    init_pair(COLOUR_PAIR_BACKGROUND, COLOR_WHITE, 8);

    // define the color #073642 (medium blue)
    init_color(9, 142, 600, 972);
    // use the color pair 2 as the application color scheme
    init_pair(COLOUR_PAIR_APPLICATION, COLOR_WHITE, 9);
  } else {
    // define two alternative color pairs if colors cannot be changed
    init_pair(COLOUR_PAIR_BACKGROUND, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(COLOUR_PAIR_APPLICATION, COLOR_WHITE, COLOR_BLUE);
  }

  // clear screen
  clear();
}

void init_form(void){
  //TODO: write code
}

void reverse(void) {
  // reset cursor to its visible state
  // (same as it was before initialising curses)
  curs_set(1);

  // re-enable line buffering
  nocbreak();

  // re-enable echo
  echo();

  // end curses session
  endwin();
}
