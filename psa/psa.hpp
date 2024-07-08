#ifndef PSA_H
#define PSA_H

#include <bits/stdc++.h>
#include "../substitution_matrix/substitution_matrix.hpp"
using namespace std;

class PSA{
public:
/* Variables */
    string seq1;
    string seq2;
    string aligned_seq_1;
    string aligned_seq_2;
    int len1;
    int len2;
    substitution_matrix sub_matrix;
    double** alignment_matrix;
    double gap_penalty;
    double dist;

    /* Functions */
    PSA(string s1, string s2, string substitution_file_path, double gap_penalty_score);
    double calculate_alignment_score();
    double final_alignment();
};

#endif