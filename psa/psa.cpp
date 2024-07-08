#include <bits/stdc++.h>
#include "psa.hpp"
#include "../substitution_matrix/substitution_matrix.hpp"
using namespace std;

    PSA::PSA(string s1, string s2, string substitution_file_path, double gap_penalty_score){
        seq1 = s1;
        seq2 = s2;
        len1 = s1.length();
        len2 = s2.length();
        aligned_seq_1 = "";
        aligned_seq_2 = "";
        alignment_matrix = new double*[len1 + 1];
        for(int i=0; i<=len1; i++){
            alignment_matrix[i] = new double[len2 + 1];
        }
        sub_matrix = substitution_matrix(substitution_file_path);
        gap_penalty = gap_penalty_score;
        dist = 0.0;
    }

    double PSA::calculate_alignment_score(){
        for (int i=0; i<=len1; i++){
            for (int j=0; j<=len2; j++){
                if(i == 0 && j == 0){
                    alignment_matrix[i][j] = 0;
                    continue;
                }
                if(i == 0){
                    alignment_matrix[i][j] = gap_penalty + alignment_matrix[i][j-1];
                    continue;
                }
                if(j == 0){
                    alignment_matrix[i][j] =  gap_penalty + alignment_matrix[i-1][j];
                    continue;
                }

                char sa1 = seq1[i-1];
                char sa2 = seq2[j-1];
                double sub_value;
                sub_value = sub_matrix.get_substitution_matrix_value(sa1, sa2);
                double ans = INT_MIN;
                ans = max(alignment_matrix[i-1][j-1] + sub_value, ans); 
                ans = max(alignment_matrix[i-1][j] + gap_penalty, ans);
                ans = max(alignment_matrix[i][j-1] + gap_penalty, ans);
                alignment_matrix[i][j] = ans;
            }
        }
        return alignment_matrix[len1][len2];
    }

    double PSA::final_alignment(){
        const double diff = 1e-9;
        int i = len1;
        int j = len2;

        while(i>0 || j>0){
            char sa1;
            char sa2;
            if(i > 0){
                sa1 = seq1[i-1];
            } 
            if(j > 0){
                sa2 = seq2[j-1];
            } 
            double sub_value = DBL_MIN;
            if(i > 0 && j > 0){
                sub_value = sub_matrix.get_substitution_matrix_value(sa1, sa2);
            }

            if(i > 0 && j > 0 && abs(alignment_matrix[i-1][j-1] - alignment_matrix[i][j] + sub_value) < diff){
                aligned_seq_1.push_back(sa1);
                aligned_seq_2.push_back(sa2);
                i--;
                j--;
                
                dist += sub_matrix.get_substitution_matrix_value(sa1, sa1) - sub_value;
            }
            else if(i > 0 && abs(alignment_matrix[i-1][j] - alignment_matrix[i][j] + gap_penalty) < diff){
                aligned_seq_1.push_back(sa1);
                aligned_seq_2.push_back('-');
                i--;
                dist += sub_matrix.get_substitution_matrix_value(sa1, sa1) - gap_penalty;
            }
            else if( j > 0 && abs(alignment_matrix[i][j-1] - alignment_matrix[i][j] + gap_penalty) < diff){
                aligned_seq_1.push_back('-');
                aligned_seq_2.push_back(sa2);
                dist += sub_matrix.get_substitution_matrix_value(sa2, sa2) - gap_penalty;
                j--;
            }
            else{
                cout<<"Error no path found!";
                double error = -1;
                return error;
            }

        }
        reverse(aligned_seq_1.begin(), aligned_seq_1.end());
        reverse(aligned_seq_2.begin(), aligned_seq_2.end());
        return dist;
    }
