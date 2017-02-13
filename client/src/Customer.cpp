/* Customer.cpp  */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../include/Customer.hpp"

Customer::Customer()
{
	std::cout << "Customer Construction" << std::endl;
	bzero(this->buffer_, SIZE);
}

Customer::~Customer()
{
	std::cout << "Customer Destruction" << std::endl;
}

bool	Customer::ConnectTo()
{

  std::cout << "Connection sur le port :" << this->port_ << std::endl;
  struct sockaddr_in addr;
  
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY; /* local */
  addr.sin_port = htons(this->port_);

  socklen_t	size = sizeof(addr);
  size_t	retSize = 0;
	
  if ((this->fdServer_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (false);
  if ((connect(this->fdServer_, (struct sockaddr *)&addr, sizeof(addr))) != 0)
    return (false);
  if ((retSize = read(this->fdServer_, this->buffer_, SIZE)) > 0)
    {
      std::string tmpHEAVY(this->buffer_);
      while (tmpHEAVY != INIT) {
      }
      std::cout << "Reception de la carte" << std::endl;
      getMenu();
    }
  return (true);	
}

void	Customer::getMenu()
{
  boost::property_tree::ptree root;

  boost::property_tree::read_json(path_vente_item_, root);

  std::vector< std::pair<std::string, std::string> >Item;
  for (boost::property_tree::ptree::value_type &Item : root.get_child("MENU"))
    {
      //      t_item	tmpItem; /* temporaire */
	//      /*tmpItem.id =*/    root.get<int>("MENU." + std::string(Item.first) + ".id");
      /*tmpItem.name = */       std::cout << root.get<std::string>("MENU." + std::string(Item.first) + ".name") + " : " << 
	root.get<int>("MENU." + std::string(Item.first) + ".prix") << "€" << std::endl;
      //      /*tmpItem.marge =*/ root.get<int>("MENU." + std::string(Item.first) + ".marge");
      //      this->menuItem_.push_back(tmpItem);
    }
}

void	Customer::Buy()
{

}

bool	Customer::Automatic()
{

}

bool	Customer::Manual()
{
  char	buffer[SIZE];
  int	ret = 0;
  bzero(buffer, SIZE);
  
  while (1)
    {
      write(1, "=>", 2);
      ret = read(0, buffer, SIZE); /* ecoute l'entrée standart pour la commande */
      write(this->fdServer_, buffer, ret); /* ecrit la commande au server */
      //      ret = read(this->fdServer_, buffer, SIZE); /* recupere le retour du server */
      //      if (strcmp(buffer, ACK))
      //	write(1, "La commande à ete faite", strlen("La commande à ete faite"));
      //      else
      //	write(1, "Erreur commande", strlen("Erreur commande"));
    }
}

void Customer::setPort(int port)
{
  this->port_ = port;
}

/* Customer.cpp  */
