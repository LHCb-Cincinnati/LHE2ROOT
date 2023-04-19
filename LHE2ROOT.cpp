// STD Includes
#include <string.h>
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// ROOT Includes
#include "TTree.h"
#include "TFile.h"


int main (int argc, char* argv[]){
    if(argc < 2){
        throw std::invalid_argument("No input files given.");
    }
    // C++ Variables
    std::fstream input_file(argv[1]);
    std::vector<int> * pid_vec;
    std::vector<double> * px_vec;
    std::vector<double> * py_vec;
    std::vector<double> * pz_vec;
    std::vector<double> * e_vec;
    std::vector<double> * wgt_vec;

    // ROOT variables
    TFile ofile("LHA2ROOT.root", "RECREATE");
    TTree tree("Title", "Title");
    tree.Branch("PID", &pid_vec);
    tree.Branch("Px", &px_vec);
    tree.Branch("Py", &py_vec);
    tree.Branch("Pz", &pz_vec);
    tree.Branch("Energy", &e_vec);
    tree.Branch("Weight", &wgt_vec);

// for(std::string line; getline( input_file, line); ){
    for(int i; i < 600; i++){
        std::string line;
        getline(input_file, line);
        static int flag = 0;
        static int num_particles = 0;  
        static int counter = 0;
        switch (flag){
            case 0:
                if (line.find("<event>") != std::string::npos){
                    flag = 2;
                }
                else if (line.find("<rwgt>") != std::string::npos){
                    flag = 3;
                }
                else if (line.find("</event>") != std::string::npos){
                    flag = 4;
                }
                break;   
            case 1:{
                std::istringstream iss(line);
                std::array<double, 13> test;
                iss >> test[0] >> test[1] >> test[2] >> test[3] >> test[4] >> test[5] >> test[6] >> test[7] >> test[8] >> test[9] >> test[10] >> test[11] >> test[12];
                pid_vec->push_back(test[0]);
                px_vec->push_back(test[6]);
                py_vec->push_back(test[7]);
                pz_vec->push_back(test[8]);
                e_vec->push_back(test[9]);
                counter = counter - 1;
                if (counter == 0){
                    flag = 0;
                } // end if
                break;
            } // end case
            case 2:{
                std::istringstream iss(line);
                iss >> num_particles;
                counter = num_particles;
                pid_vec->reserve(num_particles);
                px_vec->reserve(num_particles);
                py_vec->reserve(num_particles);
                pz_vec->reserve(num_particles);
                e_vec->reserve(num_particles);
                flag = 1;
                break;
            } // end case
            case 3:{
                if (line == "</rwgt>"){
                    flag = 0;
                    break;
                }
                else{
                    std::istringstream iss(line);
                    std::string test[3];
                    iss >> test[0] >> test[1] >> test[2];
                    wgt_vec->push_back(std::stof(test[2]));
                    break;
                }
            } // end case
            case 4:{
                tree.Fill();
                pid_vec->clear();
                px_vec->clear();
                py_vec->clear();
                pz_vec->clear();
                e_vec->clear();
                wgt_vec->clear();
                flag = 0;
                break;
            } // end case
        }
    } // end for Loop
    tree.Print();
    tree.Write();
    ofile.Close();
}// end program