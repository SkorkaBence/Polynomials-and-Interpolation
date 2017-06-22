#ifndef H_SECRETSHARING
#define H_SECRETSHARING

#include <vector>
#include <map>
#include "Polynomial.h"
#include "Interpolation.h"

template<typename Ring = int>
class Secret {
public:
	
	Polynomial<Ring> generatePolinom(Ring secret, int needed) {
		Polynomial<Ring> p;
		p.addValue(0, secret);

		for (int i = 1; i < needed; i++) {
			Ring rnd = rand() % 100 + 1;
			p.addValue(i, rnd);
		}

		return p;
	}

	Ring calculateSecret(std::map<int, Ring> input) {
		Interpolation<double> ib(map);
		Polynomial<double> p = ib.calculatePolinom();
		return p(0);
	}

};

#endif