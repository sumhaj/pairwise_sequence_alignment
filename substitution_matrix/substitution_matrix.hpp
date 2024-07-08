#ifndef SUBMATRIX_HPP
#define SUBMATRIX_HPP

#include <bits/stdc++.h>
using namespace std;

class substitution_matrix {

    vector <vector <double>> sub_matrix;
    unordered_map<string, int> sequential_alphabets;
public:

    substitution_matrix(string substitution_file_path = "data/substitution_matrices/BLOSUM62_scaled.csv");
    double get_substitution_matrix_value(char sa1, char sa2);
};

#endif