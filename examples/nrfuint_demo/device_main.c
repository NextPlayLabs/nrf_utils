
#include "nrfunit_device.h"

int main(int argc, char **argv) {

    nrfunit_device_init();

    // Main loop runs the tests.
    nrfunit_device_main_loop();

    return 0;
}
