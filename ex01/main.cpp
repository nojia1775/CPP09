#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: bad argument\n";
		return 1;
	}
	try
	{
		RPN rpn(argv[1]);
		std::cout << rpn.getResult() << "\n";
	}
	catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
	return 0;
}