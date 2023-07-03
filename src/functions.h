#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <bits/stdc++.h>
using namespace std;

// structure to store circuit information
struct Ckt
{
    string input1;
    string input2;
    string operation;
};

extern unordered_map<string, int> nodeValues; // global variable to store node values

unordered_map<string, Ckt> parseCircuitFile(const string &circuitFile);
void outputGeneration(const string &outputFile);
void justification(unordered_map<string, Ckt> circuit, string toJustify);
string propagation(unordered_map<string, Ckt> circuit, string current, int value);
void findingInputVector(unordered_map<string, Ckt> circuit);

#endif
