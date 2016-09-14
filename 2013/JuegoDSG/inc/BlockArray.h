#pragma once
#include "stdafx.h"
#include <iterator>
#include <sstream>
//#define TEST
#ifdef TEST
	#define MAX_DATA_BLOCKS 32
#endif


using namespace std;

template <typename Type, size_t Blocks, size_t BlockSize>
class BlockArray
{
private:
	Type** m_data;
	size_t m_data_index;
	size_t m_data_block;
	size_t m_data_block_index;
	
public:
	FixedArray(void){
		m_data_index = 0; // Posicion absoluta
		m_data_block = 0; // Que bloque
		m_data_block_index = 0; // Posicion dentro del bloque
		m_data = new Type*[Blocks];
		m_data[0] = new Type[BlockSize];
	}

	~FixedArray(void){
		/*
		delete[] m_data;*/
	}
	
	void push_back(Type& elem){
		if(m_data_block_index > BlockSize){
			m_data[m_data_block] = new Type[BlocksSize];
			m_data_block++;
		}
		m_data[m_data_block][m_data_block_index] = elem;
		m_data_block_index++
		m_data_index++;
	}

	size_t size(){
		return m_data_index;
	}

	Type& at(const int index){
		return m_data[index][];
	}

	Type& operator[] (const int index){
		return FixedArray::at(index);
	}

	string toString(){
		ostringstream output;
		for(size_t i=0;i<size();i++){
			output << i << ": " << at(i);
			if(i<size()-1)
				output << endl;
		}
		return output.str();
	}
};