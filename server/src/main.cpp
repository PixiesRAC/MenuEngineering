#include <iostream>

#include "../include/ServerEngMenu.hpp"

#include <signal.h>
#include <exception>

void	MDR(int v)
{
  (void)v;
  throw std::runtime_error("CTRL + C DE LA MORT MDDDR");
}


int	main(int argc, char **argv)
{
  ServerEngmenu srvEngMenu;
  

  signal(SIGINT, MDR);
  
  srvEngMenu.ProcessMargin();
  (void)argc;
  (void)argv;
  if (srvEngMenu.EtablishEndPoint() == false) {
    perror("Error Listen : ");
    return (1);
  }
  return (0);
}
