/* Customer.cpp  */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "../include/Customer.hpp"

Customer::Customer()
{
	std::cout << "Customer Construction" << std::endl;
}

Customer::~Customer()
{
	close(this->fdServer_);
	std::cout << "Customer Destruction" << std::endl;
}

bool	Customer::ConnectTo()
{
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port - htons(pg_port_);
	
	if ((this->fdClient_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return (false);
	else
		std::cout << "Connexion établie" << std::endl;
}

void	Customer::Buy()
{

}

bool	Customer::Automatic()
{

}

bool Customer::Manual()
{

}
/* Customer.cpp  */
