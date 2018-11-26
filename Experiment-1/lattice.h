//=================================
// include guard
#ifndef __LATTICE_H_INCLUDED__
#define __LATTICE_H_INCLUDED__

#include <iostream>
#include <stdlib.h>
#include "gmpxx.h"
#include "functions.h"

#define SEED 1
// #define MAXSIZE 200
#define RANDOMNESS 20
#define RANDOMNESS_LIMIT 500

using namespace std;

class Lattice {
	private:
		int n, m;
	public:
		mpz_class original[MAXSIZE][MAXSIZE];
		mpz_class B[MAXSIZE][MAXSIZE];

		Lattice(int rows, int cols);
		int getrows();
		int getcols();

		void createBasis();
		void randBasis();

		void printBasis();

		void restoreOriginal();

		mpz_class shortest();
		mpz_class sum_of_norms();

		void LLL (int deltaNum, int deltaDen);

		void perp_reduce(int numRows, int i);
		void reduce(int numRows);
		void reduce_main();
		void newLLL (int deltaNum, int deltaDen);

};

#endif
