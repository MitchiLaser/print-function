#include <cstdlib>
#include <cstring>
#include <cups/cups.h>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#define COLOUR_PAIR_BACKGROUND 1
#define COLOUR_PAIR_APPLICATION 2

// global variables
bool logging = false;
std::ofstream logfile;
std::string printfile;

// all the data retrieved from cups will be stored in this structure
struct printers_data {
  int num_dests = 0;
  cups_dest_t *dests = NULL;
};

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
  // TODO: Continue

  // clear screen
  clear();
}

int print_search_cb(void *user_data, unsigned flags, cups_dest_t *dest) {
  if (!(flags & CUPS_DEST_FLAGS_REMOVED)) {
    // replace the void* pointer with a printers_data* pointer
    // otherwise the linter will be triggered
    printers_data *myData = reinterpret_cast<printers_data *>(user_data);
    myData->num_dests = cupsCopyDest(dest, myData->num_dests, &(myData->dests));

    // [[deprecated(This code has been replaced with a newer version)]]
    // this is the deprecated old version to realise the function call without
    // annoying warnings from the linter
    /*
     *(*(printers_data*)user_data).num_dests = cupsCopyDest(
     *  dest, (*(printers_data*)user_data).num_dests,
     *&(*(printers_data*)user_data).dests
     *);
     */
  }

  return 1;
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

void log(std::string add_to_file) {
  if (logging) {
    logfile << add_to_file << std::endl;
  }
}

std::string get_help_text(void) {
  return std::string(
      "Print-Function: Print dialog for documents on the console\n"
      "\n"
      "usage: print [-l \e[3mlog-file\e[0m] \e[3mfile\e[0m\n"
      "\n"
      "options:\n"
      "\tfile\t The file which has to be printed\n"
      "\t-l\t log the applications internal operations in a logfile. "
      "This was designed only for debugging purposes.\n");
}

int main(int argc, char **argv) {
  // check command line arguments
  if (argc == 2) { // no logging, only a file to print was specified
    printfile = std::string(argv[1]);
  } else if (argc == 4) { // output file and logfile
    if (std::strcmp(argv[1], "-l") == 0) {
      // logfile is argv[2], print file is argv[3]
      printfile = std::string(argv[3]);
      logfile.open(argv[2], std::ios::out | std::ios::trunc);
    } else if (std::strcmp(argv[2], "-l") == 0) {
      // logfile is argv[3], print file is argv[1]
      printfile = std::string(argv[1]);
      logfile.open(argv[3], std::ios::out | std::ios::trunc);

    } else {
      std::cerr << "Wrong command line parameter usage" << std::endl;
      exit(EXIT_FAILURE);
    }
    logging = true;
    log("Beginning log");
  } else { // there is something wrong. Print help text and exit
    std::cerr << get_help_text();
    exit(EXIT_SUCCESS);
  }
  log("file which was selected for printing: " + std::string(printfile));
  // now the logfile and the print-file have been specified (please replace this
  // crappy argument parsing in the future)

  try {
    // get the builtin printers from the OS via the CUPS interface
    printers_data printers;
    cupsEnumDests(
        CUPS_DEST_FLAGS_NONE, // `flags` argument: specify enumeration options
        1000,                 // maximum time in milliseconds for enumerating
        NULL,                 // If not NULL: Cancel enumeration
        0,                    // filter-mask: do not filter anything
        0,               // search for printer types: do not filter anything
        print_search_cb, // callback which will be called on each destination
        &printers        // the storage location for all the retrieved data
    );
    // TODO: check wether this works (on a system with available printers)
    std::string printer_names[printers.num_dests];
    for (int i = 0; i < printers.num_dests; i++) {
      printer_names[i] = printers.dests[i].name;
      // the following statement is just for debugging there
      std::cout << "Found printer:" << printer_names[i] << std::endl;
    }

    // initialise curses object
    curse();

    // TODO: Add further changes to the screen

    // update screen
    refresh();

    // for demonstration purpose: get a single character and then exit the
    // application
    getch();

    // bring the program to an exit
  } catch (...) {
    // stop the curses session
    reverse();
    // TODO: Add proper exception printing
    if (logging) {
      log("ERROR: There was an exception");
      logfile.close();
    }
    exit(EXIT_FAILURE);
  }
  reverse();
  if (logging) {
    log("Closing program");
    logfile.close();
  }
  exit(EXIT_SUCCESS);
}
