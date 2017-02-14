#ifndef SERVERENGMENU_HPP_
# define SERVERENGMENU_HPP_

#include <string>
#include "IserverEngMenu.hpp"
#include "Item.h"

#include <vector>

# define SIZE_BUFF	256
# define INIT		"INIT"
# define ACK		"ACK"
# define OK		"OK"
# define KO		"KO"
# define HISTORY	"history"
/*
 * \class ServerEngmenu
 * \brief Class du simulateur du server de restaurant herite de IserverEngMenu 
 *
 */

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
   * \brief Etablis la connexion
   * \return bool
   */
  
  virtual bool EtablishEndPoint()  final override;

    /*
   * \fn KeepCommand  (METHODE final override)
   * \brief read sur le client pour recevoir les commandes
   */

  
  virtual void KeepCommand() final override;
  
    /*
   * \fn ProcessMargin  (METHODE final override)
   * \brief fait la conversion (%) de marge entre le prix d'achat et le prix de vente
   */

  
  virtual void ProcessMargin() final override;

    /*
   * \fn WriteTo  (METHODE final override)
   * \brief ecrit vers le client
   */
  
  virtual void WriteTo() final override;

  /*
   * \fn ProcessEng
   * \brief Algo pour le menu engineering
   */
  
  void		ProcessEng();

  /*
   * \fn checkStock
   * \brief Notification stock
   */
  
  void		checkStock();


  /*
   * \fn getBuffer
   * \brief recupere le buffer de reception
   */
  
  std::string	getBuffer() const;
  
 private :

  int				fdBuy_; /*!< fd fichier de conf pour les produits achetes (avant la marge de profit) */
  int				fdSell_; /*!< fd fichier de conf pour les produits a vendre (apres la marge de profit) */
  int				fdClient_; /*!< fd acheteur (un seul pour le moment) */
  int				fdServer_; /*!< fd acheteur (un seul pour le moment) */
  char				buffer_[SIZE_BUFF]; /*!< buffer reception client */
  static constexpr const int	pg_port_ = 4244; /*!< private global port */
  static constexpr const char   *path_achat_item_ = "../../conf/PRODUITS_ACHAT.json"; /*!< Chemin du menu d'achat */
  static constexpr const char   *path_vente_item_ = "../../conf/PRODUITS_VENTE.json"; /*!< Chemin du menu de vente */
  std::vector<t_item>		menuItem_; /*!< vector d'item contenant les produits du menu */
  std::vector<t_item>		itemBought_; /*< vector d'item contenant les produits achetés */
  bool				isReady_; /*< Permet de savoir si le server est pret */
  
};

#endif /* !SERVERENGMENU_HPP_ */
