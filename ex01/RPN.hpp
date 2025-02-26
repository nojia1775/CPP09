#ifndef RPN_HPP

# define RPN_HPP

# include <iostream>
# include <stack>
# include <fstream>
# include <string>
# include <cstdlib>

class	RPN
{
	private:
		std::stack<int>		_stack;

	public:
					RPN(void);
					~RPN(void);

					RPN(char *arg);
					RPN(const RPN& other);
		RPN&			operator=(const RPN& other);

		void			compute(char *arg);
		const int&		getResult(void) const { return _stack.top(); }

		class			Error : public std::exception
		{
			private:
				const char	*_error;

			public:
						Error(const char *error) : _error(error) {}
						~Error(void) throw() {}
				const char	*what(void) const throw();
		};
};

#endif