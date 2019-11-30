#pragma once
#include <string>
#include <vector>
#include "Cell.h"

class Executor {
private:
	// Code and input
	std::string m_Code;
	std::vector<unsigned char> m_Inputs;
	int m_InputIndex = 0;

	// Program counter
	int m_PC = 0;

	// Current storage cell
	Cell* m_Current;
public:
	Executor(std::string code, std::vector<unsigned char> inputs);
	~Executor();

	void setCode(std::string code);
	void setInputs(std::vector<unsigned char> inputs);

	void reset();
	void step();
	void run();
	void printDebug();
private:
	void processChar();
};
