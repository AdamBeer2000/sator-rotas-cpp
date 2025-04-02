#include "wordrange.h"
#include <string>

WordRange WordRange::Empty = WordRange(0,0);

int WordRange::getEnd() const
{
    return end;
}

bool WordRange::IsEmpty() const
{
    return is_empty;
}

int WordRange::getBegin() const
{
    return begin;
}
