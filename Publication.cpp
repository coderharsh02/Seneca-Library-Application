//################################
// Seneca Library Application  ###
//################################

#include <string.h>
#include "Publication.h"
using namespace std;
namespace sdds
{
    Publication::Publication()
    {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
    }
    void Publication::set(int member_id)
    {
        m_membership = member_id;
    }
    void Publication::setRef(int value)
    {
        m_libRef = value;
    }
    void Publication::resetDate()
    {
        Date dNew;
        m_date = dNew;
    }
    char Publication::type() const
    {
        return 'P';
    }
    bool Publication::onLoan() const
    {
        bool flag = false;
        if (m_membership)
        {
            flag = true;
        }
        return flag;
    }
    Date Publication::checkoutDate() const
    {
        return m_date;
    }
    bool Publication::operator==(const char *title) const
    {
        bool flag = false;
        if (strstr(m_title, title))
        {
            flag = true;
        }
        return flag;
    }
    Publication::operator const char *() const
    {
        return m_title;
    }
    int Publication::getRef() const
    {
        return m_libRef;
    }
    bool Publication::conIO(ios &io) const
    {
        bool flag = false;
        if (&io == &cin || &io == &cout)
        {
            flag = true;
        }
        return flag;
    }
    ostream &Publication::write(ostream &os) const
    {
        if (conIO(os))
        {
            char title[SDDS_TITLE_WIDTH + 1] = {'\0'};
            os << "| " << m_shelfId << " | ";
            strncpy(title, m_title, SDDS_TITLE_WIDTH);
            os.width(SDDS_TITLE_WIDTH);
            os.fill('.');
            os << left << title;
            os << " | ";
            if (m_membership == 0)
            {
                os << " N/A ";
            }
            else
            {
                os << m_membership;
            }
            os << " | " << m_date << " |";
        }
        else
        {
            os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
        }
        return os;
    }
    std::istream &Publication::read(std::istream &istr)
    {
        delete[] m_title;
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        char shelfId[5];
        char title[256];
        if (conIO(istr))
        {
            std::cout << "Shelf No: ";
            istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1);
            std::cout << "Title: ";
            istr.getline(title, 256);
            if (strlen(title) <= 0)
            {
                istr.setstate(ios::failbit);
            }
            std::cout << "Date: ";
            istr >> m_date;
            if (m_date.errCode())
            {
                istr.setstate(ios::failbit);
            }
        }
        else
        {
            char libRef[6];
            istr.getline(libRef, 6, '\t');
            m_libRef = atoi(libRef);
            istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            istr.getline(title, 256, '\t');
            istr >> m_membership;
            istr >> m_date;
        }
        if (istr)
        {
            strcpy(m_shelfId, shelfId);
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
        }
        return istr;
    }
    Publication::operator bool() const
    {
        bool flag = false;
        if (m_shelfId[0] != '\0' && m_title != nullptr)
        {
            flag = true;
        }
        return flag;
    }
    Publication &Publication::operator=(const Publication &src)
    {
        m_shelfId[0] = '\0';
        strcpy(m_shelfId, src.m_shelfId);
        delete[] m_title;
        m_membership = src.m_membership;
        m_libRef = src.m_libRef;
        m_date = src.m_date;
        if (src.m_title != nullptr)
        {
            m_title = new char[strlen(src.m_title) + 1];
            strcpy(m_title, src.m_title);
        }
        else
        {
            m_title = nullptr;
        }
        return *this;
    }
    Publication::Publication(const Publication &source)
    {
        m_title = nullptr;
        *this = source;
    }
    Publication::~Publication()
    {
        delete[] m_title;
    }
}