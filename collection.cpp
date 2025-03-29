#include "collection.h"
#include <algorithm>
#include <iostream>

// Name: Eddie Wang
// Seneca Email: ewang34@seneca.ca
// Student ID: 15511230
// Date: 2025-03-28
// I declare that this submission is the result of my own work and I only copied the code 
// that my professor provided to complete my assignments. This submitted piece of work 
// has not been shared with any other student or 3rd party content provider.

namespace seneca {
    Collection::~Collection() {
        for (auto item : m_items) {
            delete item;
        }
    }

    Collection& Collection::operator+=(MediaItem* item) {
        bool exists = false;
        for (auto existing : m_items) {
            if (existing->getTitle() == item->getTitle()) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            m_items.push_back(item);
            if (m_observer)
                m_observer(*this, *item);
        }
        else {
            delete item;
        }
        return *this;
    }

    MediaItem* Collection::operator[](size_t index) const {
        if (index < m_items.size())
            return m_items[index];
        return nullptr;
    }

    MediaItem* Collection::operator[](const std::string& title) const {
        for (auto item : m_items) {
            if (item->getTitle() == title || item->getTitle() == "\"" + title + "\"")
                return item;
        }
        return nullptr;
    }

    void Collection::sort(const std::string& criteria) {
        if (criteria == "title") {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
                return a->getTitle() < b->getTitle();
                });
        }
        else if (criteria == "year") {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
                return a->getYear() < b->getYear();
                });
        }
    }

    void Collection::removeQuotes() {
        for (auto item : m_items) {
            std::string title = item->getTitle();
            std::string summary = item->getSummary();
            title.erase(std::remove(title.begin(), title.end(), '\"'), title.end());
            summary.erase(std::remove(summary.begin(), summary.end(), '\"'), summary.end());
            item->setTitle(title);
            item->setSummary(summary);
        }
    }

    std::ostream& operator<<(std::ostream& out, const Collection& col) {
        for (auto item : col.m_items) {
            item->display(out);
        }
        return out;
    }
}