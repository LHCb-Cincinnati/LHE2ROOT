# LHE2ROOT
File converter from .lhe "Les Houches Event" files to .root "ROOT" files.

Compile with `g++ -std=c++17 -o LHE2ROOT.exe LHE2ROOT.cpp $(root-config --libs --cflags)`

Run with `LHE2ROOT.exe input_file.lhe` 

This should create a LHE2ROOT.root file in the same directory that has all the same data and weights as the .lhe file.
