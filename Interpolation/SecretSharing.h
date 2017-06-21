#ifndef H_SECRETSHARING
#define H_SECRETSHARING

#include <vector>
#include <map>
#include "Polinom.h"
#include "Interpolation.h"

template<typename Ring = int>
class Secret {
public:
	
	Polinom<Ring> generatePolinom(Ring secret, int needed) {
		Polinom<Ring> p = Polinom<Ring>();
		p.addValue(0, secret);

		for (int i = 1; i < needed; i++) {
			Ring rnd = rand() % 100 + 1;
			p.addValue(i, rnd);
		}

		return p;
	}

	Ring calculateSecret(std::map<int, Ring> input) {

	}

};

#endif