#include "lattice.h"

Lattice::Lattice (int rows, int cols) {
	if(n > m) {
		cout << "Existence of dependent vectors in the basis. Terminating the program\n";
		exit(-1);
	}
	srand(SEED);
	n = rows;
	m = cols;
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < m; ++j) B[i][j] = 0;
	}
}

int Lattice::getrows() {
	return n;
}

int Lattice::getcols() {
	return m;
}

void Lattice::createBasis() {
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if (j == 0) B[i][j] = ((rand() % RANDOMNESS_LIMIT) + 1);
			else if (i == j) B[i][j] = 1;
			else B[i][j] = 0;
		}
	}
}

void Lattice::randBasis() {
	int pos1, pos2, val;
	for(int r = 0 ; r < RANDOMNESS; ++r) {
		pos1 = rand() % n;
		pos2 = rand() % n;
		if(pos1 == pos2) continue;
		else {
			val = (rand() % RANDOMNESS_LIMIT) + 1;
			for(int j = 0; j < m; ++j) B[pos1][j] = B[pos1][j] + (val * B[pos2][j]);
		}
	}
}

void Lattice::printBasis() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) cout << B[i][j] << " ";
		cout << endl;
	}
}

void Lattice::restoreOriginal() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) B[i][j] = original[i][j];
	}
}

void Lattice::LLL (int deltaNum, int deltaDen) {
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

				num = dotp(B[i],G[j],m);
				den = dotp(G[j],G[j],m);
				mu[i][j] = num * mpq_class(den.get_den(), den.get_num());
			}
		}

		//swap step
		mpq_class LHS, RHS;
		mpq_class delta(deltaNum,deltaDen);
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
		if (should_break){
			break;
		}

	}
}

mpz_class Lattice::shortest() {
	mpz_class shortnorm = norm(B[0],m);
	for(int i = 0; i < n; i++){
		if(shortnorm > norm(B[i], m)) {
			//	cout<<"Update\n";
			shortnorm = norm(B[i], m);
		}
	}
	return shortnorm;
}

mpz_class Lattice::sum_of_norms () {
	mpz_class sum = 0;
	for (int i = 0; i < n; i++) {
		sum += norm(B[i],m);
	}
	return sum;
}
