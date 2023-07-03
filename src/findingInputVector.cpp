// module to find the input vector to confirm fault

#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

void findingInputVector(unordered_map<string, Ckt> circuit)
{
    string faulty = circuit["FAULT_AT"].input1;
    int fault = (int)(circuit["FAULT_TYPE"].input1[2]);
    fault -= 48;

    // SENSITIZATION
    nodeValues[faulty] = (!fault);
    justification(circuit, faulty);

    string toJustify; // node from which justification starts

    // PROPAGATION
    toJustify = propagation(circuit, faulty, !fault);

    // JUSTIFICATION
    justification(circuit, toJustify);
}