;;; libcwalk_clib.scm
;;;
;;; generate libcwalk_s7.c, s7 bindings for libcwalk
;;; https://github.com/likle/cwalk

(require clibgen.scm) ;; cload.scm)
(provide 'libcwalk_clibgen.scm)

;; if loading from a different directory, pass that info to C
(let ((directory (let ((current-file (port-filename)))
		   (and (memv (current-file 0) '(#\/ #\~))
			(substring current-file 0 (- (length current-file) 9))))))
  (when (and directory (not (member directory *load-path*)))
    (set! *load-path* (cons directory *load-path*))))


(if (not (defined? '*libcwalk*))
    ;; (define *libcwalk*
      (with-let (unlet)
	(set! *libraries* (cons (cons "libcwalk.scm" (curlet)) *libraries*))
        ;; IMPORTANT! if *cload-library-name* is defined, then clibgen will
	;; (set! *cload-library-name* "*libcwalk*")

	(c-define
         '(
           (in-C "static int cwk_segment_type_tag = 0;")

           (C-init "
  cwk_segment_type_tag = s7_make_c_type(sc, \"cwk_segment\");
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
")

           (size_t cwk_path_get_absolute
                   (char* ;; base
                    char* ;; path,
                    char* ;; buffer,
                    size_t;; buffer_size
                    ))

           (size_t cwk_path_get_relative
                   (char*  ;; base_directory,
                    char*  ;; path,
                    char*  ;; buffer,
                    size_t ;; buffer_size
                    ))

           ;; CWK_PUBLIC size_t cwk_path_join(const char *path_a, const char *path_b, char *buffer, size_t buffer_size);

           ;; CWK_PUBLIC size_t cwk_path_join_multiple(const char **paths, char *buffer, size_t buffer_size);

           ;; CWK_PUBLIC void cwk_path_get_root(const char *path, size_t *length);

           ;; CWK_PUBLIC size_t cwk_path_change_root(const char *path, const char *new_root, char *buffer, size_t buffer_size);

           ;; CWK_PUBLIC bool cwk_path_is_absolute(const char *path);

           ;; CWK_PUBLIC bool cwk_path_is_relative(const char *path);

           ;; void cwk_path_get_basename(const char *path, const char **basename, size_t *length);
	   (in-C "
static s7_pointer g_cwk_path_get_basename(s7_scheme *sc, s7_pointer args)
{
    char* path;
    const char *basename;
    size_t length;
    if (s7_is_string(s7_car(args)))
        path = (char*)s7_string(s7_car(args));
    else return(s7_wrong_type_error(sc,
                                    s7_make_string_wrapper_with_length(sc, \"(*libcwalk* 'cwk_path_get_basename)\", 14), 1, s7_car(args), string_string)
                );
    cwk_path_get_basename(path, &basename, &length);
    // fprintf(stderr, \"basename: '%.*s'\\n\", (int)length, basename);
    s7_pointer res = s7_make_string_with_length(sc, basename, length);
    return(res);
}")

	   (C-function ("cwk:basename" g_cwk_path_get_basename "" 1))

           ;; CWK_PUBLIC size_t cwk_path_change_basename(const char *path, const char *new_basename, char *buffer, size_t buffer_size);

           ;; CWK_PUBLIC void cwk_path_get_dirname(const char *path, size_t *length);
	   (in-C "
static s7_pointer g_cwk_path_get_dirname(s7_scheme *sc, s7_pointer args)
{
    char* path;
    size_t length;
    if (s7_is_string(s7_car(args)))
        path = (char*)s7_string(s7_car(args));
    else return(s7_wrong_type_error(sc,
                                    s7_make_string_wrapper_with_length(sc, \"(*libcwalk* 'cwk_path_get_dirname)\", 14), 1, s7_car(args), string_string)
                );
    cwk_path_get_dirname(path, &length);
    ;; fprintf(stderr, \"dirname: '%.*s'\\n\", (int)length, path);
    s7_pointer res = s7_make_string_with_length(sc, path, length);
    return(res);
}")

	   (C-function ("cwk:dirname" g_cwk_path_get_dirname "" 1))

           ;; CWK_PUBLIC bool cwk_path_get_extension(const char *path, const char **extension, size_t *length);

           ;; CWK_PUBLIC bool cwk_path_has_extension(const char *path);
           (bool cwk_path_has_extension (char*))

           ;; CWK_PUBLIC size_t cwk_path_change_extension(const char *path, const char *new_extension, char *buffer, size_t buffer_size);

           ;; CWK_PUBLIC size_t cwk_path_normalize(const char *path, char *buffer, size_t buffer_size);
	   (in-C "
static s7_pointer g_cwk_path_normalize(s7_scheme *sc, s7_pointer args)
{
    char* path;
    char result[FILENAME_MAX];
    size_t res_len;

    if (s7_is_string(s7_car(args)))
        path = (char*)s7_string(s7_car(args));
    else return(s7_wrong_type_error(sc,
                                    s7_make_string_wrapper_with_length(sc, \"(*libcwalk* 'cwk_path_normalize)\", 14), 1, s7_car(args), string_string)
                );

    res_len = cwk_path_normalize(path, result, sizeof(result));
    // printf(\"normalized: %s\\n\", result);
    s7_pointer res = s7_make_string_with_length(sc, result, res_len);
    return(res);
}")

	   (C-function ("cwk:normalize" g_cwk_path_normalize "" 1))

           ;; CWK_PUBLIC size_t cwk_path_get_intersection(const char *path_base, const char *path_other);

           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
           ;; segmentation

           ;; s7_c_type_set_mark sets the function that is called by
           ;; the GC during its marking phase. Any s7_pointer value
           ;; local to your C struct should be marked explicitly at
           ;; this time, or the GC will free it. Use s7_mark for this
           ;; (see mark_dax). Don't allocate any s7 objects in the
           ;; mark function (otherwise you'll get a recursive call of
           ;; the GC).

           ;; So we don't need this unless we put an s7 object in cwk_segment?
           (in-C "
static s7_pointer mark_cwk_segment(s7_scheme *sc, s7_pointer obj)
{
  (void)sc; (void)obj;
  // struct cwk_segment *o = (struct cwk_segment *)s7_c_object_value(obj);
  // s7_mark(o->data); // dax *o->data is an s7_pointer
  return(NULL);
}
")

           (in-C "
static s7_pointer free_cwk_segment(s7_scheme *sc, s7_pointer obj)
{
  (void)sc;
  free(s7_c_object_value(obj));
  return(NULL);
}")

           ;; CWK_PUBLIC bool cwk_path_get_first_segment(const char *path, struct cwk_segment *segment);
	   (in-C "
static s7_pointer g_cwk_path_get_first_segment(s7_scheme *sc, s7_pointer args)
{
    char* path;
    if (s7_is_string(s7_car(args)))
        path = (char*)s7_string(s7_car(args));
    else return(s7_wrong_type_error(sc,
                                    s7_make_string_wrapper_with_length(sc, \"(cwk:path-get-first-segment)\", 28), 1, s7_car(args), string_string)
                );

    struct cwk_segment *segment;
    segment = (struct cwk_segment *)malloc(sizeof(struct cwk_segment));
    s7_pointer res;

    if(!cwk_path_get_first_segment(path, segment)) {
        // res = s7_make_string_with_length(sc, segment->begin, segment->size);
        res = s7_make_string(sc, \"\");
    } else {
        // fprintf(stderr, \"segment: '%.*s'\\n\", segment->size, segment);
        res = s7_make_string_with_length(sc, segment->begin, segment->size);
        // res = segment;
    }
    return(res);

    s7_pointer r = (s7_make_c_object(sc, cwk_segment_type_tag, (void *)segment));
    // return(r);
    (void)r;

}")

	   (C-function ("cwk:first-segment" g_cwk_path_get_first_segment "" 1))

           ;; CWK_PUBLIC bool cwk_path_get_last_segment(const char *path, struct cwk_segment *segment);

           ;; CWK_PUBLIC bool cwk_path_get_next_segment(struct cwk_segment *segment);

           ;; CWK_PUBLIC bool cwk_path_get_previous_segment(struct cwk_segment *segment);

           ;; CWK_PUBLIC enum cwk_segment_type cwk_path_get_segment_type(const struct cwk_segment *segment);

           ;; CWK_PUBLIC size_t cwk_path_change_segment(struct cwk_segment *segment, const char *value, char *buffer, size_t buffer_size);

           ;; CWK_PUBLIC bool cwk_path_is_separator(const char *str);

           ;; CWK_PUBLIC enum cwk_path_style cwk_path_guess_style(const char *path);

           ;; CWK_PUBLIC void cwk_path_set_style(enum cwk_path_style style);

           ;; CWK_PUBLIC enum cwk_path_style cwk_path_get_style(void);

	   ;; (C-macro (int (RTLD_LAZY RTLD_NOW RTLD_BINDING_MASK RTLD_NOLOAD RTLD_DEEPBIND RTLD_GLOBAL RTLD_LOCAL RTLD_NODELETE)))
;; enum cwk_path_style
;; {
;;   CWK_STYLE_WINDOWS,
;;   CWK_STYLE_UNIX
;; };
           (C-macro (int (CWK_STYLE_WINDOWS CWK_STYLE_UNIX CWK_NORMAL_SEG CWK_CURRENT_SEG CWK_BACK_SEG)))
           )

	 "cwk" ;; prefix to add
         "cwk_"    ;; strip-prefix
         (list "cwalk.h")
         ;; "" ""
         "libcwalk_s7")
	(curlet))
      ;; )
)

;; *libcwalk*
;; the loader will return *libcwalk*
