#pragma once

#include "belnet_export.h"

#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C"
{
#endif

  struct belnet_context;

  /// allocate a new belnet context
  struct belnet_context* EXPORT
  belnet_context_new();

  /// free a context allocated by belnet_context_new
  void EXPORT
  belnet_context_free(struct belnet_context*);

  /// spawn all the threads needed for operation and start running
  /// return 0 on success
  /// return non zero on fail
  int EXPORT
  belnet_context_start(struct belnet_context*);

  /// return 0 if we our endpoint has published on the network and is ready to send
  /// return -1 if we don't have enough paths ready
  /// retrun -2 if we look deadlocked
  /// retrun -3 if context was null or not started yet
  int EXPORT
  belnet_status(struct belnet_context*);

  /// wait at most N milliseconds for belnet to build paths and get ready
  /// return 0 if we are ready
  /// return nonzero if we are not ready
  int EXPORT
  belnet_wait_for_ready(int N, struct belnet_context*);

  /// stop all operations on this belnet context
  void EXPORT
  belnet_context_stop(struct belnet_context*);

  /// load a bootstrap RC from memory
  /// return 0 on success
  /// return non zero on fail
  int EXPORT
  belnet_add_bootstrap_rc(const char*, size_t, struct belnet_context*);

#ifdef __cplusplus
}
#endif
