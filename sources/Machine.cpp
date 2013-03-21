#include "Machine.h"

using namespace std;

Machine::Machine(const string& name) : Material(name)
{

}

Machine::~Machine()
{
    //dtor
}

void Machine::setName(const string& name)
{
    this->name = name;
}

string Machine::getName()
{
    return this->name;
}
