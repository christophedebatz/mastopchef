#include "CookStep.h"

using namespace std;


CookStep::CookStep(Ingredient *ingredient, Material *material, string stepAction, string stepTempIngr, int time)
{
    stepIngredient = new Ingredient(*ingredient);
    stepMaterial = new Material(*material);
    this->stepAction = stepAction;
    this->stepTempIngr = stepTempIngr;
    this->time = time;
}


string CookStep::showString()
{
    string whichGives = "";
    if (stepTempIngr != "")
        whichGives = " qui donne " + stepTempIngr;

    return "[" + QString::number(time).toStdString() + " mn] " + stepAction + " " + stepIngredient->getName() + " avec " + stepMaterial->getName() + whichGives;
}


string CookStep::buildQuery()
{
    string whichGives = "";
    if (stepTempIngr != "")
        whichGives = stepTempIngr;

    return QString::number(time).toStdString() + "//" + stepAction + "//" + stepIngredient->getName() + "//" + stepMaterial->getName() + "//" + whichGives;
}


Ingredient CookStep::getStepIngredient()
{
    return *stepIngredient;
}

Material CookStep::getStepMaterial()
{
    return *stepMaterial;
}

/*bool CookStep::isEqual(const CookStep& cs)
{
    return (cs.showString() == this->showString());
}*/


string CookStep::getStepAction()
{
    return this->stepAction;
}

string CookStep::getStepTempIngr()
{
    return this->stepTempIngr;
}

CookStep::~CookStep()
{
    delete stepIngredient;
    delete stepMaterial;
}

int CookStep::getTime()
{
    return this->time;
}


