// module to read circuit file and store it in a map

#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

unordered_map<string, Ckt> parseCircuitFile(const string &circuitFile)
{
    unordered_map<string, Ckt> circuit;

    ifstream inputFile(circuitFile);
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty() || line[0] == '#')
            {
                continue; // skip empty lines and comments where '#' is the first character of a comment line
            }

            // split the line into tokens
            stringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, ' '))
            {
                tokens.push_back(token);
            }

            if (tokens[0] == "FAULT_AT" || tokens[0] == "FAULT_TYPE")
            {
                circuit[tokens[0]].input1 = tokens[2];
                continue;
            }

            if (tokens.size() != 5 && !(tokens.size() == 4 && tokens[2] == "~"))
            {
                std::cout << "Invalid circuit file format." << endl;
                circuit.clear();
                break;
            }

            if (tokens[2] == "~")
            {
                circuit[tokens[0]].input1 = tokens[3];
                circuit[tokens[0]].operation = tokens[2];
            }
            else
            {
                circuit[tokens[0]].input1 = tokens[2];
                circuit[tokens[0]].input2 = tokens[4];
                circuit[tokens[0]].operation = tokens[3];
            }
        }

        inputFile.close();
    }
    else
    {
        std::cout << "Failed to open the circuit file." << endl;
    }

    return circuit;
}