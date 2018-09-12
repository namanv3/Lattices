## Description of the directories and certain files.

### 1
In this directory, Each round is: LLL, followed by reduction. <br>
The while loop breaks if the order of the smallest vector does not change.

### 2
Each round is: LLL, followed by reduction. <br>
The while loop breaks if the largest vector in the basis does not change. <br>
Note: This method is excruciatingly slow. <br>

### 3
Each round is: For each vector, its reduction is followed by LLL on the sub-lattice.<br>
The while loop breaks if the largest vector in the basis does not change.

### 4
The reduction step is a little different. For each vector, the sub-lattice isn't changed.<br>
Rather, the vector itself is changed.<br>
Each round is: For each vector, its reduction is followed by LLL on the sub-lattice.<br>
The while loop breaks if the largest vector in the basis does not change.

### 5
The reduction step is a the same as in 4.<br>
Each round is: LLL, followed by reduction.<br>
The while loop breaks if the largest vector in the basis does not change.

### 6
The reduction step is the same as in 2.<br>
Each round is: LLL, followed by reduction. <br>
The while loop breaks if the sum of all the vector's norm is within a certain range of the previous sum.

### script.h
Usage: ./script.h <num\><br>
Here, num is the dimension of the matrix that you want to test.<br>
It runs all the executables in the five folders and stores the output into a text file.<br>
If num=30, the text file will be "temp30.txt".<br>
The key data: time taken, number of rounds, smallest vector, largest vector are stored in <num\>.txt, ie if num=30, it is stored in 30.txt.<br><br>
NOTE: 30temp.txt and 30.txt are not finished yet. Had to stop the script because the laptop got very hot while running the code.

### ./1/Terminal Saved Output- 40x40.txt
When I first ran the code in folder 1 on 30x30 and 40x40 matrices of vector orders 206.<br>
For 30x30: Did not note down the time, but it took 6 rounds and the order reduced to 12.<br>
For 40x40: Time: 93m32.409s, it took 5 rounds and the order reduced to 11.

### ./5/Terminal Saved Output- 30x30.txt
Saved this to store the output of 30x30 for folder 5 in a text file.<br>
Results: Initially, the first column has >120 digits in its entries. The initial LLL does
barely anything, but the second LLL does a lot of size-reduction. By the end of the 6th round, all the entries of the matrix have less than 6 digits.
Still, it goes on for a total of 33 rounds.<br>
At the end, only 2 matrix entries have 5 digits, rest all have 4 or less.<br>
Time: 1209.372482, rounds: 33<br>
The smallest vector's norm^2 is:  247604526<br>
The largest vector's norm^2 is:   636579895<br>

## Things to Implement further:

* A method in which the while loop breaks if the sum of all the vector's norm is within a certain range of the previous sum. Something like:
```c
if (old_norm_sum - epsilon < new_norm_sum < old_norm_sum + epsilon) break;
```
* Take the 40x40 vector from https://www.latticechallenge.org/svp-challenge/download/challenges/svpchallengedim40seed0.txt and run it and store the results. Also, run it for only LLL with high delta values.

* Print everything for 4x4 to see what is actually happening (small delta like 0.25).

* Read the paper that Mahesh emailed by Monday.

* Port lattice.h and function.h to CUDA by the start of Midsem breaks.

* Checking how all these methods perform if the swap step in ```LLL()``` is removed.
