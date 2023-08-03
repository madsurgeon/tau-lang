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
// sym				=> ws chars ws.
// 
// # common symbols
// equality			=> ws '=' ws. 
// dot 				=> ws '.' ws.
// open_parenthesis	=> ws '(' ws.
// close_parenthesis	=> ws ')' ws.
// open_bracket		=> ws '[' ws.
// close_bracket		=> ws ']' ws.
// open_brace			=> ws '{' ws.
// close_brace			=> ws '}' ws.
// less_than			=> ws '<' ws.
// greater_than		=> ws '>' ws.
// minus				=> ws '-' ws.
// plus				=> ws '+' ws.
// 
// # indexes
// indexes				=> open_bracket index* close_bracket.
// index				=> var | offset.
// num					=> digit+.
// 
// # variables 
// variable		=> var | ignore | capture.
// 
// # QUESTION dows timed variables have one index or several?
// timed			=> ( var_in| var_out) indexes. 
// offset			=> variable | variable minus num | variable plus num.
// ignore 			=> '_'.
// capture			=> '$' chars.
// var				=> '?' chars.
// var_in			=> "%i_" chars. # instead of '<', easy to remember
// var_out			=> "%o_" chars. # instead of '>', easy to remember
// 
// # wff
// wff_def				=> wff_rule dot.
// wff_rule			=> wff_head equality wff_body dot.
// wff_body 			=> wff.
// wff_head			=> sym indexes wff_head_args.
// wff_head_args		=> open_parenthesis variable* close_parenthesis.
// 
// wff 			=> wff_eq | wff_ref | wff_and | wff_neg | wff_xor | wff_or | wff_all | wff_ex.
// wff_eq 			=> bf equality bf.
// wff_ref			=> wff_head.
// wff_and			=> open_parenthesis wff wff_and_sym wff close_parenthesis.
// wff_or			=> open_parenthesis wff wff_or_sym wff close_parenthesis.
// wff_xor			=> open_parenthesis wff wff_xor_sym wff close_parenthesis.
// wff_neg			=> wff_neg_sym open_parenthesis wff close_parenthesis.
// wff_all			=> wff_all_sym variable open_parenthesis wff close_parenthesis.
// wff_ex			=> wff_ex_sym variable open_parenthesis wff close_parenthesis.
// 
// # wff_op_sym
// wff_and_sym		=> ws "wff_and" ws.
// wff_or_sym		=> ws "wff_or" ws.
// wff_xor_sym		=> ws "wff_xor" ws.
// wff_neg_sym		=> ws "wff_neg" ws.
// wff_all_sym		=> ws "wff_all" ws.
// wff_ex_sym		=> ws "wff_ex" ws.
// 
// #cbf
// cbf_def 		=> cbf_rule dot.
// cbf_rule 		=> cbf_head equality cbf dot.
// cbf_head 		=> sym indexes open_parenthesis variable* close_parenthesis.
// cbf 			=> bf | cbf_if | cbf_ref | bf_and | bf_neg | bf_xor | bf_or.
// cbf_ref			=> cbf_head.
// cbf_if			=> cbf_if_sym open_parenthesis cbf_if_condition close_parenthesis 
// 					cbf_then_sym cbf_if_then 
// 					cbf_else_sym cbf_if_else. 
// cbf_if_condition	=> wff.
// cbf_if_then			=> cbf.
// cbf_if_else			=> cbf.
// 
// # cbf_op_sym
// cbf_and_sym		=> ws "cbf_and" ws.
// cbf_or_sym		=> ws "cbf_or" ws.
// cbf_xor_sym		=> ws "cbf_xor" ws.
// cbf_neg_sym		=> ws "cbf_neg" ws.
// cbf_if_sym		=> ws "cbf_if" ws.
// cbf_then_sym	=> ws "then" ws.
// cbf_else_sym	=> ws "else" ws.
// 
// # bf - TODO bf => constant | bf & bf | bf | bf | ~bf | bf ^ bf | in[n][t] 
// # | out[n][t] <<< this thing is important!!!
// #
// # QUESTION: Does timed vars appear only in bf formulas?
// 
// bf_rule			=> ws bf equality bf ws dot.
// bf				=> bf_constant | cbf | cbf_ref | bf_and | bf_neg | bf_xor | bf_or
// 					| bf_all | bf_ex | variable | timed.
// bf_and			=> open_parenthesis bf bf_and_sym bf close_parenthesis.
// bf_or			=> open_parenthesis bf bf_or_sym close_parenthesis.
// bf_xor			=> open_parenthesis bf bf_xor_sym ws bf close_parenthesis.
// bf_neg			=> bf_neg_sym open_parenthesis bf close_parenthesis.
// bf_all			=> bf_all_sym variable open_parenthesis bf close_parenthesis.
// bf_ex			=> bf_ex_sym variable open_parenthesis bf close_parenthesis.
// 
// # bf_op_sym
// bf_and_sym		=> ws "bf_and" ws.
// bf_or_sym		=> ws "bf_or" ws.
// bf_xor_sym		=> ws "bf_xor" ws.
// bf_neg_sym		=> ws "bf_neg" ws.
// bf_all_sym		=> ws "bf_all" ws.
// bf_ex_sym		=> ws "bf_ex" ws.
// 
// # constant
// bf_constant		=> open_brace constant close_brace.
// 
// #constants
// constant		=> T | F | bf_builtin | binding | capture | ignore.
// T				=> ws '1' ws.
// F				=> ws '0' ws.
// bf_builtin		=> bf_and_bltin | bf_or_bltin | bf_xor_bltin | bf_neg_bltin | bf_subs_bltin.
// binding			=> ws chars ws.
// 
// # bf_bltins
// bf_and_bltin	=> bltin_arg bf_and_bltin_sym bltin_arg.
// bf_or_bltin		=> bltin_arg bf_or_bltin_sym bltin_arg.
// bf_xor_bltin	=> bltin_arg bf_xor_bltin_sym bltin_arg.
// bf_neg_bltin	=> neg_bltin_sym bltin_arg.
// bf_subs_bltin	=> subs_bltin_sym bltin_arg bltin_arg bltin_arg.
// 
// # bf_bultin_arg
// bltin_arg	=> capture | T | F.
// 
// # bf_bltin_syms
// bf_and_bltin_sym	=> ws "bf_and_bltin" ws.
// bf_or_bltin_sym		=> ws "bf_or_bltin" ws.
// bf_xor_bltin_sym	=> ws "bf_xor_bltin" ws.
// bf_neg_bltin_sym	=> ws "bf_neg_bltin" ws.
// subs_bltin_sym		=> ws "subs_bltin" ws.
// 
// # main - TODO - tau & tau /n tau && tau /n tau &&& tau
// main			=> wff dot.
// rule			=> wff_def | cbf_def | bf_rule.
// program			=> rule* main dot.
// library 		=> rule+.
// start			=> program | library.
// 
//

//
#ifndef __TAU_PARSER_H__
#define __TAU_PARSER_H__
#include <string.h>
#include "parser.h"
struct tau_parser {
	tau_parser() :
		nts(load_nonterminals()), cc(load_cc()),
		g(nts, load_prods(), nt(136), cc), p(g, load_opts()) {}
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
			_Rchars_4, _Rchars_5, char_class, sym, equality, dot, open_parenthesis, close_parenthesis, open_bracket, close_bracket, 
			open_brace, close_brace, less_than, greater_than, minus, plus, indexes, index, _Rindexes_6, var, 
			offset, num, _Rnum_7, variable, ignore, capture, timed, var_in, var_out, _Rtimed_8, 
			wff_def, wff_rule, wff_head, wff_body, wff, wff_head_args, _Rwff_head_args_9, wff_eq, wff_ref, wff_and, 
			wff_neg, wff_xor, wff_or, wff_all, wff_ex, bf, wff_and_sym, wff_or_sym, wff_xor_sym, wff_neg_sym, 
			wff_all_sym, wff_ex_sym, cbf_def, cbf_rule, cbf_head, cbf, _Rcbf_head_10, cbf_if, cbf_ref, bf_and, 
			bf_neg, bf_xor, bf_or, cbf_if_sym, cbf_if_condition, cbf_then_sym, cbf_if_then, cbf_else_sym, cbf_if_else, cbf_and_sym, 
			cbf_or_sym, cbf_xor_sym, cbf_neg_sym, bf_rule, bf_constant, bf_all, bf_ex, bf_and_sym, bf_or_sym, bf_xor_sym, 
			bf_neg_sym, bf_all_sym, bf_ex_sym, constant, T, F, bf_builtin, binding, bf_and_bltin, bf_or_bltin, 
			bf_xor_bltin, bf_neg_bltin, bf_subs_bltin, bltin_arg, bf_and_bltin_sym, bf_or_bltin_sym, bf_xor_bltin_sym, neg_bltin_sym, subs_bltin_sym, bf_neg_bltin_sym, 
			main, rule, program, _Rprogram_11, library, _Rlibrary_12, start, 
   };
	size_t id(const std::basic_string<char>& name) { return nts.get(name); }
private:
	std::vector<char> ts{
		'\0', '\n', '\r', '#', '\\', 'x', 'u', '\'', '"', 
		'`', 'a', 'l', 'n', 'm', 'p', 'h', 'b', 'k', 'c', 
		't', 'r', 'd', 'i', 'g', 'e', 'o', 'f', 'w', 's', 
		'=', '.', '(', ')', '[', ']', '{', '}', '<', '>', 
		'-', '+', '_', '$', '?', '%', '1', '0', 
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
			"_Rchars_4", "_Rchars_5", "char_class", "sym", "equality", "dot", "open_parenthesis", "close_parenthesis", "open_bracket", "close_bracket", 
			"open_brace", "close_brace", "less_than", "greater_than", "minus", "plus", "indexes", "index", "_Rindexes_6", "var", 
			"offset", "num", "_Rnum_7", "variable", "ignore", "capture", "timed", "var_in", "var_out", "_Rtimed_8", 
			"wff_def", "wff_rule", "wff_head", "wff_body", "wff", "wff_head_args", "_Rwff_head_args_9", "wff_eq", "wff_ref", "wff_and", 
			"wff_neg", "wff_xor", "wff_or", "wff_all", "wff_ex", "bf", "wff_and_sym", "wff_or_sym", "wff_xor_sym", "wff_neg_sym", 
			"wff_all_sym", "wff_ex_sym", "cbf_def", "cbf_rule", "cbf_head", "cbf", "_Rcbf_head_10", "cbf_if", "cbf_ref", "bf_and", 
			"bf_neg", "bf_xor", "bf_or", "cbf_if_sym", "cbf_if_condition", "cbf_then_sym", "cbf_if_then", "cbf_else_sym", "cbf_if_else", "cbf_and_sym", 
			"cbf_or_sym", "cbf_xor_sym", "cbf_neg_sym", "bf_rule", "bf_constant", "bf_all", "bf_ex", "bf_and_sym", "bf_or_sym", "bf_xor_sym", 
			"bf_neg_sym", "bf_all_sym", "bf_ex_sym", "constant", "T", "F", "bf_builtin", "binding", "bf_and_bltin", "bf_or_bltin", 
			"bf_xor_bltin", "bf_neg_bltin", "bf_subs_bltin", "bltin_arg", "bf_and_bltin_sym", "bf_or_bltin_sym", "bf_xor_bltin_sym", "neg_bltin_sym", "subs_bltin_sym", "bf_neg_bltin_sym", 
			"main", "rule", "program", "_Rprogram_11", "library", "_Rlibrary_12", "start", 
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
		q(nt(33), (nt(13)+nt(29)+nt(13)));
		q(nt(34), (nt(13)+t(29)+nt(13)));
		q(nt(35), (nt(13)+t(30)+nt(13)));
		q(nt(36), (nt(13)+t(31)+nt(13)));
		q(nt(37), (nt(13)+t(32)+nt(13)));
		q(nt(38), (nt(13)+t(33)+nt(13)));
		q(nt(39), (nt(13)+t(34)+nt(13)));
		q(nt(40), (nt(13)+t(35)+nt(13)));
		q(nt(41), (nt(13)+t(36)+nt(13)));
		q(nt(42), (nt(13)+t(37)+nt(13)));
		q(nt(43), (nt(13)+t(38)+nt(13)));
		q(nt(44), (nt(13)+t(39)+nt(13)));
		q(nt(45), (nt(13)+t(40)+nt(13)));
		q(nt(48), (nt(38)+nt(47)+nt(48)));
		q(nt(48), (nul));
		q(nt(46), (nt(48)+nt(39)));
		q(nt(47), (nt(49)));
		q(nt(47), (nt(50)));
		q(nt(52), (nt(3)));
		q(nt(52), (nt(3)+nt(52)));
		q(nt(51), (nt(52)));
		q(nt(53), (nt(49)));
		q(nt(53), (nt(54)));
		q(nt(53), (nt(55)));
		q(nt(59), (nt(57)));
		q(nt(59), (nt(58)));
		q(nt(56), (nt(59)+nt(46)));
		q(nt(50), (nt(53)));
		q(nt(50), (nt(53)+nt(44)+nt(51)));
		q(nt(50), (nt(53)+nt(45)+nt(51)));
		q(nt(54), (t(41)));
		q(nt(55), (t(42)+nt(29)));
		q(nt(49), (t(43)+nt(29)));
		q(nt(57), (t(44)+t(22)+t(41)+nt(29)));
		q(nt(58), (t(44)+t(25)+t(41)+nt(29)));
		q(nt(60), (nt(61)+nt(35)));
		q(nt(61), (nt(62)+nt(34)+nt(63)+nt(35)));
		q(nt(63), (nt(64)));
		q(nt(62), (nt(33)+nt(46)+nt(65)));
		q(nt(66), (nt(36)+nt(53)+nt(66)));
		q(nt(66), (nul));
		q(nt(65), (nt(66)+nt(37)));
		q(nt(64), (nt(67)));
		q(nt(64), (nt(68)));
		q(nt(64), (nt(69)));
		q(nt(64), (nt(70)));
		q(nt(64), (nt(71)));
		q(nt(64), (nt(72)));
		q(nt(64), (nt(73)));
		q(nt(64), (nt(74)));
		q(nt(67), (nt(75)+nt(34)+nt(75)));
		q(nt(68), (nt(62)));
		q(nt(69), (nt(36)+nt(64)+nt(76)+nt(64)+nt(37)));
		q(nt(72), (nt(36)+nt(64)+nt(77)+nt(64)+nt(37)));
		q(nt(71), (nt(36)+nt(64)+nt(78)+nt(64)+nt(37)));
		q(nt(70), (nt(79)+nt(36)+nt(64)+nt(37)));
		q(nt(73), (nt(80)+nt(53)+nt(36)+nt(64)+nt(37)));
		q(nt(74), (nt(81)+nt(53)+nt(36)+nt(64)+nt(37)));
		q(nt(76), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(10)+t(12)+t(21)+nt(13)));
		q(nt(77), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(25)+t(20)+nt(13)));
		q(nt(78), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(5)+t(25)+t(20)+nt(13)));
		q(nt(79), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(12)+t(24)+t(23)+nt(13)));
		q(nt(80), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(10)+t(11)+t(11)+nt(13)));
		q(nt(81), (nt(13)+t(27)+t(26)+t(26)+t(41)+t(24)+t(5)+nt(13)));
		q(nt(82), (nt(83)+nt(35)));
		q(nt(83), (nt(84)+nt(34)+nt(85)+nt(35)));
		q(nt(86), (nt(33)+nt(46)+nt(36)+nt(53)+nt(86)));
		q(nt(86), (nul));
		q(nt(84), (nt(86)+nt(37)));
		q(nt(85), (nt(75)));
		q(nt(85), (nt(87)));
		q(nt(85), (nt(88)));
		q(nt(85), (nt(89)));
		q(nt(85), (nt(90)));
		q(nt(85), (nt(91)));
		q(nt(85), (nt(92)));
		q(nt(88), (nt(84)));
		q(nt(87), (nt(93)+nt(36)+nt(94)+nt(37)+nt(95)+nt(96)+nt(97)+nt(98)));
		q(nt(94), (nt(64)));
		q(nt(96), (nt(85)));
		q(nt(98), (nt(85)));
		q(nt(99), (nt(13)+t(18)+t(16)+t(26)+t(41)+t(10)+t(12)+t(21)+nt(13)));
		q(nt(100), (nt(13)+t(18)+t(16)+t(26)+t(41)+t(25)+t(20)+nt(13)));
		q(nt(101), (nt(13)+t(18)+t(16)+t(26)+t(41)+t(5)+t(25)+t(20)+nt(13)));
		q(nt(102), (nt(13)+t(18)+t(16)+t(26)+t(41)+t(12)+t(24)+t(23)+nt(13)));
		q(nt(93), (nt(13)+t(18)+t(16)+t(26)+t(41)+t(22)+t(26)+nt(13)));
		q(nt(95), (nt(13)+t(19)+t(15)+t(24)+t(12)+nt(13)));
		q(nt(97), (nt(13)+t(24)+t(11)+t(28)+t(24)+nt(13)));
		q(nt(103), (nt(13)+nt(75)+nt(34)+nt(75)+nt(13)+nt(35)));
		q(nt(75), (nt(53)));
		q(nt(75), (nt(56)));
		q(nt(75), (nt(85)));
		q(nt(75), (nt(88)));
		q(nt(75), (nt(89)));
		q(nt(75), (nt(90)));
		q(nt(75), (nt(91)));
		q(nt(75), (nt(92)));
		q(nt(75), (nt(104)));
		q(nt(75), (nt(105)));
		q(nt(75), (nt(106)));
		q(nt(89), (nt(36)+nt(75)+nt(107)+nt(75)+nt(37)));
		q(nt(92), (nt(36)+nt(75)+nt(108)+nt(37)));
		q(nt(91), (nt(36)+nt(75)+nt(109)+nt(13)+nt(75)+nt(37)));
		q(nt(90), (nt(110)+nt(36)+nt(75)+nt(37)));
		q(nt(105), (nt(111)+nt(53)+nt(36)+nt(75)+nt(37)));
		q(nt(106), (nt(112)+nt(53)+nt(36)+nt(75)+nt(37)));
		q(nt(107), (nt(13)+t(16)+t(26)+t(41)+t(10)+t(12)+t(21)+nt(13)));
		q(nt(108), (nt(13)+t(16)+t(26)+t(41)+t(25)+t(20)+nt(13)));
		q(nt(109), (nt(13)+t(16)+t(26)+t(41)+t(5)+t(25)+t(20)+nt(13)));
		q(nt(110), (nt(13)+t(16)+t(26)+t(41)+t(12)+t(24)+t(23)+nt(13)));
		q(nt(111), (nt(13)+t(16)+t(26)+t(41)+t(10)+t(11)+t(11)+nt(13)));
		q(nt(112), (nt(13)+t(16)+t(26)+t(41)+t(24)+t(5)+nt(13)));
		q(nt(104), (nt(40)+nt(113)+nt(41)));
		q(nt(113), (nt(54)));
		q(nt(113), (nt(55)));
		q(nt(113), (nt(114)));
		q(nt(113), (nt(115)));
		q(nt(113), (nt(116)));
		q(nt(113), (nt(117)));
		q(nt(114), (nt(13)+t(45)+nt(13)));
		q(nt(115), (nt(13)+t(46)+nt(13)));
		q(nt(116), (nt(118)));
		q(nt(116), (nt(119)));
		q(nt(116), (nt(120)));
		q(nt(116), (nt(121)));
		q(nt(116), (nt(122)));
		q(nt(117), (nt(13)+nt(29)+nt(13)));
		q(nt(118), (nt(123)+nt(124)+nt(123)));
		q(nt(119), (nt(123)+nt(125)+nt(123)));
		q(nt(120), (nt(123)+nt(126)+nt(123)));
		q(nt(121), (nt(127)+nt(123)));
		q(nt(122), (nt(128)+nt(123)+nt(123)+nt(123)));
		q(nt(123), (nt(55)));
		q(nt(123), (nt(114)));
		q(nt(123), (nt(115)));
		q(nt(124), (nt(13)+t(16)+t(26)+t(41)+t(10)+t(12)+t(21)+t(41)+t(16)+t(11)+t(19)+t(22)+t(12)+nt(13)));
		q(nt(125), (nt(13)+t(16)+t(26)+t(41)+t(25)+t(20)+t(41)+t(16)+t(11)+t(19)+t(22)+t(12)+nt(13)));
		q(nt(126), (nt(13)+t(16)+t(26)+t(41)+t(5)+t(25)+t(20)+t(41)+t(16)+t(11)+t(19)+t(22)+t(12)+nt(13)));
		q(nt(129), (nt(13)+t(16)+t(26)+t(41)+t(12)+t(24)+t(23)+t(41)+t(16)+t(11)+t(19)+t(22)+t(12)+nt(13)));
		q(nt(128), (nt(13)+t(28)+t(6)+t(16)+t(28)+t(41)+t(16)+t(11)+t(19)+t(22)+t(12)+nt(13)));
		q(nt(130), (nt(64)+nt(35)));
		q(nt(131), (nt(60)));
		q(nt(131), (nt(82)));
		q(nt(131), (nt(103)));
		q(nt(133), (nt(131)+nt(133)));
		q(nt(133), (nul));
		q(nt(132), (nt(133)+nt(130)+nt(35)));
		q(nt(135), (nt(131)));
		q(nt(135), (nt(131)+nt(135)));
		q(nt(134), (nt(135)));
		q(nt(136), (nt(132)));
		q(nt(136), (nt(134)));
		return q;
	}
};
#endif // __TAU_PARSER_H__
