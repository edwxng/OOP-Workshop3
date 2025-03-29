#include "spellChecker.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// Name: Eddie Wang
// Seneca Email: ewang34@seneca.ca
// Student ID: 15511230
// Date: 2025-03-28
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work 
// has not been shared with any other student or 3rd party content provider.

namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);
        if (!file)
            throw "Bad file name!";
        std::string line;
        int idx = 0;
        while (std::getline(file, line) && idx < 6) {
            if (line.empty())
                continue;
            std::istringstream iss(line);
            std::string bad, good;
            iss >> bad >> good;
            m_badWords[idx] = bad;
            m_goodWords[idx] = good;
            idx++;
        }
    }

    void SpellChecker::operator()(std::string& text) {
        for (int i = 0; i < 6; i++) {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                m_replacements[i]++;
                pos += m_goodWords[i].length();
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const {
        for (int i = 0; i < 6; i++) {
            out.width(15);
            out << std::right << m_badWords[i] << ": " << m_replacements[i] << " replacements" << std::endl;
        }
    }
}