#include <string>

#include "server/config/network/mongo_proxy.h"

#include "test/mocks/server/mocks.h"
#include "test/test_common/utility.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::NiceMock;
using testing::_;

namespace Envoy {
namespace Server {
namespace Configuration {

TEST(NetworkFilterConfigTest, EmptyConfig) {
  std::string json_string = "{}";
  Json::ObjectSharedPtr json_config = Json::Factory::loadFromString(json_string);
  NiceMock<MockFactoryContext> context;
  MongoProxyFilterConfigFactory factory;

  EXPECT_THROW(factory.createFilterFactory(*json_config, context), Json::Exception);
}

TEST(NetworkFilterConfigTest, MongoProxy) {
  std::string json_string = R"EOF(
  {
    "stat_prefix": "my_stat_prefix",
    "access_log" : "path/to/access/log"
  }
  )EOF";

  Json::ObjectSharedPtr json_config = Json::Factory::loadFromString(json_string);
  NiceMock<MockFactoryContext> context;
  MongoProxyFilterConfigFactory factory;
  EXPECT_EQ(NetworkFilterType::Both, factory.type());
  NetworkFilterFactoryCb cb = factory.createFilterFactory(*json_config, context);
  Network::MockConnection connection;
  EXPECT_CALL(connection, addFilter(_));
  cb(connection);
}

TEST(NetworkFilterConfigTest, BadMongoProxyConfig) {
  std::string json_string = R"EOF(
  {
    "stat_prefix": "my_stat_prefix",
    "access_log" : "path/to/access/log",
    "test" : "a"
  }
  )EOF";

  Json::ObjectSharedPtr json_config = Json::Factory::loadFromString(json_string);
  NiceMock<MockFactoryContext> context;
  MongoProxyFilterConfigFactory factory;
  EXPECT_THROW(factory.createFilterFactory(*json_config, context), Json::Exception);
}

} // namespace Configuration
} // namespace Server
} // namespace Envoy
