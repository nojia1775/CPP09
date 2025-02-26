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
		if (!isdigit(arg[i]) && arg[i] != ' ' && arg[i] != '+' && arg[i] != '-' && arg[i] != '/' && arg[i] != '*')
		{
			throw Error();
			return;
		}
		if (isdigit(arg[i]))
		{
			tmp = std::atoi(&arg[i]);
			if (tmp > 9)
			{
				throw Error();
				return;
			}
			else
				_stack.push(tmp);
		}
		if ((arg[i] != '+' || arg[i] != '-' || arg[i] != '/' || arg[i] != '*') && _stack.size() < 2)
		{
			throw Error();
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
					_stack.push(a + b);
					break;
				case '-':
					_stack.push(a - b);
					break;
				case '*':
					_stack.push(a * b);
					break;
				case '/':
					if (b == 0)
					{
						throw Error();
						return;
					}
					_stack.push(a / b);
					break;
				default:
					break;
			}
		}
	}
	if (_stack.size() != 1)
	{
		throw Error();
		return;
	}
}

const std::string&	RPN::Error::what(void) const throw() { return std::string("Error: " + _error); }