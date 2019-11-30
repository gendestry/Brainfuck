#pragma once
#include <string>
#include <vector>

class Parser {
private:
	std::string m_Code;

	// Variables
	std::vector<std::string> m_VarList;
	std::vector<std::string> m_Vars;

	std::vector<unsigned char> m_Inputs;
public:
	Parser();
	
	void parseFromInput();
	void parseFromFile(const char* path);

	std::string& getCode();
	std::vector<unsigned char>& getInputs();
private:
	bool isDigit(std::string& s);
	bool isOperator(unsigned char c);
	int difference(std::string& s1, std::string& s2);

	void removeWhitespace(std::string& code);
	void findVarNames(std::string& code);
	void replaceVarNames(std::string& code);
};
