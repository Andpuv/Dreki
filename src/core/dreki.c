# include "../../inc/core/dreki.h"

__DREKI_CORE__
uint32_t dreki_unique_id ( void )
{
  static uint32_t unique_id = UINT32_C(0);

  if ( UINT32_MAX != unique_id )
    /* `unique_id = 0` means invalid ID. */
    return ++unique_id;

  /* /discard/ */ fprintf(stderr,
    "[ FATAL ] Unique ID overflowed (maximum unique ID: 0x%08X).\n",
    unique_id
  );

  exit(EXIT_FAILURE);
}