#include "Recipe.h"

using namespace std;

Recipe::Recipe(string name, int capacity, string difficulty, string picturePath, vector<Ingredient> ingredients, list<CookStep> stepsList)
{
    this->name = name;
    this->capacity = capacity;
    this->difficulty = difficulty;
    this->picturePath = picturePath;
    this->ingredients = ingredients;
    this->stepsList = stepsList;
}

Recipe::~Recipe()
{
    //dtor
}


string Recipe::copyPicture()
{
    QString picName = "";
    if (picturePath != "Veuillez choisir une image") {
        picName = QFileInfo(QString::fromStdString(picturePath)).fileName();
        if (!QFile::copy(QString::fromStdString(picturePath), "res/recipes/pictures/" + picName)) {
            return "impossible";
        }
    } else
        picName = "none";
    return picName.toStdString();
}


int Recipe::getTotalTimeRecipe()
{
    int totalTime = 0;

    list<CookStep>::iterator it;
    for (it = stepsList.begin(); it != stepsList.end(); it++)
        totalTime += (*it).getTime();

    return totalTime;
}


string Recipe::getIngredientsString()
{
    string ingr, sep = "||";

    vector<Ingredient>::iterator it;
    for (it = ingredients.begin(); it < ingredients.end(); ++it){
        if ((it+1) == ingredients.end()) sep = "";
        ingr += (*it).getName() + sep;
    }

    return ingr;
}



string Recipe::getCookStepsString()
{
    string steps;

    list<CookStep>::iterator it;
    for (it = stepsList.begin(); it != stepsList.end(); ++it)
        steps += (*it).showString() + "||";

    return steps;
}


void Recipe::save()
{
    QFile file("res/recipes/" + QString::fromStdString(name) + ".rcp");
    if (!file.open(QFile::WriteOnly)) {
        return;
    }
    QTextStream out(&file);



    out << QString::fromStdString(name) + "**"
        + QString::number(capacity) + "**"
        + QString::number(getTotalTimeRecipe()) + "**"
        + QString::fromStdString(difficulty) + "**"
        + QString::fromStdString(copyPicture()) + "**"
        + QString::fromStdString(getIngredientsString()) + "**"
        + QString::fromStdString(getCookStepsString());

    file.close();
}
