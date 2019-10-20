#include "literal.h"

Literal::Literal(Data *d) : data(d) {}

Data *Literal::getData()
{
    return data;
}
