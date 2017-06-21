#include <iostream>
#include <vector>
#include <map>
#include "SecretSharing.h"
#include "Field.h"

int main() {
	const int secret = 256; // the secret
	const int require = 2; // how many codes are required to decode the secret
	const int create = 20; // how many codes are to be generated

	Secret<int> s;
	Polinom<int> v = s.generatePolinom(secret, require); // create a ploinom where p(0) == secret
	
	for (int i = 1; i <= create; i++) {
		std::cout << i << ": " << v(i) << std::endl; // get the codes
	}

	std::cout << std::endl;

	// --------- DECODE ---------

	std::map<int, double> map;
	while (map.size() < require) {
		int n;
		double m;
		std::cout << "Index: ";
		std::cin >> n;
		std::cout << "Key: ";
		std::cin >> m;
		map[n] = m;

		Interpolation<double> ib(map);
		Polinom<double> p = ib.calculatePolinom(); // calculate the polinom with the given points
		p.echo(std::cout);
		std::cout << std::endl << "P(0)=" << p(0) << std::endl;
	}
	

	char c;
	std::cin >> c;
}





#define kiir(x) std::cout << x << " "


int main() {

	Field<13> f = 5;
	Field<13> d = 8;

	kiir(f); // 5
	kiir(d); // 8
	kiir(f + d); // 5 + 8 = 0
	kiir(f * d); // 5 * 8 = 1


	std::cout << std::endl;

}