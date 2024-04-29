#include "logger.h"

int main() {
    logger<std::string> log("log.txt", "test-component");
    log.debug("This is a debug message");
    log.info("This is an info message");
    log.warning("This is a warning message");
    log.error("This is an error message");
    return 0;
}
