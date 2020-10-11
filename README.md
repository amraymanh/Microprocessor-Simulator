# Microprocessor-Simulator
A multi-core microprocessor SIM (Simple Integer Machine) simulator

The nSIM simulator allows the concurrent execution of ***n*** programs by initializing ***n*** processor cores (Processor.h/cpp).

## Data Memory

The ***n*** processor cores share one Data Memory with 1024 memory locations. Access to the data memory is synchronized between the running cores to ensure data integrity and correct execution of the programs' instructions.

## Instructions

Each of the ***n*** processor cores in the nSIM has an Instruction Memory with 1024 locations. Programs are loaded from a disk file into the processor core's Instruction Memory using the Factory Method Design Pattern to allow for the future extension of the Instruction Set.

**Instruction Set:**



| Instruction | Format            | Effect                                   | Remarks                                          |
|-------------|-------------------|------------------------------------------|--------------------------------------------------|
| ADD         | ADD In1, In2, out | out = In1 + In2                          | In1, In2: Address or Constant out: Address       |
| NEG         | NEG In, out       | out = -IN                                | In: Address or Constant out: Address             |
| MUL         | MUL In1, In2, out | out = In1 * In2                          | In1, In2: Address or Constant out: Address       |
| JMP         | JMP A1            | Goto address A1                          | A1: Valid Instr Address                          |
| JMP0        | JMP0 In1, A1      | if In1 == 0:   Goto A1                   | In1: Address or Constant A1: Valid Instr Address |
| ASS         | ASS In1, out      | out = In1                                | In1: Address or Constant out: Address            |
| LE          | LE In1, In2, out  | if In1 <= In2:   out = 1 else:   out = 0 | In1, In2: Address or Constant out: Address       |
| READ        | READ X            | Read input int and store in X            | X: Valid Data Address                            |
| WRITE       | WRITE X           | WRITE X to output                        | X: Address or Constant                           |
| HALT        | HALT              | Stop SIM                                 |                                                  |
