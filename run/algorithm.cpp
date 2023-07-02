#include <bits/stdc++.h>
using namespace std;

struct Ckt
{
    // string node;
    string input1;
    string input2;
    string operation;
};

map<string, vector<int>> nodeValues;

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

            if (tokens[0] == "FAULT_AT" || tokens[0] == "FAULT_TYPE")
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
        cout << "Failed to open the circuit file." << endl;
    }

    return circuit;
}

void justification(map<string, Ckt> circuit, string toJustify)
{
    if (circuit.count(toJustify) == 0)
    {
        return;
    }

    map<string, Ckt>::iterator it2 = circuit.begin();
    int value = nodeValues[toJustify][0];
    if (circuit[toJustify].operation == "~")
    {
        nodeValues[circuit[toJustify].input1].push_back(!value);
        value = !value;
        justification(circuit, circuit[toJustify].input1);
    }
    else
    {
        if (circuit[toJustify].operation == "&")
        {
            nodeValues[circuit[toJustify].input1].push_back(value);
            nodeValues[circuit[toJustify].input2].push_back(value);
            justification(circuit, circuit[toJustify].input1);
            justification(circuit, circuit[toJustify].input2);
        }
        if (circuit[toJustify].operation == "|")
        {
            nodeValues[circuit[toJustify].input1].push_back(0); // 0|x = x
            nodeValues[circuit[toJustify].input2].push_back(value);
            justification(circuit, circuit[toJustify].input1);
            justification(circuit, circuit[toJustify].input2);
        }
        if (circuit[toJustify].operation == "^")
        {
            nodeValues[circuit[toJustify].input1].push_back(value);
            nodeValues[circuit[toJustify].input2].push_back(0); // 0^x = x
            justification(circuit, circuit[toJustify].input1);
            justification(circuit, circuit[toJustify].input2);
        }
    }
}

void findingInputVector(map<string, Ckt> circuit)
{
    // map<string, vector<int>> nodeValues;
    int expectedResult = 0;
    string faulty = circuit["FAULT_AT"].input1;
    int fault = (int)(circuit["FAULT_TYPE"].input1[2]);

    // sensitization
    nodeValues[faulty].push_back(!fault);
    justification(circuit, faulty);

    // map<string, vector<int>>::iterator itt = nodeValues.begin();
    // while (itt != nodeValues.end())
    // {
    //     cout << itt->first << " ";
    //     for (int i = 0; i < itt->second.size(); i++)
    //     {
    //         cout << itt->second[i] << " ";
    //     }
    //     cout << endl;
    //     ++itt;
    // }
    // cout << "\n\n\n\n";

    // sensitization
    // if (circuit[faulty].operation == "~")
    // {
    //     nodeValues[circuit[faulty].input1].push_back(fault);
    // }
    // else
    // {
    //     for (int i = 0; i < 2; i++)
    //     {
    //         for (int j = 0; j < 2; j++)
    //         {
    //             if (circuit[faulty].operation == "&")
    //             {
    //                 if (i & j == !fault)
    //                 {
    //                     nodeValues[circuit[faulty].input1].push_back(i);
    //                     nodeValues[circuit[faulty].input2].push_back(j);
    //                 }
    //             }
    //             if (circuit[faulty].operation == "|")
    //             {
    //                 if (i | j == !fault)
    //                 {
    //                     nodeValues[circuit[faulty].input1].push_back(i);
    //                     nodeValues[circuit[faulty].input2].push_back(j);
    //                 }
    //             }
    //             if (circuit[faulty].operation == "^")
    //             {
    //                 if (i ^ j == !fault)
    //                 {
    //                     nodeValues[circuit[faulty].input1].push_back(i);
    //                     nodeValues[circuit[faulty].input2].push_back(j);
    //                 }
    //             }
    //         }
    //     }
    // }
    // nodeValues[faulty].push_back(!fault);

    string toJustify;

    // propagation
    map<string, Ckt>::iterator it = circuit.begin();
    string current = faulty;
    int value = !fault;
    while (it != circuit.end() && current != "Z")
    {
        if (it->first == "FAULT_AT" || it->first == "FAULT_TYPE")
        {
            ++it;
            continue;
        }
        if (it->second.input1 == current || it->second.input2 == current)
        {
            if (it->second.operation == "~")
            {
                nodeValues[it->first].push_back(!value);
                value = !value;
            }
            else
            {

                if (it->second.operation == "&")
                {

                    if (it->second.input1 == current)
                    {
                        nodeValues[it->second.input2].push_back(1);
                    }
                    else
                    {
                        nodeValues[it->second.input1].push_back(1);
                    }
                    nodeValues[it->first].push_back(value);
                }
                if (it->second.operation == "|")
                {
                    if (it->second.input1 == current)
                    {
                        nodeValues[it->second.input2].push_back(0);
                    }
                    else
                    {
                        nodeValues[it->second.input1].push_back(0);
                    }
                    nodeValues[it->first].push_back(value);
                }
                if (it->second.operation == "^")
                {
                    if (it->second.input1 == current)
                    {
                        nodeValues[it->second.input2].push_back(0);
                    }
                    else
                    {
                        nodeValues[it->second.input1].push_back(0);
                    }
                    nodeValues[it->first].push_back(value);
                }
            }

            // finding the value of toJustify
            if (it->first == "Z")
            {
                if (it->second.input1 == current)
                    toJustify = it->second.input2;
                else
                    toJustify = it->second.input1;
            }

            current = it->first;
            it = circuit.begin();
            continue;
        }
        ++it;
    }

    // justification
    justification(circuit, toJustify);

    // itt = nodeValues.begin();
    // while (itt != nodeValues.end())
    // {
    //     cout << itt->first << " ";
    //     for (int i = 0; i < itt->second.size(); i++)
    //     {
    //         cout << itt->second[i] << " ";
    //     }
    //     cout << endl;
    //     ++itt;
    // }

    // OUTPUT
    cout << "[A, B, C, D] = [ " << nodeValues["A"][0] << ", " << nodeValues["B"][0] << ", " << nodeValues["C"][0] << ", " << nodeValues["D"][0] << " ], "
         << "Z = " << !(nodeValues["Z"][0]) << endl;
    // nodeValues["Z"][0] = correct result without fault
    // !(nodeValues["Z"][0]) = faulty result implying FAULT_AT node has FAULT_TYPE fault
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    map<string, Ckt> circuit = parseCircuitFile("circuit.txt");
    map<string, Ckt>::iterator it = circuit.begin();

    findingInputVector(circuit);

    return 0;
}