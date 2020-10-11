#include "Instruction.h"
#include "Processor.h"


ADD::ADD(int in1, int in2, short int out, bool isAddr1, bool isAddr2):
	operand1(in1), operand2(in2), outaddr(out), isaddr1(isAddr1), isaddr2(isAddr2){}

void ADD::execute(Processor& processor)
{
	std::mutex temp1, temp2, temp3;
	try
	{
		lck1 = (isaddr1)? processor.RequestLock(operand1) : &temp1;
		lck2 = ((isaddr2 && isaddr1 && operand2!=operand1)||(isaddr2 && !isaddr1))?
			processor.RequestLock(operand2) : &temp2;
		lck3 =  ((isaddr1 && isaddr2 && operand1 !=outaddr && operand2!=outaddr) ||
				 (isaddr1 && !isaddr2 && operand1 != outaddr) ||
				 (isaddr2 && !isaddr1 && operand2!= outaddr) ||
				 (!isaddr1 && !isaddr2))? 
			processor.RequestLock(outaddr) : &temp3;

		std::unique_lock<std::mutex> guard1(*lck1, std::defer_lock);
		std::unique_lock<std::mutex> guard2(*lck2, std::defer_lock);
		std::unique_lock<std::mutex> guard3(*lck3, std::defer_lock);

		std::lock(guard1, guard2, guard3);

		if(isaddr1)
			operand1 = processor.read(operand1);
		if(isaddr2)
			operand2 = processor.read(operand2);
		processor.write(outaddr, operand1+operand2);
	}
	catch (std::exception err)
	{
		throw std::runtime_error("Could Not Execute ADD Instruction: " + std::string(err.what()));
	}
}


MUL::MUL(int in1, int in2, short int out, bool isAddr1, bool isAddr2):
	operand1(in1), operand2(in2), outaddr(out), isaddr1(isAddr1), isaddr2(isAddr2){}

void MUL::execute(Processor& processor)
{
	std::mutex temp1, temp2, temp3;
	try
	{
		lck1 = (isaddr1)? processor.RequestLock(operand1) : &temp1;
		lck2 = ((isaddr2 && isaddr1 && operand2!=operand1)||(isaddr2 && !isaddr1))?
			processor.RequestLock(operand2) : &temp2;
		lck3 =  ((isaddr1 && isaddr2 && operand1 !=outaddr && operand2!=outaddr) ||
				 (isaddr1 && !isaddr2 && operand1 != outaddr) ||
				 (isaddr2 && !isaddr1 && operand2!= outaddr) ||
				 (!isaddr1 && !isaddr2))? 
			processor.RequestLock(outaddr) : &temp3;

		std::unique_lock<std::mutex> guard1(*lck1, std::defer_lock);
		std::unique_lock<std::mutex> guard2(*lck2, std::defer_lock);
		std::unique_lock<std::mutex> guard3(*lck3, std::defer_lock);

		std::lock(guard1, guard2, guard3);

		if(isaddr1)
			operand1 = processor.read(operand1);
		if(isaddr2)
			operand2 = processor.read(operand2);
		processor.write(outaddr, operand1*operand2);
	}
	catch (std::out_of_range err)
	{
		throw std::runtime_error("Could Not Execute MUL Instruction: " + std::string(err.what()));
	}
}

LE::LE(int in1, int in2, short int out, bool isAddr1, bool isAddr2):
	operand1(in1), operand2(in2), outaddr(out), isaddr1(isAddr1), isaddr2(isAddr2){}

void LE::execute(Processor& processor)
{
	std::mutex temp1, temp2, temp3;
	try
	{
		lck1 = (isaddr1)? processor.RequestLock(operand1) : &temp1;
		lck2 = ((isaddr2 && isaddr1 && operand2!=operand1)||(isaddr2 && !isaddr1))?
			processor.RequestLock(operand2) : &temp2;
		lck3 =  ((isaddr1 && isaddr2 && operand1 !=outaddr && operand2!=outaddr) ||
				 (isaddr1 && !isaddr2 && operand1 != outaddr) ||
				 (isaddr2 && !isaddr1 && operand2!= outaddr) ||
				 (!isaddr1 && !isaddr2))? 
			processor.RequestLock(outaddr) : &temp3;

		std::unique_lock<std::mutex> guard1(*lck1, std::defer_lock);
		std::unique_lock<std::mutex> guard2(*lck2, std::defer_lock);
		std::unique_lock<std::mutex> guard3(*lck3, std::defer_lock);

		std::lock(guard1, guard2, guard3);

		if(isaddr1)
			operand1 = processor.read(operand1);
		if(isaddr2)
			operand2 = processor.read(operand2);
		processor.write(outaddr, (operand1<=operand2)? 1: 0);
	}
	catch (std::out_of_range err)
	{
		throw std::runtime_error("Could Not Execute LE Instruction: " + std::string(err.what()));
	}
}

NEG::NEG(int in, short int out, bool isAddr):
	operand(in), outaddr(out), isaddr(isAddr){}

void NEG::execute(Processor& processor)
{
	std::mutex temp1, temp2;
	try
	{
		lck1 = (isaddr)? processor.RequestLock(operand) : &temp1;
		lck2 = ((isaddr && operand!= outaddr)||(!isaddr))?
			processor.RequestLock(outaddr) : &temp2;

		std::unique_lock<std::mutex> guard1(*lck1, std::defer_lock);
		std::unique_lock<std::mutex> guard2(*lck2, std::defer_lock);

		std::lock(guard1, guard2);


		if(isaddr)
			operand = processor.read(operand);
		processor.write(outaddr, -operand);
	}
	catch(std::out_of_range err)
	{
		throw std::runtime_error("Could Not Execute NEG Instruction: " + std::string(err.what()));
	}
}

ASS::ASS(int in, short int out, bool isAddr):
	operand(in), outaddr(out), isaddr(isAddr){}

void ASS::execute(Processor& processor)
{
	std::mutex temp1, temp2;
	try
	{
		lck1 = (isaddr)? processor.RequestLock(operand) : &temp1;
		lck2 = ((isaddr && operand!= outaddr)||(!isaddr))?
			processor.RequestLock(outaddr) : &temp2;

		std::unique_lock<std::mutex> guard1(*lck1, std::defer_lock);
		std::unique_lock<std::mutex> guard2(*lck2, std::defer_lock);

		std::lock(guard1, guard2);

		if(isaddr)
			operand = processor.read(operand);
		processor.write(outaddr, operand);
	}
	catch(std::out_of_range err)
	{
		throw std::runtime_error("Could Not Execute ASS Instruction: " + std::string(err.what()));
	}
}

JMP0::JMP0(int in, short int addr, bool isAddr):
	operand(in), trgtaddr(addr), isaddr(isAddr){}

void JMP0::execute(Processor& processor)
{
	try
	{
		if(isaddr)
		{
			lck = processor.RequestLock(operand);
			lck->lock();
			operand = processor.read(operand);
			lck->unlock();
		}
		if (operand == 0)
			processor.setPc(trgtaddr);
	}
	catch(std::exception& err)
	{
		throw std::runtime_error("Could Not Execute JMP0 Instruction: " + std::string(err.what()));
	}
}


JMP::JMP(short int addr):trgtaddr(addr){}

void JMP::execute(Processor& processor)
{
	try { processor.setPc(trgtaddr); }
	catch(std::exception& err)
	{
		throw std::runtime_error("Could Not Execute JMP Instruction: " + std::string(err.what()));
	}
}

READ::READ(short int addr):trgtaddr(addr){}

void READ::execute(Processor& processor)
{
	std::string user_input;
	IOlck = processor.RequestIO(0);
	IOlck->lock();
	std::cout<<">>..";
	IOlck->unlock();
	std::cin>>user_input;
	try
	{
		int input = std::stoi(user_input);
		lck = processor.RequestLock(trgtaddr);
		lck->lock();
		processor.write(trgtaddr, input);
		lck->unlock();
	}
	catch (std::exception& err)
	{
		throw std::runtime_error("Could Not Execute READ Instruction: " + std::string(err.what()));
	}
}

WRITE::WRITE(int in, bool IsAddr):operand(in), isaddr(IsAddr){}

void WRITE::execute(Processor& processor)
{
	IOlck = processor.RequestIO(0);
	if(isaddr)
	{
		try
		{
			lck = processor.RequestLock(operand);
			std::unique_lock<std::mutex> guard1(*lck, std::defer_lock);
			std::unique_lock<std::mutex> guard2(*IOlck, std::defer_lock);
			std::lock(guard1, guard2);
			int value = processor.read(operand);
			std::cout<<value<<'\n';
		}
		catch (std::out_of_range err)
		{
			throw std::runtime_error("Could Not Execute WRITE Instruction: " + std::string(err.what()));
		}
	}
	else
	{
		IOlck->lock();
		std::cout<<operand<<'\n';
		IOlck->unlock();

	}
}

void HALT::execute(Processor& processor)
{
	processor.stop();
}
