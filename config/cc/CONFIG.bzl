load("@obazl_tools_cc//config:BASE.bzl",
     _BASE_COPTS    = "BASE_COPTS",
     _BASE_LINKOPTS = "BASE_LINKOPTS",
     _define_module_version = "define_module_version")

define_module_version = _define_module_version

BASE_COPTS = _BASE_COPTS
BASE_LINKOPTS = _BASE_LINKOPTS

BASE_SRCS = ["@libs7//lib:libs7.h"]
BASE_DEPS = ["@libs7//lib:s7", "@liblogc//lib:logc"]

PROFILE       = ["PROFILE_$(COMPILATION_MODE)"]
