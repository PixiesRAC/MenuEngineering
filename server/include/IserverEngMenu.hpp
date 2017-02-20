#ifndef ISERVERENGMENU_HPP_
# define ISERVERENGMENU_HPP_

/*!
 * \class
 * \brief Interface correspondant au server du menu engineering
 */

class	IserverEngMenu
{
public :

    
  virtual ~IserverEngMenu() {};

  /*!
   * \fn EtablishEndPoint (METHODE final override)
   * \brief Etablis la connexion
   * \return bool
   */
  
  virtual bool EtablishEndPoint() = 0;

  /*!
   * \fn KeepCommand  (METHODE PURE)
   * \brief read sur le client pour recevoir les commandes
   */

  
  virtual void KeepCommand() = 0;

  /*!
   * \fn ProcessMargin  (METHODE PURE)
   * \brief fait la conversion (%) de marge entre le prix d'achat et le prix de vente
   */
  
  virtual void ProcessMargin() = 0;

  /*!
   * \fn WriteTo  (METHODE PURE)
   * \brief ecrit vers le client
   */
  
  virtual void WriteTo() = 0;
  
};

#endif /* !ISERVERENGMENU_HPP_ */
