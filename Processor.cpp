#include "Processor.h"

extern const int DMem_size;
std::mutex Processor::cinLock;
std::mutex Processor::coutLock;

Processor::Processor(int id, int* DMemPointer, std::mutex* Lockspointer, std::string filename):
	pid(id), DMemP(DMemPointer), LocksP(Lockspointer), pc(0), ic(0), halt(false)
{
	InstructionFactory IF;
	IF.load(*this, filename);
}
	
void Processor::addInstr(Instruction* p)
{
	if (ic < IMem_size)
	{
		InstrMem[ic] = p;
		ic++;
	}
	else
		throw std::out_of_range("Instruction Memory Is Full\n"); 
}

void Processor::write(short int addr, int value)
{
	if( addr>=0 && addr<DMem_size)
	{
		*(DMemP+addr) = value;
	}
	else throw std::out_of_range("Invalid Memory Address \n");
}

int Processor::read(short int addr)
{
	if( addr>=0 && addr<DMem_size)
	{
		return *(DMemP+addr);
	}
	else throw std::out_of_range("Invalid Memory Address \n");

}

std::mutex* Processor::RequestLock(short int addr)
{
	if(addr>= 0 && addr<DMem_size)
		return (LocksP+addr);
	else
		throw std::out_of_range("Invalid Memory Address\n");
}

std::mutex* Processor::RequestIO(int i)
{
	if(i)
		return &cinLock;
	else
		return &coutLock; 

}
void Processor::run()
{
	try
	{
		while(pc<ic && !halt)
		{
			InstrMem[pc]->execute(*this);
			pc++;
		}
		if(pc == ic && !halt)
			std::cout<<"Simultion Ended Without HALT\n";
	}
	catch(std::exception err)
	{
		std::cout<<"Runtime Error While Running Processor "<<pid<<':'+std::string(err.what());
	}
}



void Processor::setPc(short int newPc)
{
	if (newPc == pc)
		throw std::invalid_argument("Jumping To The Same Instruction Is Not Allowed\n");
	if( newPc>=0 && newPc<ic)
		pc = newPc-1;
	else throw std::out_of_range("Invalid Instruction Address \n");
}

void Processor::stop() { halt = true; }

Processor::~Processor()
{
	for(int i=0; i<ic; i++)
		delete InstrMem[i];
}