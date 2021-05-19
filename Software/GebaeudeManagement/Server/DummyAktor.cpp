#include "DummyAktor.h"

DummyAktor::DummyAktor(enumAktorTypes type)
{
    this->aktor_type = type;
}

DummyAktor::~DummyAktor()
{
}

unsigned int DummyAktor::get_aktor_type()
{
    return this->aktor_type;
}

bool DummyAktor::set_aktor_value(float wert)
{
    this->aktor_value = wert;
    return true;
}
