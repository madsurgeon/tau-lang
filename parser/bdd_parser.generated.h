// This file is generated by 
//       https://github.com/IDNI/parser/tools/parser_gen
//
// from the grammar in file ../tau-lang/parser/bdd.tgf:
//
// @use_char_class eof, space, digit, xdigit, alpha, alnum, punct, printable.
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
// # common symbols
// equality			=> ws '=' ws. 
// nequality			=> ws "!=" ws. 
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
// colon				=> ws ':' ws.
// 
// # variables
// var				=> '?' chars.
// 
// # bdd
// bdd				=> bdd_and | bdd_neg | bdd_xor | bdd_or | var | T | F.
// bdd_and			=> open_parenthesis bdd_arg bdd_and_sym bdd_arg close_parenthesis.
// bdd_or			=> open_parenthesis bdd_arg bdd_or_sym bdd_arg close_parenthesis.
// bdd_xor			=> open_parenthesis bdd_arg bdd_xor_sym bdd_arg close_parenthesis.
// bdd_neg			=> bdd_neg_sym open_parenthesis bdd_arg close_parenthesis.
// bdd_arg 		=> bdd.
// 
// # bdd_op_sym
// bdd_and_sym		=> ws "bdd_and" ws.
// bdd_or_sym		=> ws "bdd_or" ws.
// bdd_xor_sym		=> ws "bdd_xor" ws.
// bdd_neg_sym		=> ws "bdd_neg" ws.
// 
// # constants
// T				=> ws '1' ws.
// F				=> ws '0' ws.
// 
// start			=> bdd.
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
		g(nts, load_prods(), nt(60), cc), p(g, load_opts()) {}
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
			_Rchars_4, _Rchars_5, char_class, equality, nequality, dot, open_parenthesis, close_parenthesis, open_bracket, close_bracket, 
			open_brace, close_brace, less_than, greater_than, minus, plus, colon, var, bdd, bdd_and, 
			bdd_neg, bdd_xor, bdd_or, T, F, bdd_arg, bdd_and_sym, bdd_or_sym, bdd_xor_sym, bdd_neg_sym, 
			start, 
   };
	size_t id(const std::basic_string<char>& name) { return nts.get(name); }
private:
	std::vector<char> ts{
		'\0', '\n', '\r', '#', '\\', 'x', 'u', '\'', '"', 
		'`', 'a', 'l', 'n', 'm', 'p', 'h', 'b', 'k', 'c', 
		't', 'r', 'd', 'i', 'g', 'e', 'o', 'f', 'w', 's', 
		'=', '!', '.', '(', ')', '[', ']', '{', '}', '<', 
		'>', '-', '+', ':', '?', '_', '1', '0', 
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
			"_Rchars_4", "_Rchars_5", "char_class", "equality", "nequality", "dot", "open_parenthesis", "close_parenthesis", "open_bracket", "close_bracket", 
			"open_brace", "close_brace", "less_than", "greater_than", "minus", "plus", "colon", "var", "bdd", "bdd_and", 
			"bdd_neg", "bdd_xor", "bdd_or", "T", "F", "bdd_arg", "bdd_and_sym", "bdd_or_sym", "bdd_xor_sym", "bdd_neg_sym", 
			"start", 
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
		q(nt(33), (nt(13)+t(29)+nt(13)));
		q(nt(34), (nt(13)+t(30)+t(29)+nt(13)));
		q(nt(35), (nt(13)+t(31)+nt(13)));
		q(nt(36), (nt(13)+t(32)+nt(13)));
		q(nt(37), (nt(13)+t(33)+nt(13)));
		q(nt(38), (nt(13)+t(34)+nt(13)));
		q(nt(39), (nt(13)+t(35)+nt(13)));
		q(nt(40), (nt(13)+t(36)+nt(13)));
		q(nt(41), (nt(13)+t(37)+nt(13)));
		q(nt(42), (nt(13)+t(38)+nt(13)));
		q(nt(43), (nt(13)+t(39)+nt(13)));
		q(nt(44), (nt(13)+t(40)+nt(13)));
		q(nt(45), (nt(13)+t(41)+nt(13)));
		q(nt(46), (nt(13)+t(42)+nt(13)));
		q(nt(47), (t(43)+nt(29)));
		q(nt(48), (nt(47)));
		q(nt(48), (nt(49)));
		q(nt(48), (nt(50)));
		q(nt(48), (nt(51)));
		q(nt(48), (nt(52)));
		q(nt(48), (nt(53)));
		q(nt(48), (nt(54)));
		q(nt(49), (nt(36)+nt(55)+nt(56)+nt(55)+nt(37)));
		q(nt(52), (nt(36)+nt(55)+nt(57)+nt(55)+nt(37)));
		q(nt(51), (nt(36)+nt(55)+nt(58)+nt(55)+nt(37)));
		q(nt(50), (nt(59)+nt(36)+nt(55)+nt(37)));
		q(nt(55), (nt(48)));
		q(nt(56), (nt(13)+t(16)+t(21)+t(21)+t(44)+t(10)+t(12)+t(21)+nt(13)));
		q(nt(57), (nt(13)+t(16)+t(21)+t(21)+t(44)+t(25)+t(20)+nt(13)));
		q(nt(58), (nt(13)+t(16)+t(21)+t(21)+t(44)+t(5)+t(25)+t(20)+nt(13)));
		q(nt(59), (nt(13)+t(16)+t(21)+t(21)+t(44)+t(12)+t(24)+t(23)+nt(13)));
		q(nt(53), (nt(13)+t(45)+nt(13)));
		q(nt(54), (nt(13)+t(46)+nt(13)));
		q(nt(60), (nt(48)));
		return q;
	}
};
#endif // __TAU_PARSER_H__
