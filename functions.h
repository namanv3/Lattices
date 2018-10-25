//=================================
// include guard
#ifndef __FUNCTIONS_H_INCLUDED__
#define __FUNCTIONS_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <gmpxx.h>

#define MAXSIZE 200

using namespace std;

mpz_class norm(mpz_class v[], int m);
mpq_class norm(mpq_class v[], int m);

mpz_class dotp(mpz_class u[], mpz_class v[], int m);
mpq_class dotp(mpz_class u[], mpq_class v[], int m);
mpq_class dotp(mpq_class u[], mpq_class v[], int m);

void addvector(mpz_class first[], mpz_class second[], mpz_class ans[], int m);
void addvector(mpz_class first[], mpq_class second[], mpq_class ans[], int m);
void addvector(mpq_class first[], mpq_class second[], mpq_class ans[], int m);

void subvector(mpz_class first[], mpz_class second[], mpz_class ans[], int m);
void subvector(mpz_class first[], mpq_class second[], mpq_class ans[], int m);
void subvector(mpq_class first[], mpq_class second[], mpq_class ans[], int m);

void intmult(mpz_class vec[], mpz_class mult, mpz_class ans[], int m);
void intmult(mpq_class vec[], mpz_class mult, mpq_class ans[], int m);

void ratmult(mpz_class vec[], mpq_class mult, mpq_class ans[], int m);
void ratmult(mpq_class vec[], mpq_class mult, mpq_class ans[], int m);

void gso(mpz_class B[][MAXSIZE], mpq_class G[][MAXSIZE], int n, int m);

void print(mpz_class v[], int m);
void print(mpq_class v[], int m);
void print(mpz_class M[][MAXSIZE], int n, int m);
void print(mpq_class M[][MAXSIZE], int n, int m);
void print(mpf_class M[][MAXSIZE], int n, int m);

void swapArr (mpz_class a[], mpz_class b[], int m);
void swapArr (mpq_class a[], mpz_class b[], int m);

mpz_class roundtoInt(mpq_class a);

bool are_equal (mpz_class a[], mpz_class b[], int m);
void set_equal (mpz_class a[], mpz_class b[], int m);

mpf_class projectionNorm (mpz_class vec[], mpz_class base[], int m);
void projection (mpz_class vec[], mpz_class base[], mpq_class ans[], int m);
void projection (mpz_class vec[], mpq_class base[], mpq_class ans[], int m);
void projectionRounded (mpz_class vec[], mpz_class base[], mpz_class ans[], int m);
void perpComponentRounded (mpz_class vec[], mpz_class base[], mpz_class ans[], int m);

#endif
