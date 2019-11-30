#include "Cell.h"
#include <iostream>

Cell* Cell::m_First = nullptr;

Cell::Cell() {
	if(m_First == nullptr)
		m_First = this;
}

void Cell::increment() {
	m_Value++;
}

void Cell::decrement() {
	m_Value--;
}

Cell* Cell::prev() {
	if(m_Prev == nullptr) {
		m_Prev = new Cell();
		m_Prev->m_Next = this;
		m_First = m_Prev;
	}

	return m_Prev;
}

Cell* Cell::next() {
	if(m_Next == nullptr) {
		m_Next = new Cell();
		m_Next->m_Prev = this;
	}

	return m_Next;
}

void Cell::print() {
	if(printAscii)
		std::cout << m_Value << std::endl;
	else
		std::cout << (short)m_Value << std::endl;
}

unsigned char Cell::getValue() {
	return m_Value;
}

void Cell::setValue(unsigned char value) {
	m_Value = value;
}


// Static functions used for printing everything
// and cleaning up the pointers
void Cell::dprint() {
	Cell* temp = m_First;
	
	std::cout << "[" << (short)temp->getValue();
	while((temp = temp->m_Next) != nullptr) {
		std::cout << "," << (short)temp->getValue();
	}
	std::cout << "]" << std::endl;
}

void Cell::cleanup() {
	Cell* temp = m_First;

	while((temp = temp->m_Next) != nullptr) {
		delete temp->m_Prev;
	}

	delete temp;
}
