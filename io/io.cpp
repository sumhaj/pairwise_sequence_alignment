#include <bits/stdc++.h>
#include "io.hpp"
using namespace std;

Protein::Protein(string des, string ps){
    description = des;
    primary_structure = ps;
}

bool isSpace(string input_data){
    int len = input_data.length();
    for(int i=0;i<len;i++){
        if(!isspace(input_data[i])) return false;
    }
    return true;
}

string remove_spaces(string ps){
    while(isspace(ps[ps.size()-1])){
        ps.pop_back();
    }
    return ps;
}

vector<Protein> create_protein_list(string input_fasta_file_path){

    ifstream input_file(input_fasta_file_path);
    string input_data;
    string des;
    vector<Protein> protein_list;
    string ps;

    while(getline(input_file, input_data)){
        if(input_data[0] == '>'){
            des = input_data;
            des.erase(des.begin());
            des.erase(remove(des.begin(), des.end(), '\n'), des.end());
        }
        else if(!isSpace(input_data)){
            ps = input_data;
            ps = remove_spaces(ps);
            Protein protein_entry(des, ps);
            protein_list.push_back(protein_entry);
        }
    }
    input_file.close();
    return protein_list;
}

void write_in_output_file(string output_file_path, string des1, string des2, string seq1, string seq2, double dist){
    fstream output_file;
    output_file.open(output_file_path, ios::app);
    string des =  "> " + des1 + " + " + des2 + ", distance = " + to_string(dist);
    output_file << des << endl;
    output_file << seq1 << endl;
    output_file << seq2 << endl;
    output_file << endl;
    output_file.close();
    return;
}