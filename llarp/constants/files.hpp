#pragma once

#include <llarp/util/fs.hpp>

#include <stdlib.h>

#ifndef _WIN32
#include <unistd.h>
#include <pwd.h>
#endif

namespace llarp
{
  constexpr auto our_rc_filename = "self.signed";
  constexpr auto our_identity_filename = "identity.key";
  constexpr auto our_enc_key_filename = "encryption.key";
  constexpr auto our_transport_key_filename = "transport.key";

  constexpr auto nodedb_dirname = "nodedb";

  inline fs::path
  GetDefaultDataDir()
  {
#ifdef _WIN32
    return "C:/programdata/belnet";
#else
    fs::path datadir{"/var/lib/belnet"};

    if (auto uid = ::geteuid())
    {
      if (auto* pw = getpwuid(uid))
      {
        datadir = fs::path{pw->pw_dir} / ".belnet";
      }
    }
    return datadir;
#endif
  }

  inline fs::path
  GetDefaultConfigFilename()
  {
    return "belnet.ini";
  }

  inline fs::path
  GetDefaultConfigPath()
  {
    return GetDefaultDataDir() / GetDefaultConfigFilename();
  }

  inline fs::path
  GetDefaultBootstrap()
  {
    return GetDefaultDataDir() / "bootstrap.signed";
  }

}  // namespace llarp
