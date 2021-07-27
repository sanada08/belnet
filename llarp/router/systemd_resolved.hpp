#pragma once

#include <string>
#include <llarp/net/sock_addr.hpp>

namespace llarp
{
  /// Attempts to set belnet as the DNS server for systemd-resolved.  Returns true if successful,
  /// false if unsupported or fails.  (When compiled without systemd support this always returns
  /// false without doing anything).
  ///
  /// \param if_name -- the interface name to which we add the DNS servers, e.g. beldextun0.
  /// Typically tun_endpoint.GetIfName().
  /// \param dns -- the listening address of the belnet DNS server
  /// \param global -- whether to set up belnet for all DNS queries (true) or just .beldex & .mnode
  /// addresses (false).
  bool
  systemd_resolved_set_dns(std::string if_name, llarp::SockAddr dns, bool global);
}  // namespace llarp
