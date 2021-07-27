#pragma once
#include "belnet_export.h"
#ifdef __cplusplus
extern "C"
{
#endif

  /// change our network id globally across all contexts
  void EXPORT
  belnet_set_netid(const char*);

  /// get our current netid
  /// must be free()'d after use
  const char* EXPORT
  belnet_get_netid();

  /// set log level
  /// possible values: trace, debug, info, warn, error, none
  /// return 0 on success
  /// return non zero on fail
  int EXPORT
  belnet_log_level(const char*);

#ifdef __cplusplus
}
#endif
