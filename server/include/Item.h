#ifndef ITEM_H_
# define ITEM_H_

#include <string>

typedef enum	e_type
  {
    VIANDE,
    POISSON,
    FRUIT,
    BIERE,
    OASIS,
    FALAFEL,
    BURGER,
    MOUSSAKA
  }		t_type;

typdef struct	s_item
{
  t_type       	type;
  std::string	name;
  int		price;
  int		marge;
  
}		t_item;

#endif /* ! ITEM_H_ */
