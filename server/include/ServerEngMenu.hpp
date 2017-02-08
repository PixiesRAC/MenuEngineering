#ifndef SERVERENGMENU_HPP_
# define SERVERENGMENU_HPP_

#include <string>
#include "IserverEngMenu.hpp"
#include "Item.h"

#include <vector>

# define SIZE_BUFF 256

class	ServerEngmenu : public IserverEngMenu
{

public :
  
  ServerEngmenu();
  
  ServerEngmenu(const ServerEngmenu &) = delete;
  ServerEngmenu(ServerEngmenu &&) = delete;
  const ServerEngmenu & operator=(const ServerEngmenu &) = delete;
  ServerEngmenu && operator=(ServerEngmenu &&) = delete;
    
  virtual ~ServerEngmenu();

    /*
   * \fn EtablishEndPoint (METHODE final override)
   * \def Etablis la connexion
   * \return bool
   */
  
  virtual bool EtablishEndPoint()  final override;

    /*
   * \fn KeepCommand  (METHODE final override)
   * \def read sur le client pour recevoir les commandes
   */

  
  virtual void KeepCommand() final override;
  
    /*
   * \fn ProcessMargin  (METHODE final override)
   * \def fait la conversion (%) de marge entre le prix d'achat et le prix de vente
   */

  
  virtual void ProcessMargin() final override;

    /*
   * \fn WriteTo  (METHODE final override)
   * \def ecrit vers le client
   */
  
  virtual void WriteTo() final override;

  /*
   * \fn ProcessEng
   * \def Algo pour le menu engineering
   */
  
  void		ProcessEng();

  /*
   * \fn checkStock
   * \def Notification stock
   */
  
  void		checkStock();

  std::string	getBuffer() const;
  
 private :

  int				fdBuy_; /*!< fd fichier de conf pour les produits achetes (avant la marge de profit) */
  int				fdSell_; /*!< fd fichier de conf pour les produits a vendre (apres la marge de profit) */
  int				fdClient_; /*!< fd acheteur (un seul pour le moment) */
  int				fdServer_; /*!< fd acheteur (un seul pour le moment) */
  char				buffer_[SIZE_BUFF]; /*!< buffer reception client */
  static constexpr const int	pg_port_ = 4243; /*!< private global port */
  static constexpr const char   *path_client_item_ = "../../conf/PRODUITS_ACHAT.json";
  std::vector<t_item>		menuItem_;
};

#endif /* !SERVERENGMENU_HPP_ */
