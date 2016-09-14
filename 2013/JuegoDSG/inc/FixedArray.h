#pragma once
#include "../stdafx.h"
#include <string>
#include <exception>
#include <sstream>
#include <vector>

using namespace std;

template <typename Type>
class FixedArray{
private:
	Type* m_data;
	size_t m_size;
public:
	class IndexOutOfRange : public runtime_error{
		public:
			IndexOutOfRange(const size_t index) : runtime_error("Index: out of range"){};
	};

	FixedArray(size_t size){
		m_size = size;
		m_data = new Type[m_size];
	}
	
	~FixedArray(){
		cout << "DELETE FIXEDARRAY" << endl;
		delete[] m_data;
	}

	Type& operator[](const size_t index){
		return FixedArray::at(index);
	}

	Type& at(const size_t index){
		if(index>m_size-1){
			throw IndexOutOfRange(index);
		}
		return m_data[index];
	}

	size_t size(){
		return m_size;
	}
};
