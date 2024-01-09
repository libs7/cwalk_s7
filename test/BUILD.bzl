# load("//:BUILD.bzl",
#      "GOPT_VERSION",
#      "UNITY_VERSION",
#      "UTHASH_VERSION")

## Args common to all test binarys:
TIMEOUT = "short"

TEST_SRCS = [] # ["//test/unit:common.c", "//test/unit:common.h"]

TEST_DEPS = [
    "@test_s7//src:test_s7",
    "@unity//src:unity",
    # "@libs7//src:s7",
    # "@gopt//src:gopt",
    # "@uthash//src:uthash"
]

TEST_COPTS = []

TEST_INCLUDE_PATHS = [
    "-Isrc",
    # "-Iexternal/unity~{}/src".format(UNITY_VERSION),
    # "-Iexternal/gopt~{}/src".format(GOPT_VERSION),
    # "-Iexternal/uthash~{}/src".format(UTHASH_VERSION)
]

TEST_DEFINES = []

TEST_LINKOPTS = []



