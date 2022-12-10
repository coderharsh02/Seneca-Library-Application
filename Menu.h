//################################
// Seneca Library Application  ###
//################################

#ifndef SDDS_MENU_H__
#define SDDS_MENU_H__
#include <iostream>
namespace sdds
{
    class Menu;
    const unsigned int MAX_MENU_ITEMS = 20;
    class MenuItem
    {
        char *m_menuItemContent;
        MenuItem(const char * = nullptr);
        MenuItem(const MenuItem &) = delete;
        MenuItem &operator=(const MenuItem &) = delete;
        ~MenuItem();
        operator bool() const;
        operator const char *() const;
        std::ostream &display(std::ostream &) const;
        friend class Menu;
    };
    class Menu
    {
    private:
        char *m_menuTitle;
        MenuItem *m_menuItems[MAX_MENU_ITEMS]{nullptr};
        int m_menuCounter;
        Menu(const Menu &) = delete;
        Menu &operator=(const Menu &) = delete;

    public:
        Menu(const char * = nullptr);
        ~Menu();
        char *title() const;
        void displayMenu() const;
        unsigned int run() const;
        unsigned int operator~() const;
        Menu &operator<<(const char *menuitemConent);
        operator int() const;
        operator unsigned int() const;
        operator bool() const;
        const char *operator[](int) const;
    };
    std::ostream &operator<<(std::ostream &, const Menu &);
}
#endif // !SDDS_MENU_H__