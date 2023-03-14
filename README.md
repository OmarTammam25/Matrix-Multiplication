# Matrix Multiplication using Multithreading
This program is an implementation of matrix multiplication using multithreading in C. The program utilizes three different threading methods to perform matrix multiplication in parallel:

- Thread per matrix
- Thread per row
- Thread per element  

The program takes two matrices as input in the form of text files, multiplies them using each of the three methods, and writes the output to separate text files.

# Running the Program
To run the program, execute the following command:

```
./source [Mat1] [Mat2] [MatOut]
```

If the user does not enter the names of the input matrices and the prefix for the output matrices, the default values are a.txt, b.txt, and c_per_matrix, c_per_row, c_per_element.

```
./matMultp 
```

This will use the default input and output file names.

# Input File Format
The input matrices should be in text file format, with one row per line and each element separated by whitespace. The first line of each file should specify the dimensions of the matrix. For example, a 2x3 matrix would have the following input file format:

```
row=2 col=3
1 2 3
4 5 6
```

# Output File Format
The program will output the resulting matrix products using each of the three methods in separate text files. The file names will be the prefix specified by the user (or the default value c) followed by _per_matrix.txt, _per_row.txt, and _per_element.txt to represent the results obtained using thread per matrix, thread per row, and thread per element methods, respectively.

The output files will have the same format as the input files, with one row per line and each element separated by whitespace.
