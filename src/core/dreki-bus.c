# include "../../inc/core/dreki-bus.h"
# include <assert.h>

__DREKI_CORE__
struct dreki_bus_t * dreki_bus_construct (
  struct dreki_log_t * log,
  struct dreki_bus_t * bus,
  dreki_dev_cycle_t    cycle,
  dreki_dev_drive_t    drive,
  uint32_t             signature,
  dreki_bus_attach_t   attach,
  dreki_bus_detach_t   detach,
  size_t               __sizeof__
)
{
  assert(sizeof(struct dreki_bus_t) <= __sizeof__);

  struct dreki_bus_t * self =
    (struct dreki_bus_t *)dreki_dev_construct(
      log,
      bus,
      cycle,
      drive,
      signature,
      __sizeof__
    );

  if ( !self )
    return self;

  self->attach = attach;
  self->detach = detach;

  return self;
}

__DREKI_CORE__
void dreki_bus_deconstruct (
  struct dreki_bus_t * self
)
{
  dreki_dev_deconstruct(dreki_dev_of(self));
}

__DREKI_CORE__
bool dreki_bus_initialize (
  struct dreki_bus_t * self,
  struct dreki_log_t * log,
  struct dreki_bus_t * bus,
  dreki_dev_cycle_t    cycle,
  dreki_dev_drive_t    drive,
  uint32_t             signature,
  dreki_bus_attach_t   attach,
  dreki_bus_detach_t   detach
)
{
  assert(self);

  if (
    !dreki_dev_initialize(dreki_dev_of(self),
      log,
      bus,
      cycle,
      drive,
      signature
    )
  )
    return false;

  self->attach = attach;
  self->detach = detach;

  return true;
}

__DREKI_CORE__
void dreki_bus_deinitialize (
  struct dreki_bus_t * self
)
{
  assert(self);

  self->attach = (dreki_bus_attach_t)NULL;
  self->detach = (dreki_bus_detach_t)NULL;

  dreki_dev_deinitialize(dreki_dev_of(self));
}
