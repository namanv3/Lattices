# Lattices

## Basic Setup

This repository uses the GMP Library to handle large numbers in C++. The [library's homepage](https://gmplib.org) has the download links to the latest links. To download some older versions, go to this [this ftp server](https://ftp.gnu.org/gnu/gmp/) (you can find the latest release here as well).

Instructions for downloading the library can be found [here](https://gmplib.org/manual/Installing-GMP.html#Installing-GMP). <br>
This repository requires C++ support as well (it isn't enabled by default). To do this, change the first command mentioned in the above link from this:

```bash
./configure
```
To this:
```bash
./configure --enable-cxx
```
 More build options can be found [here](https://gmplib.org/manual/Build-Options.html#Build-Options). None of those are required here, however.

 Once installed, you can use the gmp in your C files like this:
 ```C
#include <gmp.h>
 ```

And in your C++ files like this:
```C++
#include <gmpxx.h>
```

Here's a link to the [documentation](https://gmplib.org/manual/index.html#Top) of this library.

## File Descriptions

1. `functions.h` defines various functions on `mpz_class` and `mpq_class` vectors, like norm, dot product, vector addition, GSO, vector projections, etc. `functions.cpp` describes all these functions.

2. `lattices.h` defines the `Lattice` class and all the functions in the lattice class.
 - In the `Lattice` class, the `void LLL (int deltaNum, int deltaDen)` function is the implementation of the original LLL algorithm, whereas the `void newLLL (int deltaNum, int deltaDen)` is the implementation of our improved LLL algorithm.


3. `scrap_matrix_from_file.py` takes a text file downloaded from [this website](https://www.latticechallenge.org/svp-challenge/) as a command line argument, and extracts the matrix from the file in a format accepted by `main.cpp`.
```bash
python3 ./scrap_matrix_from_file.py ./20/svpchallengedim20seed0.txt
```
The output is stored in a new text file, `matrix.txt`.

4. `scrap_matrix_from_url.py` does the same job as above, but it takes a url to the text file as an input rather than the text file itself (for example, [this URL](https://www.latticechallenge.org/svp-challenge/download/challenges/svpchallengedim40seed0.txt)).
```bash
python3 ./scrap_matrix_from_url.py https://www.latticechallenge.org/svp-challenge/download/challenges/svpchallengedim40seed0.txt
```

5. `Makefile` compiles the code and creates the executable.

6. `script.sh` constructs the executable using `make` and runs it on all text files in the folder `20/`.

## Usage

*  To compile the code, run:
```bash
make
```
It creates an executable named `main`.

* The folder `20/` has various text files downloaded from the generator on the [SVP Challenge website](https://www.latticechallenge.org/svp-challenge/). All these text files contain 20x20 lattice bases. To extract any one of these text files into a format readable by the executable, run (example text file used):
```bash
python3 ./scrap_matrix_from_file.py ./20/svpchallengedim20seed0.txt
```
It creates a text file named `matrix.txt` in the same directory as `main`.

* To run the code on this text file, run:
```bash
./main matrix.txt
```
In the example above, matrix.txt has a 20x20 matrix. If you want to run the executable on the lattice formed by the first few row vectors of the matrix (for example, the first 5 row vectors), just run the executable lke this:
```bash
./main matrix.txt 5
```
`main` prints onto `stdout`.

* Instead of doing each text file one by one, you can simply run `script.sh` to compute all the matrices.
```bash
./script.sh
```
