#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cwalk.h"
#include "s7.h"

static s7_pointer c_pointer_string, string_string, character_string, boolean_string, real_string, complex_string, integer_string;

static int cwk_segment_type_tag = 0;

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

static s7_pointer g_cwk_path_get_dirname(s7_scheme *sc, s7_pointer args)
{
    char* path;
    size_t length;
    if (s7_is_string(s7_car(args)))
        path = (char*)s7_string(s7_car(args));
    else return(s7_wrong_type_error(sc,
                                    s7_make_string_wrapper_with_length(sc, "(*libcwalk* 'cwk_path_get_dirname)", 14), 1, s7_car(args), string_string)
                );
    cwk_path_get_dirname(path, &length);
    ;; fprintf(stderr, "dirname: '%.*s'\n", (int)length, path);
    s7_pointer res = s7_make_string_with_length(sc, path, length);
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

static s7_pointer mark_cwk_segment(s7_scheme *sc, s7_pointer obj)
{
  (void)sc; (void)obj;
  // struct cwk_segment *o = (struct cwk_segment *)s7_c_object_value(obj);
  // s7_mark(o->data); // dax *o->data is an s7_pointer
  return(NULL);
}


static s7_pointer free_cwk_segment(s7_scheme *sc, s7_pointer obj)
{
  (void)sc;
  free(s7_c_object_value(obj));
  return(NULL);
}

static s7_pointer g_cwk_path_get_first_segment(s7_scheme *sc, s7_pointer args)
{
    char* path;
    if (s7_is_string(s7_car(args)))
        path = (char*)s7_string(s7_car(args));
    else return(s7_wrong_type_error(sc,
                                    s7_make_string_wrapper_with_length(sc, "(cwk:path-get-first-segment)", 28), 1, s7_car(args), string_string)
                );

    struct cwk_segment *segment;
    segment = (struct cwk_segment *)malloc(sizeof(struct cwk_segment));
    s7_pointer res;

    if(!cwk_path_get_first_segment(path, segment)) {
        // res = s7_make_string_with_length(sc, segment->begin, segment->size);
        res = s7_make_string(sc, "");
    } else {
        // fprintf(stderr, "segment: '%.*s'\n", segment->size, segment);
        res = s7_make_string_with_length(sc, segment->begin, segment->size);
        // res = segment;
    }
    return(res);

    s7_pointer r = (s7_make_c_object(sc, cwk_segment_type_tag, (void *)segment));
    // return(r);
    (void)r;

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
  
  cwk_segment_type_tag = s7_make_c_type(sc, "cwk_segment");
  s7_c_type_set_gc_free(sc, cwk_segment_type_tag, free_cwk_segment);
  s7_c_type_set_gc_mark(sc, cwk_segment_type_tag, mark_cwk_segment); // Not needed?
/*
  s7_c_type_set_is_equal(sc, cwk_segment_type_tag, cwk_segment_is_equal);
  s7_c_type_set_to_string(sc, cwk_segment_type_tag, cwk_segment_to_string);
  s7_c_type_set_ref      (sc, cwk_segment_type_tag, cwk_segment_ref);
  s7_c_type_set_set      (sc, cwk_segment_type_tag, cwk_segment_set);
  s7_c_type_set_to_list  (sc, cwk_segment_type_tag, cwk_segment_to_list);
  s7_c_type_set_to_string(sc, cwk_segment_type_tag, cwk_segment_to_string);
  s7_c_type_set_length   (sc, cwk_segment_type_tag, cwk_segment_length);

void s7_c_type_set_getter       (s7_scheme *sc, s7_int type, s7_pointer getter);
void s7_c_type_set_setter       (s7_scheme *sc, s7_int type, s7_pointer setter);

void s7_c_type_set_copy         (s7_scheme *sc, s7_int type, s7_pointer (*copy)      (s7_scheme *sc, s7_pointer args));
void s7_c_type_set_fill         (s7_scheme *sc, s7_int type, s7_pointer (*fill)      (s7_scheme *sc, s7_pointer args));
void s7_c_type_set_reverse      (s7_scheme *sc, s7_int type, s7_pointer (*reverse)   (s7_scheme *sc, s7_pointer args));
*/


#ifdef CWK_BACK_SEG
  s7_define(sc, cur_env, s7_make_symbol(sc, "cwk:CWK_BACK_SEG"), s7_make_integer(sc, (s7_int)CWK_BACK_SEG));
#endif
#ifdef CWK_CURRENT_SEG
  s7_define(sc, cur_env, s7_make_symbol(sc, "cwk:CWK_CURRENT_SEG"), s7_make_integer(sc, (s7_int)CWK_CURRENT_SEG));
#endif
#ifdef CWK_NORMAL_SEG
  s7_define(sc, cur_env, s7_make_symbol(sc, "cwk:CWK_NORMAL_SEG"), s7_make_integer(sc, (s7_int)CWK_NORMAL_SEG));
#endif
#ifdef CWK_STYLE_UNIX
  s7_define(sc, cur_env, s7_make_symbol(sc, "cwk:CWK_STYLE_UNIX"), s7_make_integer(sc, (s7_int)CWK_STYLE_UNIX));
#endif
#ifdef CWK_STYLE_WINDOWS
  s7_define(sc, cur_env, s7_make_symbol(sc, "cwk:CWK_STYLE_WINDOWS"), s7_make_integer(sc, (s7_int)CWK_STYLE_WINDOWS));
#endif

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:first-segment"),
            s7_make_typed_function(sc, "cwk:first-segment", g_cwk_path_get_first_segment, 1, 0, false, "cwk:first-segment", NULL));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:normalize"),
            s7_make_typed_function(sc, "cwk:normalize", g_cwk_path_normalize, 1, 0, false, "cwk:normalize", NULL));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-has-extension"),
            s7_make_typed_function(sc, "cwk:path-has-extension", cwk_cwk_path_has_extension, 1, 0, false, "bool cwk_path_has_extension(char*)", pl_bs));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:dirname"),
            s7_make_typed_function(sc, "cwk:dirname", g_cwk_path_get_dirname, 1, 0, false, "cwk:dirname", NULL));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:basename"),
            s7_make_typed_function(sc, "cwk:basename", g_cwk_path_get_basename, 1, 0, false, "cwk:basename", NULL));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-get-relative"),
            s7_make_typed_function(sc, "cwk:path-get-relative", cwk_cwk_path_get_relative, 4, 0, false, "size_t cwk_path_get_relative(char* char* char* size_t)", pl_isssi));

  s7_define(sc, cur_env,
            s7_make_symbol(sc, "cwk:path-get-absolute"),
            s7_make_typed_function(sc, "cwk:path-get-absolute", cwk_cwk_path_get_absolute, 4, 0, false, "size_t cwk_path_get_absolute(char* char* char* size_t)", pl_isssi));
  s7_set_shadow_rootlet(sc, old_shadow);

  return(cur_env);

}
