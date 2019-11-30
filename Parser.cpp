#include "Parser.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cmath>

Parser::Parser() {}

void Parser::parseFromInput() {
	std::string line, code;
	m_Inputs.clear();
	
	// seperate code from inputs 
	while(std::getline(std::cin, line)) {
		if(isDigit(line))
			m_Inputs.push_back(std::atoi(line.c_str()));
		else 
			code += line;
	}

	removeWhitespace(code);
	findVarNames(code);
	replaceVarNames(code);

	m_Code.clear();
	m_Code = code;
}

void Parser::parseFromFile(const char* path) {
	std::ifstream file(path);

	if(file.is_open()) {
		std::string line, code;

		while(std::getline(file, line)) {
			if(isDigit(line))
				m_Inputs.push_back(std::atoi(line.c_str()));
			else 
				code += line;	
		}
		file.close();

		removeWhitespace(code);
		findVarNames(code);
		replaceVarNames(code);

		m_Code.clear();
		m_Code = code;
	}
	else {
		std::cerr << "File not found!" << std::endl;
	}
}

// Getters
std::string& Parser::getCode() {
	return m_Code;
}

std::vector<unsigned char>& Parser::getInputs() {
	return m_Inputs;
}


// Helper functions
bool Parser::isDigit(std::string& s) {
	return !s.empty() && std::find_if(s.begin(), s.end(), [](char c){
		return !std::isdigit(c);
	}) == s.end();
}

bool Parser::isOperator(unsigned char c) {
	return (c == '+' || c == '-' || c == '.' || c == ',' || c == '[' || c == ']' || c == '<' || c == '>' || c == '#'); 
}

int Parser::difference(std::string& s1, std::string& s2) {
	int a = std::distance(m_VarList.begin(), std::find(m_VarList.begin(), m_VarList.end(), s1));
	int b = std::distance(m_VarList.begin(), std::find(m_VarList.begin(), m_VarList.end(), s2));

	return b - a;
}


// Functions used in parsing
void Parser::removeWhitespace(std::string& code) {
	code.erase(std::remove_if(code.begin(), code.end(), ::isspace), code.end());
}

void Parser::findVarNames(std::string& code) {
	m_VarList.clear();
	m_Vars.clear();
	
	std::string temp;
	for(int i = 0; i < code.length(); i++) {
		temp.clear();

		char c = code.at(i);
		while(!isOperator(c)) {
			temp += c;
			c = code.at(++i);
		}

		if(!isOperator(code.at(i-1))) {
			if(!(std::find(m_VarList.begin(), m_VarList.end(), temp) != m_VarList.end()))
				m_VarList.push_back(temp);
			m_Vars.push_back(temp);
		}
	}
}

void Parser::replaceVarNames(std::string& code) {
	std::string prev = m_Vars[0];

	for(int i = 0; i < m_Vars.size(); i++) {
		std::string curr = m_Vars[i];
		
		int index = code.find(m_Vars[i]);
		int length = curr.length();

		code.erase(index, length);

		int diff = difference(prev, curr);
		std::string insertStr = (diff > 0) ? ">" : "<";

		for(int j = 0; j < abs(diff); j++)
			code.insert(index, insertStr);

		prev = curr;
	}
}
