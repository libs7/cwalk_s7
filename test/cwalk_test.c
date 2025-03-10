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

#define S7_DEBUG_LEVEL libs7_debug
extern int  libs7_debug;
extern bool s7plugin_trace;
extern int  s7plugin_debug;

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
    sexp_input = "(cwk:basename \"/my/path.txt\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\"path.txt\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    /* cwk_path_normalize("/var/log/weird/////path/.././..///", result, sizeof(result)); */
    /* sexp_input = "((*libcwalk* 'cwk:path_normalize) \"/var/log/weird/////path/.././..///\")"; */
    sexp_input = "(cwk:normalize \"/var/log/weird/////path/.././..///\")";
    sexp_expected = "\"/var/log\"";
    utstring_renew(sexp);
    utstring_printf(sexp, "%s", sexp_input);
    actual = s7_eval_c_string(s7, utstring_body(sexp));
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:normalize \"~/foo/bar/../\")";
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

void test_dirname(void) {
    log_debug("foo");
    sexp_input = "(cwk:dirname \"/my/path.txt\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\"/my/\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:dirname \"//foo/bar/baz\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\"//foo/bar/\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));
}

void test_get_first_segment(void) {
    sexp_input = "(cwk:first-segment \"/my/path.txt\")";
    s7_pointer actual = s7_eval_c_string(s7, sexp_input);
    /* seg is cwk:segment, with fields size and begin */
    /* actual = s7_call(s7, s7_name_to_value(s7, "cwk:seg"), */
    /* TRACE_S7_DUMP(0, "actual: '%s'", actual); */

    sexp_expected = "\"my\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:first-segment \"my/path.txt\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\"my\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:first-segment \"my\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\"my\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:first-segment \"/my\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\"my\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:first-segment \"./\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\".\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:first-segment \"./foo/bar\")";
    actual = s7_eval_c_string(s7, sexp_input);
    sexp_expected = "\".\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));

    sexp_input = "(cwk:first-segment \"/\")";
    actual = s7_eval_c_string(s7, sexp_input);
    /* TRACE_S7_DUMP(0, "actual: '%s'", actual); */
    sexp_expected = "\"\"";
    expected = s7_eval_c_string(s7, sexp_expected);
    TEST_ASSERT_TRUE(s7_is_equal(s7, actual, expected));
}

int main(int argc, char **argv)
{
    libs7_debug = 1;
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
    RUN_TEST(test_dirname);
    RUN_TEST(test_get_first_segment);

    utstring_free(sexp);
    return UNITY_END();
}
