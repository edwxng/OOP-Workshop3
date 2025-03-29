#include "book.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <sstream>

namespace seneca {

    void Book::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            out << "B | ";
            out << std::left << std::setfill('.') << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ') << std::setw(2) << m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else {
                out << this->getSummary();
            }
            out << std::endl;
        }
        else {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [" << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
        }
    }

    Book* Book::createItem(const std::string& strBook) {
        if (strBook.empty() || strBook[0] == '#')
            throw "Not a valid book.";
        std::string token;
        std::istringstream iss(strBook);
        std::string fields[6];
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            if (idx < 5) {
                // Since this is a member function of Book, we can access the protected trim.
                MediaItem::trim(token);
                fields[idx++] = token;
            }
            else {
                std::string rest = token;
                std::string extra;
                while (std::getline(iss, extra))
                    rest += "," + extra;
                MediaItem::trim(rest);
                fields[idx++] = rest;
                break;
            }
        }
        if (idx != 6)
            throw "Not a valid book.";
        double price = std::stod(fields[3]);
        unsigned short year = static_cast<unsigned short>(std::stoi(fields[4]));
        return new Book(fields[0], fields[1], fields[2], price, year, fields[5]);
    }
}