load("//:BUILD.bzl",
     "GOPT_VERSION",
     "UNITY_VERSION",
     "UTHASH_VERSION")

## Args common to all test binarys:
TEST_SRCS = [] # ["//test/unit:common.c", "//test/unit:common.h"]

TEST_DEPS = [
    "@libs7//src:s7", # always statically link libs7 for tests???
    "@gopt//:gopt",
    "@unity//src:unity",
    "@uthash//src:uthash"
]

TEST_COPTS = []

TEST_INCLUDE_PATHS = [
    "-Isrc",
    "-Iexternal/gopt~{}/src".format(GOPT_VERSION),
    "-Iexternal/unity~{}/src".format(UNITY_VERSION),
    "-Iexternal/uthash~{}/src".format(UTHASH_VERSION)
]

TEST_DEFINES = []

TEST_LINKOPTS = []



