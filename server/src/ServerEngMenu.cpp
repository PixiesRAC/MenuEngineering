#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include "../include/ServerEngMenu.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <climits>

ServerEngmenu::ServerEngmenu()
{
  std::cout << "ServerEngmenu Construction" << std::endl;
}

ServerEngmenu::~ServerEngmenu()
{
  close(this->fdClient_);
  close(this->fdServer_);
  std::cout << "ServerEngmenu Destruction" << std::endl;
}

bool	 ServerEngmenu::EtablishEndPoint()
{
  if ((this->fdServer_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (false);

  struct sockaddr_in addrServer;
  struct sockaddr_in addrClient;
  socklen_t	     sizeClient;
  
  bzero(&addrServer, sizeof(addrServer));
  bzero(&addrClient, sizeof(addrClient));

  addrServer.sin_family = AF_INET;
  addrServer.sin_addr.s_addr = INADDR_ANY;
  addrServer.sin_port = htons(pg_port_);

  if (bind(this->fdServer_, (struct sockaddr *) &addrServer, socklen_t(sizeof(addrServer))) != 0)
    return (false);
  if ((listen(this->fdServer_, 1)) != 0)
    return (false);
  if ((this->fdClient_ = accept(this->fdServer_, (struct sockaddr *)&addrClient, &sizeClient)) == -1)
    return (false);
  return (true);
}

void ServerEngmenu::KeepCommand()
{
  int	tmpSize = 0;
    if ((tmpSize = read(this->fdClient_, this->buffer_, SIZE_BUFF)) != -1)
      buffer_[tmpSize] = '\0';
}

std::string	ServerEngmenu::getBuffer() const
{
  return (std::string(this->buffer_));
}

void	 ServerEngmenu::ProcessMargin()
{
  boost::property_tree::ptree root;

  boost::property_tree::read_json(path_achat_item_, root);

  std::vector< std::pair<std::string, std::string> >Item;
  for (boost::property_tree::ptree::value_type &Item : root.get_child("MENU"))
    {
      t_item	tmpItem; /* temporaire */
      
      tmpItem.id = root.get<int>("MENU." + std::string(Item.first) + ".id");
      tmpItem.name = root.get<std::string>("MENU." + std::string(Item.first) + ".name");
      tmpItem.price = root.get<int>("MENU." + std::string(Item.first) + ".prix");
      tmpItem.marge = root.get<int>("MENU." + std::string(Item.first) + ".marge");

      if ((((tmpItem.price * tmpItem.marge) / 100) + tmpItem.price) <= ULONG_MAX) {
	
	unsigned int	tmpResult = ((tmpItem.price * tmpItem.marge) / 100) + tmpItem.price;
      
	root.put("MENU." + std::string(Item.first) + ".prix", tmpResult);
    }
      
  this->menuItem_.push_back(tmpItem);
}
  boost::property_tree::write_json(path_vente_item_, root);
  //  for (auto &menu :  this->menuItem_)
  //    {
  //      std::cout << menu.name << std::endl;
  //    }
}

void	 ServerEngmenu::WriteTo()
{
  
}

void	ServerEngmenu::ProcessEng()
{
  
}

void	ServerEngmenu::checkStock()
{
  
}
