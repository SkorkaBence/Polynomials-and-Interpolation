#ifndef H_INTERPOLATION
#define H_INTERPOLATION

#include <map>
#include "Polinom.h"

template<typename Ring>
class Interpolation {
private:
	std::map<int, Ring> known_points;
public:
	Interpolation(std::map<int, Ring> input) : known_points(input) {}

	Polinom<Ring> calculatePolinom() {
		std::vector<int> xs;
		std::vector<Ring> ys;

		typename std::map<int, Ring>::iterator it;
		for (it = known_points.begin(); it != known_points.end(); it++) {
			xs.push_back(it->first);
			ys.push_back(it->second);
		}

		Polinom<Ring> P1;
		for (int j = 0; j < xs.size(); j++) {
			Polinom<Ring> temp1;
			temp1.addValue(0, 1);
			for (int k = 0; k < xs.size(); k++) {
				if (k != j) {
					Polinom<Ring> temp2;
					temp2.addValue(0, - xs[k]);
					temp2.addValue(1, 1);

					temp1 = temp1 * (temp2 / (xs[j] - xs[k]));
				}
			}
			P1 = P1 + (ys[j] * temp1);
		}

		return P1;
	}

};

#endif
