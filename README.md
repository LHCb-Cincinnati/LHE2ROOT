# LHE2ROOT
File converter from .lhe "Les Houches Event" files to .root "ROOT" files.  There is a very general C++ version and a more specific python version where the user must do some work to apply it to a specific file.

## C++ Version
Compile with `g++ -std=c++17 -o LHE2ROOT.exe LHE2ROOT.cpp $(root-config --libs --cflags)`

Run with `LHE2ROOT.exe input_file.lhe` 

This should create a LHE2ROOT.root file in the same directory that has all the same data and weights as the .lhe file.

## Python Version
Change settings in the .py file relevant for the .lhe file.

Run with `python LHE2ROOT.py`
