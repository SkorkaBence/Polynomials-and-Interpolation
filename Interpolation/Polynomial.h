#ifndef H_POLINOM
#define H_POLINOM

#include <iostream>
#include <vector>

template<typename Ring>
class Polynomial {
private:
	std::vector<Ring> vals;
public:
	Polynomial() {

	}

	Polynomial(std::vector<Ring> vr) : vals(vr) {

	}

	void addValue(int n, Ring v) {
		if (n < 0) {
			throw "Not valid";
		}
		while (vals.size() <= n) {
			vals.push_back(0);
		}
		vals[n] = v;
	}

	Ring getValue(int n) {
		if (n < 0) {
			throw "not valid";
		}
		if (n >= vals.size()) {
			return 0;
		}
		return vals[n];
	}

	Ring operator () (Ring c) {
		Ring o = 0;
		for (int i = 0; i < vals.size(); i++) {
			Ring x = vals[i];
			for (int j = 0; j < i; j++) {
				x = x * c;
			}
			o = o + x;
		}
		return o;
	}

	bool isNull() {
		int i = vals.size() - 1;
		while (i >= 0 && vals[i] == 0) {
			i--;
		}
		return (i < 0);
	}

	int deg() {
		int i = vals.size() - 1;
		while (i >= 0 && (int)vals[i] == 0) {
			i--;
		}
		if (i < 0) {
			return -2147483648;
		}
		return i;
	}

	friend std::ostream& operator << (std::ostream& out, Polynomial<Ring> p) {
		int d = p.deg();
		out << "Polynomial:";
		for (int i = 0; i <= d; i++) {
			if ((int)p.getValue(i) != 0) {
				out << "   " << p.getValue(i) << "x^" << i;
			}
		}
		return out;
	}
};

template<typename T>
Polynomial<T> operator + (Polynomial<T> p1, Polynomial<T> p2) {
	Polynomial<T> r = Polynomial<T>();
	int d1 = p1.deg();
	int d2 = p2.deg();
	int mx = (d1 > d2 ? d1 : d2);
	for (int i = 0; i <= mx; i++) {
		r.addValue(i, p1.getValue(i) + p2.getValue(i));
	}
	return r;
}

template<typename T>
Polynomial<T> operator - (Polynomial<T> p1, Polynomial<T> p2) {
	Polynomial<T> r = Polynomial<T>();
	int d1 = p1.deg();
	int d2 = p2.deg();
	int mx = (d1 > d2 ? d1 : d2);
	for (int i = 0; i <= mx; i++) {
		r.addValue(i, p1.getValue(i) - p2.getValue(i));
	}
	return r;
}

template<typename T>
Polynomial<T> operator * (Polynomial<T> p1, Polynomial<T> p2) {
	Polynomial<T> r = Polynomial<T>();
	int d1 = p1.deg();
	int d2 = p2.deg();
	for (int i = 0; i <= ((d1+1) * (d2+1)); i++) {
		T g = 0;
		for (int k = 0; k <= i; k++) {
			g = g + p1.getValue(k) * p2.getValue(i - k);
		}
		r.addValue(i, g);
	}
	return r;
}

template<typename T>
Polynomial<T> operator / (Polynomial<T> n, Polynomial<T> d) {
	Polynomial<T> q = Polynomial<T>();
	Polynomial<T> r = n;

	while (!r.isNull() && r.deg() >= d.deg()) {
		T leading_v = r.getValue(r.deg()) / d.getValue(d.deg());
		int leadign_p = r.deg() - d.deg();
		Polynomial<T> t = Polynomial<T>();
		t.addValue(leadign_p, leading_v);
		q = q + t;
		r = r - t * d;
	}

	if (r.isNull()) {
		throw "not divisable";
	}

	return q;
}

template<typename T, typename K>
Polynomial<T> operator * (Polynomial<T> p, K s) {
	Polynomial<T> r = Polynomial<T>();
	for (int i = 0; i <= p.deg(); i++) {
		r.addValue(i, p.getValue(i) * s);
	}
	return r;
}

template<typename T, typename K>
Polynomial<T> operator * (K s, Polynomial<T> p) {
	return p * s;
}

template<typename T, typename K>
Polynomial<T> operator / (Polynomial<T> p, K s) {
	Polynomial<T> r = Polynomial<T>();
	for (int i = 0; i <= p.deg(); i++) {
		r.addValue(i, p.getValue(i) / s);
	}
	return r;
}

#endif