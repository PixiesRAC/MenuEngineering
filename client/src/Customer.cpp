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
	close(this->fdClient_);
	close(this->fdServer_);
	std::cout << "Customer Destruction" << std::endl;
}

bool	Customer::ConnectTo()
{
	
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
