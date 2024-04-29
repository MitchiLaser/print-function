#include "process_args.h"

std::shared_ptr<arg_results> process_args(int argc, char **argv) {
	std::shared_ptr<arg_results> parsed = std::make_shared<arg_results>();

	// TODO: parse cli arguments

  /*

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

  */

	return parsed;
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
