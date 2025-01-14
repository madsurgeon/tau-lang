// LICENSE
// This software is free for use and redistribution while including this
// license notice, unless:
// 1. is used for commercial or non-personal purposes, or
// 2. used for a product which includes or associated with a blockchain or other
// decentralized database technology, or
// 3. used for a product which includes or associated with the issuance or use
// of cryptographic or electronic currencies/coins/tokens.
// On all of the mentiTd cases, an explicit and written permission is required
// from the Author (Ohad Asor).
// Contact ohad@idni.org for requesting a permission. This license may be
// modified over time by the Author.

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <cassert>

#include "doctest.h"
#include "nso_rr.h"
#include "bool_ba.h"
#include "bdd_handle.h"
#include "normalizer.h"
#include "bdd_binding.h"

using namespace idni::rewriter;
using namespace idni::tau;

namespace testing = doctest;

bool check_hook(const char* sample, const char* expected) {
	auto tau_sample = make_nso_using_factory<
		tau_ba<bdd_binding>, bdd_binding>(sample, { .start = tau_parser::bf }).value();
	auto tau_expected = make_nso_using_factory<
		tau_ba<bdd_binding>, bdd_binding>(expected, { .start = tau_parser::bf }).value();

	#ifdef DEBUG
	std::string str(sample);
	std::cout << "sample: " << str << " expected: " << tau_expected << " got: " << tau_sample << "\n";
	#endif // DEBUG

	return tau_sample == tau_expected;
}

TEST_SUITE("wff logical hooks") {

	TEST_CASE("'") {
		CHECK( check_hook("0'", "1") );
		CHECK( check_hook("1'", "0") );

		CHECK( check_hook("x''", "x") );

		CHECK( check_hook("{T}'", "0") );
		CHECK( check_hook("{F}'", "1") );
	}

	TEST_CASE("|") {
		CHECK( check_hook("1|0", "1") );
		CHECK( check_hook("0|1", "1") );
		CHECK( check_hook("1|1", "1") );
		CHECK( check_hook("0|0", "0") );

		CHECK( check_hook("1|x", "1") );
		CHECK( check_hook("x|1", "1") );
		CHECK( check_hook("0|x", "x") );
		CHECK( check_hook("x|0", "x") );
		CHECK( check_hook("x|x", "x") );
		CHECK( check_hook("x|x'", "1") );
		CHECK( check_hook("x'|x", "1") );

		CHECK( check_hook("{T}|{T}", "1"));
		CHECK( check_hook("{T}|{F}", "1"));
		CHECK( check_hook("{F}|{T}", "1"));
		CHECK( check_hook("{F}|{F}", "0"));
	}

	TEST_CASE("&") {
		CHECK( check_hook("0&1", "0") );
		CHECK( check_hook("1&0", "0") );
		CHECK( check_hook("1&1", "1") );
		CHECK( check_hook("0&0", "0") );

		CHECK( check_hook("1&x", "x") );
		CHECK( check_hook("x&1", "x") );
		CHECK( check_hook("0&x", "0") );
		CHECK( check_hook("x&0", "0") );
		CHECK( check_hook("x&x", "x") );
		CHECK( check_hook("x&x'", "0") );
		CHECK( check_hook("x'&x", "0") );

		CHECK( check_hook("{T}&{T}", "1"));
		CHECK( check_hook("{T}&{F}", "0"));
		CHECK( check_hook("{F}&{T}", "0"));
		CHECK( check_hook("{F}&{F}", "0"));
	}

	TEST_CASE("+") {
		CHECK( check_hook("0+1", "1") );
		CHECK( check_hook("1+0", "1") );
		CHECK( check_hook("1+1", "0") );
		CHECK( check_hook("0+0", "0") );

		CHECK( check_hook("1+x", "x'") );
		CHECK( check_hook("x+1", "x'") );
		CHECK( check_hook("0+x", "x") );
		CHECK( check_hook("x+0", "x") );
		CHECK( check_hook("x+x", "0") );
		CHECK( check_hook("x+x'", "1") );
		CHECK( check_hook("x'+x", "1") );


		CHECK( check_hook("{T}+{T}", "0") );
		CHECK( check_hook("{T}+{F}", "1") );
		CHECK( check_hook("{F}+{T}", "1") );
		CHECK( check_hook("{F}+{F}", "0") );
	}
}
