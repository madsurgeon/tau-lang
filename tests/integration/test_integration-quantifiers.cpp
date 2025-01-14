// LICENSE
// This software is free for use and redistribution while including this
// license notice, unless:
// 1. is used for commercial or non-personal purposes, or
// 2. used for a product which includes or associated with a blockchain or other
// decentralized database technology, or
// 3. used for a product which includes or associated with the issuance or use
// of cryptographic or electronic currencies/coins/tokens.
// On all of the mentioned cases, an explicit and written permission is required
// from the Author (Ohad Asor).
// Contact ohad@idni.org for requesting a permission. This license may be
// modified over time by the Author.

// tests parsing, printing, normalization and printed result of
// quantifiers: all, ex

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "nso_rr.h"
#include "bool_ba.h"
#include "bdd_handle.h"
#include "bdd_binding.h"
#include "normalizer.h"

#include "test_integration_helpers-bdd.h"
#include "../unit/test_helpers.h"

#include "debug_helpers.h"

using namespace std;
using namespace idni::rewriter;
using namespace idni::tau;

namespace testing = doctest;

using test_case = array<string, 3>;
using test_cases = vector<test_case>;

test_cases ex_cases = {
	{ "ex x x=0.",                  "ex x x = 0.",             "T" },
	{ "ex x,y xy=0.",               "ex x, y xy = 0.",         "T" },
	{ "ex x ex y xy=0.",            "ex x, y xy = 0.",         "T" },
};

test_cases all_cases = {
	{ "all x x!=0.",                "all x x != 0.",           "F" },
	{ "all x,y xy!=0.",             "all x, y xy != 0.",       "F" },
	{ "all x all y xy!=0.",         "all x, y xy != 0.",       "F" },
};

test_cases ex_all_cases = {
	{ "ex x all y x=y.",            "ex x all y x'y|xy' = 0.", "F" },
	{ "ex x,y all w,z x=w&&y=z.",
		"ex x, y all w, z x'w|xw' = 0 && y'z|yz' = 0.",     "F"},
};

test_cases all_ex_cases = {
	{ "all x ex y x=y.",            "all x ex y x'y|xy' = 0.", "T" },
	{ "all x,y ex w,z x=w && y=z.",
		"all x, y ex w, z x'w|xw' = 0 && y'z|yz' = 0.",    "T"},
};

ostream& operator<<(ostream& os, const test_case& tc) {
	return os << "input source: \"" << tc[0]
		<< "\"\n\texpected: \"" << tc[1]
		<< "\" result: \""      << tc[2] << "\"";
}

string to_str(const auto& n) {
	stringstream ss; return (ss << n, ss.str());
}

bool test(const test_case& tc) {
	const auto& [ sample, exp, nexp ] = tc;
	bool fail = false;
	auto src = make_tau_source(sample.c_str());
	auto formula = make_nso_rr_using_factory<bdd_binding>(src);
	if (!formula.has_value()) return fail;
	auto got = to_str(formula.value());
	if (got != exp) fail = true;
	auto norm = normalizer<bdd_binding>(formula.value());
	auto ngot = to_str(norm);
	if (fail || ngot != nexp) fail = true,
		cout << tc << "\n\tgot:      \"" << got
				<< "\" result: \"" << ngot << "\"\n";
	return !fail;
}

#define CASES(name, cases) TEST_CASE(name) { \
		for (const auto& tc : cases) { \
			bool result = test(tc); \
			CHECK( result ); \
			if (!result) break; \
		} \
	}

TEST_SUITE("quantifiers") {
	CASES("ex",     ex_cases);
	CASES("all",    all_cases);
	CASES("ex all", ex_all_cases);
	CASES("all ex", all_ex_cases);
}
