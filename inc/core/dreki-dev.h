# ifndef __CORE_DREKI_DEV_H__
#   define __CORE_DREKI_DEV_H__

#   include "dreki.h"

typedef uint32_t ( * dreki_dev_cycle_t ) (
  struct dreki_dev_t * /* self   */,
  uint32_t             /* cycles */
);

typedef uint32_t ( * dreki_dev_drive_t ) (
  struct dreki_dev_t * /* self   */,
  uint32_t             /* func   */,
  uint32_t             /* size   */,
  uint8_t *            /* data   */
);

struct dreki_dev_t {
  struct dreki_log_t * log;
  bool                 __owns_log__;
  struct dreki_bus_t * bus;
  dreki_dev_cycle_t    cycle;
  dreki_dev_drive_t    drive;
  uint32_t             signature;
  uint32_t             unique_id;
};

#   define dreki_dev()       struct dreki_dev_t super_dev
#   define dreki_dev_of(obj) ( &(obj)->super_dev )

__DREKI_CORE__
struct dreki_dev_t * dreki_dev_construct (
  struct dreki_log_t * log,
  struct dreki_bus_t * bus,
  dreki_dev_cycle_t    cycle,
  dreki_dev_drive_t    drive,
  uint32_t             signature,
  size_t               __sizeof__
);

__DREKI_CORE__
void dreki_dev_deconstruct (
  struct dreki_dev_t * self
);

__DREKI_CORE__
bool dreki_dev_initialize (
  struct dreki_dev_t * self,
  struct dreki_log_t * log,
  struct dreki_bus_t * bus,
  dreki_dev_cycle_t    cycle,
  dreki_dev_drive_t    drive,
  uint32_t             signature
);

__DREKI_CORE__
void dreki_dev_deinitialize (
  struct dreki_dev_t * self
);

#   define dreki_dev_log(self) (self)->log
#   define dreki_dev_cycle(self, cycles)                                       \
  ( (self)->cycle ? (self)->cycle((self), (cycles)) : 0 )
#   define dreki_dev_drive(self, func, size, data)                             \
  ( (self)->drive ? (self)->drive((self), (func), (size), (data)) : 0 )

# endif /* __CORE_DREKI_DEV_H__ */
