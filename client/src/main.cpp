#include <iostream>

#include "../include/Customer.hpp"

int	main(int argc, char **argv)
{
  Customer cstmr;
  
  if (argc >= 2) {
    cstmr.setPort(atoi(argv[1]));
    if (cstmr.ConnectTo() == false){
      perror("Error de code : ");
      return (1);
    }
    cstmr.Manual();
  }
  return (0);	
}
