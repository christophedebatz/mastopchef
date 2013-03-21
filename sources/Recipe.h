#ifndef RECIPE_H
#define RECIPE_H

#include "Recipe.h"
#include "Ingredient.h"
#include "CookStep.h"
#include <list>
#include <vector>
#include <QApplication>
#include <QtGui>


class Recipe
{
    public:
        Recipe(std::string name, int capacity, std::string difficulty, std::string picturePath, std::vector<Ingredient> ingredients, std::list<CookStep> stepsList);
        ~Recipe();
        std::string copyPicture();
        int getTotalTimeRecipe();
        std::string getIngredientsString();
        std::string getCookStepsString();
        void save();

    private:
        std::list<CookStep> stepsList;
        std::string name;
        std::vector<Ingredient> ingredients;
        std::string picturePath;
        std::string difficulty;
        int capacity;
};

#endif
