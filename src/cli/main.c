# include "main.h"

int main ( int argc, char ** argv )
{
  struct dreki_log_t * log = dreki_log_construct(
    "log/default.txt", (FILE *)NULL,
    "=================================== PROLOGUE ===================================",
    "=================================== EPILOGUE ===================================",
    "... ",
    DREKI_LOG_LEVEL_DEBUG
  );

  if ( !log )
    return EXIT_FAILURE;

  dreki_log_error(log, "Just an error without arguments.");
  dreki_log_alert(log, "Just an alert without arguments.");
  dreki_log_debug(log, "Just a debug message without arguments.");
  dreki_log_trace(log, "Just a trace message without arguments.");

  struct dreki_dev_t * dev = dreki_dev_construct(
    (struct dreki_log_t *)NULL,
    (struct dreki_bus_t *)NULL,
    (dreki_dev_cycle_t)NULL,
    (dreki_dev_drive_t)NULL,
    UINT32_C(0x45005044),
    sizeof(*dev)
  );

  if ( dev ) {
    dreki_log_error(dev->log, "Just a device error without arguments.");
    dreki_log_alert(dev->log, "Just a device alert without arguments.");
    dreki_log_debug(dev->log, "Just a device debug message without arguments.");
    dreki_log_trace(dev->log, "Just a device trace message without arguments.");

    dreki_dev_deconstruct(dev);
  }

  dreki_log_errorf(log, "Just an error with %d arguments.", 1);
  dreki_log_alertf(log, "Just an alert with %d arguments.", 3);
  dreki_log_debugf(log, "Just a debug message with %d arguments.", 5);
  dreki_log_tracef(log, "Just a trace message with %d arguments.", 7);

  dreki_log_fatal(log, "Just a fatal error without arguments.");
  dreki_log_fatalf(log, "Just a fatal error with %d arguments.", 9);

  dreki_log_deconstruct(log);

  return EXIT_SUCCESS;
}