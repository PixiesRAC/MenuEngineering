#include <iostream>

#include "../include/ServerEngMenu.hpp"

#include <signal.h>
#include <exception>

void	MDR(int v)
{
  throw std::runtime_error("CTRL + C DE LA MORT MDDDR");
}


int	main(int argc, char **argv)
{
  ServerEngmenu srvEngMenu;
  

  signal(SIGINT, MDR);
  
  srvEngMenu.ProcessMargin();
  if (srvEngMenu.EtablishEndPoint() == false) {
    perror("Error Listen : ");
    return (1);
  }
  return (0);
}
