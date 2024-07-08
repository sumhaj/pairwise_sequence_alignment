#include <bits/stdc++.h>
#include "substitution_matrix.hpp"
using namespace std;

substitution_matrix::substitution_matrix(string substitution_file_path){
    fstream substitution_file;
    string input_data;
    string sa;
    string alphabet;
    string sub_value;
    vector<double> row;
    substitution_file.open(substitution_file_path, ios::in);
    int i = 0;
    getline(substitution_file, sa);
    stringstream s(sa);
    while (getline(s, alphabet, ',')){
        sequential_alphabets[alphabet] = i;
        i++;
    }

    while(getline(substitution_file, input_data)){
        stringstream s(input_data);
        while (getline(s, sub_value, ',')){
            row.push_back(stod(sub_value));
        }
        sub_matrix.push_back(row);
         row.clear();
    }
}

double substitution_matrix::get_substitution_matrix_value(char sa1, char sa2){

    string alphabet1 = "";
    string alphabet2 = "";
    alphabet1 += sa1;
    alphabet2 += sa2;

    if(sequential_alphabets.find(alphabet1) == sequential_alphabets.end()){
        cout << "'" << alphabet1 << "' is not a valid input character\n";
        exit(0);
    }
    else if(sequential_alphabets.find(alphabet2) == sequential_alphabets.end()){
        cout << "'" << alphabet2 << "' is not a valid input character\n";
        exit(0);
    }
    int i = sequential_alphabets[alphabet1];
    int j = sequential_alphabets[alphabet2];
    if(j > i) return sub_matrix[j][i];
    return sub_matrix[i][j];
}
