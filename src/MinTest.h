#ifndef MIN_TEST_H_
#define MIN_TEST_H_

// Based on http://www.jera.com/techinfo/jtns/jtn002.html

#define mu_assert(message, test)                                                                   \
    do {                                                                                           \
        if (!(test))                                                                               \
            return message;                                                                        \
    } while (0)

#define mu_run_test(test)                                                                          \
    do {                                                                                           \
        char* message = test();                                                                    \
        tests_run++;                                                                               \
        if (message)                                                                               \
            return message;                                                                        \
    } while (0)

extern int test_run;

#endif // MIN_TEST_H_