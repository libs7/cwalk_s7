LIBS7_VERSION = "0.1.0"
CWALK_VERSION = "1.2.7"
CWALK_S7_VERSION = "1.2.7"

GOPT_VERSION = "10.0.0"
LIBLOG_CC_VERSION = "1.0.0"
UNITY_VERSION = "2.5.2"
UTHASH_VERSION = "2.3.0"

BASE_SRCS = []
BASE_DEPS = [
    "@libs7//src:s7",
    "@liblog_cc//src:logc"
]
BASE_INCLUDE_PATHS = [
    "-Iexternal/libs7~{}/src".format(LIBS7_VERSION),
    "-Iexternal/liblog_cc~{}/src".format(LIBLOG_CC_VERSION)
]
BASE_COPTS = []
BASE_DEFINES = []
BASE_LINKOPTS = []
TIMEOUT = "short"
