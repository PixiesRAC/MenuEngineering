/* Icustomer.hpp  */

#ifndef ICUSTOMER_HPP_
# define ICUSTOMER_HPP_

class	Icustomer
{
public :

	virtual ~Icustomer() {};

	virtual bool ConnectTo() = 0;
	
	virtual void Buy() = 0;
};

#endif /* !ICUSTOMER_HPP_ */
