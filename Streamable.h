//################################
// Seneca Library Application  ###
//################################

#ifndef SDDS_STREAMABLE_H_
#define SDDS_STREAMABLE_H_
#include <iostream>
namespace sdds
{
    class Streamable
    {
    public:
        virtual std::ostream &write(std::ostream &ostr) const = 0;
        virtual std::istream &read(std::istream &istr) = 0;
        virtual bool conIO(std::ios &is) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable();
    };
    std::istream &operator>>(std::istream &istr, Streamable &S);
    std::ostream &operator<<(std::ostream &ostr, const Streamable &S);
}
#endif // !SDDS_STREAMABLE_H_