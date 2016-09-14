#pragma once

#include "FixedArray.h"

using namespace std;

/*
 * Abstract class for Parser
 */

class Parser
{
public:

	typedef vector<string> Arguments;
	struct Statement{
		string command;
		Arguments arguments;
	};


	//////    Exceptions    //////////////////////////////////////////////////
	class FileNotFound : public runtime_error{
	public:
		FileNotFound::FileNotFound(string filename) 
			: runtime_error("File \""+filename+"\" does not exist"){};
	};

	class ParseException : public runtime_error{
	public:
		ParseException::ParseException(string err) : runtime_error(err){};
	};

	class SyntaxError: public ParseException{
	public:
		SyntaxError::SyntaxError(string filename,  int line_index ,string line) 
			: ParseException("Syntax error in file \""+ filename +"\""){};
	};

	//////////////////////////////////////////////////////////////////////////

protected:
	// Constructor
	Parser(string filename);
	~Parser(void);

	// Variables
	int m_lineIndex;
	string m_currentLine;
	string m_filename;
	// Temp variables
	Parser::Arguments t_arg;
	Parser::Statement t_st;
	// Methods
	void split(Parser::Arguments& arguments,const string& line, const char delim, bool ignore_empty=true);
	void parseStatement(Parser::Statement&, const string& line, const char delim=' ');
	virtual void endFile()=0;
	virtual void processStatement(Parser::Statement* statement)=0;
	void throwSyntaxError(void);
	float stringToFloat(const string& s);
	int stringToInt(const string& s);

public:
	void load(void);
};

