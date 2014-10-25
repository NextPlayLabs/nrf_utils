/* 
 * Copyright (c) 2014 Next Play Labs Inc. All Rights Reserved.
 */

#include <stdio.h>
#include "nrfunit.h"
#include "ts_example_basic.h"

#define YES 1
#define NO 0

// This is a test, this is only a test...
// By convention, there is a function for each
// test, beginning with test_, that asserts
// a series of related assertions.
static const char *test_example_basic_bool() {

    nu_assert("True better be assertable.", YES);
    nu_assert("True better be assertable.", !NO);

    int this = YES;
    int that = NO;

    nu_assert("At least one of these.", this || that);

    return TEST_SUCCEEDED;
}

// Another test
static const char *test_example_more_stuff() {

    int a = -1;
    int b = 1;

    nu_assert("signed compare works.", a < b);

    unsigned ua = a;
    unsigned ub = b;

    nu_assert("unsigned compare works.", ua > ub);

    return TEST_SUCCEEDED;
}

// This is a test suite for a series of tests.
// By convention, test suites' names start with ts_
const char *ts_example_basic() {

    nu_run_test(test_example_basic_bool);
    nu_run_test(test_example_more_stuff);

	return TEST_SUCCEEDED;
}


