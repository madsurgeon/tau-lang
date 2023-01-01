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
#ifndef __BOOL_H__
#define __BOOL_H__
struct Bool {
	bool b;
	Bool(bool b) : b(b) {}
	template<typename T> Bool(const T&) {
		static_assert(is_same<T, bool>::value);
	}
	static const Bool& zero() { static Bool b(false); return b; }
	static const Bool& one() { static Bool b(true); return b; }
	Bool operator&(const Bool& x) const;
	Bool operator|(const Bool& x) const;
	Bool operator~() const;
	bool operator<(const Bool& x) const { return b < x.b; }
	bool operator==(bool t) const { return b == t; }
};

Bool Bool::operator&(const Bool& x) const {
	return (*this == false) ? zero() : x;
}
Bool Bool::operator|(const Bool& x) const {
	return (*this == true) ? one() : x;
}

Bool Bool::operator~() const { return *this == true ? zero() : one(); }
#endif
