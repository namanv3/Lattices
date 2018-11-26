#include "functions.h"

mpz_class norm(mpz_class v[], int m) {
	mpz_class val = 0;
	for(int i = 0; i < m; ++i) val = val + v[i]*v[i];
	return val;
}

mpq_class norm(mpq_class v[], int m) {
	mpq_class val = 0;
	for(int i = 0; i < m; ++i) val = val + v[i]*v[i];
	val.canonicalize();
	return val;
}


mpz_class dotp(mpz_class u[], mpz_class v[], int m) {
	mpz_class val = 0;
	for(int i = 0; i < m; ++i) val = val + u[i] * v[i];
	return val;
}

mpq_class dotp(mpz_class u[], mpq_class v[], int m) {
	mpq_class val = 0;
	for(int i = 0; i < m; ++i) val = val + u[i] * v[i];
	val.canonicalize();
	return val;
}

mpq_class dotp(mpq_class u[], mpq_class v[], int m) {
	mpq_class val = 0;
	for(int i = 0; i < m; ++i) val = val + u[i] * v[i];
	val.canonicalize();
	return val;
}


void addvector(mpz_class first[], mpz_class second[], mpz_class ans[], int m) {
	for(int i = 0; i < m; ++i) ans[i] = first[i] + second[i];
}

void addvector(mpz_class first[], mpq_class second[], mpq_class ans[], int m) {
	for(int i = 0; i < m; ++i) {
		ans[i] = first[i] + second[i];
		ans[i].canonicalize();
	}
}

void addvector(mpq_class first[], mpq_class second[], mpq_class ans[], int m) {
	for(int i = 0; i < m; ++i) {
		ans[i] = first[i] + second[i];
		ans[i].canonicalize();
	}
}


void subvector(mpz_class first[], mpz_class second[], mpz_class ans[], int m) {
	for(int i = 0; i < m; ++i) ans[i] = first[i] - second[i];
}

void subvector(mpz_class first[], mpq_class second[], mpq_class ans[], int m) {
	for(int i = 0; i < m; ++i) {
		ans[i] = first[i] - second[i];
		ans[i].canonicalize();
	}
}

void subvector(mpq_class first[], mpq_class second[], mpq_class ans[], int m) {
	for(int i = 0; i < m; ++i) {
		ans[i] = first[i] - second[i];
		ans[i].canonicalize();
	}
}


void intmult(mpz_class vec[], mpz_class mult, mpz_class ans[], int m) {
	for(int i = 0; i < m; ++i) ans[i] = mult * vec[i];
}

void intmult(mpq_class vec[], mpz_class mult, mpq_class ans[], int m) {
	for(int i = 0; i < m; ++i) {
		ans[i] = mult * vec[i];
		ans[i].canonicalize();
	}
}


void ratmult(mpz_class vec[], mpq_class mult, mpq_class ans[], int m) {
	for(int i = 0; i < m; ++i) ans[i] = mult * vec[i];
}

void ratmult(mpq_class vec[], mpq_class mult, mpq_class ans[], int m) {
	for(int i = 0; i < m; ++i) {
		ans[i] = mult * vec[i];
		ans[i].canonicalize();
	}
}


void gso(mpz_class B[][MAXSIZE], mpq_class G[][MAXSIZE], int n, int m) {
	int i, j, k;
	mpq_class temp[m], proj, num ,den;
	for(i = 0; i < n; ++i) {
		for(j = 0; j < m; ++j) G[i][j] = B[i][j];
		for(k = 0; k < i; ++k) {
			num = dotp(B[i], G[k], m);
			den = dotp(G[k], G[k], m);
			proj = num * mpq_class(den.get_den(), den.get_num());

			ratmult(G[k], proj, temp, m);
			subvector(G[i], temp, G[i], m);
		}
	}
}


void print(mpz_class v[], int m) {
	for(int i = 0; i < m; ++i) cout<<v[i]<<" ";
	cout<<endl;
}

void print(mpq_class v[], int m) {
	for(int i = 0; i < m; ++i) cout<<v[i]<<" ";
	cout<<endl;
}

void print(mpz_class M[][MAXSIZE], int n, int m) {
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) cout<<M[i][j]<<" ";
		cout<<endl;
	}
}

void print(mpq_class M[][MAXSIZE], int n, int m) {
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) cout<<M[i][j]<<" ";
		cout<<endl;
	}
}

void print(mpf_class M[][MAXSIZE], int n, int m) {
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) cout<<M[i][j]<<" ";
		cout<<endl;
	}
}

void swapArr (mpz_class a[], mpz_class b[], int m) {
	for (int i = 0; i < m; i++) swap (a[i],b[i]);
	//printf("Swapping, as harmless as usual\n");
}

void swapArr (mpq_class a[], mpq_class b[], int m) {
	for (int i = 0; i < m; i++) swap (a[i],b[i]);
}


mpz_class roundtoInt(mpq_class a) {
	mpf_class b(a);
	if (abs(b - ceil(b)) <= 0.5) return mpz_class(ceil(b));
	return mpz_class(floor(b));
}


bool are_equal (mpz_class a[], mpz_class b[], int m) {
	for (int i = 0; i < m; i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}

void set_equal (mpz_class a[], mpz_class b[], int m) {
	for (int i = 0; i < m; i++) a[i] = b[i];
}


mpf_class projectionNorm (mpz_class vec[], mpz_class base[], int m) {
	mpq_class num = abs(dotp(vec,base,m));
	mpf_class den = norm(base,m);
	den = sqrt(den);
	mpf_class proj = num/den;
	return proj*proj;
}

void projection (mpz_class vec[], mpz_class base[], mpq_class ans[], int m) {
	mpq_class num = dotp(vec,base,m);
	mpq_class den = norm(base,m);
	mpq_class proj = (num * mpq_class(den.get_den(), den.get_num()));
	ratmult(base, proj, ans, m);
}

void projection (mpz_class vec[], mpq_class base[], mpq_class ans[], int m) {
	mpq_class num = dotp(vec,base,m);
	mpq_class den = norm(base,m);
	mpq_class proj = (num * mpq_class(den.get_den(), den.get_num()));
	ratmult(base, proj, ans, m);
}

void projectionRounded (mpz_class vec[], mpz_class base[], mpz_class ans[], int m) {
	mpq_class num = dotp(vec,base,m);
	mpq_class den = norm(base,m);
	mpz_class proj = roundtoInt(num * mpq_class(den.get_den(), den.get_num()));
	intmult(base, proj, ans, m);
}

void perpComponentRounded (mpz_class vec[], mpz_class base[], mpz_class ans[], int m) {
	mpz_class temp[m];
	projectionRounded(vec,base,temp,m);
	subvector (vec,temp,ans,m);
}
