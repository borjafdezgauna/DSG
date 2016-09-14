#pragma once
#include "../stdafx.h"
#include <iterator>
#include <sstream>
#include "FixedArray.h"

#define MAX_SIZE 4096
#define MAX_BLOCKS 32

using namespace std;

// Clase Array para longitud no determinada
template <typename Type>
class FitArray
{
private:
	Type** m_data;

	size_t m_next_index; // Siguiente elemento a insertar
	size_t m_current_block; // Bloque actual
	size_t m_data_length; // Cantidad de datos total

	size_t m_block_num; // Numero de bloques maximo
	size_t m_block_size; // Tamano de cada bloque

public:
	class IndexOutOfRange : public runtime_error{
	public:
		IndexOutOfRange(const size_t index) : runtime_error("Index: out of range"){};
	};

	
	FitArray(void){
		m_block_size = MAX_SIZE;
		m_block_num = MAX_BLOCKS;
		m_data_length = 0;
		m_next_index = 0;
		m_current_block = 0;
		m_data = new Type*[m_block_num];
		m_data[0] = new Type[m_block_size]; // Creamos solo el primer elemento para ahorrar memoria
	}

	FitArray(size_t max_size){
		m_block_size = max_size;
		m_block_num = MAX_BLOCKS;
		m_data_length = 0;
		m_next_index = 0;
		m_current_block = 0;
		m_data = new Type*[m_block_num];
		m_data[0] = new Type[m_block_size]; // Creamos solo el primer elemento para ahorrar memoria
	}

	FitArray(size_t max_size, size_t max_blocks){
		m_block_size = max_size;
		m_block_num = max_blocks;
		m_data_length = 0;
		m_next_index = 0;
		m_current_block = 0;
		m_data = new Type*[m_block_num];
		m_data[0] = new Type[m_block_size]; // Creamos solo el primer elemento para ahorrar memoria
	}

	~FitArray(void){
		for (size_t i = 0; i < m_current_block+1; i++){
			delete[] m_data[i];
		}
		delete[] m_data;
	}

	void push_back(Type& elem){
		m_data[m_current_block][m_next_index] = elem;
		m_next_index++;
		m_data_length++;

		if(m_next_index >= m_block_size){
			m_next_index=0;
			m_current_block++;
			m_data[m_current_block] = new Type[m_block_size];
		}
	}

	size_t size(){
		return m_data_length;
	}

	Type& at(const size_t index){
		if(index>=m_data_length){
			throw IndexOutOfRange(index);
		}
		size_t block_index = (size_t)(index / m_block_size);
		size_t data_index = (size_t)(index % m_block_size);
		return m_data[block_index][data_index];
	}

	Type& operator[] (const size_t index){
		return FitArray::at(index);
	}

	 FixedArray<Type>* getData(){ // Devuelve un Array con longitud fija
		FixedArray<Type>* datap = new FixedArray<Type>(m_data_length);
		size_t new_index=0;
		for (size_t block = 0; block < m_current_block; block++){
			for (size_t data_index = 0; data_index < m_block_size; data_index++){
				Type d = m_data[block][data_index];
				datap->at(new_index) = d;
				new_index++;
			}
		}
		for (size_t data_index=0; data_index < m_next_index; data_index++){
			Type d = m_data[m_current_block][data_index];
			datap->at(new_index) = d;
			new_index++;
		}
		return datap;
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