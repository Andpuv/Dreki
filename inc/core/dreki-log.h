# ifndef __CORE_DREKI_LOG_H__
#   define __CORE_DREKI_LOG_H__

enum {
  DREKI_LOG_LEVEL_MIN = INT32_C(0),
  DREKI_LOG_LEVEL_MAX = INT32_C(5),
  DREKI_LOG_N_LEVELS,

  DREKI_LOG_LEVEL_UNDEF = DREKI_LOG_LEVEL_MIN + INT32_C(0),
  DREKI_LOG_LEVEL_FATAL = DREKI_LOG_LEVEL_MIN + INT32_C(1),
  DREKI_LOG_LEVEL_ERROR = DREKI_LOG_LEVEL_MIN + INT32_C(2),
  DREKI_LOG_LEVEL_ALERT = DREKI_LOG_LEVEL_MIN + INT32_C(3),
  DREKI_LOG_LEVEL_DEBUG = DREKI_LOG_LEVEL_MIN + INT32_C(4),
  DREKI_LOG_LEVEL_TRACE = DREKI_LOG_LEVEL_MIN + INT32_C(5)
};

struct dreki_log_t {
  FILE *       file;
  char const * prologue;
  char const * epilogue;
  char const * prompt;
  int          level;
};

__DREKI_CORE__
struct dreki_log_t * dreki_log_construct (
  char const * filename,
  FILE *       file,
  char const * prologue,
  char const * epilogue,
  char const * prompt,
  int          level
);

__DREKI_CORE__
void dreki_log_deconstruct (
  struct dreki_log_t * self
);

__DREKI_CORE__
bool dreki_log_initialize (
  struct dreki_log_t * self,
  char const *         filename,
  FILE *               file,
  char const *         prologue,
  char const *         epilogue,
  char const *         prompt,
  int                  level
);

__DREKI_CORE__
void dreki_log_deinitialize (
  struct dreki_log_t * self
);

__DREKI_CORE__
void dreki_log_vreportf (
  struct dreki_log_t * self,
  int                  level,
  char const *         format,
  va_list              args
);

__DREKI_CORE__
void dreki_log_reportf (
  struct dreki_log_t * self,
  int                  level,
  char const *         format,
  ...
);

#   define dreki_log_vfatalf(self, format, args)                               \
  dreki_log_vreportf((self), DREKI_LOG_LEVEL_FATAL, (format), (args))
#   define dreki_log_fatalf(self, format, ...)                                 \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_FATAL, (format), __VA_ARGS__)
#   define dreki_log_fatal(self, message)                                      \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_FATAL, (message))
#   define dreki_log_verrorf(self, format, args)                               \
  dreki_log_vreportf((self), DREKI_LOG_LEVEL_ERROR, (format), (args))
#   define dreki_log_errorf(self, format, ...)                                 \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_ERROR, (format), __VA_ARGS__)
#   define dreki_log_error(self, message)                                      \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_ERROR, (message))
#   define dreki_log_valertf(self, format, args)                               \
  dreki_log_vreportf((self), DREKI_LOG_LEVEL_ALERT, (format), (args))
#   define dreki_log_alertf(self, format, ...)                                 \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_ALERT, (format), __VA_ARGS__)
#   define dreki_log_alert(self, message)                                      \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_ALERT, (message))

#   if defined(NDEBUG) && !defined(DEBUG)
#     define dreki_log_vdebugf(self, format, args) do {} while ( false )
#     define dreki_log_debugf(self, format, ...)   do {} while ( false )
#     define dreki_log_debug(self, message)        do {} while ( false )
#     define dreki_log_vtracef(self, format, args) do {} while ( false )
#     define dreki_log_tracef(self, format, ...)   do {} while ( false )
#     define dreki_log_trace(self, message)        do {} while ( false )
#   else
#     define dreki_log_vdebugf(self, format, args)                             \
  dreki_log_vreportf((self), DREKI_LOG_LEVEL_DEBUG, (format), (args))
#     define dreki_log_debugf(self, format, ...)                               \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_DEBUG, (format), __VA_ARGS__)
#     define dreki_log_debug(self, message)                                    \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_DEBUG, (message))
#     define dreki_log_vtracef(self, format, args)                             \
  dreki_log_vreportf((self), DREKI_LOG_LEVEL_TRACE, (format), (args))
#     define dreki_log_tracef(self, format, ...)                               \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_TRACE, (format), __VA_ARGS__)
#     define dreki_log_trace(self, message)                                    \
  dreki_log_reportf((self), DREKI_LOG_LEVEL_TRACE, (message))
#   endif

# endif /* __CORE_DREKI_LOG_H__ */