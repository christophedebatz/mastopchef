#include "Ingredient.h"

using namespace std;

Ingredient::Ingredient(const string& name)
{
    this->name = name;
}

Ingredient::Ingredient(const string& name, const string& unit, double quantity)
{
    this->name = name;
    this->unit = unit;
    this->quantity = quantity;
}

Ingredient::Ingredient(const Ingredient& ingredient)
{
    this->name = ingredient.name;
    this->unit = ingredient.unit;
    this->quantity = ingredient.quantity;
}

Ingredient::~Ingredient(){}


void Ingredient::setName(const string& name)
{
    this->name = name;
}

void Ingredient::setUnit(const string& unit)
{
    this->unit = unit;
}

void Ingredient::setQuantity(double quantity)
{
    this->quantity = quantity;
}


double Ingredient::getQuantity()
{
    return this->quantity;
}


string Ingredient::getName()
{
    return this->name;
}


string Ingredient::getUnit()
{
    return this->unit;
}


