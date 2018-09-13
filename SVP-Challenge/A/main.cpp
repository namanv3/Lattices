#include <iostream>
#include <time.h>
#include <fstream>
#include "lattice.h"
#include "functions.h"

using namespace std;

#define printhere(M,n,m) for(int i = 0; i < n; ++i) {for(int j = 0; j < m; ++j) cout<<M[i][j]<<" ";cout<<endl;}

void LLL (mpz_class B[][MAXSIZE], int n, int m) {
	mpq_class G[n][MAXSIZE];
	mpq_class num, den;
	mpz_class roundOff;
	mpz_class temp[m]; mpq_class mu[n][n];
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
		mpq_class temp2[m];
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

void reduce_new (mpz_class B[][MAXSIZE], int n, int m) {
	mpq_class G[n][MAXSIZE];
	gso (B, G, n-1, m);
	mpq_class gn_1[MAXSIZE], num, den, proj, temp[MAXSIZE];
	for(int j = 0; j < m; ++j) gn_1[j] = B[n-1][j];
	for(int k = 0; k < n-2; ++k) {
		num = dotp(B[n-1], G[k], m);
		den = dotp(G[k], G[k], m);
		proj = num * mpq_class(den.get_den(), den.get_num());
		ratmult(G[k], proj, temp, m);
		subvector(gn_1, temp, gn_1, m);
	}
	num = dotp(gn_1, G[n-2], m);
	den = norm(gn_1, m);
	proj = num * mpq_class(den.get_den(), den.get_num());

	mpz_class val = roundtoInt(proj);
	mpz_class temp2[MAXSIZE];
	intmult(B[n-1], val, temp2, m);
	subvector(B[n-2], temp2, B[n-2], m);
}

void reduce (mpz_class B[][MAXSIZE], int n, int m) {
	mpq_class dist, val;
	for (int i = 0; i < n-1; i++) {
		swapArr (B[n-2], B[i], m);
		reduce_new(B, n, m);
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

void norm_sum (mpz_class B[][MAXSIZE], int n, int m, mpz_class& sum) {
	sum = mpz_class(0);
	for (int i = 0; i < n; i++) sum += norm(B[i], m);
}

int reduce_main (mpz_class B[][MAXSIZE], int n, int m) {
	char opfile[] = "out00.txt";
	if (n < 10) opfile[4] = n + '0';
	else {
		opfile[3] = (n/10) + '0';
		opfile[4] = (n%10) + '0';
	}
	#ifdef LOCAL_TEST
		ifstream cin("matrix.txt");ofstream cout(opfile);//time_p=clock();
	#endif
	for (int i = 0; i < 5; i++) cout << "                                           " << endl;
	if(n == 1) return 0;
	int count = 0;
	mpz_class sum, new_sum; mpq_class ratio;
	mpq_class epsilon(1,100);
	norm_sum(B,n,m,sum);
	while (true) {
		LLL (B, n, m);
		cout << "After LLL, the matrix is:\n";
		printhere(B,n,m);
		cout << endl;
		for (int i = 0; i < n; i++) {
			if (i != n-1) swapArr(B[n-1], B[i], m);
			reduce (B, n, m);
			//reduce_main (B, n-1, m);
			if (i != n-1) swapArr(B[n-1], B[i], m);
		}
		count++;
		cout << "After reduction, the matrix is:\n";
		printhere(B,n,m);
		cout << "Round" << count <<  " done\n\n";

		norm_sum(B,n,m,new_sum);
		ratio = mpq_class(sum - new_sum, sum);
		cout << new_sum << " " << sum << " ratio:" <<  mpf_class(ratio) << endl;
		if ( ratio < epsilon ) break;
		sum = new_sum;
	}
	return count;
}

int main(int argc, char** argv) {
	int n = atoi(argv[1]), m = 40;
	char opfile[] = "out00.txt";
	if (n < 10) opfile[4] = argv[1][0];
	else {
		opfile[3] = argv[1][0];
		opfile[4] = argv[1][1];
	}
	#ifdef LOCAL_TEST
		ifstream cin("matrix.txt");ofstream cout(opfile);//time_p=clock();
	#endif
	Lattice L = Lattice(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cin >> L.B[i][j];
	}
	L.printBasis();

	clock_t t;
	t = clock();
	int c = reduce_main(L.B, n, m);
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	cout << "Time:" <<  time_taken << " rounds: " << c << "\n";

	int idx = findsmallest(L.B,n,m);
	cout << norm(L.B[idx],m) << endl;
	idx = findlargest(L.B,n,m);
	cout << norm(L.B[idx],m) << endl;
	return 0;
}
// 3
