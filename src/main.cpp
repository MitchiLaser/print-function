#include <cstdlib>
#include <cstring>
#include <cups/cups.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

//#include "cli/process_args.h"
#include "logging/logger.h"
//#include "tui/tui.h"

// all the data retrieved from cups will be stored in this structure
struct printers_data {
  int num_dests = 0;
  cups_dest_t *dests = NULL;
};


/*
 * Callback function which will be called on each printer found by CUPS
 * Add the printer to the list of available devices
 */
int print_search_cb(void *user_data, unsigned flags, cups_dest_t *dest) {
  if (!(flags & CUPS_DEST_FLAGS_REMOVED)) {
    // replace the void* pointer with a printers_data* pointer
    // otherwise the linter will be triggered
    printers_data *myData = reinterpret_cast<printers_data *>(user_data);
    myData->num_dests = cupsCopyDest(dest, myData->num_dests, &(myData->dests));
  }
  return 1;
}


int main(int argc, char **argv) {
  //std::shared_ptr<arg_results> args = process_args(argc, argv);

  // TODO: check cli argument and then create logger object
  // then continue from here on

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

  std::string printer_names[printers.num_dests];
  for (int i = 0; i < printers.num_dests; i++) {
    printer_names[i] = printers.dests[i].name;
    //log.debug("Found printer: " + std::string(printer_names[i])); // TODO
  }

  exit(EXIT_SUCCESS);
}
