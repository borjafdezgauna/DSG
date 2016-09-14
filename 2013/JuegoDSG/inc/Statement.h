#pragma once
#include "../stdafx.h"

using namespace std;
class Statement
{
private:
	const string* m_line; 
	string m_command;
	vector<string> m_arguments;
	int argnum;
	char m_delim;
	void parseStatement();
public:
	Statement(string* line, const char delim=' ');
	~Statement(void);
	int getArgNum();
	string& getCommand();
	string& getArgument(const int index);
	vector<string> split(string line, const char delim);
};