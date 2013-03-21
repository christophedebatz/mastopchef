#ifndef MACHINE_H
#define MACHINE_H

#include "Material.h"

class Machine : public Material
{
    public:
        Machine(const std::string& name);
        ~Machine();
        void setName(const std::string& name);
        std::string getName();

};

#endif
