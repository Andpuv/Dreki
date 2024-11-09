# ifndef __CORE_DREKI_H__
#   define __CORE_DREKI_H__

#   include <stdio.h>
#   include <stdlib.h>
#   include <stddef.h>
#   include <stdint.h>
#   include <stdarg.h>
#   include <stdbool.h>

#   if defined(_WIN32)
#     define __DREKI_CORE_EXPORT__ __declspec(dllexport)
#     define __DREKI_CORE_IMPORT__ __declspec(dllimport)
#   else
#     define __DREKI_CORE_EXPORT__ __attribute__((visibility("default")))
#     define __DREKI_CORE_IMPORT__ __attribute__((visibility("default")))
#   endif

#   if defined(__DREKI_CORE_STANDS_ALONE__)
#     define __DREKI_CORE__
#   else
#     if defined(__DREKI_CORE_BUILD__)
#       define __DREKI_CORE__ __DREKI_CORE_EXPORT__
#     else
#       define __DREKI_CORE__ __DREKI_CORE_IMPORT__
#     endif
#   endif

__DREKI_CORE__
uint32_t dreki_unique_id ( void );

struct dreki_log_t;
struct dreki_dev_t;
struct dreki_bus_t;

#   include "dreki-log.h"
#   include "dreki-dev.h"

# endif /* __CORE_DREKI_H__ */