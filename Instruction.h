#ifndef Instruction_h
#define Instruction_h

#include <iostream>
#include <mutex>
class Processor;

class Instruction
{
public:
	Instruction(){}
	virtual void execute(Processor& processor) = 0;
	//virtual ~Instruction();
};

class ADD : public Instruction
{
public:
	ADD(int in1, int in2, short int out, bool isAddr1, bool isAddr2);
	void execute(Processor&);

private:
	int operand1;
	int operand2;
	short int outaddr;
	bool isaddr1;
	bool isaddr2;
	std::mutex* lck1;
	std::mutex* lck2;
	std::mutex* lck3;
};


class MUL : public Instruction
{
public:
	MUL(int in1, int in2, short int out, bool isAddr1, bool isAddr2);
	void execute(Processor&);

private:
	int operand1;
	int operand2;
	short int outaddr;
	bool isaddr1;
	bool isaddr2;
	std::mutex* lck1;
	std::mutex* lck2;
	std::mutex* lck3;
};

class LE : public Instruction
{
public:
	LE(int in1, int in2, short int out, bool isAddr1, bool isAddr2);;
	void execute(Processor&);

private:
	int operand1;
	int operand2;
	short int outaddr;
	bool isaddr1;
	bool isaddr2;
	std::mutex* lck1;
	std::mutex* lck2;
	std::mutex* lck3;
};

class NEG : public Instruction
{
public:
	NEG(int in, short int out, bool isAddr);
	void execute(Processor&);

private:
	int operand;
	short int outaddr;
	bool isaddr;
	std::mutex* lck1;
	std::mutex* lck2;
};

class ASS : public Instruction
{
public:
	ASS(int in, short int out, bool isAddr);
	void execute(Processor&);

private:
	int operand;
	short int outaddr;
	bool isaddr;
	std::mutex* lck1;
	std::mutex* lck2;
};

class JMP0 : public Instruction
{
public:
	JMP0(int in, short int out, bool isAddr);
	void execute(Processor&);

private:
	int operand;
	short int trgtaddr;
	bool isaddr;
	std::mutex* lck;
};

class JMP : public Instruction
{
public:
	JMP(short int addr);
	void execute(Processor&);

private:
	short int trgtaddr;
};

class READ: public Instruction
{
public:
	READ(short int addr);
	void execute(Processor&);
		
private:
	short int trgtaddr;
	std::mutex* lck;
	std::mutex* IOlck;
};

class WRITE: public Instruction
{
public:
	WRITE(int in, bool isAddr);
	void execute(Processor&);

private:
	int operand;
	bool isaddr;
	std::mutex* lck;
	std::mutex* IOlck;
};


class HALT: public Instruction
{
public: 
	HALT(){}
	void execute(Processor&);
};

#endif // !Instruction_h
