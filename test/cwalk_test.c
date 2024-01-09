#include "gopt.h"
#include "liblogc.h"
#include "unity.h"
#include "utarray.h"
#include "utstring.h"

#include "s7plugin_test_config.h"
#include "cwalk_test.h"

s7_scheme *s7;

extern struct option options[];

int  s7plugin_verbosity;
extern int  libs7_verbosity;

#if defined(PROFILE_fastbuild)
#define     TRACE_FLAG cwalk_s7_trace
extern bool TRACE_FLAG;
#define     DEBUG_LEVEL cwalk_s7_debug
extern int  DEBUG_LEVEL;

extern bool libs7_debug_runfiles;
#endif

char *sexp_input;
char *sexp_expected;

UT_string *setter;
UT_string *sexp;
s7_pointer actual;
s7_pointer expected;

/* WARNING: setUp and tearDown are run once per test. */
void setUp(void) {
    /* log_info("setup"); */
}

void tearDown(void) {
    /* log_info("teardown"); */
}

/* s7_flush_output_port(s7, s7_current_output_port(s7)); */
/* char *s = s7_object_to_c_string(s7, actual); */
/* log_debug("result: %s", s); */
/* free(s); */

void test_cwalk(void) {

    /* cwk_path_get_basename("/my/path.txt", &basename, &length); */
    /* sexp_input = "((*libcwalk* 'cwk_path_get_basename) \"/my/path.txt\")"; */
    sexp_input = "(cwk:path-get-basename \"/my/path.txt\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\"path.txt\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    /* cwk_path_normalize("/var/log/weird/////path/.././..///", result, sizeof(result)); */
    /* sexp_input = "((*libcwalk* 'cwk:path_normalize) \"/var/log/weird/////path/.././..///\")"; */
    sexp_input = "(cwk:path-normalize \"/var/log/weird/////path/.././..///\")";
    sexp_expected = "\"/var/log\"";
    utstring_renew(sexp);
    utstring_printf(sexp, "%s", sexp_input);
    actual = s7_eval_c_string(s7, utstring_body(sexp));
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:path-normalize \"~/foo/bar/../\")";
    sexp_expected = "\"~/foo\"";
    utstring_renew(sexp);
    utstring_printf(sexp, "%s", sexp_input);
    actual = s7_eval_c_string(s7, utstring_body(sexp));
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    /* char *test_file; */
    /* if (strncmp(getenv("TEST_WORKSPACE"), "libs7", 5) == 0) */
    /*     test_file = "test/test.c"; */
    /* else */
    /*     test_file = "external/libs7/test/s7_test.c"; */

    /* /\* sexp_input = "(libc:realpath \"" testfile "\")"); *\/ */
    /* utstring_renew(sexp); */
    /* utstring_printf(sexp, "(libc:realpath \"%s\")", test_file); */
    /* /\* log_debug("cwd: %s", getcwd(NULL,0)); *\/ */
    /* /\* log_debug("test file: %s", utstring_body(sexp)); *\/ */
    /* actual = s7_eval_c_string(s7, utstring_body(sexp)); */
    /* char *rp = realpath(test_file, NULL); */
    /* /\* log_debug("expected: %s", rp); *\/ */
    /* /\* free(s); *\/ */
    /* TEST_ASSERT_TRUE(s7_is_equal(s7, actual, s7_make_string(s7, rp))); */
    /* free(rp); */

    sexp_input = "(->canonical-path \"/var/log/weird/path/../..\")";
    sexp_expected = "\"/var/log/weird/\"";
    utstring_renew(sexp);
    utstring_printf(sexp, "%s", sexp_input);
    actual = s7_eval_c_string(s7, utstring_body(sexp));
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));
}

/* static void _print_usage(char *test) { */
/*     printf("Usage:\t$ bazel test test:%s [-- flags]\n", test); */
/*     printf("  Flags (repeatable)\n"); */
/*     printf("\t-d, --debug\t\tEnable debugging flags.\n"); */
/*     printf("\t-t, --trace\t\tEnable trace flags.\n"); */
/*     printf("\t-v, --verbose\t\tEnable verbosity. Repeatable.\n"); */
/*     printf("\t    --plugin-debug\tEnable plugin debugging flags.\n"); */
/* } */

/* enum OPTS { */
/*     FLAG_HELP, */
/* #if defined(PROFILE_fastbuild) */
/*     FLAG_DEBUG, */
/*     FLAG_DEBUG_PLUGINS, */
/*     FLAG_TRACE, */
/* #endif */
/*     FLAG_VERBOSE, */
/*     LAST */
/* }; */

/* struct option options[] = { */
/*     /\* 0 *\/ */
/* #if defined(PROFILE_fastbuild) */
/*     [FLAG_DEBUG] = {.long_name="debug", .short_name='d', */
/*                     .flags=GOPT_ARGUMENT_FORBIDDEN | GOPT_REPEATABLE}, */
/*     [FLAG_DEBUG_PLUGINS] = {.long_name="plugin-debug", */
/*                     .flags=GOPT_ARGUMENT_FORBIDDEN | GOPT_REPEATABLE}, */
/*     [FLAG_TRACE] = {.long_name="trace",.short_name='t', */
/*                     .flags=GOPT_ARGUMENT_FORBIDDEN}, */
/* #endif */
/*     [FLAG_VERBOSE] = {.long_name="verbose",.short_name='v', */
/*                       .flags=GOPT_ARGUMENT_FORBIDDEN | GOPT_REPEATABLE}, */
/*     [FLAG_HELP] = {.long_name="help",.short_name='h', */
/*                    .flags=GOPT_ARGUMENT_FORBIDDEN}, */
/*     [LAST] = {.flags = GOPT_LAST} */
/* }; */

/* void set_options(char *test, struct option options[]) */
/* { */
/*     /\* log_trace("set_options"); *\/ */
/*     if (options[FLAG_HELP].count) { */
/*         _print_usage(test); */
/*         exit(EXIT_SUCCESS); */
/*     } */
/* #if defined(PROFILE_fastbuild) */
/*     if (options[FLAG_DEBUG].count) { */
/*         cwalk_s7_debug = options[FLAG_DEBUG].count; */
/*     } */
/*     if (options[FLAG_DEBUG_PLUGINS].count) { */
/*         s7plugin_debug = options[FLAG_DEBUG_PLUGINS].count; */
/*     } */
/*     if (options[FLAG_TRACE].count) { */
/*         cwalk_s7_trace = true; */
/*     } */
/* #endif */
/*     if (options[FLAG_VERBOSE].count) { */
/*         verbosity = options[FLAG_VERBOSE].count; */
/*         LOG_INFO(0, "verbosity: %d", verbosity); */
/*         if (verbosity > 1) { */
/*             libs7_verbosity = verbosity; */
/*         } */
/*     } */
/* } */

int main(int argc, char **argv)
{
    /* argc = gopt (argv, options); */
    /* (void)argc; */
    /* gopt_errors (argv[0], options); */

    /* set_options("cwalk_s7", options); */

    s7 = s7_plugin_initialize("cwalk_s7", argc, argv);

/* #if defined(PROFILE_fastbuild) */
/*     libs7_debug = true; */
/*     libs7_debug_runfiles = true; */
/* #endif */

    libs7_load_plugin(s7, "cwalk"); //, libcwalk_s7_init);

    char *script_dir = "./test";
    s7_pointer newpath;
    newpath =  s7_add_to_load_path(s7, script_dir);
    (void)newpath;

    /* debugging: */
    if (s7plugin_verbosity > 2) {
        s7_pointer loadpath = s7_load_path(s7);
        char *s = s7_object_to_c_string(s7, loadpath);
        log_debug("load path: %s", s);
        free(s);
    }

    utstring_new(sexp);

    UNITY_BEGIN();

    RUN_TEST(test_cwalk);

    utstring_free(sexp);
    return UNITY_END();
}
