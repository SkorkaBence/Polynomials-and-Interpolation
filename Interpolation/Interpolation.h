#ifndef H_INTERPOLATION
#define H_INTERPOLATION

#include <map>
#include "Polynomial.h"

template<typename Ring>
class Interpolation {
private:
	std::map<int, Ring> known_points;
public:
	Interpolation(std::map<int, Ring> input) : known_points(input) {}

	Polynomial<Ring> calculatePolinom() {
		typename std::map<int, Ring>::iterator iterator_j;
		typename std::map<int, Ring>::iterator iterator_k;

		Polynomial<Ring> P1;
		for (iterator_j = known_points.begin(); iterator_j != known_points.end(); iterator_j++) {
			Polynomial<Ring> temp1;
			temp1.addValue(0, 1);
			for (iterator_k = known_points.begin(); iterator_k != known_points.end(); iterator_k++) {
				if (iterator_j != iterator_k) {
					Polynomial<Ring> temp2;
					temp2.addValue(0, - iterator_k->first);
					temp2.addValue(1, 1);

					temp1 = temp1 * (temp2 / (iterator_j->first - iterator_k->first));
				}
			}
			P1 = P1 + (iterator_j->second * temp1);
		}

		return P1;
	}

};

#endif
