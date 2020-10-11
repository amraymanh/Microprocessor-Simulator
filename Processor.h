#ifndef Processor_h
#define Processor_h

#include <iostream>
#include <string>
#include <mutex>
#include "InstructionFactory.h"
#include "Instruction.h"

const int IMem_size = 15;

class Processor
{
public:
	Processor(int id, int* DMemPointer, std::mutex* LocksPointer, std::string filename);
	void addInstr(Instruction*);
	void write(short int addr, int value);
	int read(short int addr);
	std::mutex* RequestLock(short int addr);
	std::mutex* RequestIO(int);
	void run();
	void stop();
	void setPc(short int);
	~Processor();

private:
	short int pc;	//program counter
	short int ic;	//instruction counter (how many instructions in memory)
	int pid;	//processor id
	bool halt;
	Instruction* InstrMem[IMem_size];
	int* DMemP;
	std::mutex* LocksP;
	static std::mutex cinLock;
	static std::mutex coutLock;
};

#endif // !Processor_h
