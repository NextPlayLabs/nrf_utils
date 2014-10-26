/*
 * Copyright (c) 2014 Next Play Labs, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


// This is an example of what a test_main.c typically
// looks like in a project.

#include "nrfunit.h"

// Include headers for the test suites.
#include "ts_example_basic.h"
#include "ts_example_another.h"

// We begin by defining the counters that keep track of how many
// tests we have run. These were declared in nrfunit.h so they
// are known to all test files.
unsigned test_suites_run = 0;
unsigned tests_run = 0;
unsigned asserts_run = 0;
#if NRFUNIT_CONTINUE_ON_FAILURE
unsigned asserts_failed = 0;
#endif

// Finally, main invokes all the tests and reports overall results.

int main(int argc, char **argv) {

    // Note that this will fail, deliberately, to demonstrate
    // how test failures are handled. When you run this code,
    // the output will be a file name and line number where the
    // failure happened. As an exercise, go fix that test and
    // compile and run again to see what success looks like.
    // But don't check in the fixed code. We want the next person
    // to be able to do this exercise too.


#if NRFUNIT_CONTINUE_ON_FAILURE
    all_tests();

    if (asserts_failed) {
        printf("%u of %u asserts failed in %u tests and %u test suites.\n", asserts_failed, asserts_run, tests_run, test_suites_run);
    } else {
        printf("%u asserts passed in %u tests and %u test suites.\n", asserts_run, tests_run, test_suites_run);
    }

    return asserts_failed != 0;
#else
    const char *result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }

    printf("%u asserts run in %u tests and %u test suites.\n", asserts_run, tests_run, test_suites_run);

    return result != 0;
#endif

}


