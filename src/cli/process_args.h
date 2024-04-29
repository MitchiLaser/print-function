#pragma once

#include <memory>
#include <string>

struct arg_results{
	std::string printfile;
	std::string logfile;
};

std::shared_ptr<arg_results> process_args(int argc, char **argv);
