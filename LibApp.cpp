//################################
// Seneca Library Application  ###
//################################

#include <fstream>
#include <iomanip>
#include "Utils.h"
#include "LibApp.h"
#include "Book.h"
#include "PublicationSelector.h"
using namespace std;
namespace sdds
{
    void prnPub(Publication *p[], int size, int ref)
    {
        for (int i = 0; i < size; i++)
        {
            if (ref == p[i]->getRef())
            {
                cout << *p[i] << endl;
                i = size;
            }
        }
    }
    Publication *LibApp::getPub(int libRef)
    {
        Publication *pubPtr = nullptr;
        for (int i = 0; i < m_noOfLoadedPubs && !pubPtr; i++)
        {
            if (libRef == m_pubsPtrArr[i]->getRef())
            {
                pubPtr = m_pubsPtrArr[i];
                i = m_noOfLoadedPubs;
            }
        }
        return pubPtr;
    }
    bool LibApp::confirm(const char *message)
    {
        bool res = false;
        Menu m(message);
        m << "Yes";
        if (m.run())
        {
            res = true;
        }
        return res;
    }
    void LibApp::load()
    {
        cout << "Loading Data\n";
        ifstream filein(m_filename);
        char pType = '*';
        for (int row = 1; filein; row++)
        {
            filein >> pType;
            filein.ignore();
            if (filein)
            {
                if (pType == 'B')
                    m_pubsPtrArr[m_noOfLoadedPubs] = new Book();
                else if (pType == 'P')
                    m_pubsPtrArr[m_noOfLoadedPubs] = new Publication();
                else
                {
                    cout << "The Record type signature is supposed to be B or P, but it is: " << pType << endl;
                    filein.setstate(ios::failbit);
                }
                if (m_pubsPtrArr[m_noOfLoadedPubs])
                {
                    filein >> *m_pubsPtrArr[m_noOfLoadedPubs];
                    m_noOfLoadedPubs++;
                }
            }
        }
        m_lastLibRefNo = m_pubsPtrArr[m_noOfLoadedPubs - 1]->getRef() + 1;
    }
    void LibApp::save()
    {
        cout << "Saving Data\n";
        ofstream fileout(m_filename);
        for (int i = 0; i < m_noOfLoadedPubs; i++)
        {
            if (m_pubsPtrArr[i]->getRef())
            {
                fileout << *m_pubsPtrArr[i] << endl;
            }
        }
        fileout.close();
    }
    int LibApp::search(int choice)
    {
        int selectRefNo = 0;
        char searchTitle[256];
        PublicationSelector ps("Select one of the following found matches:");
        int type = m_pubTypeMenu.run();
        char pType = 'x';
        switch (type)
        {
        case 1:
            pType = 'B';
            break;
        case 2:
            pType = 'P';
            break;
        case 0:
            break;
        }
        if (type)
        {
            cout << "Publication Title: ";
            cin.getline(searchTitle, 256, '\n');
            for (int i = 0; i < m_noOfLoadedPubs; i++)
            {
                if (m_pubsPtrArr[i]->getRef() && m_pubsPtrArr[i]->type() == pType)
                {
                    switch (choice)
                    {
                    case 1: // search all
                        if (strstr(*m_pubsPtrArr[i], searchTitle))
                            ps << m_pubsPtrArr[i];
                        break;
                    case 2: // seach that are on loan
                        if (m_pubsPtrArr[i]->onLoan() && strstr(*m_pubsPtrArr[i], searchTitle))
                            ps << m_pubsPtrArr[i];

                        break;
                    case 3: // search that are not on loan
                        if (!m_pubsPtrArr[i]->onLoan() && strstr(*m_pubsPtrArr[i], searchTitle))
                            ps << m_pubsPtrArr[i];
                        break;
                    }
                }
            }
            if (ps)
            {
                ps.sort();          // sort them based on date and title
                int ref = ps.run(); // display the publications and select one
                if (ref)
                {
                    selectRefNo = ref;
                    prnPub(m_pubsPtrArr, m_noOfLoadedPubs, ref);
                }
                else
                {
                    cout << "Aborted!\n";
                }
            }
            else
            {
                cout << "No matches found!\n";
            }
        }
        else
        {
            cout << "Aborted!\n";
        }
        return selectRefNo;
    }

    void LibApp::newPublication()
    {
        if (m_noOfLoadedPubs == SDDS_LIBRARY_CAPACITY)
        {
            cout << "Library is at its maximum capacity!\n";
        }
        else
        {
            cout << "Adding new publication to the library\n";
            int type = m_pubTypeMenu.run();
            Publication *pub = nullptr;
            switch (type)
            {
            case 1:
                pub = new Book();
                break;
            case 2:
                pub = new Publication();
                break;
            case 0:
                break;
            }
            if (type)
            {

                cin >> *pub;
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Aborted!";
                }
                else
                {
                    if (confirm("Add this publication to the library?"))
                    {
                        if (*pub)
                        {
                            pub->setRef(m_lastLibRefNo++);
                            m_pubsPtrArr[m_noOfLoadedPubs] = pub;
                            m_noOfLoadedPubs++;
                            m_changed = true;
                            cout << "Publication added\n";
                        }
                        else
                        {
                            cout << "Failed to add publication!";
                            delete pub;
                        }
                    }
                    else
                    {
                        cout << "Aborted!\n";
                    }
                }
            }
            else
            {
                cout << "Aborted!\n";
            }
        }
        cout << "\n";
    }
    void LibApp::removePublication()
    {
        cout << "Removing publication from the library\n";
        int ref = search(1);
        if (ref)
        {
            if (confirm("Remove this publication from the library?"))
            {
                getPub(ref)->setRef(0);
                m_changed = true;
                cout << "Publication removed\n";
            }
        }
        cout << "\n";
    }
    void LibApp::checkOutPub()
    {
        cout << "Checkout publication from the library\n";
        int ref = search(3);
        if (ref)
        {
            if (confirm("Check out publication?"))
            {
                cout << "Enter Membership number: ";
                int membership = getInt();
                while (membership < 10000 || membership > 99999)
                {
                    cout << "Invalid membership number, try again: ";
                    membership = getInt();
                }
                Publication *pub = getPub(ref);
                pub->set(membership);
                pub->resetDate();
                m_changed = true;
                cout << "Publication checked out\n";
            }
        }
        cout << "\n";
    }
    void LibApp::returnPub()
    {
        cout << "Return publication to the library\n";
        int ref = search(2);
        if (ref)
        {
            if (confirm("Return Publication?"))
            {
                Publication *pub = getPub(ref);
                int days = Date() - pub->checkoutDate();
                if (days > 15)
                {
                    float penalty = (days - 15) * 0.5;
                    cout << "Please pay $" << fixed << setprecision(2) << penalty << " penalty for being " << (days - 15) << " days late!\n";
                }
                pub->set(0);
                // pub->resetDate();
                m_changed = true;
                cout << "Publication returned\n";
            }
        }
        cout << "\n";
    }
    LibApp::LibApp(const char filename[]) : m_mainMenu("Seneca Library Application"),
                                            m_exitMenu("Changes have been made to the data, what would you like to do?"),
                                            m_pubTypeMenu("Choose the type of publication:")
    {
        m_changed = false;
        m_mainMenu << "Add New Publication"
                   << "Remove Publication"
                   << "Checkout publication from library"
                   << "Return publication to library";

        m_exitMenu << "Save changes and exit"
                   << "Cancel and go back to the main menu";

        m_pubTypeMenu << "Book"
                      << "Publication";

        m_noOfLoadedPubs = 0;
        m_lastLibRefNo = 0;
        strcpy(m_filename, filename);
        load();
    }
    LibApp::~LibApp()
    {
        for (int i = 0; i < m_noOfLoadedPubs; i++)
        {
            delete m_pubsPtrArr[i];
        }
    }
    void LibApp::run()
    {
        int selection = 0;
        do
        {
            selection = m_mainMenu.run();
            switch (selection)
            {
            case 1:
                newPublication();
                break;

            case 2:
                removePublication();
                break;

            case 3:
                checkOutPub();
                break;

            case 4:
                returnPub();
                break;

            case 0:
                if (m_changed)
                {
                    selection = m_exitMenu.run();
                    switch (selection)
                    {
                    case 1:
                        save();
                        selection = 0;
                        break;

                    case 2:
                        selection = 1;
                        cout << "\n";
                        break;

                    case 0:
                        if (!confirm("This will discard all the changes are you sure?"))
                        {
                            selection = 1;
                        }
                        break;
                    }
                }
            }
        } while (selection);
        cout << "\n-------------------------------------------\n";
        cout << "Thanks for using Seneca Library Application\n";
    }
}
