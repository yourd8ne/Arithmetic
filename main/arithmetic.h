#pragma once
#include <iostream>
#include "stack.h"
const int tmp = 200;

using namespace std;

class Arithm
{
	char* exp;
	int size;
	Stack stack;
	stackch stackch;

	int Priority(int n);

public:
	Arithm(char* c);
	Arithm(const Arithm& a);
	~Arithm();
	Arithm& operator=(const Arithm& op);
	int* CheckExp(int& errors, int& LenStrBr);
	char* Postfix();
	double* Calculate(char* postf);
	double* StrToNum(int n, char* postf);
	friend ostream& operator<<(ostream& os, const Arithm& op);
};

Arithm::Arithm(char* c)
{
	size = strlen(c);
	exp = new char[size];
	stack.Resize(size);
	stackch.Resize(size);
	for (int i = 0; i < size; i++)
		exp[i] = c[i];
}

Arithm::Arithm(const Arithm& a)
{
	size = a.size;
	exp = new char[size];
	stack.Resize(size);
	stackch.Resize(size);
	for (int i = 0; i < size; i++)
		exp[i] = a.exp[i];
}

Arithm::~Arithm()
{
	if (exp != NULL)
		delete[] exp;
}

Arithm& Arithm::operator=(const Arithm& op)
{
	if (this != &op)
	{
		if (size != op.size)
		{
			delete[] exp;
			size = op.size;
			exp = new char[size];
		}
		for (int i = 0; i < size; i++)
			exp[i] = op.exp[i];
	}
	return *this;
}

int* Arithm::CheckExp(int& errors, int& LenStrBr)
{
	errors = 0;
	int n = 1, m = 0, count = 0;
	int* brackets = new int[2 * size];
	for (int i = 0; i < size; i++)
	{
		if (exp[i] == '(')
		{
			stack.Add(n);
			n++;
		}
		else if (exp[i] == ')')
		{
			if (!stack.Check_empty())
			{
				m = stack.Del();
				brackets[count] = m;
				count++;
				brackets[count] = n;
				count++;
				n++;
				LenStrBr += 2;
			}
			else
			{
				brackets[count] = 0;
				count++;
				brackets[count] = n;
				count++;
				n++;
				errors++;
				LenStrBr += 2;
			}
		}
	}
	while (!stack.Check_empty())
	{
		n = stack.Del();
		brackets[count] = n;
		count++;
		brackets[count] = 0;
		count++;
		errors++;
		LenStrBr += 2;
	}
	return brackets;
}

int Arithm::Priority(int i)
{
	
	int p = -1;
	if (exp[i] == '(')
		p = 0;
	else if (exp[i] == ')')
		p = 1;
	else if (exp[i] == '+' || exp[i] == '-')
		p = 2;
	else if (exp[i] == '*' || exp[i] == '/')
		p = 3;
	return p;
}

char* Arithm::Postfix()
{
	int pr = -1, count = 0, el = 0, countD = 0;
	char* postf = new char[2 * size];
	for (int i = 0; i < size; i++)
	{
		if ((exp[i] == '-' && i == 0) || (exp[i] == '-' && exp[i - 1] == '(' && i != 0))
		{
			postf[count] = exp[i];
			count++;
			postf[count] = ' ';
			count++;
			continue;
		}
		pr = Priority(i);
		if (pr == -1)
		{
			postf[count] = exp[i];
			count++;
			if (i != size - 1)
			{
				if (!(isdigit(exp[i + 1])) && exp[i + 1] != '.')
				{
					postf[count] = ' ';
					count++;
				}
			}
			else if (i == size - 1)
			{
				postf[count] = ' ';
				count++;
			}
		}
		else if (stack.GetTopIndex() == 0 && pr != 0)
		{
			stack.Add(pr);
			stackch.Add(exp[i]);
			countD++;
		}
		else if (pr == 0 || pr > stack.GetTop())
		{
			if (pr > stack.GetTop() && pr != 0 && pr != 1)
			{
				stack.Add(pr);
				stackch.Add(exp[i]);
				if (pr != 1)
					countD++;
			}
			else if (stack.GetTop() == 0 && pr == 1)
			{
				stack.Del();
				stackch.Del();
			}
			else if (pr == 0)
			{
				stack.Add(pr);
				stackch.Add(exp[i]);
			}
		}
		else if (pr != 0 && pr <= stack.GetTop())
		{
			do
			{
				if (stack.GetTop() == 2 || stack.GetTop() == 3)
				{
					stack.Del();
					postf[count] = stackch.Del();
					count++;
					countD--;
				}
				if (pr == 1 && stack.GetTop() == 0)
				{
					stack.Del();
					stackch.Del();
					break;
				}
			} while (pr <= stack.GetTop());
			if (pr != 1 && pr != 0)
			{
				stack.Add(pr);
				stackch.Add(exp[i]);
				countD++;
			}
		}
		/*else if (pr != 0 && pr < stack.GetTop())
		{
			do
			{
				if (stack.GetTop() == 2)
				{
					stack.Del();
					postf[count] = '+';
					count++;
					countD--;
				}
				else if (stack.GetTop() == 3)
				{
					stack.Del();
					postf[count] = '-';
					count++;
					countD--;
				}
				else if (stack.GetTop() == 4)
				{
					stack.Del();
					postf[count] = '*';
					count++;
					countD--;
				}
				else if (stack.GetTop() == 5)
				{
					stack.Del();
					postf[count] = '/';
					count++;
					countD--;
				}
				else if (stack.GetTop() == 0 || stack.GetTop() == 1)
					stack.Del();
				if (pr == 1 && stack.GetTop() == 0)
				{
					stack.Del();
					break;
				}
			} while (pr < stack.GetTop());
			if (pr != 1 && pr != 0)
			{
				stack.Add(pr);
				countD++;
			}
		}*/
	}
	do
	{
		if (stack.GetTop() == 2 || stack.GetTop() == 3)
		{
			stack.Del();
			postf[count] = stackch.Del();
			count++;
			countD--;
		}
		else
		{
			stack.Del();
			stackch.Del();
		}
	} while (countD > 0);
	/*do
	{
		if (stack.GetTop() == 2)
		{
			stack.Del();
			postf[count] = '+';
			count++;
			countD--;
		}
		else if (stack.GetTop() == 3)
		{
			stack.Del();
			postf[count] = '-';
			count++;
			countD--;
		}
		else if (stack.GetTop() == 4)
		{
			stack.Del();
			postf[count] = '*';
			count++;
			countD--;
		}
		else if (stack.GetTop() == 5)
		{
			stack.Del();
			postf[count] = '/';
			count++;
			countD--;
		}
		else
			stack.Del();
	} while (countD > 0);*/
	postf[count] = '\0';
	return postf;
}

double* Arithm::StrToNum(int n, char* postf)
{
	int m = -1, i = n, j = 0;
	double c = 0, * res;
	bool flag;
	res = new double[2];
	do
	{
		flag = false;
		if (isdigit(postf[i]))
			c = c * 10 + postf[i] - 48;
		else if (postf[i] == '.' && isdigit(postf[i + 1]) && i != 0 && i != strlen(postf) - 1)
			for (j = i + 1; j < size; j++)
			{
				if (isdigit(postf[j]))
				{
					c = c + pow(10, m) * (postf[j] - 48);
					m--;
				}
				else
					break;
				flag = true;
			}
		else if (!isdigit(postf[i]))
			break;
		if (flag == true)
			i = j;
		else
			i++;
	} while (postf[i] != '\0');
	res[0] = c;
	res[1] = i;
	return res;
}

double* Arithm::Calculate(char* postf)
{
	int err = 0, flag, i = 0;
	double op1, op2, res = 0, * result, * tmp;
	result = new double[2];
	stack.Resize(strlen(postf));
	tmp = new double[2];
	do
	{
		if (isdigit(postf[i]))
		{
			/*char* tmp = new char[1];
			tmp[0] = postf[i];
			stack.Add(atoi(tmp));*/
			tmp = StrToNum(i, postf);
			stack.Add(tmp[0]);
			i = tmp[1] + 1;
		}
		else if (postf[i] == '-' && postf[i + 1] == ' ')
		{
			tmp = StrToNum(i + 2, postf);
			stack.Add(-tmp[0]);
			i = tmp[1] + 1;
		}
		else if (isalpha(postf[i]))
		{
			err = -1;
			break;
		}
		else if (!isdigit(postf[i]) && postf[i] != ' ')
		{
			if (!stack.Check_empty())
			{
				op2 = stack.Del();
			}
			else
			{
				cout << "Стек пуст, невозможно извлечь операнд 2\n";
				err++;
			}
			if (!stack.Check_empty())
			{
				op1 = stack.Del();
				if (postf[i] == '+')
					res = op1 + op2;
				else if (postf[i] == '-')
					res = op1 - op2;
				else if (postf[i] == '*')
					res = op1 * op2;
				else if (postf[i] == '/')
				{
					if (op2 != 0)
						res = op1 / op2;
					else
					{
						cout << "Деление на ноль невозможно\n";
						err++;
					}
				}
				stack.Add(res);
				res = 0;
			}
			else
			{
				cout << "Стек пуст, невозможно извлечь операнд 1\n";
				err++;
			}
			i++;
		}
		//i++;
	} while (postf[i] != '\0');
	if (!stack.Check_empty())
		result[0] = stack.Del();
	else
		result[0] = res;
	result[1] = err;
	return result;
}

ostream& operator<<(ostream& os, const Arithm& ex)
{
	for (int i = 0; i < ex.size; i++)
		os << ex.exp[i];
	return os;
}