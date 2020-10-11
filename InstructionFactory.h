#ifndef InstructionFactory_h
#define InstructionFactory_h 

#include <iostream>
#include <string>
#include <fstream>

class Instruction;
class Processor;

class InstructionFactory
{
public:
	InstructionFactory();
	Instruction* create(std::string InstrStr);
	void load(Processor& processor, std::string filename);
private:
	Instruction* p;
};
#endif // !InstructionFactory_h
