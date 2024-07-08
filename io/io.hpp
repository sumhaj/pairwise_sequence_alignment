#ifndef IO_HPP
#define IO_HPP

#include <bits/stdc++.h>
using namespace std;

class Protein{
public:
    string description;
    string primary_structure;

    Protein(string des, string ps);
};

vector<Protein> create_protein_list(string input_fasta_file_path); 
void write_in_output_file(string output_file_path,string des1, string des2, string seq1, string seq2, double dist);

#endif