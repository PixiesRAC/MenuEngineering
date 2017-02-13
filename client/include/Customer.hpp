#ifndef CUSTOMER_HPP_
# define CUSTOMER_HPP_

#include <vector>
#include "Icustomer.hpp"
//#include "../../server/include/Item.hpp"
#include "../../server/include/Item.h"

# define SIZE  96
# define INIT  "INIT" /* oui je sais on devrait faire un header commun */
# define ACK   "ACK"

class	Customer : public Icustomer
{

public :
  
  Customer();
  
  Customer(const Customer &) = delete;
  Customer(Customer &&) = delete;
  const Customer & operator=(const Customer &) = delete;
  Customer && operator=(Customer &&) = delete;
  
  virtual ~Customer();
  
  virtual bool ConnectTo() final override;
  
  virtual void Buy() final override;
  
  void	setPort(int port);
  
  bool	Automatic();

  bool	Manual();

  void	getMenu();
private :


  int			fdServer_;
  int			port_;
  ///  std::vector<t_item>	menuItem_;
  char			buffer_[SIZE];
  static constexpr const char   *path_vente_item_ = "../../conf/PRODUITS_VENTE.json";  /* oui je sais on devrait faire un header commun */
};

#endif /* !CUSTOMER_HPP_  */
