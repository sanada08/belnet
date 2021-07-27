#include <service/address.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Address", "[Address]")
{
  const std::string mnode = "8zfiwpgonsu5zpddpxwdurxyb19x6r96xy4qbikff99jwsziws9y.mnode";
  const std::string beldex = "7okic5x5do3uh3usttnqz9ek3uuoemdrwzto1hciwim9f947or6y.beldex";
  const std::string sub = "belnet.test";
  const std::string invalid = "7okic5x5do3uh3usttnqz9ek3uuoemdrwzto1hciwim9f947or6y.net";
  llarp::service::Address addr;

  SECTION("Parse bad TLD")
  {
    REQUIRE_FALSE(addr.FromString(mnode, ".net"));
    REQUIRE_FALSE(addr.FromString(invalid, ".net"));
  }

  SECTION("Parse bad TLD appened on end")
  {
    const std::string bad = beldex + ".net";
    REQUIRE_FALSE(addr.FromString(bad, ".net"));
  }

  SECTION("Parse bad TLD appened on end with subdomain")
  {
    const std::string bad = sub + "." + beldex + ".net";
    REQUIRE_FALSE(addr.FromString(bad, ".net"));
  }

  SECTION("Parse MNode not Beldex")
  {
    REQUIRE(addr.FromString(mnode, ".mnode"));
    REQUIRE_FALSE(addr.FromString(mnode, ".beldex"));
  }

  SECTION("Parse Beldex not .MNode")
  {
    REQUIRE_FALSE(addr.FromString(beldex, ".mnode"));
    REQUIRE(addr.FromString(beldex, ".beldex"));
  }

  SECTION("Parse Beldex with subdomain")
  {
    const std::string addr_str = sub + "." + beldex;
    REQUIRE(addr.FromString(addr_str, ".beldex"));
    REQUIRE(addr.subdomain == sub);
    REQUIRE(addr.ToString() == addr_str);
  };

  SECTION("Parse .MNode with subdomain")
  {
    const std::string addr_str = sub + "." + mnode;
    REQUIRE(addr.FromString(addr_str, ".mnode"));
    REQUIRE(addr.subdomain == sub);
    REQUIRE(addr.ToString(".mnode") == addr_str);
  }
}
