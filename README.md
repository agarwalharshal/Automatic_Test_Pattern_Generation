# Automatic Test Pattern Generation

Manufactured chips may have structural faults at certain places/nodes, which must be tested before being delivered to end users. These structural faults can be confirmed by testing _logical faults_ which can represent the effects of the _physical faults_ on the behavior of the system.

The two types of faults under consideration for this project are:

- **SA0** : stuck-at-0, a fault where node is not able to attain value 1, irrespective of inputs
- **SA1** : stuck-at-1, a fault where node is not able to attain value 0, irrespective of inputs

A logical fault can be tested by passing a _test pattern_ or input vector and comparing the obtained result with the expected result. This project is conducted to design an algorithm to generate an input vector along with the expected result to test the above mentioned faults.

The algorithm is designed using the following 3 steps:

- **Fault Sensitisation:** Attempts to sensitize the fault site to a value opposite to the stuck fault.
- **Propagation:** Propagate the fault to a primary output.
- **Justification:** Justify the value at each node.

Detailed solution can be found in this [document](https://drive.google.com/file/d/1MrU_eStIcBmg8w9dZAuP3B32LXHGV1L_/view).

This project is the submission for **Google Girl Hackathon 2023**.

# Algorithm

## Flowchart

<img width="1616" alt="ATPG Algorithm" src="https://github.com/agarwalharshal/Automatic_Test_Pattern_Generation/assets/76912714/3c410ff7-431a-4ea1-99e7-b30e0c16a377">

This [link](https://www.figma.com/file/eIHykHcucw7Ju3Omf21DnY/ATPG-Algorithm?type=whiteboard&node-id=0%3A1&t=VT5nGpi7xJGnmpJf-1) contains a detailed flowchart.

## Pseudocode

The steps involved in the algorithm are:

<u> _Step 1:_ </u> &nbsp; Parse through the circuit file and store the circuit information in a structure.

<u>_Step 2:_</u> &nbsp; Declare a global variable to store and access the node values throughout the algorithm.

<u>_Step 3:_</u> &nbsp; Sensitize the faulty node (FAULT_AT) by assigning the value opposite to its stuck-at fault value (FAULT_TYPE). For example, to sensitize the SA0 (stuck-at 0) fault, the faulty node is assigned the opposite value 1.

<u>_Step 4:_</u> &nbsp; Backtrack the inputs of the faulty node to justify the sensitized value assigned.

<u>_Step 5:_</u> &nbsp; From the faulty node, propagate the fault to a primary output. The output should be the result of the sensitized value. This should be made sure by assigning a value to the second input (if any) of the output gate which ensures the output to be based on the sensitized value.
The following 4 equations have been used in the algorithm to ensure this assignment, for

- AND gate: 1 & ⍺ = ⍺
- OR gate: 0 | ⍺ = ⍺
- XOR gate: 0 ^ ⍺ = ⍺
- NOT gate: ~ ⍺ = ⍺ &nbsp; &nbsp; &nbsp; where, ⍺ is a variable.

<u>_Step 6:_</u> &nbsp; Keep track of the node to be justified (toJustify) after propagation. This is usually the second input (if any) of the output gate other than the faulty input.

<u>_Step 7:_</u> &nbsp; Justify the node and input values by backtracking the inputs from the toJustify node and assigning them the values required to ensure the assigned value of toJustify.

<u>_Step 8:_</u> &nbsp; In the output.txt file, write the resultant input vector, that is, the values assigned to inputs A, B, C and D and the expected value of output to confirm the fault, that is, the opposite of the value stored in Z.

# Project Environment

## Tools Used

- [C++](https://isocpp.org/) - Programming Language
- [Visual Studio Code](https://code.visualstudio.com/) - Integrated Development Environment (IDE)
- [GCC/G++ with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw) - C++ compiler
- [Git](https://git-scm.com/), [GitHub](https://github.com/) - Version History Control
- [Markdown](https://www.markdownguide.org/) - Documentation Language

## How to run the project

1. Clone the repository

```
git clone https://github.com/agarwalharshal/Automatic_Test_Pattern_Generation.git
```

2. Open the directory in Visual Studio Code
3. Launch a new terminal within the **Automatic_Test_Pattern_Generation** directory
4. Change the directory to the `./src` directory.

```
cd .\src\
```

5. Compile the source files using the command:

```
g++ -o out *.cpp
```

6. Run the program:

```
./out
```

7. The output will be generated in the **output.txt** file.

This [video](https://youtu.be/3tIOq7tZQCM) is a demonstration to run the project.

# Test Circuits

## Test Circuit 1

### circuit.txt

```
net_e = A & B
net_f = ~ net_e
net_g = C ^ D
Z = net_f | net_g
FAULT_AT = net_g
FAULT_TYPE = SA0
```

<img width="500" alt="Test Circuit 1" src="https://github.com/agarwalharshal/Automatic_Test_Pattern_Generation/assets/76912714/fe49cd1c-0de5-4ce1-999a-4ef41191e026">

### output.txt

```
[A, B, C, D] = [1, 1, 1, 0], Z = 0
```

## Test Circuit 2

### circuit.txt

```
net_e = ~ A
net_f = net_e | B
net_g = C ^ D
Z = net_f & net_g
FAULT_AT = net_e
FAULT_TYPE = SA1
```

<img width="500" alt="Test Circuit 2" src="https://github.com/agarwalharshal/Automatic_Test_Pattern_Generation/assets/76912714/4de1dabc-bf9b-498d-ae82-d2ea3b4e72ff">

### output.txt

```
[A, B, C, D] = [1, 0, 1, 0], Z = 1
```

## Test Circuit 3

### circuit.txt

```
net_e = A & B
net_f = C | D
net_g = net_e ^ net_f
Z = ~ net_g
FAULT_AT = net_g
FAULT_TYPE = SA1
```

<img width="500" alt="Test Circuit 3" src="https://github.com/agarwalharshal/Automatic_Test_Pattern_Generation/assets/76912714/20b5ebee-60e3-45e6-b01d-1618641a1170">

### output.txt

```
[A, B, C, D] = [1, 0, 0, 0], Z = 0
```
