
#include "nrfunit.h"

#include "ts_example_basic.h"
#include "ts_example_another.h"

// This is the function that runs all the tests. We could
// just do this in main, but it's nice to have them here
// in one function that does nothing else. I use the 
// name all_tests() as a convention.
const char *all_tests() {

    // Run each of the suites in turn.
	nu_run_test_suite(ts_example_basic);
	nu_run_test_suite(ts_example_another);

    return TEST_SUCCEEDED;
}
