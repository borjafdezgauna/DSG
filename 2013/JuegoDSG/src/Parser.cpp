#include "../stdafx.h"

#include "../inc/Parser.h"
#include <fstream>
#include <sstream>

Parser::Parser(string filename){
	m_filename = filename;
	m_lineIndex = 0;
}


Parser::~Parser(void){}

void Parser::load(){
	ifstream file(m_filename.c_str());
	if(file){
		while(!file.eof()){
			getline(file,m_currentLine);
			if(m_currentLine.size()==0 || m_currentLine[0]=='#')
				continue;
			Statement st;
			parseStatement(st,m_currentLine);
			processStatement(&st);
			m_lineIndex++;
		}
		endFile();
	}
	else{
		throw FileNotFound(m_filename);
	}
}

void Parser::parseStatement(Parser::Statement& statement ,const string& line, const char delim){
	int endSt = line.find(delim);
	if(endSt>0){
		statement.command = line.substr(0,endSt);
		string params = line.substr(endSt);
		split(statement.arguments,params,delim);
	}
	else{
		statement.command = line;
	}
}

void Parser::split(Parser::Arguments& arguments,const string& line, const char delim ,bool ignore_empty/*=true*/)
{
	//m_cargument = FixedArray<string, 16>();
	char current[128];

	int i= 0;
	char c;
	for(int j= 0; j<line.size(); j++)
	{
		c= line[j];
		if(c!=delim){
			current[i] = c;
			i++;
		}
		else if(i!=0 || !ignore_empty){
			current[i] = '\0';
			arguments.push_back(string(current));
			i=0;
		}
	}
	if(i!=0){
		current[i] = '\0';
		arguments.push_back(string(current));
	}
}

int Parser::stringToInt( const string& s )
{
	try{
		return atoi(s.c_str());
	}
	catch(invalid_argument){
		throwSyntaxError();
	}
}

float Parser::stringToFloat( const string& s )
{
	try{
		return atof(s.c_str());
	}
	catch(invalid_argument){
		throwSyntaxError();
	}
}

void Parser::throwSyntaxError(){
	throw SyntaxError(m_filename, m_lineIndex, m_currentLine);
}