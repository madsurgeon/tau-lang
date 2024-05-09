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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "nso_rr.h"
#include "bool_ba.h"
#include "bdd_handle.h"
#include "normalizer.h"
#include "satisfiability.h"
#include "test_helpers.h"

using namespace idni::rewriter;
using namespace idni::tau;

namespace testing = doctest;

TEST_SUITE("parsing tau rules") {

	TEST_CASE("TAU_DISTRIBUTE_0") {
		auto src_rule = make_tau_source(TAU_DISTRIBUTE_0);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_DISTRIBUTE_1") {
		auto src_rule = make_tau_source(TAU_DISTRIBUTE_1);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ONE_0") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ONE_0);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ONE_1") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ONE_1);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ONE_2") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ONE_2);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ONE_3") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ONE_3);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ONE_4") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ONE_4);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ZERO_0") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ZERO_0);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ZERO_1") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ZERO_1);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ZERO_2") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ZERO_2);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ZERO_3") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ZERO_3);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_ZERO_4") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_ZERO_4);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_SELF_0") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_SELF_0);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_SELF_1") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_SELF_1);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_SELF_2") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_SELF_2);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_SELF_3") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_SELF_3);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_SELF_4") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_SELF_4);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_SIMPLIFY_SELF_5") {
		auto src_rule = make_tau_source(TAU_SIMPLIFY_SELF_5);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_COLLAPSE_POSITIVES_0") {
		auto src_rule = make_tau_source(TAU_COLLAPSE_POSITIVES_0);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_COLLAPSE_POSITIVES_1") {
		auto src_rule = make_tau_source(TAU_COLLAPSE_POSITIVES_1);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_COLLAPSE_POSITIVES_2") {
		auto src_rule = make_tau_source(TAU_COLLAPSE_POSITIVES_2);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_COLLAPSE_POSITIVES_3") {
		auto src_rule = make_tau_source(TAU_COLLAPSE_POSITIVES_3);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_COLLAPSE_POSITIVES_4") {
		auto src_rule = make_tau_source(TAU_COLLAPSE_POSITIVES_4);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_COLLAPSE_POSITIVES_5") {
		auto src_rule = make_tau_source(TAU_COLLAPSE_POSITIVES_5);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_COLLAPSE_POSITIVES_6") {
		auto src_rule = make_tau_source(TAU_COLLAPSE_POSITIVES_6);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_PUSH_POSITIVES_UPWARDS_0") {
		auto src_rule = make_tau_source(TAU_PUSH_POSITIVES_UPWARDS_0);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_PUSH_POSITIVES_UPWARDS_1") {
		auto src_rule = make_tau_source(TAU_PUSH_POSITIVES_UPWARDS_1);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_PUSH_POSITIVES_UPWARDS_2") {
		auto src_rule = make_tau_source(TAU_PUSH_POSITIVES_UPWARDS_2);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}

	TEST_CASE("TAU_PUSH_POSITIVES_UPWARDS_3") {
		auto src_rule = make_tau_source(TAU_PUSH_POSITIVES_UPWARDS_3);
		auto tau_rule = make_statement(src_rule);
		auto check = tau_rule
			| tau_parser::library
			| tau_parser::rules
			| tau_parser::rule
			| tau_parser::tau_rule;
		CHECK( check.has_value() );
	}
}
