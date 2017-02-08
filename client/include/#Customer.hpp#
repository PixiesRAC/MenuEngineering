#ifndef CUSTOMER_HPP_
# define CUSTOMER_HPP_

#include <vector>
#include "Icustomer.hpp"
#include "../../server/include/Item.hpp"

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

	bool Automatic();

	bool Manual();

private :

	std::vector<t_item> menuItem_;
};

#endif /* !CUSTOMER_HPP_  */
