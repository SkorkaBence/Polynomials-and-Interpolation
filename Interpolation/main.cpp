#include <iostream>
#include <vector>
#include <map>

#include "Polynomial.h"
#include "SecretSharing.h"
#include "Field.h"

#define USED_FIELD int

int main() {
	const USED_FIELD secret = 256; // the secret
	const int require = 2; // how many codes are required to decode the secret
	const int create = 20; // how many codes are to be generated

	std::cout << "Secret: " << secret << std::endl;

	Secret<USED_FIELD> s;
	Polynomial<USED_FIELD> v = s.generatePolynomial(secret, require); // create a ploinom where p(0) == secret

	std::cout << v << std::endl;
	
	for (int i = 1; i <= create; i++) {
		std::cout << i << ": " << v(i) << std::endl; // get the codes
	}

	std::cout << std::endl;

	// --------- DECODE ---------

	std::map<int, USED_FIELD> map;
	while (map.size() < require) {
		int n;
		USED_FIELD m;
		std::cout << "Index: ";
		std::cin >> n;
		std::cout << "Key: ";
		std::cin >> m;
		map[n] = m;
	}

	Secret<USED_FIELD> decoder;
	USED_FIELD result = decoder.calculateSecret(map);
	std::cout << std::endl << "P(0)=" << result << std::endl;
	
	Polynomial<USED_FIELD> pol = decoder.calculatePolynomial(map);
	std::cout << pol << std::endl;

	char c;
	std::cin >> c;

	return 0;
}