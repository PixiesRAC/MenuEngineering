/* Icustomer.hpp  */

#ifndef ICUSTOMER_HPP_
# define ICUSTOMER_HPP_

/*
 * \class Icustomer
 * \brief Class correspondant à l'interface du simulateur du client qui va passer la commande
 *
 */

class	Icustomer
{
public :

  
	virtual ~Icustomer() {};
  
  /*
   * \fn ConnectTo
   * \brief Methode pure pour se connecter au server
   * \return bool
   */

	virtual bool ConnectTo() = 0;


  /*
   * \fn Buy
   * \brief Methode pure pour acheter au server
   */
  
	virtual void Buy() = 0;
};

#endif /* !ICUSTOMER_HPP_ */
