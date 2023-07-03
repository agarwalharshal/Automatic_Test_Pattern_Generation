// module to write into the output file

#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

void outputGeneration(const string &outputFile)
{
    ofstream file(outputFile); // to overwrite the file
    // ofstream file(outputFile, std::ios::app);  // to append to the file
    if (file.is_open())
    {
        file << "[A, B, C, D] = [ " << nodeValues["A"] << ", " << nodeValues["B"] << ", " << nodeValues["C"]
             << ", " << nodeValues["D"] << " ], "
             << "Z = " << !(nodeValues["Z"]) << endl;
        // nodeValues["Z"] = correct result without fault
        // !(nodeValues["Z"]) = faulty result implying FAULT_AT node has FAULT_TYPE fault (the expected value of output to confirm the fault)
        file.close();
        std::cout << "Output written to " << outputFile << endl; // confirmation message along with the file path link
    }
    else
    {
        std::cout << "Failed to open the file." << endl;
    }
}