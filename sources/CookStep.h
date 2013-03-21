#ifndef COOKSTEP_H
#define COOKSTEP_H

#include "Ingredient.h"
#include "Material.h"
#include <iostream>
#include <sstream>
#include <QApplication>


class CookStep
{
    public:
        ~CookStep();
        CookStep(Ingredient *ingredient, Material *material, std::string stepAction, std::string stepTempIngr, int time);
        Ingredient getStepIngredient();
        Material getStepMaterial();
        int getTime();
        std::string getStepAction();
        std::string getStepTempIngr();
        std::string showString();
        std::string buildQuery();

    private:
        Ingredient *stepIngredient;
        Material *stepMaterial;
        int time;
        std::string stepAction;
        std::string stepTempIngr;
};

#endif
