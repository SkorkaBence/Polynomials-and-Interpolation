#ifndef H_SECRETSHARING
#define H_SECRETSHARING

#include <vector>
#include <map>
#include <time.h>
#include "Polynomial.h"
#include "Interpolation.h"

template<typename Ring>
class Secret {
public:
	
	Polynomial<Ring> generatePolynomial(Ring secret, int needed) {
		Polynomial<Ring> p;
		p.addValue(0, secret);

		srand(time(NULL));

		for (int i = 1; i < needed; i++) {
			Ring rnd = rand() % 100 + 1;
			p.addValue(i, rnd);
		}

		return p;
	}

	Ring calculateSecret(std::map<int, Ring> input) {
		Interpolation<Ring> ib(input);
		Polynomial<Ring> p = ib.calculatePolinom();
		return p(0);
	}

	Polynomial<Ring> calculatePolynomial(std::map<int, Ring> input) {
		Interpolation<Ring> ib(input);
		return ib.calculatePolinom();
	}

};

#endif