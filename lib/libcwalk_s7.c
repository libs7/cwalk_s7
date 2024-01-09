#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cwalk.h>
#include "libs7.h"

const char *cwalk_s7_version = CWALK_S7_VERSION;

#if defined(PROFILE_fastbuild)
#define DEBUG_LEVEL cwalk_s7_debug
int     DEBUG_LEVEL = 0;
#define TRACE_FLAG cwalk_s7_trace
bool    TRACE_FLAG = false;
#endif

static s7_pointer c_pointer_string, string_string, character_string, boolean_string, real_string, complex_string, integer_string;


/* -------- cwk_path_get_absolute -------- */
static s7_pointer cwk_cwk_path_get_absolute(s7_scheme *sc, s7_pointer args)
{
  s7_pointer p, arg;
  char* cwk_cwk_path_get_absolute_0;
  char* cwk_cwk_path_get_absolute_1;
  char* cwk_cwk_path_get_absolute_2;
  size_t cwk_cwk_path_get_absolute_3;
  p = args;
  arg = s7_car(p);
  if (s7_is_string(arg))
    cwk_cwk_path_get_absolute_0 = (char*)s7_string(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-absolute", 21), 1, arg, string_string));
  p = s7_cdr(p);
  arg = s7_car(p);
  if (s7_is_string(arg))
    cwk_cwk_path_get_absolute_1 = (char*)s7_string(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-absolute", 21), 2, arg, string_string));
  p = s7_cdr(p);
  arg = s7_car(p);
  if (s7_is_string(arg))
    cwk_cwk_path_get_absolute_2 = (char*)s7_string(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-absolute", 21), 3, arg, string_string));
  p = s7_cdr(p);
  arg = s7_car(p);
  if (s7_is_integer(arg))
    cwk_cwk_path_get_absolute_3 = (size_t)s7_integer(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-absolute", 21), 4, arg, integer_string));
  return(s7_make_integer(sc, (s7_int)cwk_path_get_absolute(cwk_cwk_path_get_absolute_0, cwk_cwk_path_get_absolute_1, cwk_cwk_path_get_absolute_2, cwk_cwk_path_get_absolute_3)));
}


/* -------- cwk_path_get_relative -------- */
static s7_pointer cwk_cwk_path_get_relative(s7_scheme *sc, s7_pointer args)
{
  s7_pointer p, arg;
  char* cwk_cwk_path_get_relative_0;
  char* cwk_cwk_path_get_relative_1;
  char* cwk_cwk_path_get_relative_2;
  size_t cwk_cwk_path_get_relative_3;
  p = args;
  arg = s7_car(p);
  if (s7_is_string(arg))
    cwk_cwk_path_get_relative_0 = (char*)s7_string(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-relative", 21), 1, arg, string_string));
  p = s7_cdr(p);
  arg = s7_car(p);
  if (s7_is_string(arg))
    cwk_cwk_path_get_relative_1 = (char*)s7_string(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-relative", 21), 2, arg, string_string));
  p = s7_cdr(p);
  arg = s7_car(p);
  if (s7_is_string(arg))
    cwk_cwk_path_get_relative_2 = (char*)s7_string(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-relative", 21), 3, arg, string_string));
  p = s7_cdr(p);
  arg = s7_car(p);
  if (s7_is_integer(arg))
    cwk_cwk_path_get_relative_3 = (size_t)s7_integer(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-get-relative", 21), 4, arg, integer_string));
  return(s7_make_integer(sc, (s7_int)cwk_path_get_relative(cwk_cwk_path_get_relative_0, cwk_cwk_path_get_relative_1, cwk_cwk_path_get_relative_2, cwk_cwk_path_get_relative_3)));
}


                  static s7_pointer g_cwk_path_get_basename(s7_scheme *sc, s7_pointer args)
                  {
                    char* path;
                    const char *basename;
                    size_t length;
                    if (s7_is_string(s7_car(args)))
                       path = (char*)s7_string(s7_car(args));
                    else return(s7_wrong_type_error(sc,
                        s7_make_string_wrapper_with_length(sc, "(*libcwalk* 'cwk_path_get_basename)", 14), 1, s7_car(args), string_string)
                         );
                    cwk_path_get_basename(path, &basename, &length);
                    // fprintf(stderr, "basename: '%.*s'\n", (int)length, basename);
                    s7_pointer res = s7_make_string_with_length(sc, basename, length);
                    return(res);
                  }
                 

/* -------- cwk_path_has_extension -------- */
static s7_pointer cwk_cwk_path_has_extension(s7_scheme *sc, s7_pointer args)
{
  s7_pointer p, arg;
  char* cwk_cwk_path_has_extension_0;
  p = args;
  arg = s7_car(p);
  if (s7_is_string(arg))
    cwk_cwk_path_has_extension_0 = (char*)s7_string(arg);
  else return(s7_wrong_type_error(sc, s7_make_string_wrapper_with_length(sc, "cwk:path-has-extension", 22), 0, arg, string_string));
  return(s7_make_boolean(sc, (bool)cwk_path_has_extension(cwk_cwk_path_has_extension_0)));
}


                  static s7_pointer g_cwk_path_normalize(s7_scheme *sc, s7_pointer args)
                  {
                    char* path;
                    char result[FILENAME_MAX];
                    size_t res_len;

                    if (s7_is_string(s7_car(args)))
                       path = (char*)s7_string(s7_car(args));
                    else return(s7_wrong_type_error(sc,
                        s7_make_string_wrapper_with_length(sc, "(*libcwalk* 'cwk_path_normalize)", 14), 1, s7_car(args), string_string)
                         );

                    res_len = cwk_path_normalize(path, result, sizeof(result));
                    // printf("normalized: %s\n", result);
                    s7_pointer res = s7_make_string_with_length(sc, result, res_len);
                    return(res);
                  }
                 
s7_pointer libcwalk_s7_init(s7_scheme *sc);
s7_pointer libcwalk_s7_init(s7_scheme *sc)
{
  s7_pointer cur_env;
  s7_pointer pl_bs, pl_isssi;
  {
    s7_pointer s, b, i;
    s = s7_make_symbol(sc, "string?");
    b = s7_make_symbol(sc, "boolean?");
    i = s7_make_symbol(sc, "integer?");

    pl_bs = s7_make_signature(sc, 2, b, s);
    pl_isssi = s7_make_signature(sc, 5, i, s, s, s, i);
  }

  string_string = s7_make_semipermanent_string(sc, "a string");
  c_pointer_string = s7_make_semipermanent_string(sc, "a c-pointer");
  character_string = s7_make_semipermanent_string(sc, "a character");
  boolean_string = s7_make_semipermanent_string(sc, "a boolean");
  real_string = s7_make_semipermanent_string(sc, "a real");
  complex_string = s7_make_semipermanent_string(sc, "a complex number");
  integer_string = s7_make_semipermanent_string(sc, "an integer");
  cur_env = s7_inlet(sc, s7_nil(sc));
  s7_pointer old_shadow = s7_set_shadow_rootlet(sc, cur_env);

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-normalize"),
            s7_make_typed_function(sc, "cwk:path-normalize", g_cwk_path_normalize, 1, 0, false, "cwk:path_normalize", NULL));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-has-extension"),
            s7_make_typed_function(sc, "cwk:path-has-extension", cwk_cwk_path_has_extension, 1, 0, false, "bool cwk_path_has_extension(char*)", pl_bs));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-get-basename"),
            s7_make_typed_function(sc, "cwk:path-get-basename", g_cwk_path_get_basename, 1, 0, false, "cwk:path_get_basename", NULL));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-get-relative"),
            s7_make_typed_function(sc, "cwk:path-get-relative", cwk_cwk_path_get_relative, 4, 0, false, "size_t cwk_path_get_relative(char* char* char* size_t)", pl_isssi));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-get-absolute"),
            s7_make_typed_function(sc, "cwk:path-get-absolute", cwk_cwk_path_get_absolute, 4, 0, false, "size_t cwk_path_get_absolute(char* char* char* size_t)", pl_isssi));
  s7_set_shadow_rootlet(sc, old_shadow);

  return(cur_env);

}
