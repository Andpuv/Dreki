# include "../../inc/core/dreki-dev.h"
# include "../../inc/core/dreki-log.h"
# include <assert.h>
# include <string.h>
# include <errno.h>

__DREKI_CORE__
struct dreki_dev_t * dreki_dev_construct (
  struct dreki_log_t * log,
  struct dreki_bus_t * bus,
  dreki_dev_cycle_t    cycle,
  dreki_dev_drive_t    drive,
  uint32_t             signature,
  size_t               __sizeof__
)
{
  assert(sizeof(struct dreki_dev_t) <= __sizeof__);

  struct dreki_dev_t * self =
    (struct dreki_dev_t *)malloc(
      __sizeof__
    );

  if ( !self ) {
    if ( !log ) {
      log = dreki_log_construct(
        (char const *)NULL,
        stderr,
        (char const *)NULL,
        (char const *)NULL,
        (char const *)NULL,
        DREKI_LOG_LEVEL_ERROR
      );

      if ( !log )
        return self;
    }

    dreki_log_fatalf(log,
      "Cannot construct the device (size: %zu bytes): %s.\n",
      __sizeof__,
      strerror(errno)
    );
  }

  if ( dreki_dev_initialize(self, log, bus, cycle, drive, signature) )
    return self;

  free(self);
  return (struct dreki_dev_t *)NULL;
}

__DREKI_CORE__
void dreki_dev_deconstruct (
  struct dreki_dev_t * self
)
{
  dreki_dev_deinitialize(self);
  free(self);
}

__DREKI_CORE__
bool dreki_dev_initialize (
  struct dreki_dev_t * self,
  struct dreki_log_t * log,
  struct dreki_bus_t * bus,
  dreki_dev_cycle_t    cycle,
  dreki_dev_drive_t    drive,
  uint32_t             signature
)
{
  assert(self);

  uint32_t unique_id = dreki_unique_id();

  if ( !log ) {
    char const filename [] = {
      '.', '/', 'l', 'o', 'g', '/',
      '0' + (int)( ( signature >> 28 ) & UINT32_C(0xF) ),
      '0' + (int)( ( signature >> 24 ) & UINT32_C(0xF) ),
      '0' + (int)( ( signature >> 20 ) & UINT32_C(0xF) ),
      '0' + (int)( ( signature >> 16 ) & UINT32_C(0xF) ),
      '0' + (int)( ( signature >> 12 ) & UINT32_C(0xF) ),
      '0' + (int)( ( signature >>  8 ) & UINT32_C(0xF) ),
      '0' + (int)( ( signature >>  4 ) & UINT32_C(0xF) ),
      '0' + (int)( ( signature >>  0 ) & UINT32_C(0xF) ),
      '_',
      '0' + (int)( ( unique_id >> 28 ) & UINT32_C(0xF) ),
      '0' + (int)( ( unique_id >> 24 ) & UINT32_C(0xF) ),
      '0' + (int)( ( unique_id >> 20 ) & UINT32_C(0xF) ),
      '0' + (int)( ( unique_id >> 16 ) & UINT32_C(0xF) ),
      '0' + (int)( ( unique_id >> 12 ) & UINT32_C(0xF) ),
      '0' + (int)( ( unique_id >>  8 ) & UINT32_C(0xF) ),
      '0' + (int)( ( unique_id >>  4 ) & UINT32_C(0xF) ),
      '0' + (int)( ( unique_id >>  0 ) & UINT32_C(0xF) ),
      '.', 't', 'x', 't', '\0'
    };

    log = dreki_log_construct(
      filename,
      (FILE *)NULL,
      (char const *)NULL,
      (char const *)NULL,
      (char const *)NULL,
# if defined(NDEBUG) && !defined(DEBUG)
      DREKI_LOG_LEVEL_ALERT
# else
      DREKI_LOG_LEVEL_DEBUG
# endif
    );

    if ( !log )
      return self;

    self->__owns_log__ = true;
  } else {
    self->__owns_log__ = false;
  }

  self->log       = log;
  self->bus       = bus;
  self->cycle     = cycle;
  self->drive     = drive;
  self->signature = signature;
  self->unique_id = unique_id;

  return true;
}

__DREKI_CORE__
void dreki_dev_deinitialize (
  struct dreki_dev_t * self
)
{
  assert(self);

  if ( self->__owns_log__ ) {
    dreki_log_deconstruct(self->log);
  }

  self->log          = (struct dreki_log_t *)NULL;
  self->__owns_log__ = false;
  self->bus          = (struct dreki_bus_t *)NULL;
  self->cycle        = (dreki_dev_cycle_t)NULL;
  self->drive        = (dreki_dev_drive_t)NULL;
  self->signature    = UINT32_C(0);
  self->unique_id    = UINT32_C(0);
}
