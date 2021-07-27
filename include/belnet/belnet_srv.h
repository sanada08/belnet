#pragma once

#include "belnet_context.h"

#ifdef __cplusplus
extern "C"
{
#endif

  // a single srv record
  struct belnet_srv_record
  {
    /// the srv priority of the record
    uint16_t priority;
    /// the weight of this record
    uint16_t weight;
    /// null terminated string of the hostname
    char target[256];
    /// the port to use
    int port;
  };

  /// private members of a srv lookup
  struct belnet_srv_lookup_private;

  /// the result of an srv lookup
  struct belnet_srv_lookup_result
  {
    /// set to zero on success otherwise is the error code
    int error;
    /// pointer to internal members
    /// dont touch me
    struct belnet_srv_lookup_private* internal;
  };

  /// do a srv lookup on host for service
  /// caller MUST call belnet_srv_lookup_done when they are done handling the result
  int EXPORT
  belnet_srv_lookup(
      char* host,
      char* service,
      struct belnet_srv_lookup_result* result,
      struct belnet_context* ctx);

  /// a hook function to handle each srv record in a srv lookup result
  /// passes in NULL when we are at the end of iteration
  /// passes in void * user data
  /// hook should NOT free the record
  typedef void (*belnet_srv_record_iterator)(struct belnet_srv_record*, void*);

  /// iterate over each srv record in a lookup result
  /// user is passes into hook and called for each result and then with NULL as the result on the
  /// end of iteration
  void EXPORT
  belnet_for_each_srv_record(
      struct belnet_srv_lookup_result* result, belnet_srv_record_iterator iter, void* user);

  /// free internal members of a srv lookup result after use of the result
  void EXPORT
  belnet_srv_lookup_done(struct belnet_srv_lookup_result* result);

#ifdef __cplusplus
}
#endif
