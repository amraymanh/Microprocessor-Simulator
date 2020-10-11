#include "InstructionFactory.h"
#include "Instruction.h"
#include "Processor.h"

InstructionFactory::InstructionFactory(){}

Instruction* InstructionFactory::create(std::string InstrStr)
{
	int pos;
	if(InstrStr.find("ADD" ) != std::string::npos ||
		InstrStr.find("MUL" ) != std::string::npos || 
		InstrStr.find("LE" ) != std::string::npos )
	{
		pos = InstrStr.find(' ');
		std:: string inst = InstrStr.substr(0, pos);
		InstrStr.erase(0,pos+1);
		pos = InstrStr.find(',');
		std::string in1 = InstrStr.substr(0,pos);
		InstrStr.erase(0, pos+2);
		pos = InstrStr.find(',');
		std::string in2 = InstrStr.substr(0,pos);
		InstrStr.erase(0, pos+2);

		bool isAddr1 = false;
		bool isAddr2 = false;

		if(in1[0] == '$')
		{
			isAddr1 = true;
			in1.erase(0,1);
		}
		if(in2[0] == '$')
		{
			isAddr2 = true;
			in2.erase(0,1);
		}

		int operand1 = std::stoi(in1);
		int operand2 = std::stoi(in2);
		short int outaddr = std::stoi(InstrStr);

		if(inst == "ADD")
			return new ADD(operand1, operand2, outaddr, isAddr1, isAddr2);
		else if(inst == "MUL")
			return new MUL(operand1, operand2, outaddr, isAddr1, isAddr2);
		else if(inst == "LE")
			return new LE(operand1, operand2, outaddr, isAddr1, isAddr2);
		else throw std::invalid_argument("Invalid Instruction\n");

	}
	else if(InstrStr.find("NEG" ) != std::string::npos ||
			InstrStr.find("ASS" ) != std::string::npos ||
			InstrStr.find("JMP0" ) != std::string::npos )
	{
		pos = InstrStr.find(' ');
		std:: string inst = InstrStr.substr(0, pos);
		InstrStr.erase(0,pos+1);
		pos = InstrStr.find(',');
		std::string in = InstrStr.substr(0,pos);
		InstrStr.erase(0, pos+1);

		bool isAddr = false;

		if(in[0] == '$')
		{
			isAddr = true;
			in.erase(0,1);
		}

		int operand = std::stoi(in);
		short int outaddr = std::stoi(InstrStr);

		if(inst == "NEG")
			return new NEG(operand, outaddr, isAddr);
		else if (inst == "ASS")
			return new ASS(operand, outaddr, isAddr);
		else if (inst == "JMP0")
			return new JMP0(operand, outaddr, isAddr);
		else throw std::invalid_argument("Invalid Instruction\n");

	}
	else if(InstrStr.find("JMP" ) != std::string::npos || 
			InstrStr.find("READ") != std::string::npos ||
			InstrStr.find("WRITE" ) != std::string::npos )
	{
		pos = InstrStr.find(' ');
		std:: string inst = InstrStr.substr(0, pos);
		InstrStr.erase(0,pos+1);

		bool isAddr = false;

		if(InstrStr[0] == '$')
		{
			isAddr = true;
			InstrStr.erase(0,1);
		}

		int outaddr = std::stoi(InstrStr);

		if(inst == "JMP")
			return new JMP(outaddr);
		else if(inst == "READ")
			return new READ(outaddr);
		else if (inst == "WRITE")
			return new WRITE(outaddr, isAddr);
		else throw std::invalid_argument("Invalid Instruction\n");
	}
	else if(InstrStr.find("HALT" ) != std::string::npos){ return new HALT(); }
	else throw std::invalid_argument("Invalid Instruction\n");
}

void InstructionFactory::load(Processor& processor, std::string filename)
{
	std::ifstream FileReader(filename);
	if(FileReader.is_open())
	{
		std::string line;
		while(!FileReader.eof())
		{
			getline(FileReader, line);
			try
			{ 
				p = create(line);
				processor.addInstr(p);
			}
			catch (std::exception& err)
			{
				throw std::runtime_error("Failed To Load Instructions Into Memory: " + std::string(err.what()));
			}
		}
		p = nullptr;
	}
	else
		throw std::runtime_error("FAILED TO OPEN PROGRAM FILE\n");
}