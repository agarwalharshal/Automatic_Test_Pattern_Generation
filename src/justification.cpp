// module to backtrack the node path and assign values to the nodes suitable for test pattern generation

#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

void justification(unordered_map<string, Ckt> circuit, string toJustify)
{
    if (circuit.count(toJustify) == 0)
    {
        return;
    }

    int value = nodeValues[toJustify];
    if (circuit[toJustify].operation == "~")
    {
        nodeValues[circuit[toJustify].input1] = (!value);
        value = !value;
        justification(circuit, circuit[toJustify].input1);
    }
    else
    {
        if (circuit[toJustify].operation == "&")
        {
            nodeValues[circuit[toJustify].input1] = 1; // 1&x = x
            nodeValues[circuit[toJustify].input2] = value;
            justification(circuit, circuit[toJustify].input1);
            justification(circuit, circuit[toJustify].input2);
        }
        if (circuit[toJustify].operation == "|")
        {
            nodeValues[circuit[toJustify].input1] = 0; // 0|x = x
            nodeValues[circuit[toJustify].input2] = value;
            justification(circuit, circuit[toJustify].input1);
            justification(circuit, circuit[toJustify].input2);
        }
        if (circuit[toJustify].operation == "^")
        {
            nodeValues[circuit[toJustify].input1] = value;
            nodeValues[circuit[toJustify].input2] = 0; // 0^x = x
            justification(circuit, circuit[toJustify].input1);
            justification(circuit, circuit[toJustify].input2);
        }
    }
}