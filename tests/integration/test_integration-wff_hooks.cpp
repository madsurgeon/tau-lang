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
		tau_ba<bdd_binding>, bdd_binding>(sample, { .start = tau_parser::wff }).value();
	auto tau_expected = make_nso_using_factory<
		tau_ba<bdd_binding>, bdd_binding>(expected, { .start = tau_parser::wff }).value();

	#ifdef DEBUG
	std::string str(sample);
	std::cout << "sample: " << str << " expected: " << tau_expected << " got: " << tau_sample << "\n";
	#endif // DEBUG

	return tau_sample == tau_expected;
}

TEST_SUITE("wff logical hooks") {

	TEST_CASE("!") {
		CHECK( check_hook("!F", "T") );
		CHECK( check_hook("!T", "F") );

		CHECK( check_hook("!!(x = 0)", "(x = 0)") );
	}

	TEST_CASE("<->") {
		CHECK( check_hook("T<->T", "T") );
		CHECK( check_hook("T<->F", "F") );
		CHECK( check_hook("F<->T", "F") );
		CHECK( check_hook("F<->F", "T") );

		CHECK( check_hook("F<->(x = 0)", "!(x = 0)") );
		CHECK( check_hook("T<->(x = 0)", "(x = 0)") );
		CHECK( check_hook("(x = 0)<->F", "!(x = 0)") );
		CHECK( check_hook("(x = 0)<->T", "(x = 0)") );
		CHECK( check_hook("(x = 0)<->(x = 0)", "T") );
		CHECK( check_hook("!(x = 0)<->(x = 0)", "F") );
		CHECK( check_hook("(x = 0)<->!(x = 0)", "F") );
	}

	TEST_CASE("->") {
		CHECK( check_hook("T->T", "T") );
		CHECK( check_hook("T->F", "F") );
		CHECK( check_hook("F->T", "T") );
		CHECK( check_hook("F->F", "T") );

		CHECK( check_hook("F->(x = 0)", "T") );
		CHECK( check_hook("T->(x = 0)", "(x = 0)") );
		CHECK( check_hook("(x = 0)->F", "!(x = 0)") );
		CHECK( check_hook("(x = 0)->T", "T") );
		CHECK( check_hook("(x = 0)->(x = 0)", "T") );
	}

	TEST_CASE("||") {
		CHECK( check_hook("T||T", "T") );
		CHECK( check_hook("T||F", "T") );
		CHECK( check_hook("F||T", "T") );
		CHECK( check_hook("F||F", "F") );

		CHECK( check_hook("T||(x = 0)", "T") );
		CHECK( check_hook("(x = 0)||T", "T") );
		CHECK( check_hook("F||(x = 0)", "(x = 0)") );
		CHECK( check_hook("(x = 0)||F", "(x = 0)") );
		CHECK( check_hook("(x = 0)||(x = 0)", "(x = 0)") );
		CHECK( check_hook("!(x = 0)||(x = 0)", "T") );
		CHECK( check_hook("(x = 0)||!(x = 0)", "T") );

	}

	TEST_CASE("&&") {
		CHECK( check_hook("T&&T", "T") );
		CHECK( check_hook("T&&F", "F") );
		CHECK( check_hook("F&&T", "F") );
		CHECK( check_hook("F&&F", "F") );

		CHECK( check_hook("T&&(x = 0)", "(x = 0)") );
		CHECK( check_hook("(x = 0)&&T", "(x = 0)") );
		CHECK( check_hook("F&&(x = 0)", "F") );
		CHECK( check_hook("(x = 0)&&F", "F") );
		CHECK( check_hook("(x = 0)&&(x = 0)", "(x = 0)") );
		CHECK( check_hook("!(x = 0)&&(x = 0)", "F") );
		CHECK( check_hook("(x = 0)&&!(x = 0)", "F") );
	}

	TEST_CASE("^") {
		CHECK( check_hook("T^T", "F") );
		CHECK( check_hook("T^F", "T") );
		CHECK( check_hook("F^T", "T") );
		CHECK( check_hook("F^F", "F") );

		CHECK( check_hook("(x = 0)^F", "(x = 0)") );
		CHECK( check_hook("F^(x = 0)", "(x = 0)") );
		CHECK( check_hook("(x = 0)^(x = 0)", "F") );
		CHECK( check_hook("!(x = 0)^(x = 0)", "T") );
		CHECK( check_hook("(x = 0)^!(x = 0)", "T") );
		CHECK( check_hook("(x = 0)^T", "!(x = 0)") );
		CHECK( check_hook("T^(x = 0)", "!(x = 0)") );

	}

	TEST_CASE("?") {
		CHECK( check_hook("T?T:F", "T") );
		CHECK( check_hook("T?T:T", "T") );
		CHECK( check_hook("T?F:T", "F") );
		CHECK( check_hook("T?F:F", "F") );
		CHECK( check_hook("F?T:F", "F") );
		CHECK( check_hook("F?F:F", "F") );
		CHECK( check_hook("F?F:T", "T") );
		CHECK( check_hook("F?T:T", "T") );

		CHECK( check_hook("F?(x=0):(y=0)", "(y=0)") );
		CHECK( check_hook("T?(x=0):(y=0)", "(x=0)") );
		CHECK( check_hook("F?(x=0):(x=0)", "(x=0)") );
		CHECK( check_hook("T?(x=0):(x=0)", "(x=0)") );
	}
}

TEST_SUITE("wff order hooks") {

	TEST_CASE("=") {
		CHECK( check_hook("1=1", "T") );
		CHECK( check_hook("0=0", "T") );
		CHECK( check_hook("1=0", "F") );
		CHECK( check_hook("0=1", "F") );

		CHECK( check_hook("{T}=0", "F") );
		CHECK( check_hook("{F}=0", "T") );
		CHECK( check_hook("x = y", "x + y = 0") );
	}

	TEST_CASE("!=") {
		CHECK( check_hook("1!=1", "F") );
		CHECK( check_hook("0!=0", "F") );
		CHECK( check_hook("1!=0", "T") );
		CHECK( check_hook("0!=1", "T") );

		CHECK( check_hook("{T}!=0", "T") );
		CHECK( check_hook("{F}!=0", "F") );
		CHECK( check_hook("x != y", "x + y != 0") );
	}

	TEST_CASE("<") {
		CHECK( check_hook("1<1", "F") );
		CHECK( check_hook("0<0", "F") );
		CHECK( check_hook("1<0", "F") );
		CHECK( check_hook("0<1", "T") );

		CHECK( check_hook("X<0", "F") );
		CHECK( check_hook("X<1", "X'!=0") );
	}

	TEST_CASE("!<"){
		CHECK( check_hook("1!<1", "T") );
		CHECK( check_hook("0!<0", "T") );
		CHECK( check_hook("1!<0", "T") );
		CHECK( check_hook("0!<1", "F") );

		CHECK( check_hook("X!<0", "T") );
		CHECK( check_hook("X!<1", "X'=0") );
	}

	TEST_CASE(">"){
		CHECK( check_hook("1>1", "F") );
		CHECK( check_hook("0>0", "F") );
		CHECK( check_hook("1>0", "T") );
		CHECK( check_hook("0>1", "F") );

		CHECK( check_hook("X>1", "F") );
		CHECK( check_hook("0>X", "F") );
	}

	TEST_CASE("!>"){
		CHECK( check_hook("1!>1", "T") );
		CHECK( check_hook("0!>0", "T") );
		CHECK( check_hook("1!>0", "F") );
		CHECK( check_hook("0!>1", "T") );

		CHECK( check_hook("X!>1", "T") );
		CHECK( check_hook("0!>X", "T") );
	}

	TEST_CASE("<="){
		CHECK( check_hook("1<=1", "T") );
		CHECK( check_hook("0<=0", "T") );
		CHECK( check_hook("1<=0", "F") );
		CHECK( check_hook("0<=1", "T") );

		CHECK( check_hook("X<=1", "T") );
	}

	TEST_CASE("!<="){
		CHECK( check_hook("1!<=1", "F") );
		CHECK( check_hook("0!<=0", "F") );
		CHECK( check_hook("1!<=0", "T") );
		CHECK( check_hook("0!<=1", "F") );

		CHECK( check_hook("X!<=1", "F") );
	}

	TEST_CASE(">="){
		CHECK( check_hook("1>=1", "T") );
		CHECK( check_hook("0>=0", "T") );
		CHECK( check_hook("1>=0", "T") );
		CHECK( check_hook("0>=1", "F") );

		CHECK( check_hook("X>=0", "T") );
		CHECK( check_hook("1>=X", "T") );
	}

	TEST_CASE("!>="){
		CHECK( check_hook("1!>=1", "F") );
		CHECK( check_hook("0!>=0", "F") );
		CHECK( check_hook("1!>=0", "F") );
		CHECK( check_hook("0!>=1", "T") );

		CHECK( check_hook("X!>=0", "F") );
		CHECK( check_hook("1!>=X", "F") );
	}
}
