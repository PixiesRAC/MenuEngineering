#ifndef CUSTOMER_HPP_
# define CUSTOMER_HPP_

#include <vector>
#include "Icustomer.hpp"
//#include "../../server/include/Item.hpp"
#include "../../server/include/Item.h"

# define SIZE			96
# define INIT			"INIT" /* oui je sais on devrait faire un header commun */
# define ACK			"ACK"
# define RECEPTION		"Reception de la carte"
# define DISPLAY_CARTE		"Afficher la carte => 'carte'\n"
# define DISPLAY_HISTORY	"Historique des achats => 'history'\n"
# define CURSOR			"=>"		
/*
 * \class Customer
 * \brief Class correspondant au simulateur du client qui va passer la commande (herite de Icustomer)
 *
 */

class	Customer : public Icustomer
{

public :

  
  Customer();
  
  Customer(const Customer &) = delete;
  Customer(Customer &&) = delete;
  const Customer & operator=(const Customer &) = delete;
  Customer && operator=(Customer &&) = delete;
  
  virtual ~Customer();

    /*
   * \fn ConnectTo
   * \brief Methode pour se connecter au server
   * \return bool
   */
  
  virtual bool ConnectTo() final override;

    /*
   * \fn Buy
   * \brief Methode pure pour acheter au server
   */
  
  virtual void Buy() final override;

  /*
   * \fn setPort
   * \brief set le port en question
   * \param int port
   */
  
  void	setPort(int port);

  /*
   * \fn Automatic
   * \brief Permet de faire des achats automatique
   * \return bool
   */
  
  bool	Automatic();

  /*
   * \fn Manual
   * \brief Permet de faire des achats Manuel
   * \return bool
   */
  
  bool	Manual();

  /*
   * \fn getMenu
   * \brief Lit la carte du menu
   */
  
  void	getMenu();
  
private :


  int			fdServer_; /*!< file descriptor du server */
  int			port_; /*!< port du server */
  char			buffer_[SIZE]; /*!< Buffer de reception */
  static constexpr const char   *path_vente_item_ = "../../conf/PRODUITS_VENTE.json";  /* oui je sais on devrait faire un header commun */ /*!< Chemin de la carte pour le client */
};

#endif /* !CUSTOMER_HPP_  */
