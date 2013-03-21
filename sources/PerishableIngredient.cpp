#include "PerishableIngredient.h"

using namespace std;

PerishableIngredient::PerishableIngredient(const string& name) : Ingredient(name)
{
}

PerishableIngredient::PerishableIngredient(const string& name, const string& unit, double quantity) : Ingredient(name, unit, quantity)
{
}

PerishableIngredient::~PerishableIngredient()
{
}
