#pragma once
#include <iostream>

class Stack {

private:
	double* st_arr;
	int size;
	int top;

public:
	Stack()
	{
		size = 1;
		st_arr = new double[size];
		top = 0;
	}
	Stack(int n)
	{
		size = n;
		st_arr = new double[size];
		top = 0;
	}
	Stack(const Stack& st)
	{
		if (st_arr != NULL)
			delete[] st_arr;
		size = st.size;
		st_arr = new double[size];
		top = st.top;
		for (int i = 0; i < top; i++)
			st_arr[i] = st.st_arr[i];
	}

	~Stack()
	{
		size = 0;
		top = 0;
		delete[] st_arr;
	}

	void Add(double n)
	{
		st_arr[top] = n;
		top++;
	}

	int GetSize()
	{
		return size;
	}

	double GetTop()
	{
		return st_arr[top - 1];
	}

	int GetTopIndex()
	{
		return top;
	}

	double Del()
	{
		top--;
		return st_arr[top];
	}

	bool Check_empty()
	{
		return top == 0;
	}

	bool Check_full()
	{
		return top == size;
	}

	void Resize(int n)
	{
		if (st_arr != NULL)
			delete[] st_arr;
		size = n;
		st_arr = new double[size];
		top = 0;
	}
};

class stackch
{
private:
	char* st_arr;
	int size;
	int top;
public:
	stackch()
	{
		size = 1;
		st_arr = new char[size];
		top = 0;
	}
	stackch(int n)
	{
		size = n;
		st_arr = new char[size];
		top = 0;
	}
	stackch(const stackch& st)
	{
		if (st_arr != nullptr)
			delete[] st_arr;
		size = st.size;
		st_arr = new char[size];
		top = st.top;
		for (int i = 0; i < top; i++)
			st_arr[i] = st.st_arr[i];
	}
	~stackch()
	{
		size = 0;
		top = 0;
		delete[] st_arr;
	}
	void Add(char n)
	{
		st_arr[top] = n;
		top++;
	}
	char Del()
	{
		top--;
		return st_arr[top];
	}
	bool Check_empty()
	{
		return top == 0;
	}
	bool Check_full()
	{
		return top == size;
	}
	void Resize(int n)
	{
		if (st_arr != nullptr)
			delete[] st_arr;
		size = n;
		st_arr = new char[size];
		top = 0;
	}
};