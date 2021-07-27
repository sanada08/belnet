#include "catch2/catch.hpp"
#include <crypto/crypto_libsodium.hpp>
#include <service/name.hpp>
#include <oxenmq/hex.h>

using namespace std::literals;

TEST_CASE("Test LNS name decrypt", "[lns]")
{
  llarp::sodium::CryptoLibSodium crypto;
  constexpr auto recordhex = "0ba76cbfdb6dc8f950da57ae781912f31c8ad0c55dbf86b88cb0391f563261a9656571a817be4092969f8a78ee0fcee260424acb4a1f4bbdd27348b71de006b6152dd04ed11bf3c4"sv;
  const auto recordbin = oxenmq::from_hex(recordhex);
  CHECK(not recordbin.empty());
  llarp::SymmNonce n{};
  std::vector<byte_t> ciphertext{};
  const auto len = recordbin.size() - n.size();
  std::copy_n(recordbin.cbegin() + len, n.size(), n.data());
  std::copy_n(recordbin.cbegin(), len, std::back_inserter(ciphertext));
  const auto maybe = crypto.maybe_decrypt_name(std::string_view{reinterpret_cast<const char *>(ciphertext.data()), ciphertext.size()}, n, "jason.beldex");
  CHECK(maybe.has_value());
  const llarp::service::Address addr{*maybe};
  CHECK(addr.ToString() == "azfoj73snr9f3neh5c6sf7rtbaeabyxhr1m4un5aydsmsrxo964o.beldex");
}


TEST_CASE("Test LNS validity", "[lns]")
{
  CHECK(not llarp::service::NameIsValid("beldex.beldex"));
  CHECK(not llarp::service::NameIsValid("mnode.beldex"));
  CHECK(not llarp::service::NameIsValid("localhost.beldex"));
  CHECK(not llarp::service::NameIsValid("gayballs22.beldex.beldex"));
  CHECK(not llarp::service::NameIsValid("-beldex.beldex"));
  CHECK(not llarp::service::NameIsValid("super-mario-gayballs-.beldex"));
  CHECK(not llarp::service::NameIsValid("bn--lolexdeeeeee.beldex"));
  CHECK(not llarp::service::NameIsValid("2222222222a-.beldex"));
  CHECK(not llarp::service::NameIsValid("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.beldex"));
  
  CHECK(llarp::service::NameIsValid("xn--animewasindeedamistake.beldex"));
  CHECK(llarp::service::NameIsValid("memerionos.beldex"));
  CHECK(llarp::service::NameIsValid("whyis.xn--animehorrible.beldex"));
  CHECK(llarp::service::NameIsValid("the.goog.beldex"));
  CHECK(llarp::service::NameIsValid("420.beldex"));
}
