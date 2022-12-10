//################################
// Seneca Library Application  ###
//################################

#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include "Publication.h"
namespace sdds
{
        class Book : public Publication
        {
                char *m_author;

        public:
                // Constructor
                Book();

                // Rule of three
                Book(const Book &src);
                Book &operator=(const Book &src);
                ~Book();

                // Methods
                char type() const;
                std::ostream &write(std::ostream &ostr) const;
                std::istream &read(std::istream &istr);
                void set(int member_id);
                operator bool() const;
        };
}
#endif //! SDDS_BOOK_H__