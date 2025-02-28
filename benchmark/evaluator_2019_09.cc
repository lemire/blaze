#include <benchmark/benchmark.h>

#include <cassert> // assert

#include <sourcemeta/jsontoolkit/json.h>
#include <sourcemeta/jsontoolkit/jsonschema.h>

#include <sourcemeta/blaze/compiler.h>
#include <sourcemeta/blaze/evaluator.h>

static void Evaluator_2019_09_Unevaluated_Properties(benchmark::State &state) {
  const sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(R"JSON({
    "$schema": "https://json-schema.org/draft/2019-09/schema",
    "type": "object",
    "properties": {
      "name": true,
      "prohibited": false
    },
    "not": {
      "required": [ "prohibited" ]
    },
    "unevaluatedProperties": false,
    "$ref": "#/$defs/extension",
    "$defs": {
      "extension": {
        "patternProperties": { "^x-": true }
      }
    }
  })JSON")};

  const auto instance{sourcemeta::jsontoolkit::parse(R"JSON({
    "name": "John Doe",
    "x-foo": "bar"
  })JSON")};

  const auto schema_template{sourcemeta::blaze::compile(
      schema, sourcemeta::jsontoolkit::default_schema_walker,
      sourcemeta::jsontoolkit::official_resolver,
      sourcemeta::blaze::default_schema_compiler)};
  for (auto _ : state) {
    auto result{sourcemeta::blaze::evaluate(schema_template, instance)};
    assert(result);
    benchmark::DoNotOptimize(result);
  }
}

BENCHMARK(Evaluator_2019_09_Unevaluated_Properties);
