# Imports
import pdb
import awkward as ak
import pylhe
# import ROOT

# pylhe SETUP
# Input file name.  File must be in current directory.
ifile_str = "test.lhe"
# Ensures that pylhe reads in data as an akward array.
pylhe.register_awkward() 
# Read in lhe data.  
arr = pylhe.to_awkward(pylhe.read_lhe_with_attributes(ifile_str))

# Look in arr['particles']['id'] to find which particle ID you would like.
# In this example we will choose 3, just to show the syntax.
# Once the index of the particle is known, the 4 vector can be retrieved.
# The vector is in awkward array format and has many of the basic particle
# properties you would like.  Ex: pt, eta, phi.
test_array = arr['particles']['vector'][:,3]

# The array can then be turned into an RDataframe.
# The names and data of the column are up to the user.
df = ak.to_rdataframe({"x": test_array.x, "y": test_array.y, "z": test_array.z})

# Writes the dataframe as a Tree to an output file using the same column names
# as the awkward array.  Currently the output file is named the same as the
# input file
df.Snapshot("Tree", ifile_str[:-4] + ".root")