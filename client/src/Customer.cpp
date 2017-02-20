/* Customer.cpp  */

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../include/Customer.hpp"

Customer::Customer() : nbItem_(0)
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
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(this->port_);

  //  socklen_t	size = sizeof(addr);
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
      std::cout << RECEPTION << std::endl;
      getMenu();
    }
  return (true);
}

void	Customer::getMenu()
{
  this->nbItem_ = 0;
  boost::property_tree::ptree root;

  boost::property_tree::read_json(path_vente_item_, root);

  std::vector< std::pair<std::string, std::string> >Item;
  for (boost::property_tree::ptree::value_type &Item : root.get_child("MENU"))
    {
      t_item	tmpItem; /* temporaire */
      //      /*tmpItem.id =*/    root.get<int>("MENU." + std::string(Item.first) + ".id");
      tmpItem.name = root.get<std::string>("MENU." + std::string(Item.first) + ".name");
      std::cout << tmpItem.name << " : " << 
      root.get<int>("MENU." + std::string(Item.first) + ".prix") << "€" << std::endl;
      this->mItemId_.insert( {this->nbItem_, tmpItem.name} );
      ++(this->nbItem_);
      //      /*tmpItem.marge =*/ root.get<int>("MENU." + std::string(Item.first) + ".marge");
      //      this->menuItem_.push_back(tmpItem);
    }
}

void	Customer::Buy()
{

}

bool	Customer::Automatic()
{
  std::cout << this->nbItem_;
  char	buffer[SIZE];
  int	ret = 0;
  for (int i = 2000; i != 0; --i) /* nombre d'achat automatique ramdom */
    {
      int randomValue;
      randomValue = rand() % this->nbItem_ ;
      write(this->fdServer_, this->mItemId_[randomValue].c_str(), this->mItemId_[randomValue].size());
      bzero(buffer, SIZE);
      ret = read(this->fdServer_, buffer, SIZE); /* recupere le retour du server */
      buffer[ret] = '\0';
      std::cout << "Recu : " << buffer << std::endl;
      bzero(buffer, SIZE);
      usleep(1000); /* It's bad je sais */
    }
  return (true);
}

bool	Customer::Manual()
{
  char	buffer[SIZE];
  int	ret = 0;
  bzero(buffer, SIZE);
  
  while (1) /* Le code est moche je sais */
    {
      write(1, DISPLAY_CARTE, strlen(DISPLAY_CARTE));
      write(1, START_ENG, strlen(START_ENG));
      write(1, CURSOR, 2);
      bzero(buffer, SIZE);
      ret = read(0, buffer, SIZE); /* ecoute l'entrée standart pour la commande */
      std::string tmp(buffer);
      if (tmp == "carte\n")
	{
	  this->getMenu();
	}
      else {
	write(this->fdServer_, buffer, ret); /* ecrit la commande au server */
	bzero(buffer, SIZE);
	ret = read(this->fdServer_, buffer, SIZE); /* recupere le retour du server */
	buffer[ret] = '\0';
	std::cout << "Recu : " << buffer << std::endl;
	bzero(buffer, SIZE);
      }
    }
  return (true);
}

void Customer::setPort(int port)
{
  this->port_ = port;
}

/* Customer.cpp  */
