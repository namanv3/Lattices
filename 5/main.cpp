#include <iostream>
#include <time.h>
#include "lattice.h"
#include "functions.h"

using namespace std;

void LLL (mpz_class B[][MAXSIZE], int n, int m) {
	mpq_class G[n][MAXSIZE];
	mpq_class num, den;
	mpz_class roundOff;
	mpz_class temp[MAXSIZE]; mpq_class mu[n][n];
	while (true) {
		gso(B, G, n, m);
		for (int i = 1; i < n; i++) {
			for (int j = i - 1; j >= 0; j--) {
				num = dotp(B[i],G[j],m);
				den = dotp(G[j],G[j],m);
				mu[i][j] = num * mpq_class(den.get_den(), den.get_num());
			 	roundOff = roundtoInt(mu[i][j]);
				intmult(B[j],roundOff,temp,m);
				subvector(B[i],temp,B[i],m);
			}
		}
		//swap step
		mpq_class LHS, RHS;
		mpq_class delta(251,1000);
		mpq_class temp2[MAXSIZE];
		bool should_break = true;
		for (int i = 0; i < n-1; i++) {
			LHS = delta * norm(G[i],m);
			ratmult(G[i],mu[i+1][i],temp2,m);
			addvector(temp2,G[i+1],temp2,m);
			RHS = norm(temp2,m);
			if (LHS > RHS) {
				swapArr (B[i],B[i+1],m);
				should_break = false;
				break;
			}
		}
		if (should_break) break;
	}
	return;
}

void reduce_single (mpz_class B[][MAXSIZE], int n, int m) {
	mpq_class num, den, proj;
	mpz_class val, temp[MAXSIZE];
	for (int i = 0; i < n-1; i++) {
		swapArr (B[n-2], B[i], m);

		num = dotp(B[n-1], B[n-2], m);
		den = norm(B[n-2], m);
		proj = num * mpq_class(den.get_den(), den.get_num());

		val = roundtoInt(proj);
		intmult(B[n-2], val, temp, m);
		subvector(B[n-1], temp, B[n-1], m);
		swapArr (B[n-2], B[i], m);
	}
}

int findsmallest (mpz_class B[][MAXSIZE], int n, int m) {
	mpz_class minNorm = norm(B[0],m), currNorm; int idx = 0;
	for (int i = 1; i < n; i++) {
		currNorm = norm(B[i],m);
		if (minNorm > currNorm) {
            minNorm = currNorm;
            idx = i;
        }
	}
    return idx;
}

int findlargest (mpz_class B[][MAXSIZE], int n, int m) {
	mpz_class maxNorm = norm(B[0],m), currNorm; int idx = 0;
	for (int i = 1; i < n; i++) {
		currNorm = norm(B[i],m);
		if (maxNorm < currNorm) {
            maxNorm = currNorm;
            idx = i;
        }
	}
    return idx;
}

int reduce_main (mpz_class B[][MAXSIZE], int n, int m) {
	if(n == 1) return 0;
	int count = 0;
    mpz_class largest[m];
    set_equal(largest,B[findlargest(B,n,m)],m);
	while (true) {
		printf("After the LLL, the basis is:\n");
		LLL(B,n,m);
		print(B,n,m);
		printf("\n");
		for (int i = 0; i < n; i++) {
			if (i != n-1) swapArr(B[n-1], B[i], m);
			reduce_single (B, n, m);
			//reduce_main (B, n-1, m);
			if (i != n-1) swapArr(B[n-1], B[i], m);
		}
		count++;
		printf("After reduction, the matrix is:\n");
		print(B,n,m);
		printf("Round %d done\n\n", count);

        int curr = findlargest(B,n,m);
        if ( are_equal(B[curr],largest,m) ) break;
        set_equal(largest,B[curr],m);
	}
	return count;
}

int main(int argc, char** argv) {
	int n = atoi(argv[1]), m = atoi(argv[2]);
	Lattice L = Lattice(n, m);
	L.createBasis();
	L.printBasis();
	printf("\n");

	clock_t t;
    t = clock();
    int c = reduce_main(L.B, n, m);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("\nTime: %lf, rounds: %d\n", time_taken, c);

	int idx = findsmallest(L.B,n,m);
	printf("The smallest vector's norm is: "); cout << norm(L.B[idx],m) << endl;
	idx = findlargest(L.B,n,m);
	printf("The largest vector's norm is: "); cout << norm(L.B[idx],m) << endl;
	return 0;
}