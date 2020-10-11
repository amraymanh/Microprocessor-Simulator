#ifndef nSIM_H
#define nSIM_H

#include <mutex>
#include <thread>
#include "Processor.h"

extern const int DMem_size = 15;
const int Max_Processors = 10;

class nSIM
{
public: 
	nSIM(int n, std::string []);
	void run();
	void printDataMem();
	~nSIM();
private:
	Processor* processors[Max_Processors];
	std::thread* threads[Max_Processors];
	int DataMem[DMem_size];
	std::mutex DMemLocks[DMem_size];
	int ProcessorsCount;
};


#endif // !nSIM_H
