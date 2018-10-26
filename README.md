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
