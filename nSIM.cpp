#include "nSIM.h"

nSIM::nSIM(int n, std::string filenames[]):ProcessorsCount(0), DataMem()
{
	if(n<Max_Processors)
	{
		for (int i=0; i<n; i++)
		{
			try
			{
				processors[i] = new Processor(ProcessorsCount, DataMem, DMemLocks, filenames[i]);
				ProcessorsCount++;
			}
			catch(std::exception& err)
			{
				throw std::runtime_error("Failed To Construct Processor #"+std::to_string(ProcessorsCount)+':'+std::string(err.what()));
			}
		}
	}
	else
		throw std::invalid_argument("Number Of Processors Bigger Than Max Allowed\n");
}

void nSIM::run()
{
	for(int i=0; i<ProcessorsCount; i++)
		threads[i] = new std::thread(&Processor::run, processors[i]);
	for(int i=0; i<ProcessorsCount; i++)
		threads[i]->join();
}

void nSIM::printDataMem()
{
	for(int i=0; i<DMem_size; i++)
	{
		std::cout<<DataMem[i]<<'\n';
	}
}

nSIM::~nSIM()
{
	for(int i=0; i<ProcessorsCount; i++)
	{
		delete processors[i];
		delete threads[i];
	}
}


void main()
{
	try
	{
		std::string testfiles [] = {"Program 3.txt", "Program 4.txt"};
		nSIM h(2, testfiles);
		h.run();
		std::cout<<"Printing Data Memory:...\n";
		h.printDataMem();
	}
	catch (std::exception err)
	{
		std::cout<<err.what();
	}
}