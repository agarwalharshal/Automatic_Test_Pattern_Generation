// module to assign values to the nodes to propagate the fault to a primary output

#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

string propagation(unordered_map<string, Ckt> circuit, string current, int value)
{
    unordered_map<string, Ckt>::iterator it = circuit.begin();
    string toJustify;
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
                nodeValues[it->first] = (!value);
                value = !value;
            }
            else
            {

                if (it->second.operation == "&")
                {

                    if (it->second.input1 == current)
                    {
                        nodeValues[it->second.input2] = 1;
                    }
                    else
                    {
                        nodeValues[it->second.input1] = 1;
                    }
                    nodeValues[it->first] = value;
                }
                if (it->second.operation == "|")
                {
                    if (it->second.input1 == current)
                    {
                        nodeValues[it->second.input2] = 0;
                    }
                    else
                    {
                        nodeValues[it->second.input1] = 0;
                    }
                    nodeValues[it->first] = value;
                }
                if (it->second.operation == "^")
                {
                    if (it->second.input1 == current)
                    {
                        nodeValues[it->second.input2] = 0;
                    }
                    else
                    {
                        nodeValues[it->second.input1] = 0;
                    }
                    nodeValues[it->first] = value;
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
    return toJustify;
}