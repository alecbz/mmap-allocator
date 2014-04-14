#include <map>
#include <unordered_map>
#include <gtest/gtest.h>
#include "mmap_allocator.h"

using std::string;
using std::to_string;

namespace mm {

class AllocatorTest : public testing::Test {
 protected:
  void SetUp() { SetDefault("test.db"); }
  void TearDown() { FreeDefault(); }
};

TEST_F(AllocatorTest, VectorInt) {
  vector<int> vec;

  for (int i = 0; i < 10; ++i) {
    vec.push_back(i);
  }

  EXPECT_EQ(10, vec.size());

  for (int i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(i, vec[i]);
  }
}

TEST_F(AllocatorTest, VectorIntInitialized) {
  vector<int> vec{4, 42, 24, 7};

  EXPECT_EQ(4, vec.size());
  EXPECT_EQ(4, vec[0]);
  EXPECT_EQ(42, vec[1]);
  EXPECT_EQ(24, vec[2]);
  EXPECT_EQ(7, vec[3]);
}

TEST_F(AllocatorTest, VectorDouble) {
  vector<double> vec;

  for (int i = 0; i < 10; ++i) {
    vec.push_back(sqrt(i));
  }

  EXPECT_EQ(10, vec.size());

  for (int i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(sqrt(i), vec[i]);
  }
}

TEST_F(AllocatorTest, VectorString) {
  vector<string> vec;

  for (int i = 0; i < 10; ++i) {
    vec.push_back("Hello, world!");
  }

  EXPECT_EQ(10, vec.size());

  for (int i = 0; i < vec.size(); ++i) {
    EXPECT_EQ("Hello, world!", vec[i]);
  }
}

TEST_F(AllocatorTest, MapStringString) {
  map<string, string> m;

  m["Hello"] = "World";
  m["Goodbye"] = "All";
  m["2+2"] = "4";

  EXPECT_EQ(3, m.size());
  EXPECT_EQ("World", m["Hello"]);
}

TEST_F(AllocatorTest, SetString) {
  set<string> s;
  
  s.insert("foo");
  s.insert("bar");

  EXPECT_EQ(2, s.size());
  EXPECT_EQ(1, s.count("foo"));
  EXPECT_EQ(1, s.count("bar"));
  EXPECT_EQ(0, s.count("baz"));
}

TEST_F(AllocatorTest, HashStringString) {
  unordered_map<string, string> m;

  m["Hello"] = "World";
  m["Goodbye"] = "All";
  m["2+2"] = "4";

  EXPECT_EQ(3, m.size());
  EXPECT_EQ("World", m["Hello"]);
}

TEST_F(AllocatorTest, Nested) {
  unordered_map<string, vector<string>> m;
  EXPECT_EQ(0, m.size());

  for (int i = 0; i < 10; ++i) {
    m["foo"].push_back(to_string(i));
  }
  EXPECT_EQ(10, m["foo"].size());

  for (int i = 0; i < 10; ++i) {
    m["bar"].push_back(to_string(i * i));
  }
  EXPECT_EQ(10, m["bar"].size());

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(to_string(i), m["foo"][i]);
  }
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(to_string(i * i), m["bar"][i]);
  }
}

};  // namespace mm
