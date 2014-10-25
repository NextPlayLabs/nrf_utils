
#include "nrfunit.h"

int main(int argc, char **argv) {

    nrfunit_init();

    // Main loop runs the tests.
    nrfunit_main_loop();

    return 0;
}
