#ifndef H_POLINOM
#define H_POLINOM

#include <iostream>
#include <vector>

template<typename Ring>
class Polinom {
private:
	std::vector<Ring> vals;
public:
	Polinom() {

	}

	Polinom(std::vector<Ring> vr) : vals(vr) {

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
		while (i >= 0 && vals[i] == 0) {
			i--;
		}
		if (i < 0) {
			return -2147483648;
		}
		return i;
	}

	void echo(std::ostream& out) {
		int d = this->deg();
		out << "Polinom:";
		for (int i = 0; i <= d; i++) {
			if (this->getValue(i) != 0) {
				out << "   " << this->getValue(i) << "x^" << i;
			}
		}
	}
};

template<typename T>
Polinom<T> operator + (Polinom<T> p1, Polinom<T> p2) {
	Polinom<T> r = Polinom<T>();
	int d1 = p1.deg();
	int d2 = p2.deg();
	int mx = (d1 > d2 ? d1 : d2);
	for (int i = 0; i <= mx; i++) {
		r.addValue(i, p1.getValue(i) + p2.getValue(i));
	}
	return r;
}

template<typename T>
Polinom<T> operator - (Polinom<T> p1, Polinom<T> p2) {
	Polinom<T> r = Polinom<T>();
	int d1 = p1.deg();
	int d2 = p2.deg();
	int mx = (d1 > d2 ? d1 : d2);
	for (int i = 0; i <= mx; i++) {
		r.addValue(i, p1.getValue(i) - p2.getValue(i));
	}
	return r;
}

template<typename T>
Polinom<T> operator * (Polinom<T> p1, Polinom<T> p2) {
	Polinom<T> r = Polinom<T>();
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
Polinom<T> operator / (Polinom<T> n, Polinom<T> d) {
	Polinom<T> q = Polinom<T>();
	Polinom<T> r = n;

	while (!r.isNull() && r.deg() >= d.deg()) {
		T leading_v = r.getValue(r.deg()) / d.getValue(d.deg());
		int leadign_p = r.deg() - d.deg();
		Polinom<T> t = Polinom<T>();
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
Polinom<T> operator * (Polinom<T> p, K s) {
	Polinom<T> r = Polinom<T>();
	for (int i = 0; i <= p.deg(); i++) {
		r.addValue(i, p.getValue(i) * s);
	}
	return r;
}

template<typename T, typename K>
Polinom<T> operator * (K s, Polinom<T> p) {
	return p * s;
}

template<typename T, typename K>
Polinom<T> operator / (Polinom<T> p, K s) {
	Polinom<T> r = Polinom<T>();
	for (int i = 0; i <= p.deg(); i++) {
		r.addValue(i, p.getValue(i) / s);
	}
	return r;
}

#endif