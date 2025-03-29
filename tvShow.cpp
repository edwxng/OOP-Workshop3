#include "tvShow.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <vector>

namespace seneca {

    void TvShow::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            out << "S | ";
            out << std::left << std::setfill('.') << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ') << std::setw(2) << m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes) {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (!item.m_title.empty())
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';
                pos = 0;
                while (pos < item.m_summary.size()) {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const std::string& strShow) {
        if (strShow.empty() || strShow[0] == '#')
            throw "Not a valid show.";
        std::string token;
        std::istringstream iss(strShow);
        std::string fields[4];
        int idx = 0;
        while (std::getline(iss, token, ',')) {
            MediaItem::trim(token);
            fields[idx++] = token;
            if (idx == 4) break;
        }
        if (idx != 4)
            throw "Not a valid show.";
        unsigned short year = static_cast<unsigned short>(std::stoi(fields[2]));
        return new TvShow(fields[0], fields[1], fields[3], year);
    }

    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty()) return 0.0;
        unsigned int total = std::accumulate(m_episodes.begin(), m_episodes.end(), 0u,
            [](unsigned int sum, const TvEpisode& ep) { return sum + ep.m_length; });
        return static_cast<double>(total) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const {
        // Step 1: Transform m_episodes into a vector of pointers.
        std::vector<const TvEpisode*> pointers;
        pointers.reserve(m_episodes.size());
        std::transform(m_episodes.begin(), m_episodes.end(), std::back_inserter(pointers),
            [](const TvEpisode& ep) -> const TvEpisode* { return &ep; });

        // Step 2: Filter the pointers for episodes with length at least 3600 seconds.
        std::vector<const TvEpisode*> long_eps;
        std::copy_if(pointers.begin(), pointers.end(), std::back_inserter(long_eps),
            [](const TvEpisode* ep) { return ep->m_length >= 3600; });

        // Step 3: Transform the filtered pointers into a list of episode names.
        std::list<std::string> result;
        std::transform(long_eps.begin(), long_eps.end(), std::back_inserter(result),
            [](const TvEpisode* ep) -> std::string {
                return (!ep->m_title.empty()) ? ep->m_title : ("Episode " + std::to_string(ep->m_numberOverall));
            });

        return result;
    }
}
