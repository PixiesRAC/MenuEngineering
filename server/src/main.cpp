#include <iostream>

#include "../include/ServerEngMenu.hpp"

int	main(int argc, char **argv)
{
  ServerEngmenu srvEngMenu;

  if (srvEngMenu.EtablishEndPoint() == false) {
    perror("Error Listen : ");
    return (1);
  }
  else {
    while (1) {
      srvEngMenu.KeepCommand();
      std::cout << srvEngMenu.getBuffer();
    }
   }
  //srvEngMenu.ProcessMargin();
  return (0);
}
