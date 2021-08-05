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

std::vector<std::string> SplitIntoWords(const std::string& line) {
    std::istringstream words_input(line);
    std::vector<std::string> result =
        {std::make_move_iterator(std::istream_iterator<std::string>(words_input)),
         std::make_move_iterator(std::istream_iterator<std::string>())};
    return result;
}

SearchServer::SearchServer(std::istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(std::istream& document_input) {
    InvertedIndex new_index(document_input);
    index_serv.GetAccess().ref_to_value = std::move(new_index);
}

void SearchServer::AddQueriesStream(std::istream& query_input,
                                    std::ostream& search_results_output) {
    std::vector<size_t> docid_count;
    std::vector<size_t> ids;
    std::string current_query;
    while (getline(query_input, current_query)) {
        auto access = index_serv.GetAccess();
        docid_count.assign(access.ref_to_value.GetIdCount(), 0);
        ids.resize(access.ref_to_value.GetIdCount());
        //std::fill(docid_count.begin(), docid_count.end(), 0);
        const auto words = SplitIntoWords(current_query);
        for (const auto& word: words) {
            for (const auto& t: access.ref_to_value.Lookup(word)) {
                docid_count[t.first] += t.second;
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

InvertedIndex::InvertedIndex(std::istream& document_input) {
//    index.reserve(15000);

    std::string line;
    while(std::getline(document_input, line)){
        for (const std::string& word: SplitIntoWords(line)) {
            auto& id_to_count = index[std::move(word)];
            if (!id_to_count.empty() && id_to_count.count(id_count)) {
                ++id_to_count[id_count];
            } else {
                id_to_count[id_count] = 1;
            }
        }
        ++id_count;
    }
}

std::unordered_map<size_t, size_t> InvertedIndex::Lookup(const std::string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}

