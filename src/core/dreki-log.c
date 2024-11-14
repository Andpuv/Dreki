# include "../../inc/core/dreki-log.h"
# include <assert.h>
# include <string.h>
# include <errno.h>

__DREKI_CORE__
struct dreki_log_t * dreki_log_construct (
  char const * filename,
  FILE *       file,
  char const * prologue,
  char const * epilogue,
  char const * prompt,
  int          level
)
{
  struct dreki_log_t * self =
    (struct dreki_log_t *)malloc(
      sizeof(*self)
    );

  if ( !self ) {
    /* /discard/ */ fprintf(stderr,
      "[ FATAL ] Cannot construct the logger (size: %zu bytes):\n"
      "          %s.\n",
      sizeof(*self),
      strerror(errno)
    );

    exit(EXIT_FAILURE);
  }

  if (
    dreki_log_initialize(self,
      filename,
      file,
      prologue,
      epilogue,
      prompt,
      level
    )
  )
    return self;

  free(self);
  return (struct dreki_log_t *)NULL;
}

__DREKI_CORE__
void dreki_log_deconstruct (
  struct dreki_log_t * self
)
{
  dreki_log_deinitialize(self);
  free(self);
}

__DREKI_CORE__
bool dreki_log_initialize (
  struct dreki_log_t * self,
  char const *         filename,
  FILE *               file,
  char const *         prologue,
  char const *         epilogue,
  char const *         prompt,
  int                  level
)
{
  assert(self);

  if ( level < DREKI_LOG_LEVEL_MIN || DREKI_LOG_LEVEL_MAX < level ) {
    /* /discard/ */ fprintf(stderr,
      "[ ERROR ] Cannot construct the logger:\n"
      "          level %d is out of range (minimum: %d, maximum: %d).\n",
      level,
      DREKI_LOG_LEVEL_MIN,
      DREKI_LOG_LEVEL_MAX
    );

    return false;
  }

  if ( !file && filename ) {
    file = fopen(filename, "w");
  }

  if ( !file ) {
    file = stderr;
  }

  self->file     = file;
  self->prologue = prologue;
  self->epilogue = epilogue;
  self->prompt   = prompt;
  self->level    = level;

  if ( self->prologue ) {
    /* /discard/ */ fprintf(self->file, "%s\n", self->prologue);
    /* /discard/ */ fflush(self->file);
  }

  return true;
}

__DREKI_CORE__
void dreki_log_deinitialize (
  struct dreki_log_t * self
)
{
  assert(self);

  if ( self->epilogue ) {
    /* /discard/ */ fprintf(self->file, "%s\n", self->epilogue);
    /* /discard/ */ fflush(self->file);
  }

  if ( stderr != self->file && stdout != self->file ) {
    /* /discard/ */ fclose(self->file);
  }

  self->file     = (FILE *)NULL;
  self->prologue = (char *)NULL;
  self->epilogue = (char *)NULL;
  self->prompt   = (char *)NULL;
  self->level    = DREKI_LOG_LEVEL_MIN;
}

__DREKI_CORE__
void dreki_log_vreportf (
  struct dreki_log_t * self,
  int                  level,
  char const *         format,
  va_list              args
)
{
  assert(self && format);

  if ( level < DREKI_LOG_LEVEL_MIN || DREKI_LOG_LEVEL_MAX < level ) {
    level = DREKI_LOG_LEVEL_UNDEF;
  }

  if ( self->level < level )
    return;

  static char const * levels [] = {
    "?????",
    "FATAL",
    "ERROR",
    "ALERT",
    "DEBUG",
    "TRACE"
  };

  /* /discard/ */ fprintf(self->file, "%s", self->prompt);
  /* /discard/ */ fprintf(self->file, "[ %s ] ", levels[ level ]);
  /* /discard/ */ vfprintf(self->file, format, args);
  /* /discard/ */ fprintf(self->file, "\n");

  if ( DREKI_LOG_LEVEL_FATAL == level ) {
    /* /discard/ */ fflush(self->file);
    dreki_log_deinitialize(self);

    exit(EXIT_FAILURE);
  }
}

__DREKI_CORE__
void dreki_log_reportf (
  struct dreki_log_t * self,
  int                  level,
  char const *         format,
  ...
)
{
  va_list args;
  va_start(args, format);
  dreki_log_vreportf(self, level, format, args);
  va_end(args);
}
