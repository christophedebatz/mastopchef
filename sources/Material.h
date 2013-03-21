#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>


class Material
{
    public:
        Material(const std::string& name);
        Material(const Material& material);
        std::string getName();
        ~Material();

    protected:
        std::string name;
};

#endif
