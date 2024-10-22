Program A:

mpicc assignment_10A -o assignment_10A -lm
mpirun -np 4 assignment_10A

==> -lm ==> used for mathematical operations
/sample/in1 and /sample/in2 matrices generated from https://onlinetools.com/math/generate-random-matrix


Program B:

mpicc assignment_10B.c -o assignment_10B
mpirun -np 4 assignment_10B 1024

==> 1024 is buffer size