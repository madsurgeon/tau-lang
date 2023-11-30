// This file is generated by
//       https://github.com/IDNI/parser/tools/parser_gen
//
// from the grammar in file ../tau-lang/parser/tau.tgf:
//
// @use_char_class eof, space, digit, xdigit, alpha, alnum, punct, printable.
//
// # in all those cases: x and y is are vars and "tau" is a constant
// # x & tau // wrong
// # x & {tau} // ok
// # x && {tau} // wrong
// # x && tau // wrong
// # x &&& tau // wrong
// # x &&& {tau} // ok
// # x && y // wrong
// # x & y // ok if x and y came from the same boolean algebra
// # x &&& y // ok if x and y came from the boolean algebra of tau formulas
//
// #
// # as a rule of thumb, to ease navigation of the corresponding tree, the
// # non-terminals shouldn't appear in * or + expressions. Otherwise,
// # intermediate non terminals would be created and break the expected tree
// # structure
// #
//
// # whitespace and comments
// eol				=> '\n' | '\r' | eof.
// ws_comment		=> '#' eol | '#' printable+ eol.
// ws_required		=> space ws | ws_comment ws.
// ws				=> ws_required | null.
//
// # characters
// hex_escape			=> "\\x" xdigit xdigit.
// unicode_escape		=> "\\u" xdigit xdigit xdigit xdigit.
// char_escape_encode	=> hex_escape | unicode_escape.
//
// # defining char/string/qstring as all chars but its wrapping character
// # enables using TAB and new lines in char(')/string(")/bqstring(`)
// # sequences
//
// # common stuff copy cut from tml grammar
// esc				=> "\\\\".
// q_char			=> '\''.
// q_str			=> '"'.
// q_bqstr			=> '`'.
// char_punct		=> punct & ~q_char & ~q_str & ~q_bqstr
// 					& ~(esc q_char) & ~(esc q_str) & ~(esc q_bqstr).
//
// char0			=> alnum | space | char_escape_encode | char_punct.
// char_			=> char0 | esc q_char |     q_str |     q_bqstr.
// string_char		=> char0 |     q_char | esc q_str |     q_bqstr.
// bqstring_char	=> char0 |     q_char |     q_str | esc q_bqstr.
// chars			=> alpha (alnum)*.
//
// char_class    	=> "eof" | "alnum" | "alpha" | "blank" | "cntrl" | "digit"
// 				| "graph" | "lower" | "printable" | "punct" | "space"
// 				| "upper" | "xdigit".
//
// # elements
// sym				=> chars.
//
// # common symbols
// definition			=> ws ":=" ws.
// equality			=> ws "=" ws.
// nequality			=> ws "!=" ws.
// dot 				=> ws '.' ws.
// open_parenthesis	=> ws '(' ws.
// close_parenthesis	=> ws ')' ws.
// open_bracket		=> ws '[' ws.
// close_bracket		=> ws ']' ws.
// open_brace			=> ws '{' ws.
// close_brace			=> ws '}' ws.
// minus				=> ws '-' ws.
// colon				=> ws ':' ws.
// less				=> ws '<' ws.
//
// # indexes
// indexes			=> open_bracket (index)* close_bracket.
// index			=> variable | capture | ignore | offset.
// num				=> digit+.
//
// # captures
//
// captures 		=> open_parenthesis capture (ws_required capture)* close_parenthesis
// 				| open_parenthesis close_parenthesis.
//
// # variables
// variable		=> var | timed.
//
// # QUESTION does timed variables have one index or several?
// # this should be typed according to the original BA.
// timed			=> (in | out)  indexes.
// offset			=> variable | variable minus num.
// # TODO (MEDIUM) remove ignore as it is not used
// #
// # That aldo implies removing the ignore rule from the code when neccessary
// ignore 			=> '_'.
// capture			=> '$' chars.
// var				=> '?' chars.
// in				=> "?i_" chars. # instead of '<', easy to remember
// out				=> "?o_" chars. # instead of '>', easy to remember
//
// # wff
// wff_rule		=> wff_matcher definition wff_body dot.
//
// # needed for rule CBF_DEF_IF
// wff_matcher	=> wff | wff_ref.
// wff_body	=> wff | bf_eq_cb | bf_neq_cb | wff_has_clashing_subformulas_cb
// 				| wff_has_subformula_cb | wff_remove_existential.
//
// wff_ref			=> sym indexes wff_ref_args.
// wff_ref_args	=> open_parenthesis (variable)* close_parenthesis.
//
// # TODO (LOW) rename wff_eq and wff_new to bf_eq and bf_neq
// wff 			=> wff_eq | wff_neq | wff_ref | wff_and | wff_neg | wff_xor
// 					| wff_or | wff_all | wff_ex | wff_imply | wff_equiv
// 					| wff_coimply | wff_t | wff_f | capture |ignore.
// wff_eq 			=> open_parenthesis bf equality wff_f close_parenthesis.
// wff_neq 		=> open_parenthesis bf nequality wff_f close_parenthesis.
// wff_and			=> open_parenthesis wff wff_and_sym wff close_parenthesis.
// wff_or			=> open_parenthesis wff wff_or_sym wff close_parenthesis.
// wff_xor			=> open_parenthesis wff wff_xor_sym wff close_parenthesis.
// wff_neg			=> wff_neg_sym wff.
// wff_imply		=> open_parenthesis wff wff_imply_sym wff close_parenthesis.
// wff_equiv		=> open_parenthesis wff wff_equiv_sym wff close_parenthesis.
// wff_coimply		=> open_parenthesis wff wff_coimply_sym wff close_parenthesis.
// wff_all			=> wff_all_sym (variable|capture|ignore) ws_required wff.
// wff_ex			=> wff_ex_sym (variable|capture|ignore) ws_required wff.
//
// # wff_op_sym
// wff_and_sym		=> ws "wff_and" ws.
// wff_or_sym		=> ws "wff_or" ws.
// wff_xor_sym		=> ws "wff_xor" ws.
// wff_neg_sym		=> ws "wff_neg" ws.
// wff_imply_sym	=> ws "wff_imply" ws.
// wff_equiv_sym	=> ws "wff_equiv" ws.
// wff_coimply_sym	=> ws "wff_coimply" ws.
// wff_all_sym		=> ws "wff_all" ws.
// wff_ex_sym		=> ws "wff_ex" ws.
// wff_t			=> ws 'T' ws.
// wff_f			=> ws 'F' ws.
//
// # bf
// bf_ref 		=> sym indexes bf_ref_args.
// bf_ref_args	=> open_parenthesis (variable)* close_parenthesis.
// bf_rule		=> bf_matcher definition bf_body dot.
//
// bf_matcher	=> bf.
// bf_body 	=> bf | bf_is_zero_cb | bf_is_one_cb | bf_has_clashing_subformulas_cb
// 				| bf_has_subformula_cb.
//
// bf				=> bf_constant | bf_and | bf_neg | bf_xor | bf_or
// 					| bf_all | bf_ex | bf_less | bf_less_equal | bf_greater
// 					| bf_less_cb | bf_less_equal_cb | bf_greater_cb
// 					# TODO (LOW) check proper use of bf_subs_cb in code
// 					#
// 					# we should have a check method that verifies that the user
// 					# is not uising subs in its code.
// 					| bf_subs_cb | bf_t | bf_f | variable | capture | ignore.
// bf_and			=> open_parenthesis bf bf_and_sym bf close_parenthesis.
// bf_or			=> open_parenthesis bf bf_or_sym bf close_parenthesis.
// bf_xor			=> open_parenthesis bf bf_xor_sym ws bf close_parenthesis.
// bf_neg			=> bf_neg_sym bf.
// bf_less			=> open_parenthesis bf bf_less_sym bf close_parenthesis.
// bf_less_equal	=> open_parenthesis bf bf_less_equal_sym bf close_parenthesis.
// bf_greater		=> open_parenthesis bf bf_greater_sym bf close_parenthesis.
// bf_all			=> bf_all_sym ws_required (variable | capture) ws_required bf.
// bf_ex			=> bf_ex_sym ws_required (variable | capture) ws_required bf.
//
// # bf_op_sym
// bf_and_sym			=> ws "bf_and" ws.
// bf_or_sym			=> ws "bf_or" ws.
// bf_xor_sym			=> ws "bf_xor" ws.
// bf_neg_sym			=> ws "bf_neg" ws.
// bf_less_sym			=> ws "bf_less" ws.
// bf_less_equal_sym	=> ws "bf_less_equal" ws.
// bf_greater_sym		=> ws "bf_greater" ws.
// bf_all_sym			=> ws "bf_all" ws.
// bf_ex_sym			=> ws "bf_ex" ws.
// bf_t				=> ws 'T' ws.
// bf_f				=> ws 'F' ws.
//
// # constant
// bf_constant		=> open_brace constant close_brace.
//
// #constants, test_bf is included for testing purposes only
// constant		=>  binding | capture | ignore
// 					| bf_and_cb | bf_or_cb | bf_xor_cb | bf_neg_cb.
// binding			=> source_binding | named_binding.
// named_binding	=> chars.
// source_binding	=> type colon source.
// type 			=> chars | null.
//
// # source related definition
// source0			=> alnum | space | char_escape_encode | char_punct.
// source			=> (source0)+.
//
// # callbacks
//
// # callbacks must be used in the following cases:
// #
// # 1.- underlying boolean algebras operations: and, or, xor, neg, less,
// # less_equal, greater, subs, eq, neq, is_zero, is_one,... In this case, no
// # other way we have to call the uderlying operations of the boolean algebra
// # 2.- speed up computations: has_clashing_subformulas, has_subformula,
// # remove_existential... In this case, we could use the the callback to
// # avoid the creation of intermediate formulas. For instance, if we want
// # to check if a formula has a subformula, we could use the callback to
// # avoid the creation of the subformulas to check that point.
// # 3.- to create new subformulas in other rules, for instance, to create a
// # new formula that is the substitution of a variable by a constant.
//
// # TODO (HIGH) Earley parser doesn't support tabs in comments
//
// bf_and_cb			=> bf_cb_arg bf_and_cb_sym bf_cb_arg.
// bf_or_cb			=> bf_cb_arg bf_or_cb_sym bf_cb_arg.
// bf_xor_cb			=> bf_cb_arg bf_xor_cb_sym bf_cb_arg.
// bf_neg_cb			=> bf_neg_cb_sym bf_cb_arg.
// bf_less_cb			=> bf_less_cb_sym bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg.
// bf_less_equal_cb	=> bf_less_equal_cb_sym bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg.
// bf_greater_cb		=> bf_greater_cb_sym bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg.
// bf_subs_cb			=> bf_subs_cb_sym bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg.
// bf_eq_cb			=> bf_eq_cb_sym bf_cb_arg ws_required wff_cb_arg ws_required wff_cb_arg.
// bf_neq_cb			=> bf_neq_cb_sym bf_cb_arg ws_required wff_cb_arg ws_required wff_cb_arg.
// bf_is_zero_cb		=> bf_is_zero_cb_sym bf_cb_arg ws_required bf_cb_arg.
// bf_is_one_cb		=> bf_is_one_cb_sym bf_cb_arg ws_required bf_cb_arg.
//
// # extra callbacks to speed up computations
// bf_has_clashing_subformulas_cb	=> bf_has_clashing_subformulas_cb_sym bf_cb_arg ws_required bf_cb_arg.
// wff_has_clashing_subformulas_cb	=> wff_has_clashing_subformulas_cb_sym wff_cb_arg ws_required wff_cb_arg.
// bf_has_subformula_cb 			=> bf_has_subformula_cb_sym bf_cb_arg ws_required bf_cb_arg ws_required bf_cb_arg.
// wff_has_subformula_cb 			=> wff_has_subformula_cb_sym wff_cb_arg ws_required wff_cb_arg ws_required wff_cb_arg.
// wff_remove_existential			=> wff_remove_existential_cb_sym wff_cb_arg ws_required wff_cb_arg.
// # bultin_args
// bf_cb_arg	=> capture | ignore | bf.
// wff_cb_arg	=> capture | ignore | wff.
//
// # bf_cb_syms
// bf_and_cb_sym			=> ws "bf_and_cb" ws.
// bf_or_cb_sym			=> ws "bf_or_cb" ws.
// bf_xor_cb_sym			=> ws "bf_xor_cb" ws.
// bf_neg_cb_sym			=> ws "bf_neg_cb" ws.
// bf_less_cb_sym			=> ws "bf_less_cb" ws.
// bf_less_equal_cb_sym	=> ws "bf_less_equal_cb" ws.
// bf_greater_cb_sym		=> ws "bf_greater_cb" ws.
// bf_subs_cb_sym			=> ws "bf_subs_cb" ws.
// bf_eq_cb_sym			=> ws "bf_eq_cb" ws.
// bf_neq_cb_sym			=> ws "bf_neq_cb" ws.
// bf_is_zero_cb_sym		=> ws "bf_is_zero_cb" ws.
// bf_is_one_cb_sym		=> ws "bf_is_one_cb" ws.
//
// # speed up callbacks syms
// # IDEA we could reuse the same symbol
// bf_has_clashing_subformulas_cb_sym		=> ws "bf_has_clashing_subformulas_cb" ws.
// bf_has_subformula_cb_sym				=> ws "bf_has_subformula_cb" ws.
// wff_has_clashing_subformulas_cb_sym		=> ws "wff_has_clashing_subformulas_cb" ws.
// wff_has_subformula_cb_sym				=> ws "wff_has_subformula_cb" ws.
// wff_remove_existential_cb_sym			=> ws "wff_remove_existential_cb" ws.
//
// # input definition
// input			=> in colon open_brace source_binding close_brace.
//
// # main posibilities
// inputs			=> less input (input)* dot.
// main			=> wff dot.
// rule			=> wff_rule | bf_rule .
// rules			=> (rule)*.
// formula			=> rules main.
// library 		=> rules.
// # each builder is define on its own string
// builder			=> captures definition builder_body dot.
// builder_body	=> wff | bf.
// start			=> formula | library | builder | inputs.
//

//
#ifndef __TAU_PARSER_H__
#define __TAU_PARSER_H__
#include <string.h>
#include "parser.h"
struct tau_parser {
	tau_parser() :
		nts(load_nonterminals()), cc(load_cc()),
		g(nts, load_prods(), nt(186), cc), p(g, load_opts()) {}
	std::unique_ptr<typename idni::parser<char, char>::pforest> parse(
		const char* data, size_t size = 0,
		char eof = std::char_traits<char>::eof())
			{ return p.parse(data, size, eof); }
	std::unique_ptr<typename idni::parser<char, char>::pforest> parse(
		int fd, size_t size = 0,
		char eof = std::char_traits<char>::eof())
			{ return p.parse(fd, size, eof); }
	std::unique_ptr<typename idni::parser<char, char>::pforest> parse(
		std::basic_istream<char>& is,
		size_t size = 0,
		char eof = std::char_traits<char>::eof())
			{ return p.parse(is, size, eof); }
	bool found() { return p.found(); }
	typename idni::parser<char, char>::perror_t get_error()
		{ return p.get_error(); }
   enum nonterminal {

			empty_string, eof, space, digit, xdigit, alpha, alnum, punct, printable, eol,
			ws_comment, _Rws_comment_0, ws_required, ws, hex_escape, unicode_escape, char_escape_encode, esc, q_char, q_str,
			q_bqstr, char_punct, _Rchar_punct_1, _Rchar_punct_2, _Rchar_punct_3, char0, char_, string_char, bqstring_char, chars,
			_Rchars_4, _Rchars_5, char_class, sym, definition, equality, nequality, dot, open_parenthesis, close_parenthesis,
			open_bracket, close_bracket, open_brace, close_brace, minus, colon, less, indexes, index, _Rindexes_6,
			_Rindexes_7, variable, capture, ignore, offset, num, _Rnum_8, captures, _Rcaptures_9, _Rcaptures_10,
			var, timed, in, out, _Rtimed_11, wff_rule, wff_matcher, wff_body, wff, wff_ref,
			bf_eq_cb, bf_neq_cb, wff_has_clashing_subformulas_cb, wff_has_subformula_cb, wff_remove_existential, wff_ref_args, _Rwff_ref_args_12, _Rwff_ref_args_13, wff_eq, wff_neq,
			wff_and, wff_neg, wff_xor, wff_or, wff_all, wff_ex, wff_imply, wff_equiv, wff_coimply, wff_t,
			wff_f, bf, wff_and_sym, wff_or_sym, wff_xor_sym, wff_neg_sym, wff_imply_sym, wff_equiv_sym, wff_coimply_sym, wff_all_sym,
			_Rwff_all_14, wff_ex_sym, _Rwff_ex_15, bf_ref, bf_ref_args, _Rbf_ref_args_16, _Rbf_ref_args_17, bf_rule, bf_matcher, bf_body,
			bf_is_zero_cb, bf_is_one_cb, bf_has_clashing_subformulas_cb, bf_has_subformula_cb, bf_constant, bf_and, bf_neg, bf_xor, bf_or, bf_all,
			bf_ex, bf_less, bf_less_equal, bf_greater, bf_less_cb, bf_less_equal_cb, bf_greater_cb, bf_subs_cb, bf_t, bf_f,
			bf_and_sym, bf_or_sym, bf_xor_sym, bf_neg_sym, bf_less_sym, bf_less_equal_sym, bf_greater_sym, bf_all_sym, _Rbf_all_18, bf_ex_sym,
			_Rbf_ex_19, constant, binding, bf_and_cb, bf_or_cb, bf_xor_cb, bf_neg_cb, source_binding, named_binding, type,
			source, source0, _Rsource_20, _Rsource_21, bf_cb_arg, bf_and_cb_sym, bf_or_cb_sym, bf_xor_cb_sym, bf_neg_cb_sym, bf_less_cb_sym,
			bf_less_equal_cb_sym, bf_greater_cb_sym, bf_subs_cb_sym, bf_eq_cb_sym, wff_cb_arg, bf_neq_cb_sym, bf_is_zero_cb_sym, bf_is_one_cb_sym, bf_has_clashing_subformulas_cb_sym, wff_has_clashing_subformulas_cb_sym,
			bf_has_subformula_cb_sym, wff_has_subformula_cb_sym, wff_remove_existential_cb_sym, input, inputs, _Rinputs_22, _Rinputs_23, main, rule, rules,
			_Rrules_24, _Rrules_25, formula, library, builder, builder_body, start,
   };
	size_t id(const std::basic_string<char>& name) { return nts.get(name); }
private:
	std::vector<char> ts{
		'\0', '\n', '\r', '#', '\\', 'x', 'u', '\'', '"',
		'`', 'a', 'l', 'n', 'm', 'p', 'h', 'b', 'k', 'c',
		't', 'r', 'd', 'i', 'g', 'e', 'o', 'f', 'w', 's',
		':', '=', '!', '.', '(', ')', '[', ']', '{', '}',
		'-', '<', '_', '$', '?', 'y', 'q', 'v', 'T', 'F',
		'z',
	};
	idni::nonterminals<char, char> nts{};
	idni::char_class_fns<char> cc;
	idni::grammar<char, char> g;
	idni::parser<char, char> p;
	idni::prods<char, char> t(size_t tid) {
		return idni::prods<char, char>(ts[tid]);
	}
	idni::prods<char, char> nt(size_t ntid) {
		return idni::prods<char, char>(idni::lit<char, char>(ntid, &nts));
	}
	idni::nonterminals<char, char> load_nonterminals() const {
		idni::nonterminals<char, char> nts{};
		for (const auto& nt : {
			"", "eof", "space", "digit", "xdigit", "alpha", "alnum", "punct", "printable", "eol",
			"ws_comment", "_Rws_comment_0", "ws_required", "ws", "hex_escape", "unicode_escape", "char_escape_encode", "esc", "q_char", "q_str",
			"q_bqstr", "char_punct", "_Rchar_punct_1", "_Rchar_punct_2", "_Rchar_punct_3", "char0", "char_", "string_char", "bqstring_char", "chars",
			"_Rchars_4", "_Rchars_5", "char_class", "sym", "definition", "equality", "nequality", "dot", "open_parenthesis", "close_parenthesis",
			"open_bracket", "close_bracket", "open_brace", "close_brace", "minus", "colon", "less", "indexes", "index", "_Rindexes_6",
			"_Rindexes_7", "variable", "capture", "ignore", "offset", "num", "_Rnum_8", "captures", "_Rcaptures_9", "_Rcaptures_10",
			"var", "timed", "in", "out", "_Rtimed_11", "wff_rule", "wff_matcher", "wff_body", "wff", "wff_ref",
			"bf_eq_cb", "bf_neq_cb", "wff_has_clashing_subformulas_cb", "wff_has_subformula_cb", "wff_remove_existential", "wff_ref_args", "_Rwff_ref_args_12", "_Rwff_ref_args_13", "wff_eq", "wff_neq",
			"wff_and", "wff_neg", "wff_xor", "wff_or", "wff_all", "wff_ex", "wff_imply", "wff_equiv", "wff_coimply", "wff_t",
			"wff_f", "bf", "wff_and_sym", "wff_or_sym", "wff_xor_sym", "wff_neg_sym", "wff_imply_sym", "wff_equiv_sym", "wff_coimply_sym", "wff_all_sym",
			"_Rwff_all_14", "wff_ex_sym", "_Rwff_ex_15", "bf_ref", "bf_ref_args", "_Rbf_ref_args_16", "_Rbf_ref_args_17", "bf_rule", "bf_matcher", "bf_body",
			"bf_is_zero_cb", "bf_is_one_cb", "bf_has_clashing_subformulas_cb", "bf_has_subformula_cb", "bf_constant", "bf_and", "bf_neg", "bf_xor", "bf_or", "bf_all",
			"bf_ex", "bf_less", "bf_less_equal", "bf_greater", "bf_less_cb", "bf_less_equal_cb", "bf_greater_cb", "bf_subs_cb", "bf_t", "bf_f",
			"bf_and_sym", "bf_or_sym", "bf_xor_sym", "bf_neg_sym", "bf_less_sym", "bf_less_equal_sym", "bf_greater_sym", "bf_all_sym", "_Rbf_all_18", "bf_ex_sym",
			"_Rbf_ex_19", "constant", "binding", "bf_and_cb", "bf_or_cb", "bf_xor_cb", "bf_neg_cb", "source_binding", "named_binding", "type",
			"source", "source0", "_Rsource_20", "_Rsource_21", "bf_cb_arg", "bf_and_cb_sym", "bf_or_cb_sym", "bf_xor_cb_sym", "bf_neg_cb_sym", "bf_less_cb_sym",
			"bf_less_equal_cb_sym", "bf_greater_cb_sym", "bf_subs_cb_sym", "bf_eq_cb_sym", "wff_cb_arg", "bf_neq_cb_sym", "bf_is_zero_cb_sym", "bf_is_one_cb_sym", "bf_has_clashing_subformulas_cb_sym", "wff_has_clashing_subformulas_cb_sym",
			"bf_has_subformula_cb_sym", "wff_has_subformula_cb_sym", "wff_remove_existential_cb_sym", "input", "inputs", "_Rinputs_22", "_Rinputs_23", "main", "rule", "rules",
			"_Rrules_24", "_Rrules_25", "formula", "library", "builder", "builder_body", "start",
		}) nts.get(nt);
		return nts;
	}
	idni::char_class_fns<char> load_cc() {
		return idni::predefined_char_classes<char, char>({
			"eof",
			"space",
			"digit",
			"xdigit",
			"alpha",
			"alnum",
			"punct",
			"printable",
		}, nts);
	}
	idni::parser<char, char>::options load_opts() {
		idni::parser<char, char>::options o;
		return o;
	}
	idni::prods<char, char> load_prods() {
		idni::prods<char, char> q, nul(idni::lit<char, char>{});
		q(nt(9), (nt(1)));
		q(nt(9), (t(1)));
		q(nt(9), (t(2)));
		q(nt(11), (nt(8)));
		q(nt(11), (nt(8)+nt(11)));
		q(nt(10), (t(3)+nt(9)));
		q(nt(10), (t(3)+nt(11)+nt(9)));
		q(nt(12), (nt(2)+nt(13)));
		q(nt(12), (nt(10)+nt(13)));
		q(nt(13), (nt(12)));
		q(nt(13), (nul));
		q(nt(14), (t(4)+t(4)+t(5)+nt(4)+nt(4)));
		q(nt(15), (t(4)+t(4)+t(6)+nt(4)+nt(4)+nt(4)+nt(4)));
		q(nt(16), (nt(14)));
		q(nt(16), (nt(15)));
		q(nt(17), (t(4)+t(4)+t(4)+t(4)));
		q(nt(18), (t(7)));
		q(nt(19), (t(8)));
		q(nt(20), (t(9)));
		q(nt(22), (nt(17)+nt(18)));
		q(nt(23), (nt(17)+nt(19)));
		q(nt(24), (nt(17)+nt(20)));
		q(nt(21), (nt(7)) & ~(nt(18)) & ~(nt(19)) & ~(nt(20)) & ~(nt(22)) & ~(nt(23)) & ~(nt(24)));
		q(nt(25), (nt(2)));
		q(nt(25), (nt(6)));
		q(nt(25), (nt(16)));
		q(nt(25), (nt(21)));
		q(nt(26), (nt(17)+nt(18)));
		q(nt(26), (nt(19)));
		q(nt(26), (nt(20)));
		q(nt(26), (nt(25)));
		q(nt(27), (nt(17)+nt(19)));
		q(nt(27), (nt(18)));
		q(nt(27), (nt(20)));
		q(nt(27), (nt(25)));
		q(nt(28), (nt(17)+nt(20)));
		q(nt(28), (nt(18)));
		q(nt(28), (nt(19)));
		q(nt(28), (nt(25)));
		q(nt(30), (nt(6)));
		q(nt(31), (nt(30)+nt(31)));
		q(nt(31), (nul));
		q(nt(29), (nt(5)+nt(31)));
		q(nt(32), (t(10)+t(11)+t(12)+t(6)+t(13)));
		q(nt(32), (t(10)+t(11)+t(14)+t(15)+t(10)));
		q(nt(32), (t(16)+t(11)+t(10)+t(12)+t(17)));
		q(nt(32), (t(18)+t(12)+t(19)+t(20)+t(11)));
		q(nt(32), (t(21)+t(22)+t(23)+t(22)+t(19)));
		q(nt(32), (t(24)+t(25)+t(26)));
		q(nt(32), (t(23)+t(20)+t(10)+t(14)+t(15)));
		q(nt(32), (t(11)+t(25)+t(27)+t(24)+t(20)));
		q(nt(32), (t(14)+t(20)+t(22)+t(12)+t(19)+t(10)+t(16)+t(11)+t(24)));
		q(nt(32), (t(14)+t(6)+t(12)+t(18)+t(19)));
		q(nt(32), (t(28)+t(14)+t(10)+t(18)+t(24)));
		q(nt(32), (t(6)+t(14)+t(14)+t(24)+t(20)));
		q(nt(32), (t(5)+t(21)+t(22)+t(23)+t(22)+t(19)));
		q(nt(33), (nt(29)));
		q(nt(34), (nt(13)+t(29)+t(30)+nt(13)));
		q(nt(35), (nt(13)+t(30)+nt(13)));
		q(nt(36), (nt(13)+t(31)+t(30)+nt(13)));
		q(nt(37), (nt(13)+t(32)+nt(13)));
		q(nt(38), (nt(13)+t(33)+nt(13)));
		q(nt(39), (nt(13)+t(34)+nt(13)));
		q(nt(40), (nt(13)+t(35)+nt(13)));
		q(nt(41), (nt(13)+t(36)+nt(13)));
		q(nt(42), (nt(13)+t(37)+nt(13)));
		q(nt(43), (nt(13)+t(38)+nt(13)));
		q(nt(44), (nt(13)+t(39)+nt(13)));
		q(nt(45), (nt(13)+t(29)+nt(13)));
		q(nt(46), (nt(13)+t(40)+nt(13)));
		q(nt(49), (nt(48)));
		q(nt(50), (nt(49)+nt(50)));
		q(nt(50), (nul));
		q(nt(47), (nt(40)+nt(50)+nt(41)));
		q(nt(48), (nt(51)));
		q(nt(48), (nt(52)));
		q(nt(48), (nt(53)));
		q(nt(48), (nt(54)));
		q(nt(56), (nt(3)));
		q(nt(56), (nt(3)+nt(56)));
		q(nt(55), (nt(56)));
		q(nt(58), (nt(12)+nt(52)));
		q(nt(59), (nt(58)+nt(59)));
		q(nt(59), (nul));
		q(nt(57), (nt(38)+nt(52)+nt(38)+nt(39)));
		q(nt(57), (nt(38)+nt(52)+nt(59)+nt(39)));
		q(nt(51), (nt(60)));
		q(nt(51), (nt(61)));
		q(nt(64), (nt(62)));
		q(nt(64), (nt(63)));
		q(nt(61), (nt(64)+nt(47)));
		q(nt(54), (nt(51)));
		q(nt(54), (nt(51)+nt(44)+nt(55)));
		q(nt(53), (t(41)));
		q(nt(52), (t(42)+nt(29)));
		q(nt(60), (t(43)+nt(29)));
		q(nt(62), (t(43)+t(22)+t(41)+nt(29)));
		q(nt(63), (t(43)+t(25)+t(41)+nt(29)));
		q(nt(65), (nt(66)+nt(34)+nt(67)+nt(37)));
		q(nt(66), (nt(68)));
		q(nt(66), (nt(69)));
		q(nt(67), (nt(68)));
		q(nt(67), (nt(70)));
		q(nt(67), (nt(71)));
		q(nt(67), (nt(72)));
		q(nt(67), (nt(73)));
		q(nt(67), (nt(74)));
		q(nt(69), (nt(33)+nt(47)+nt(75)));
		q(nt(76), (nt(51)));
		q(nt(77), (nt(76)+nt(77)));
		q(nt(77), (nul));
		q(nt(75), (nt(38)+nt(77)+nt(39)));
		q(nt(68), (nt(52)));
		q(nt(68), (nt(53)));
		q(nt(68), (nt(69)));
		q(nt(68), (nt(78)));
		q(nt(68), (nt(79)));
		q(nt(68), (nt(80)));
		q(nt(68), (nt(81)));
		q(nt(68), (nt(82)));
		q(nt(68), (nt(83)));
		q(nt(68), (nt(84)));
		q(nt(68), (nt(85)));
		q(nt(68), (nt(86)));
		q(nt(68), (nt(87)));
		q(nt(68), (nt(88)));
		q(nt(68), (nt(89)));
		q(nt(68), (nt(90)));
		q(nt(78), (nt(38)+nt(91)+nt(35)+nt(90)+nt(39)));
		q(nt(79), (nt(38)+nt(91)+nt(36)+nt(90)+nt(39)));
		q(nt(80), (nt(38)+nt(68)+nt(92)+nt(68)+nt(39)));
		q(nt(83), (nt(38)+nt(68)+nt(93)+nt(68)+nt(39)));
		q(nt(82), (nt(38)+nt(68)+nt(94)+nt(68)+nt(39)));
		q(nt(81), (nt(95)+nt(68)));
		q(nt(86), (nt(38)+nt(68)+nt(96)+nt(68)+nt(39)));
		q(nt(87), (nt(38)+nt(68)+nt(97)+nt(68)+nt(39)));
		q(nt(88), (nt(38)+nt(68)+nt(98)+nt(68)+nt(39)));
		q(nt(100), (nt(51)));
		q(nt(100), (nt(52)));
		q(nt(100), (nt(53)));
		q(nt(84), (nt(99)+nt(100)+nt(12)+nt(68)));
		q(nt(102), (nt(51)));
		q(nt(102), (nt(52)));
		q(nt(102), (nt(53)));
		q(nt(85), (nt(101)+nt(102)+nt(12)+nt(68)));
		q(nt(92), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(10)+t(12)+t(21)+nt(13)));
		q(nt(93), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(25)+t(20)+nt(13)));
		q(nt(94), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(5)+t(25)+t(20)+nt(13)));
		q(nt(95), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(12)+t(24)+t(23)+nt(13)));
		q(nt(96), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(22)+t(13)+t(14)+t(11)+t(44)+nt(13)));
		q(nt(97), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(24)+t(45)+t(6)+t(22)+t(46)+nt(13)));
		q(nt(98), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(18)+t(25)+t(22)+t(13)+t(14)+t(11)+t(44)+nt(13)));
		q(nt(99), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(10)+t(11)+t(11)+nt(13)));
		q(nt(101), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(24)+t(5)+nt(13)));
		q(nt(89), (nt(13)+t(47)+nt(13)));
		q(nt(90), (nt(13)+t(48)+nt(13)));
		q(nt(103), (nt(33)+nt(47)+nt(104)));
		q(nt(105), (nt(51)));
		q(nt(106), (nt(105)+nt(106)));
		q(nt(106), (nul));
		q(nt(104), (nt(38)+nt(106)+nt(39)));
		q(nt(107), (nt(108)+nt(34)+nt(109)+nt(37)));
		q(nt(108), (nt(91)));
		q(nt(109), (nt(91)));
		q(nt(109), (nt(110)));
		q(nt(109), (nt(111)));
		q(nt(109), (nt(112)));
		q(nt(109), (nt(113)));
		q(nt(91), (nt(51)));
		q(nt(91), (nt(52)));
		q(nt(91), (nt(53)));
		q(nt(91), (nt(114)));
		q(nt(91), (nt(115)));
		q(nt(91), (nt(116)));
		q(nt(91), (nt(117)));
		q(nt(91), (nt(118)));
		q(nt(91), (nt(119)));
		q(nt(91), (nt(120)));
		q(nt(91), (nt(121)));
		q(nt(91), (nt(122)));
		q(nt(91), (nt(123)));
		q(nt(91), (nt(124)));
		q(nt(91), (nt(125)));
		q(nt(91), (nt(126)));
		q(nt(91), (nt(127)));
		q(nt(91), (nt(128)));
		q(nt(91), (nt(129)));
		q(nt(115), (nt(38)+nt(91)+nt(130)+nt(91)+nt(39)));
		q(nt(118), (nt(38)+nt(91)+nt(131)+nt(91)+nt(39)));
		q(nt(117), (nt(38)+nt(91)+nt(132)+nt(13)+nt(91)+nt(39)));
		q(nt(116), (nt(133)+nt(91)));
		q(nt(121), (nt(38)+nt(91)+nt(134)+nt(91)+nt(39)));
		q(nt(122), (nt(38)+nt(91)+nt(135)+nt(91)+nt(39)));
		q(nt(123), (nt(38)+nt(91)+nt(136)+nt(91)+nt(39)));
		q(nt(138), (nt(51)));
		q(nt(138), (nt(52)));
		q(nt(119), (nt(137)+nt(12)+nt(138)+nt(12)+nt(91)));
		q(nt(140), (nt(51)));
		q(nt(140), (nt(52)));
		q(nt(120), (nt(139)+nt(12)+nt(140)+nt(12)+nt(91)));
		q(nt(130), (nt(13)+t(16)+t(26)+t(41)+t(10)+t(12)+t(21)+nt(13)));
		q(nt(131), (nt(13)+t(16)+t(26)+t(41)+t(25)+t(20)+nt(13)));
		q(nt(132), (nt(13)+t(16)+t(26)+t(41)+t(5)+t(25)+t(20)+nt(13)));
		q(nt(133), (nt(13)+t(16)+t(26)+t(41)+t(12)+t(24)+t(23)+nt(13)));
		q(nt(134), (nt(13)+t(16)+t(26)+t(41)+t(11)+t(24)+t(28)+t(28)+nt(13)));
		q(nt(135), (nt(13)+t(16)+t(26)+t(41)+t(11)+t(24)+t(28)+t(28)+t(41)+t(24)+t(45)+t(6)+t(10)+t(11)+nt(13)));
		q(nt(136), (nt(13)+t(16)+t(26)+t(41)+t(23)+t(20)+t(24)+t(10)+t(19)+t(24)+t(20)+nt(13)));
		q(nt(137), (nt(13)+t(16)+t(26)+t(41)+t(10)+t(11)+t(11)+nt(13)));
		q(nt(139), (nt(13)+t(16)+t(26)+t(41)+t(24)+t(5)+nt(13)));
		q(nt(128), (nt(13)+t(47)+nt(13)));
		q(nt(129), (nt(13)+t(48)+nt(13)));
		q(nt(114), (nt(42)+nt(141)+nt(43)));
		q(nt(141), (nt(52)));
		q(nt(141), (nt(53)));
		q(nt(141), (nt(142)));
		q(nt(141), (nt(143)));
		q(nt(141), (nt(144)));
		q(nt(141), (nt(145)));
		q(nt(141), (nt(146)));
		q(nt(142), (nt(147)));
		q(nt(142), (nt(148)));
		q(nt(148), (nt(29)));
		q(nt(147), (nt(149)+nt(45)+nt(150)));
		q(nt(149), (nt(29)));
		q(nt(149), (nul));
		q(nt(151), (nt(2)));
		q(nt(151), (nt(6)));
		q(nt(151), (nt(16)));
		q(nt(151), (nt(21)));
		q(nt(152), (nt(151)));
		q(nt(153), (nt(152)));
		q(nt(153), (nt(152)+nt(153)));
		q(nt(150), (nt(153)));
		q(nt(143), (nt(154)+nt(155)+nt(154)));
		q(nt(144), (nt(154)+nt(156)+nt(154)));
		q(nt(145), (nt(154)+nt(157)+nt(154)));
		q(nt(146), (nt(158)+nt(154)));
		q(nt(124), (nt(159)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)));
		q(nt(125), (nt(160)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)));
		q(nt(126), (nt(161)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)));
		q(nt(127), (nt(162)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)));
		q(nt(70), (nt(163)+nt(154)+nt(12)+nt(164)+nt(12)+nt(164)));
		q(nt(71), (nt(165)+nt(154)+nt(12)+nt(164)+nt(12)+nt(164)));
		q(nt(110), (nt(166)+nt(154)+nt(12)+nt(154)));
		q(nt(111), (nt(167)+nt(154)+nt(12)+nt(154)));
		q(nt(112), (nt(168)+nt(154)+nt(12)+nt(154)));
		q(nt(72), (nt(169)+nt(164)+nt(12)+nt(164)));
		q(nt(113), (nt(170)+nt(154)+nt(12)+nt(154)+nt(12)+nt(154)));
		q(nt(73), (nt(171)+nt(164)+nt(12)+nt(164)+nt(12)+nt(164)));
		q(nt(74), (nt(172)+nt(164)+nt(12)+nt(164)));
		q(nt(154), (nt(52)));
		q(nt(154), (nt(53)));
		q(nt(154), (nt(91)));
		q(nt(164), (nt(52)));
		q(nt(164), (nt(53)));
		q(nt(164), (nt(68)));
		q(nt(155), (nt(13)+t(16)+t(26)+t(41)+t(10)+t(12)+t(21)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(156), (nt(13)+t(16)+t(26)+t(41)+t(25)+t(20)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(157), (nt(13)+t(16)+t(26)+t(41)+t(5)+t(25)+t(20)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(158), (nt(13)+t(16)+t(26)+t(41)+t(12)+t(24)+t(23)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(159), (nt(13)+t(16)+t(26)+t(41)+t(11)+t(24)+t(28)+t(28)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(160), (nt(13)+t(16)+t(26)+t(41)+t(11)+t(24)+t(28)+t(28)+t(41)+t(24)+t(45)+t(6)+t(10)+t(11)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(161), (nt(13)+t(16)+t(26)+t(41)+t(23)+t(20)+t(24)+t(10)+t(19)+t(24)+t(20)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(162), (nt(13)+t(16)+t(26)+t(41)+t(28)+t(6)+t(16)+t(28)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(163), (nt(13)+t(16)+t(26)+t(41)+t(24)+t(45)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(165), (nt(13)+t(16)+t(26)+t(41)+t(12)+t(24)+t(45)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(166), (nt(13)+t(16)+t(26)+t(41)+t(22)+t(28)+t(41)+t(49)+t(24)+t(20)+t(25)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(167), (nt(13)+t(16)+t(26)+t(41)+t(22)+t(28)+t(41)+t(25)+t(12)+t(24)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(168), (nt(13)+t(16)+t(26)+t(41)+t(15)+t(10)+t(28)+t(41)+t(18)+t(11)+t(10)+t(28)+t(15)+t(22)+t(12)+t(23)+t(41)+t(28)+t(6)+t(16)+t(26)+t(25)+t(20)+t(13)+t(6)+t(11)+t(10)+t(28)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(170), (nt(13)+t(16)+t(26)+t(41)+t(15)+t(10)+t(28)+t(41)+t(28)+t(6)+t(16)+t(26)+t(25)+t(20)+t(13)+t(6)+t(11)+t(10)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(169), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(15)+t(10)+t(28)+t(41)+t(18)+t(11)+t(10)+t(28)+t(15)+t(22)+t(12)+t(23)+t(41)+t(28)+t(6)+t(16)+t(26)+t(25)+t(20)+t(13)+t(6)+t(11)+t(10)+t(28)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(171), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(15)+t(10)+t(28)+t(41)+t(28)+t(6)+t(16)+t(26)+t(25)+t(20)+t(13)+t(6)+t(11)+t(10)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(172), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(20)+t(24)+t(13)+t(25)+t(46)+t(24)+t(41)+t(24)+t(5)+t(22)+t(28)+t(19)+t(24)+t(12)+t(19)+t(22)+t(10)+t(11)+t(41)+t(18)+t(16)+nt(13)));
		q(nt(173), (nt(62)+nt(45)+nt(42)+nt(147)+nt(43)));
		q(nt(175), (nt(173)));
		q(nt(176), (nt(175)+nt(176)));
		q(nt(176), (nul));
		q(nt(174), (nt(46)+nt(173)+nt(176)+nt(37)));
		q(nt(177), (nt(68)+nt(37)));
		q(nt(178), (nt(65)));
		q(nt(178), (nt(107)));
		q(nt(180), (nt(178)));
		q(nt(181), (nt(180)+nt(181)));
		q(nt(181), (nul));
		q(nt(179), (nt(181)));
		q(nt(182), (nt(179)+nt(177)));
		q(nt(183), (nt(179)));
		q(nt(184), (nt(57)+nt(34)+nt(185)+nt(37)));
		q(nt(185), (nt(68)));
		q(nt(185), (nt(91)));
		q(nt(186), (nt(174)));
		q(nt(186), (nt(182)));
		q(nt(186), (nt(183)));
		q(nt(186), (nt(184)));
		return q;
	}
};
#endif // __TAU_PARSER_H__
