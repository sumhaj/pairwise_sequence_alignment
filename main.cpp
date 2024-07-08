#include <bits/stdc++.h>
#include "psa/psa.hpp"
#include "io/io.hpp"
using namespace std;


int main(int argc, char* argv[]){

    if(argc == 1){
        cout << "Pairwise Sequence Alignment Algorithm" << endl;
        cout << "Use \"executable_file_path -help\" to view all valid commands"<<endl;
        return 0;
    }

    if(argc == 2 && !strcmp(argv[1], "-help")){
        cout << "Command should be of the form: \"executable_file_path -in input_file_path -out output_file_path -sub substitution_matrix_file -gap gap_penalty_score\"." << endl << endl;
        cout << "The order of the arguments is not interchangable and should be as mentioned above." << endl << endl;
        cout << "All the valid arguments are listed below: " << endl << endl;
        cout << "-help: This is used to view all the commands available" << endl << endl;
        cout << "-in: This argument expects user to enter input file path. Input file should be in fasta format." << endl << endl;
        cout << "-out: This argument expects user to enter output file path. Output file generated will be in fasta format." << endl << endl;
        cout << "-sub: Optional, This argument expects user to enter substitution file path. Substitution file should be in CSV format. By default Blosum62 substitution matrix scaled between 0 and 1 is used" << endl << endl;
        cout << "-gap: Optional, This argument  expects user to enter gap penalty value. Default value for gap penalty is -0.0"  << endl << endl;
        return 0;
    }    

    if(argc < 5 || argc > 9 || strcmp(argv[1], "-in") || strcmp(argv[3], "-out") || argc%2 == 0) {
        cout << "Invalid command : Command should be of the form: \"executable_file_path -in input_file_path -out output_file_name -sub substitution_matrix_file -gap gap_penalty_score\"."<<"\n";
        cout << "Use \"executable_file_path -help\" to view all valid commands"<<endl;
        return 0;
    }
    vector<Protein> protein_list;
    string input_file_path = argv[2];
    string output_file = argv[4];
    string substitution_file_path = "data/substitution_matrices/BLOSUM62_scaled.csv";
    double gap_penalty = -0.0;
    if(argc >= 7){
        if(!strcmp(argv[5], "-sub")){
            substitution_file_path = argv[6];
            ifstream substitution_file(substitution_file_path);
            if(!substitution_file.is_open()){
                cout << "Invalid path: Substitution file not Found" << endl;
                return 0;
            }
            substitution_file.close();
        }
        else if(!strcmp(argv[5], "-gap") && argc == 7){
            gap_penalty = stod(argv[6]);
        }
        else{
            cout << "Invalid command : Command should be of the form: \"executable_file_path -in input_file_path -out output_file_name -sub substitution_matrix_file -gap gap_penalty_score\"."<<"\n";
            cout << "Use \"executable_file_path -help\" to view all valid commands"<<endl;
            return 0;
        }
    }
        
    if(argc == 9){
        if(!strcmp(argv[7], "-gap")) gap_penalty = stod(argv[8]);
        else{
            cout << "Invalid command : Command should be of the form: \"executable_file_path -in input_file_path -out output_file_name -sub substitution_matrix_file -gap gap_penalty_score\"."<<"\n";
            cout << "Use \"executable_file_path -help\" to view all valid commands"<<endl;
            return 0;
        }
    } 
    
    
    ifstream input_file(input_file_path);
    if(!input_file.is_open()){
        cout<<"Invalid path: Input file not Found"<<endl;
        return 0;
    }
    input_file.close(); 
    protein_list = create_protein_list(input_file_path);

    int len = protein_list.size();

    if(len < 2){
        cout << "Insufficient number of protein sequences" << endl;
    }
    else{
        for(int i=0;i<len-1;i++){
            for(int j=i+1;j<len;j++){
                string des1 = protein_list[i].description;
                string des2 = protein_list[j].description;
                string seq1 = protein_list[i].primary_structure;
                string seq2 = protein_list[j].primary_structure;
                PSA psa(seq1, seq2, substitution_file_path, gap_penalty);
                psa.calculate_alignment_score();
                psa.final_alignment();
                write_in_output_file(output_file, des1, des2, psa.aligned_seq_1, psa.aligned_seq_2, psa.dist); 
            }
        }
    }
    cout<< output_file << " created successfully" << endl;
}