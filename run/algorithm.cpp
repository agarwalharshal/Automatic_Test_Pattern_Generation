#include <bits/stdc++.h>
using namespace std;

struct Ckt
{
    // string node;
    string input1;
    string input2;
    string operation;
};


map<string, Ckt> parseCircuitFile(const string &circuitFile)
{
    map<string, Ckt> circuit;

    ifstream inputFile(circuitFile);
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty() || line[0] == '#')
            {
                continue; // Skip empty lines and comments where '#' is the first character of a comment line
            }

            // Split the line into tokens
            stringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, ' '))
            {
                tokens.push_back(token);
            }

            if(tokens[0] == "FAULT_AT" || tokens[0] == "FAULT_TYPE")
            {
                circuit[tokens[0]].input1 = tokens[2];
                continue;
            }


            if (tokens.size() != 5 && !(tokens.size() == 4 && tokens[2] == "~"))
            {
                cout << "Invalid circuit file format." << endl;
                circuit.clear(); // Clear the circuit representation
                break;
            }

            if(tokens[2] == "~")
            {
                circuit[tokens[0]].input1 = tokens[3];
                circuit[tokens[0]].operation = tokens[2];

            }
            else{
            circuit[tokens[0]].input1 = tokens[2];
            circuit[tokens[0]].input2 = tokens[4];
            circuit[tokens[0]].operation = tokens[3];

            }
            
        }

        inputFile.close();
    }
    else
    {
        cout << "Failed to open the circuit file." << endl;
    }

    return circuit;
}

void findingInputVector(map<string, Ckt> circuit)
{
    map<string, vector<int>> nodeValues;
    int expectedResult = 0;
    string faulty = circuit["FAULT_AT"].input1;
    int fault = (int)(circuit["FAULT_TYPE"].input1[3]);

    //sensitization
    if (circuit[faulty].operation == "~")
    {
        nodeValues[circuit[faulty].input1].push_back(fault);
    }
    else
    {
        for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if(circuit[faulty].operation == "&")
            {
                if(i&j == !fault)
                {
                    nodeValues[circuit[faulty].input1].push_back(i);
                    nodeValues[circuit[faulty].input2].push_back(j);
                }
            }
            if(circuit[faulty].operation == "|")
            {
                if(i|j == !fault)
                {
                    nodeValues[circuit[faulty].input1].push_back(i);
                    nodeValues[circuit[faulty].input2].push_back(j);
                }
            }
            if(circuit[faulty].operation == "^")
            {
                if(i^j == !fault)
                {
                    nodeValues[circuit[faulty].input1].push_back(i);
                    nodeValues[circuit[faulty].input2].push_back(j);
                }
            }
        }
        
    }
    }
    
    map<string, vector<int>>::iterator it = nodeValues.begin();
    while (it != nodeValues.end())
    {
        cout<<it->first<<" ";
        for (int i = 0; i < it->second.size(); i++)
        {
            cout<<it->second[i]<<" ";
        }
        cout<<endl;
        ++it;
    }
    
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    map<string, Ckt> circuit = parseCircuitFile("circuit.txt");
    map<string, Ckt>::iterator it = circuit.begin();
//     while (it != circuit.end())
//   {
//     cout<<it->first<<" "<<it->second.input1<<" "<<it->second.input2<<" "<<it->second.operation<<endl;
//     ++it;
//   }
    
    findingInputVector(circuit);

    return 0;
}