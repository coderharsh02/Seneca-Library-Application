//################################
// Seneca Library Application  ###
//################################

#include <string.h>
#include "Book.h"
using namespace std;
namespace sdds
{
        Book::Book()
        {
                m_author = nullptr;
        }
        char Book::type() const
        {
                return 'B';
        }
        ostream &Book::write(ostream &os) const
        {
                this->Publication::write(os);
                if (conIO(os))
                {
                        char author[SDDS_AUTHOR_WIDTH + 1] = {'\0'};
                        os << " ";
                        os.width(SDDS_AUTHOR_WIDTH);
                        strncpy(author, m_author, SDDS_AUTHOR_WIDTH);
                        os << left << author;
                        os << " |";
                }
                else
                {
                        os << "\t" << m_author;
                }
                return os;
        }
        std::istream &Book::read(std::istream &istr)
        {
                this->Publication::read(istr);
                delete[] m_author;
                m_author = nullptr;
                char author[256];
                if (conIO(istr))
                {
                        istr.ignore();
                        std::cout << "Author: ";
                        istr.getline(author, 256);
                }
                else
                {
                        istr.ignore();
                        istr.getline(author, 256, '\n');
                        istr.putback('\n');
                }
                if (istr)
                {
                        m_author = new char[strlen(author) + 1];
                        strcpy(m_author, author);
                }
                return istr;
        }
        void Book::set(int member_id)
        {
                this->Publication::set(member_id);
                resetDate();
        }
        Book::operator bool() const
        {
                bool flag = false;
                if (m_author != nullptr && m_author[0] != '\0' && this->Publication::operator bool())
                {
                        flag = true;
                }
                return flag;
        }
        Book::Book(const Book &src)
        {
                m_author = nullptr;
                *this = src;
        }
        Book &Book::operator=(const Book &src)
        {
                if (this != &src)
                {
                        Publication &Publication = *this;
                        Publication = src;
                        delete[] m_author;
                        if (src.m_author)
                        {
                                m_author = new char[strlen(src.m_author) + 1];
                                strcpy(m_author, src.m_author);
                        }
                        else
                        {
                                m_author = nullptr;
                        }
                }
                return *this;
        }
        Book::~Book()
        {
                delete[] m_author;
        }
}