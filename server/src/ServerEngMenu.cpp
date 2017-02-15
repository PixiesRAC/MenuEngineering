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

extern bool global_MOCHE;

ServerEngmenu::ServerEngmenu() : isReady_(false), bought_(0), medianMargin_(0), cptItem_(0)
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
  
  bzero(&addrServer, sizeof(addrServer));
  bzero(&addrClient, sizeof(addrClient));

  addrServer.sin_family = AF_INET;
  addrServer.sin_port = htons(pg_port_);

  socklen_t		lens = sizeof(addrServer);
  if (bind(this->fdServer_, (struct sockaddr *) &addrServer, socklen_t(sizeof(addrServer))) != 0)
    return (false);
  if ((listen(this->fdServer_, 10)) != 0)
    return (false);
  while (1) {
    if ((this->fdClient_ = accept(this->fdServer_, (struct sockaddr *)&addrClient, &lens)) == -1)
      return (false);
    std::cout << "Connection entrante" << std::endl;
    while (this->isReady_ != true)
      {
	this->ProcessMargin();
      }
    write(this->fdClient_, INIT, strlen(INIT));
    this->KeepCommand();
  }
  return (true);
}

void ServerEngmenu::KeepCommand()
{
  int	tmpSize = 0;
  bool	rightCmd = false;
  
  while (1) {
    rightCmd = false;
    bzero(this->buffer_, SIZE_BUFF);
    if ((tmpSize = read(this->fdClient_, this->buffer_, SIZE_BUFF)) > 0) {
      buffer_[tmpSize] = '\0';
      std::string tmpBuff(this->buffer_);
      std::cout << "Recu : " << tmpBuff << " => ";
      tmpBuff.erase(std::remove(tmpBuff.begin(), tmpBuff.end(), '\n'), tmpBuff.end());
      for (auto &menu :  this->menuItem_)
	{
	  if (tmpBuff == menu.name)
	    {
	      std::cout << OK << std::endl;
	      ++(this->bought_);
	      write(this->fdClient_, ACK, 3);
	      rightCmd = true;
	      menu.bought++;
	      this->itemBought_.push_back(menu);
	      break;
	    }
	  else if (tmpBuff == MENU)
	    {
	      if (this->itemBought_.size() > 0)
		{
		  this->ProcessEng();
		  write(this->fdClient_, ACK, 3);
		  rightCmd = true;
		}
	      break;
	    }
	  bzero(this->buffer_, SIZE_BUFF);
	}
      if (rightCmd == false)
	{
	  write(this->fdClient_, KO, 2);
	}
    }
    else
      break;
  }
  std::cout << "Connection perdu" << std::endl;
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
  
  int	medianMarginTmp = 0;
  
  for (boost::property_tree::ptree::value_type &Item : root.get_child("MENU"))
    {
      t_item	tmpItem; /* temporaire */
      
      tmpItem.id = root.get<int>("MENU." + std::string(Item.first) + ".id");
      tmpItem.name = root.get<std::string>("MENU." + std::string(Item.first) + ".name");
      tmpItem.price = root.get<unsigned int>("MENU." + std::string(Item.first) + ".prix");
      tmpItem.marge = root.get<unsigned int>("MENU." + std::string(Item.first) + ".marge");
      tmpItem.bought = 0;
      if ((((tmpItem.price * tmpItem.marge) / 100) + tmpItem.price) + 1 <= UINT_MAX) {
	
	unsigned int	tmpResult = ((tmpItem.price * tmpItem.marge) / 100) + tmpItem.price;
	if (tmpResult == tmpItem.price)
	  ++tmpResult;
	
	root.put("MENU." + std::string(Item.first) + ".prix", tmpResult);
	++this->cptItem_; /* Nombre d'item total */
	medianMarginTmp += tmpItem.marge; /* additionne la marge des produits */
	//	std::cout << "marge : " << tmpItem.marge << std::endl;
      }
      
      this->menuItem_.push_back(tmpItem);
    }
  boost::property_tree::write_json(path_vente_item_, root);
  this->isReady_ = true;
  if (this->cptItem_ > 0)
    this->medianMargin_ = medianMarginTmp / this->cptItem_; /* calcul la marge */
}

void	 ServerEngmenu::WriteTo()
{
  /* useless */
}

void	ServerEngmenu::ProcessEng()
{
  unsigned int	medianPrcQty = 0;
  unsigned int	medianPrcQtyT = 0;
  
  system("clear");
  std::cout << "margin : " << this->medianMargin_ << std::endl;
  std::cout << "bought : " << this->bought_ << std::endl;
  for (auto &item : this->menuItem_)
    {
      medianPrcQtyT += ((item.bought * 100) / this->bought_);
      item.bought = ((item.bought * 100) / this->bought_); /* pourcentage */
      std::cout << item.name << ":" << item.bought << std::endl;
    }
  medianPrcQty = medianPrcQtyT  / this->cptItem_;
  std::cout << "Voici la moyenne de pourcentage" << medianPrcQty << std::endl;
  for (auto &item : this->menuItem_)
    {
      std::cout << item.name << " : marge " << item.marge << " : qty " << item.bought << "  my :" << (medianPrcQty / 2) << std::endl;
      if (item.marge < this->medianMargin_ && item.bought <= (medianPrcQty))
	this->dog_.push_back(item); /* push un produit avec une marge faible  & peu de notoriete */
      else if (item.marge < this->medianMargin_ && item.bought > (medianPrcQty ))
	this->horse_.push_back(item); /* push un produit avec une marge faible & bcp de notoriete */
      else if (item.marge > this->medianMargin_ && item.bought <= (medianPrcQty ))
	this->puzzle_.push_back(item); /* push un produit avec une marge haute & peu de notoriete */
      else if (item.marge > this->medianMargin_ && item.bought > (medianPrcQty ))
	this->star_.push_back(item); /* push un produit avec une marge haute & bcp de notoriete */
    }
  // DOG
  std::cout << "@@@@@ DOG @@@@@" << std::endl;
  std::cout << "Les produits ci-dessous on une marge faible et une notorieté faible" << std::endl;
  for (auto &item : this->dog_)
    {
      std::cout << item.name << std::endl;
    }
  // HORSE
  std::cout << "@@@@@ HORSE @@@@@" << std::endl;
  std::cout << "Les produits ci-dessous on une marge faible et une notorieté haute" << std::endl;
  for (auto &item : this->horse_)
    {
      std::cout << item.name << std::endl;
    }
  // STAR
  std::cout << "@@@@@ STAR @@@@@" << std::endl;
    std::cout << "Les produits ci-dessous on une marge haute et une notorieté haute" << std::endl;
  for (auto &item : this->star_)
    {
      std::cout << item.name << std::endl;
    }
  // PUZZLE
  std::cout << "@@@@@ PUZZLE @@@@@" << std::endl;
  std::cout << "Les produits ci-dessous on une marge haute et une notorieté faible" << std::endl;
  for (auto &item : this->puzzle_)
    {
      std::cout << item.name << std::endl;
    }
}

void	ServerEngmenu::displayHistory()
{
  //  std::string tmp;
  //  for (auto &item : this->itemBought_)
  //    {
  //      std::cout << item.name << std::endl;
  //      tmp += item.name;
  //      tmp += ",";
  //    }
}

void	ServerEngmenu::checkStock()
{
  
}
