#include "Executor.h"
#include "Cell.h"
#include <iostream>

Executor::Executor(std::string code, std::vector<unsigned char> inputs) {
	m_Current = new Cell();
	m_Code = code;
	m_Inputs = inputs;
}

Executor::~Executor() {
	Cell::cleanup();
}	


// Setters
void Executor::setCode(std::string code) {
	m_Code = code;
}

void Executor::setInputs(std::vector<unsigned char> inputs) {
	m_Inputs = inputs;
}


// Execution
void Executor::reset() {
	m_PC = 0;
	m_InputIndex = 0;
	Cell::cleanup();

	m_Current = new Cell();
}

void Executor::step() {
	printDebug();
	processChar();
	m_PC++;
}

void Executor::run() {
	for(m_PC = 0; m_PC < m_Code.length(); m_PC++) {
		processChar();
	}
}

void Executor::printDebug() {
	int segLen = 16;
	int strLen = m_Code.length();

	if(strLen > segLen) {
		if(m_PC < (segLen / 2)) { // clamp to left
			std::cout << m_Code.substr(0, segLen);
			std::cout << std::endl;

			for(int i = 0; i < m_PC; i++)
				std::cout << ' ';
			std::cout << '^' << std::endl;
		}
		else if(strLen - m_PC < (segLen / 2)) { // clamp to right
			std::cout << m_Code.substr(strLen - segLen, segLen); 
			std::cout << std::endl;

			for(int i = 0; i < segLen - (strLen - m_PC); i++)
				std::cout << ' ';
			std::cout << '^' << std::endl;
		}
		else {
			std::cout << m_Code.substr(m_PC - segLen/2, segLen); 
			std::cout << std::endl;

			for(int i = 0; i < segLen / 2; i++)
				std::cout << ' ';
			std::cout << '^' << std::endl;
		}
	}
	else {
		std::cout << m_Code << std::endl;
		for(int i = 0; i < m_PC; i++)
			std::cout << ' ';

		std::cout << '^' << std::endl;
	}
}

void Executor::processChar() {
	if(m_PC >= m_Code.length())
		return;
		
	char c = m_Code.at(m_PC);

	if(c == '+') {
		m_Current->increment();
	}
	else if(c == '-') {
		m_Current->decrement();
	}
	else if(c == '<') {
		m_Current = m_Current->prev();
	}
	else if(c == '>') {
		m_Current = m_Current->next();
	}
	else if(c == '.') {
		m_Current->print();
	}
	else if(c == ',') {
		if(m_InputIndex < m_Inputs.size())
			m_Current->setValue(m_Inputs[m_InputIndex++]);
		else
			m_Current->setValue(0);
	}
	else if(c == '[') {
		if(m_Current->getValue() == 0) {
			int counter = 0;
			for(int j = m_PC + 1; j < m_Code.length(); j++) {
				if(m_Code.at(j) == '[')
					counter++;
				else if(m_Code.at(j) == ']') {
					if(counter > 0)
						counter--;
					else {
						m_PC = j;
						break;
					}
				}
			}

		}
	}
	else if(c == ']') {
		if(m_Current->getValue() != 0) {
			int counter = 0;
			for(int j = m_PC - 1; j > 0; j--) {
				if(m_Code.at(j) == ']')
					counter++;
				else if(m_Code.at(j) == '[') {
					if(counter > 0)
						counter--;
					else {
						m_PC = j;
						break;
					}
				}
			}
		}
	}
	else if(c == '#') {
		Cell::dprint();
	}
}
