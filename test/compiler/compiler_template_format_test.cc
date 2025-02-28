#include <gtest/gtest.h>
#include <sstream>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/jsontoolkit/json.h>

TEST(Compiler_template_format, example_1) {
  const sourcemeta::jsontoolkit::JSON document =
      sourcemeta::jsontoolkit::parse(R"JSON({
    "absoluteKeywordLocation": "#/properties",
    "category": "annotation",
    "evaluatePath": true,
    "unknown": 1,
    "track": true,
    "dynamic": true,
    "type": "public",
    "relativeSchemaLocation": "",
    "relativeInstanceLocation": "",
    "value": {
      "category": "value",
      "type": "json",
      "value": "foo"
    }
  })JSON");

  std::ostringstream stream;
  sourcemeta::jsontoolkit::prettify(document, stream,
                                    sourcemeta::blaze::template_format_compare);
  EXPECT_EQ(stream.str(), R"JSON({
  "category": "annotation",
  "type": "public",
  "value": {
    "category": "value",
    "type": "json",
    "value": "foo"
  },
  "absoluteKeywordLocation": "#/properties",
  "relativeSchemaLocation": "",
  "relativeInstanceLocation": "",
  "evaluatePath": true,
  "dynamic": true,
  "track": true,
  "unknown": 1
})JSON");
}
