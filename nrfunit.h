/* 
 * Copyright (c) 2014 Next Play Labs Inc. All Rights Reserved.
 */
#ifndef NRFUNIT_H
#define NRFUNIT_H

/* Inspired by nrfunit, from http://www.jera.com/techinfo/jtns/jtn002.html */

#include <stdio.h>


// Added these so we can get line numbers.
#define __S(x) #x
#define __S__(x) __S(x)
#define __S__LINE__ __S__(__LINE__)

#ifndef NU_PRINTF
#define NU_PRINTF(f, s) printf(f, s)
#endif

#if NU_CONTINUE_ON_FAILURE
#define NU_RETURN(ret) do { NU_PRINTF("%s\n\r", ret); ++asserts_failed; } while(0)
#else
#define NU_RETURN(ret) return ret
#endif


#define nu_format_message(message) (__FILE__ ":" __S__LINE__ ": error: " message)


#define nu_assert(message, test) do { ++asserts_run; if (!(test)) NU_RETURN(nu_format_message(message)); } while (0)

#define nu_assert_equals(message, a, b) nu_assert(message, (a) == (b))
#define nu_assert_not_equals(message, a, b) nu_assert(message, (a) != (b))

#define nu_assert_zero(message, a) nu_assert_equals(message, 0, a)
#define nu_assert_not_zero(message, a) nu_assert_not_equals(message, 0, a)

#define nu_assert_equals_within(message, a, b, epsilon) nu_assert(message, fabs((a) - (b)) <= epsilon)


#define nu_run_test(test) do { NU_PRINTF("Running %s\n\r", __S(test)); const char *message = test(); tests_run++; \
		if (message) return message; } while (0)
#define nu_run_test_suite(test) do { NU_PRINTF("Running %s\n\r", __S(test)); const char *message = test(); test_suites_run++; \
		if (message) return message; } while (0)

#define TEST_SUCCEEDED NULL

extern unsigned test_suites_run;
extern unsigned tests_run;
extern unsigned asserts_run;

#if NU_CONTINUE_ON_FAILURE
extern unsigned asserts_failed;
#endif

const char *all_tests();

#endif // NRFUNIT_H
