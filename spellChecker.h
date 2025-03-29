#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <iostream>

// Name: Eddie Wang
// Seneca Email: ewang34@seneca.ca
// Student ID: 15511230
// Date: 2025-03-28
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work 
// has not been shared with any other student or 3rd party content provider.

namespace seneca {
    class SpellChecker {
        std::string m_badWords[6];
        std::string m_goodWords[6];
        int m_replacements[6]{ 0,0,0,0,0,0 };
    public:
        // Constructor loads the 6 pairs of words from the file.
        SpellChecker(const char* filename);
        // Functor operator to replace bad words in text.
        void operator()(std::string& text);
        // Display how many replacements have been made for each bad word.
        void showStatistics(std::ostream& out) const;
    };
}

#endif