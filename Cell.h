#pragma once

class Cell {
private:
	Cell *m_Prev = nullptr, *m_Next = nullptr;
	unsigned char m_Value = 0;

	const bool printAscii = false;
	static Cell* m_First;
public:
	Cell();

	void increment();
	void decrement();

	Cell* prev();
	Cell* next();

	void print();

	unsigned char getValue();
	void setValue(unsigned char value);

	static void dprint();
	static void cleanup();
};
