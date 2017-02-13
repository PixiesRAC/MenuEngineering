#include <iostream>

#include "../include/Customer.hpp"

int	main(int argc, char **argv)
{
	Customer cstmr;
	
	if (cstmr.ConnectTo() == false){
		perror("Error de code : ");
		return (1);
	}
	else {
		std::cout << "Tout est ok" << std::endl;
	}
}
	return (0);	
}
