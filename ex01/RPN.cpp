#include "RPN.hpp"

RPN::RPN(void) {}

RPN::~RPN(void) {}

RPN::RPN(char *arg) { compute(arg); }

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN&	RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

void	RPN::compute(char *arg)
{
	int tmp;
	for (int i = 0 ; arg[i] ; i++)
	{
		if (arg[i] != ' ' && arg[i + 1] && arg[i + 1] != ' ')
		{
			throw Error("wrong character");
			return;
		}
		if (!isdigit(arg[i]) && arg[i] != ' ' && arg[i] != '+' && arg[i] != '-' && arg[i] != '/' && arg[i] != '*')
		{
			throw Error("wrong character");
			return;
		}
		if (isdigit(arg[i]))
		{
			tmp = std::atoi(&arg[i]);
			if (tmp > 9)
			{
				throw Error("numbers have to be lower than 10");
				return;
			}
			_stack.push(tmp);
		}
		if (arg[i] == '+' || arg[i] == '-' || arg[i] == '/' || arg[i] == '*')
		{
			if (_stack.size() < 2)
			{
				throw Error("not enough numbers in the stack");
				return;
			}
			else
			{
				int a = _stack.top();
				_stack.pop();
				int b = _stack.top();
				_stack.pop();
				switch (arg[i])
				{
					case '+':
						_stack.push(b + a);
						break;
					case '-':
						_stack.push(b - a);
						break;
					case '*':
						_stack.push(b * a);
						break;
					case '/':
						if (a == 0)
						{
							throw Error("division by 0 impossible");
							return;
						}
						_stack.push(b / a);
						break;
					default:
						break;
				}
			}
		}
	}
	if (_stack.size() != 1)
	{
		throw Error("there is too much numbers in the stack");
		return;
	}
}

const char	*RPN::Error::what(void) const throw()
{
	return _error;
}