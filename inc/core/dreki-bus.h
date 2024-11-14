# ifndef __CORE_DREKI_BUS_H__
#   define __CORE_DREKI_BUS_H__

#   include "dreki.h"
#   include "dreki-dev.h"

typedef bool ( * dreki_bus_attach_t ) (
  struct dreki_bus_t * /* self */,
  struct dreki_dev_t * /* dev  */,
  uint32_t *           /* idx  */
);

typedef bool ( * dreki_bus_detach_t ) (
  struct dreki_bus_t * /* self */,
  struct dreki_dev_t * /* dev  */,
  uint32_t             /* idx  */
);

struct dreki_bus_t {
  dreki_dev();
  dreki_bus_attach_t attach;
  dreki_bus_detach_t detach;
};

#   define dreki_bus()       struct dreki_bus_t super_bus
#   define dreki_bus_of(obj) ( &(obj)->super_bus )

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
);

__DREKI_CORE__
void dreki_bus_deconstruct (
  struct dreki_bus_t * self
);

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
);

__DREKI_CORE__
void dreki_bus_deinitialize (
  struct dreki_bus_t * self
);

#   define dreki_bus_log(self) dreki_dev_of(self)->log
#   define dreki_bus_cycle(self, cycles)                                       \
  dreki_dev_cycle(dreki_dev_of(self), (cycles))
#   define dreki_bus_drive(self, func, size, data)                             \
  dreki_dev_drive(dreki_dev_of(self), (func), (size), (data))
#   define dreki_bus_attach(self, dev, idx)                                    \
  ( (self)->attach ? (self)->attach((self), (dev), (idx)) : false )
#   define dreki_bus_detach(self, dev, idx)                                    \
  ( (self)->detach ? (self)->detach((self), (dev), (idx)) : false )

# endif /* __CORE_DREKI_BUS_H__ */
