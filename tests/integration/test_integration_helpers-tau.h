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

#ifndef __TEST_INTEGRATION_HELPERS_TAU_H__
#define __TEST_INTEGRATION_HELPERS_TAU_H__

#include "../src/formula.h"
#include "../src/babdd.h"
#include "../src/bdd_handle.h"
#include "../src/bool.h"
#include "../src/normalizer2.h"
#include "../src/tau.h"

using namespace idni::rewriter;
using namespace idni::tau;

using bdd_test = hbdd<Bool>;

template<typename...BAs>
struct bdd_test_factory {

	sp_tau_node<tau<bdd_test>, bdd_test> build(const std::string type_name, const sp_tau_node<tau<bdd_test>, bdd_test>& n) {
		if (type_name != "bdd") return n;
		std::string var = make_string_with_skip<
			tau_node_terminal_extractor_t<tau<bdd_test>, bdd_test>,
			not_whitespace_predicate_t<tau<bdd_test>, bdd_test>,
			sp_tau_node<tau<bdd_test>, bdd_test>>(
				tau_node_terminal_extractor<tau<bdd_test>, bdd_test>,
				not_whitespace_predicate<tau<bdd_test>, bdd_test>, n);
		if (auto cn = cache.find(var); cn != cache.end()) return cn->second;
		auto ref = bdd<Bool>::bit(index++);
		auto sp = bdd_handle<Bool>::get(ref);
		tau_sym<tau<bdd_test>, bdd_test> ts(sp);
		auto nn =  make_node<tau_sym<tau<bdd_test>, bdd_test>>(ts, {});
		return cache.emplace(var, nn).first->second;
	}

	size_t index = 0;
	std::map<std::string, sp_tau_node<tau<bdd_test>, bdd_test>> cache;
};

template<typename...BAs>
using bdd_test_factory_t = bdd_test_factory<BAs...>;

formula<tau<bdd_test>, bdd_test> normalize_test_tau(const char* src) {
	bdd_test_factory<bdd_test> bf;
	tau_factory<bdd_test_factory_t<bdd_test>, bdd_test> fb(bf);
	factory_binder<tau_factory<bdd_test_factory_t<bdd_test>, bdd_test>, tau<bdd_test>, bdd_test> fbinder(fb);
	formula<tau<bdd_test>, bdd_test> formula = make_formula_using_factory<
			factory_binder<tau_factory<bdd_test_factory_t<bdd_test>, bdd_test>,tau<bdd_test>, bdd_test>,
			tau<bdd_test>, bdd_test>(src, fbinder);

	return normalizer<tau<bdd_test>, bdd_test>(formula);
}

#endif // __TEST_INTEGRATION_HELPERS_TAU_H__