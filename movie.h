#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

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
    class Movie : public MediaItem {
        // Private constructor used by createItem.
        Movie(const std::string& title, const std::string& summary, unsigned short year)
            : MediaItem(title, summary, year) { }
    public:
        void display(std::ostream& out = std::cout) const override;
        // Factory function: builds a Movie object from a CSV string "TITLE,YEAR,SUMMARY".
        static Movie* createItem(const std::string& strMovie);
    };
}

#endif