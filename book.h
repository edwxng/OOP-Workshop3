#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <sstream>
#include <iomanip>

// Name: Eddie Wang
// Seneca Email: ewang34@seneca.ca
// Student ID: 15511230
// Date: 2025-03-28
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work 
// has not been shared with any other student or 3rd party content provider.

namespace seneca {
    class Book : public MediaItem {
        std::string m_author;
        std::string m_country;
        double m_price;
        // Private constructor: used by createItem
        Book(const std::string& author, const std::string& title, const std::string& country, double price, unsigned short year, const std::string& summary)
            : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) { }
    public:
        void display(std::ostream& out = std::cout) const override;
        // Factory function: builds a Book object from a CSV string.
        static Book* createItem(const std::string& strBook);
    };
}

#endif
