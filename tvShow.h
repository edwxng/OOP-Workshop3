#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iomanip>

// Name: Eddie Wang
// Seneca Email: ewang34@seneca.ca
// Student ID: 15511230
// Date: 2025-03-28
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work 
// has not been shared with any other student or 3rd party content provider.

namespace seneca {

    // Structure to represent an episode.
    struct TvEpisode {
        const class TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem {
        std::string m_id;
        std::vector<TvEpisode> m_episodes;
        // Private constructor
        TvShow(const std::string& id, const std::string& title, const std::string& summary, unsigned short year)
            : MediaItem(title, summary, year), m_id(id) { }
    public:
        void display(std::ostream& out = std::cout) const override;
        // Factory function: builds a TvShow from a CSV string "ID,TITLE,YEAR,SUMMARY".
        static TvShow* createItem(const std::string& strShow);
        // Template function to add an episode from a CSV string.
        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode) {
            if (strEpisode.empty() || strEpisode[0] == '#')
                throw "Not a valid episode.";
            std::istringstream iss(strEpisode);
            std::string token;
            std::string fields[8];
            int idx = 0;
            while (std::getline(iss, token, ',')) {
                if (idx < 7) {
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
            if (idx < 7)
                throw "Not a valid episode.";
            // Find the TvShow with the given ID in collection col.
            TvShow* show = nullptr;
            for (size_t i = 0; i < col.size(); i++) {
                show = dynamic_cast<TvShow*>(col[i]);
                if (show && show->m_id == fields[0])
                    break;
                show = nullptr;
            }
            if (!show)
                throw "Not a valid episode.";
            TvEpisode ep;
            ep.m_show = show;
            ep.m_numberOverall = static_cast<unsigned short>(std::stoi(fields[1]));
            ep.m_season = (fields[2].empty()) ? 1 : static_cast<unsigned short>(std::stoi(fields[2]));
            ep.m_numberInSeason = static_cast<unsigned short>(std::stoi(fields[3]));
            ep.m_airDate = fields[4];
            ep.m_length = static_cast<unsigned int>(std::stoi(fields[5]));
            ep.m_title = fields[6];
            if (idx >= 8)
                ep.m_summary = fields[7];
            show->m_episodes.push_back(ep);
        }
        // Using STL algorithms (no manual loops) to compute the average episode length (in seconds).
        double getEpisodeAverageLength() const;
        // Using STL algorithms (no manual loops) to get a list of episode names that are at least 60 minutes long.
        std::list<std::string> getLongEpisodes() const;
    };
}

#endif