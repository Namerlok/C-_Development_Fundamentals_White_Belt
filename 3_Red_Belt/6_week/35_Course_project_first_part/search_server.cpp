#include "search_server.h"
#include "iterator_range.h"
//#include "timer.h"
//#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>
#include <future>

const size_t MAX_SIZE_OF_DOCUMENT = 50000;

std::vector<std::string> SplitIntoWords(const std::string& line) {
    std::istringstream words_input(line);
    return {std::make_move_iterator(std::istream_iterator<std::string>(words_input)),
            std::make_move_iterator(std::istream_iterator<std::string>())};
}

SearchServer::SearchServer(std::istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(std::istream& document_input) {
    InvertedIndex new_index;

    for (std::string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }

    index = std::move(new_index);
}

void SearchServer::AddQueriesStream(std::istream& query_input,
                                    std::ostream& search_results_output) {
    std::vector<size_t> docid_count(MAX_SIZE_OF_DOCUMENT);
    std::vector<size_t> ids(docid_count.size());
    std::string current_query;
    while (getline(query_input, current_query)) {
        std::fill(docid_count.begin(), docid_count.end(), 0);
        const auto words = SplitIntoWords(current_query);
        for (const auto& word: words) {
            for (const size_t& docid: index.Lookup(word)) {
                ++(docid_count[docid]);
            }
        }

        std::iota(ids.begin(), ids.end(), 0);

        std::partial_sort(
            std::begin(ids),
            Head(ids, 5).end(),
            std::end(ids),
            [&docid_count](size_t lhs, size_t rhs) {
                if (docid_count[lhs] > docid_count[rhs])
                    return true;
                else if (docid_count[lhs] == docid_count[rhs] && lhs < rhs)
                    return true;
                else
                    return false;
            }
        );

        search_results_output << current_query << ':';
        for (auto& id: Head(ids, 5)) {
            if (docid_count[id] != 0) {
                search_results_output << " {"
                << "docid: " << id << ", "
                << "hitcount: " << docid_count[id] << '}';
            }
        }
        search_results_output << "\n";
    }
}

void InvertedIndex::Add(const std::string& document) {
    docs.push_back(document);

    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(document)) {
        index[word].push_back(docid);
    }
}

std::list<size_t> InvertedIndex::Lookup(const std::string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}
