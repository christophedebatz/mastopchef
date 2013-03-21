#ifndef PINGREDIENT_H
#define PINGREDIENT_H

#include "Ingredient.h"
#include <string>

class PerishableIngredient : public Ingredient
{
    public:
        PerishableIngredient(const std::string& name, const std::string& unit, double quantity);
        PerishableIngredient(const std::string& name);
        ~PerishableIngredient();
};

#endif
