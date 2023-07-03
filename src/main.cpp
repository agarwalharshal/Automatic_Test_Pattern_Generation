// Driver Program

#include <bits/stdc++.h>
#include "functions.h"

unordered_map<string, int> nodeValues;

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    std::unordered_map<string, Ckt> circuit = parseCircuitFile("../circuit.txt");

    findingInputVector(circuit);

    outputGeneration("../output.txt");

    return 0;
}