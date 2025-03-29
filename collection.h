#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include "mediaItem.h"
#include <vector>
#include <string>
#include <functional>

// Name: Eddie Wang
// Seneca Email: ewang34@seneca.ca
// Student ID: 15511230
// Date: 2025-03-28
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work 
// has not been shared with any other student or 3rd party content provider.

namespace seneca {
    class Collection {
        std::string m_name;
        std::vector<MediaItem*> m_items;
        std::function<void(const Collection&, const MediaItem&)> m_observer;
    public:
        Collection(const std::string& name) : m_name(name) { }
        ~Collection();
        // Disallow copy operations.
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        const std::string& name() const { return m_name; }
        size_t size() const { return m_items.size(); }
        void setObserver(std::function<void(const Collection&, const MediaItem&)> observer) {
            m_observer = observer;
        }
        // Overloaded operator+= adds an item and notifies the observer.
        Collection& operator+=(MediaItem* item);
        // Overloaded subscripting by index.
        MediaItem* operator[](size_t index) const;
        // Overloaded subscripting by title: returns pointer if found; otherwise nullptr.
        MediaItem* operator[](const std::string& title) const;
        // Sort the collection based on criteria ("title" or "year").
        void sort(const std::string& criteria);
        // Remove quotes from titles and summaries of all items.
        void removeQuotes();
        friend std::ostream& operator<<(std::ostream& out, const Collection& col);
    };
}

#endif