#include "Material.h"

using namespace std;


Material::Material(const string& name)
{
    this->name = name;
}

Material::Material(const Material& material)
{
    this->name = material.name;
}

string Material::getName()
{
    return this->name;
}

Material::~Material()
{
    //dtor
}
