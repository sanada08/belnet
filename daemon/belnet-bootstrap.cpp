#include <cpr/cpr.h>
#include <llarp/constants/files.hpp>
#include <llarp/constants/version.hpp>
#include <llarp/util/buffer.hpp>
#include <llarp/util/fs.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

#include <unordered_map>

#ifndef _WIN32
#include <openssl/x509.h>
#endif

#include <sstream>

#ifndef _WIN32
#include <openssl/x509.h>
#endif

namespace
{
  int
  fail(std::string msg)
  {
    std::cout << msg << std::endl;
    return 1;
  }
}  // namespace

int
main(int argc, char* argv[])
{
  const std::unordered_map<std::string, std::string> bootstrap_urls = {
      {"mainnet", "https://deb.beldex.io/Beldex-projects/Belnet/bootstrap-files/belnet.signed"},
      {"belnet", "https://deb.beldex.io/Beldex-projects/Belnet/bootstrap-files/belnet.signed"},
      {"testnet", "https://deb.beldex.io/Beldex-projects/Belnet/bootstrap-files/testnet.signed"},
      {"gamma", "https://deb.beldex.io/Beldex-projects/Belnet/bootstrap-files/testnet.signed"}};

  std::string bootstrap_url = bootstrap_urls.at("belnet");
  fs::path outputfile{llarp::GetDefaultBootstrap()};

  if (argc > 1)
  {
    if (auto itr = bootstrap_urls.find(argv[1]); itr != bootstrap_urls.end())
    {
      bootstrap_url = itr->second;
    }
    else
    {
      bootstrap_url = argv[1];
    }
  }
  if (argc > 2)
  {
    outputfile = fs::path{argv[2]};
  }

  cpr::Response resp =
#ifdef _WIN32
      cpr::Get(
          cpr::Url{bootstrap_url}, cpr::Header{{"User-Agent", std::string{llarp::VERSION_FULL}}});
#else
      cpr::Get(
          cpr::Url{bootstrap_url},
          cpr::Header{{"User-Agent", std::string{llarp::VERSION_FULL}}},
          cpr::Ssl(cpr::ssl::CaPath{X509_get_default_cert_dir()}));
#endif
  if (resp.status_code != 200)
  {
    return fail("failed to fetch '" + bootstrap_url + "' HTTP " + std::to_string(resp.status_code));
  }
  std::stringstream ss;
  ss << resp.text;
  std::string data{ss.str()};
  if (data[0] == 'l' or data[0] == 'd')
  {
    try
    {
      fs::ofstream ofs{outputfile, std::ios::binary};
      ofs.exceptions(fs::ofstream::failbit);
      ofs << data;
      return 0;
    }
    catch (std::exception& ex)
    {
      return fail(std::string{"failed to write bootstrap file: "} + ex.what());
    }
  }
  return fail("got invalid bootstrap file content");
}
