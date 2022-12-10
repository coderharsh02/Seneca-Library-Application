//################################
// Seneca Library Application  ###
//################################

#include "Streamable.h"
namespace sdds
{
    Streamable::~Streamable() {}
    std::istream &operator>>(std::istream &istr, Streamable &S)
    {
        S.read(istr);
        return istr;
    }
    std::ostream &operator<<(std::ostream &ostr, const Streamable &S)
    {
        if (S)
        {
            S.write(ostr);
        }
        return ostr;
    }
}