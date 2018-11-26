#include <iostream>
#include <ctime>
#include "lattice.h"
#include "functions.h"

using namespace std;

mpz_class shortn;

void Lattice::perp_reduce (int numRows, int i) {
	mpz_class val, temp[MAXSIZE];
	mpq_class proj, num, den;
	mpq_class G[numRows][MAXSIZE], qtemp[m];

	gso(B, G, numRows, m);

    projection (B[numRows-1], G[numRows-2], qtemp, m);
	addvector(G[numRows-1], qtemp, G[numRows-1], m);

    num = dotp(G[numRows-1], G[numRows-2], m);
	den = norm(G[numRows-1], m);
	val = roundtoInt(num * mpq_class(den.get_den(), den.get_num()));
	intmult(B[numRows-1], val, temp, m);
	subvector(B[numRows-2], temp, B[numRows-2], m);

}

void Lattice::reduce (int numRows) {
	mpq_class dist, val;

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < numRows-1; i++) {
			swapArr(B[numRows-2], B[i], m);
			perp_reduce(numRows, i);
			swapArr(B[numRows-2], B[i], m);
		}
	}
    return;
}

void Lattice::reduce_main() {
	for(int i = 0; i < n-1; i++) {
        reduce(n-i);
    }
    return;
}

void Lattice::newLLL (int deltaNum, int deltaDen) {
	mpz_class shortnorm,prev;
	mpz_class new_sum, prev_sum;
	shortnorm = shortest();

	LLL(deltaNum, deltaDen);

	shortnorm = prev = shortest();
	prev_sum = sum_of_norms();
	while (1) {
		reduce_main();

		LLL(deltaNum, deltaDen);

		shortnorm = shortest();
		new_sum = sum_of_norms();
		if (new_sum >= prev_sum && shortnorm >= prev) {
			cout << "No improvement, breaking from newLLL.." << endl;
 			break;
		}
		prev_sum = new_sum;
		prev = shortnorm;
	}

}

int main(int argc, char** argv) {
	if (argc != 2 && argc != 3) {
        printf("Usage: ./main <filename> <dimension (optional parameter)>\n");
        exit(-1);
    }
    ifstream cin(argv[1]);
    int dn, dd;

    int n, m, dimension;
    cin >> n >> m;
    if (argc == 3) dimension = atoi(argv[2]);
    else dimension = n;

    Lattice L = Lattice(dimension, dimension);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
            mpz_class input;
            cin >> input;
            if (i < dimension && j < dimension) {
				L.B[i][j] = input;
				L.original[i][j] = input;
			}
        }
	}
	cout << "The original basis is:" << endl;
	L.printBasis();
	cout << endl;
	n = m = dimension;

	int start_s, stop_s;
	double t1, t2;

	dn = 251, dd = 1000;
	start_s = clock();
    L.LLL(dn,dd);
	stop_s = clock();

	shortn = L.shortest();
	cout << "Shortest distance found by old LLL: " << sqrt(mpf_class(shortn)) << endl;

	t1 = (stop_s - start_s) / ((double)(CLOCKS_PER_SEC));
	cout << "time: " << t1 << endl;
	cout << endl;

    L.restoreOriginal();

	dn = 251, dd = 1000;
	start_s = clock();
    L.newLLL(dn,dd);
	stop_s = clock();

	shortn = L.shortest();
	cout << "Shortest distance found by new LLL: " << sqrt(mpf_class(shortn)) << endl;
	t2 = (stop_s-start_s)/((double)(CLOCKS_PER_SEC));
	cout << "time: " << t2 << endl;
	cout<< "Speedup: " << t1 / t2 << endl;

	return 0;
}
