#pragma once

#include "belnet_context.h"
#include "belnet_os.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /// poll many sockets for activity
  /// each pollfd.fd should be set to the socket id
  /// returns 0 on sucess
  int EXPORT
  belnet_poll(struct pollfd* poll, nfds_t numsockets, struct belnet_context* ctx);

  /// close a udp socket or a stream socket by its id
  void EXPORT
  belnet_close_socket(int id, struct belnet_context* ctx);

#ifdef __cplusplus
}
#endif
