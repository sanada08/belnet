#pragma once
#include "belnet_context.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /// get a free()-able null terminated string that holds our .beldex address
  /// returns NULL if we dont have one right now
  char* EXPORT
  belnet_address(struct belnet_context*);
#ifdef __cplusplus
}
#endif
