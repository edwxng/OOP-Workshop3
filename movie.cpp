#include "movie.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <sstream>

namespace seneca {

    void Movie::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            out << "M | ";
            out << std::left << std::setfill('.') << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ') << std::setw(9) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << std::setfill(' ') << '\n';
        }
    }

    Movie* Movie::createItem(const std::string& strMovie) {
        if (strMovie.empty() || strMovie[0] == '#')
            throw "Not a valid movie.";
        std::string token;
        std::istringstream iss(strMovie);
        std::string fields[3];
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            if (idx < 2) {
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
        if (idx != 3)
            throw "Not a valid movie.";
        unsigned short year = static_cast<unsigned short>(std::stoi(fields[1]));
        return new Movie(fields[0], fields[2], year);
    }
}