#ifndef SERVERENGMENU_HPP_
# define SERVERENGMENU_HPP_

#include "IserverEngMenu.hpp"
class	ServerEngmenu final : public IserverEngMenu
{

public :
  
  ServerEngmenu();
  
  ServerEngmenu(const ServerEngmenu &) = delete;
  ServerEngmenu(ServerEngmenu &&) = delete;
  const ServerEngmenu & operator=(const ServerEngmenu &) = delete;
  ServerEngmenu && operator=(ServerEngmenu &&) = delete;
    
  virtual ~ServerEngmenu();

    /*
   * \fn ListTo (METHODE final override)
   * \def Ecoute les clients
   * \return bool
   */
  
  virtual bool ListenTo()  final override;

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

 private :

  int fdBuy; /*!< fd fichier de conf pour les produits achetes (avant la marge de profit) */
  int fdSell; /*!< fd fichier de conf pour les produits a vendre (apres la marge de profit) */
  int fdClient; /*!< fd acheteur (un seul pour le moment) */
};

#endif /* !SERVERENGMENU_HPP_ */
