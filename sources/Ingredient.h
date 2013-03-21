#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient
{
    public:
        Ingredient(const std::string& name, const std::string& unit, double quantity);
        Ingredient(const std::string& name);
        Ingredient(const Ingredient& ingredient);
        void setName(const std::string& name);
        void setUnit(const std::string& unit);
        void setQuantity(double quantity);
        double getQuantity();
        std::string getName();
        std::string getUnit();
        ~Ingredient();

    protected:
        std::string name;
        std::string unit;
        double quantity;
};

#endif
