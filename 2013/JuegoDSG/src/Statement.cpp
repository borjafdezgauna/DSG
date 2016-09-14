#include "../inc/Statement.h"


Statement::Statement(string* line, const char delim /* =' ' */)
{
	m_line = line;
	m_delim = delim;
}

void Statement::parseStatement(){
	int endSt = m_line->find(m_delim);
	if(endSt>0){
		m_command = m_line->substr(0,endSt);
		string params = m_line->substr(endSt+1);
		m_arguments = split(params,m_delim);
	}
	else{
		m_command = *m_line;
		m_arguments = vector<string>();
	}
}

vector<string> Statement::split(string line, const char delim){
	string sp_ar[32];
	char currentc[128];
	string current;
	int spi = 0;
	int ci = 0;
	char c;
	for(int i= 0; i<line.size(); i++)
	{
		c= line[i];
		if(c!=delim){
			/*
			currentc[ci] = line[ci];
			*/
			currentc[ci] = c;
			ci++;
		}
		else if(ci!=0){
			/*
			currentc[ci] = '\0';
			sp_ar[spi] = string(currentc);
			*/
			currentc[ci] = '\0';
			sp_ar[spi] = string(currentc);
			spi++;
			ci = 0;
		}
	}
	if(ci!=0){
		currentc[ci] = '\0';
		sp_ar[spi] = string(currentc);
		spi++;
	}
	vector<string> sp = vector<string>(spi);
	for(int i=0;i<spi;i++){
		sp[i] = sp_ar[i];
	}
	return sp;
}


Statement::~Statement(void)
{
}

