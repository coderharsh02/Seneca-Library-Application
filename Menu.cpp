//################################
// Seneca Library Application  ###
//################################

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    MenuItem::MenuItem(const char *content)
    {
        if (content && content[0] != '\0')
        {
            m_menuItemContent = new char[strlen(content) + 1];
            strcpy(m_menuItemContent, content);
        }
        else
        {
            m_menuItemContent = nullptr;
        }
    }
    MenuItem::~MenuItem()
    {
        delete[] m_menuItemContent;
    }
    MenuItem::operator bool() const
    {
        return m_menuItemContent != nullptr;
    }
    MenuItem::operator const char *() const
    {
        return m_menuItemContent;
    }
    ostream &MenuItem::display(ostream &os) const
    {
        if (m_menuItemContent && m_menuItemContent[0] != '\0')
            os << m_menuItemContent;
        return os;
    }
    Menu::Menu(const char *title)
    {
        if (title && title[0] != '\0')
        {
            m_menuTitle = new char[strlen(title) + 1];
            strcpy(m_menuTitle, title);
            m_menuCounter = 0;
        }
        else
        {
            m_menuTitle = nullptr;
            m_menuCounter = 0;
        }
    }
    Menu::~Menu()
    {
        delete[] m_menuTitle;
        m_menuTitle = nullptr;
        for (int i = 0; i < m_menuCounter; i++)
        {
            delete m_menuItems[i];
            m_menuItems[i] = nullptr;
        }
    }
    char *Menu::title() const
    {
        char *res = nullptr;
        if (m_menuTitle && m_menuTitle[0] != '\0')
            res = m_menuTitle;
        return res;
    }
    void Menu::displayMenu() const
    {
        if (title())
        {
            cout << title() << endl;
            // cout << ":\n";
        }

        for (int i = 0; i < m_menuCounter; i++)
        {
            cout.setf(ios::right);
            cout.width(2);
            cout << (i + 1) << "- " << m_menuItems[i]->m_menuItemContent << endl;
        }
        cout << " 0- Exit" << endl;
        cout << "> ";
    }
    unsigned int Menu::run() const
    {
        displayMenu();
        return getIntRange(0, m_menuCounter);
    }
    unsigned int Menu::operator~() const
    {
        return run();
    }
    Menu &Menu::operator<<(const char *menuitemConent)
    {
        if (m_menuCounter < int(MAX_MENU_ITEMS))
        {
            m_menuItems[m_menuCounter] = new MenuItem(menuitemConent);
            m_menuCounter++;
        }
        return *this;
    }
    Menu::operator int() const
    {
        return m_menuCounter;
    }
    Menu::operator unsigned int() const
    {
        return m_menuCounter;
    }
    Menu::operator bool() const
    {
        return m_menuCounter > 0;
    }
    ostream &operator<<(ostream &os, const Menu &M)
    {
        if (M.title())
            os << M.title();
        return os;
    }
    const char *Menu::operator[](int idx) const
    {
        const char *res = nullptr;
        idx = idx % m_menuCounter;
        if (idx > -1)
            res = m_menuItems[idx]->m_menuItemContent;
        return res;
    }
}