#include "iterator_range.h"
#include "search_server.h"
#include "profile.h"
//#include "timer.h"
#include "parse.h"

#include <string_view>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <numeric>
#include <future>

SearchServer::SearchServer(std::istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(std::istream& document_input) {
    InvertedIndex new_index(document_input);
    index_serv.GetAccess().ref_to_value = std::move(new_index);
}

void SearchServer::ReverseIndexPadding(const std::string& current_query,
                                       std::vector<size_t>& docid_count) {
//    TotalDuration words_split("\tSplitIntoWords");
//    TotalDuration lookup("\tReverseIndexPadding");

    auto access = index_serv.GetAccess();
    docid_count.assign(access.ref_to_value.GetIdCount(), 0);
    std::vector<std::string_view> words;
    {
//        ADD_DURATION(words_split);
        words = SplitIntoWords(std::string_view(current_query));
    }
//    ADD_DURATION(lookup);
    for (std::string_view word: words) {
        for (const auto& t: access.ref_to_value.Lookup(word)) {
            docid_count[t.doc_id] += t.hitcount;
        }
    }
}

void SearchServer::SortingIndexingArray(const size_t resize_arr,
                                        const std::vector<size_t>& docid_count,
                                        std::vector<size_t>& ids) const {
//    TotalDuration sorting("\tSortingIndexingArray");
//    ADD_DURATION(sorting);

    ids.resize(resize_arr);
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
}

void SearchServer::WritingResultToStream(const std::vector<size_t>& docid_count,
                                         const std::vector<size_t>& ids,
                                         const std::string& current_query,
                                         std::ostream& search_results_output) const {
//    TotalDuration build_results("\tWritingResultToStream");
//    ADD_DURATION(build_results);

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

void SearchServer::AddQueriesStream(std::istream& query_input,
                                    std::ostream& search_results_output) {
    std::vector<size_t> docid_count;
    std::vector<size_t> ids;
    std::string current_query;

//    TotalDuration total_iteration("\tTotal loop iteration");
    while (getline(query_input, current_query)) {
//        ADD_DURATION(total_iteration);
        ReverseIndexPadding(current_query, docid_count);
        SortingIndexingArray(index_serv.GetAccess().ref_to_value.GetIdCount(),
                             docid_count, ids);
        WritingResultToStream(docid_count, ids, current_query, search_results_output);
    }
}

InvertedIndex::InvertedIndex(std::istream& document_input) {
    std::string current_document;
    while(std::getline(document_input, current_document)) {
        docs.push_back(std::move(current_document));
        size_t id_count = GetIdCount() - 1;
        for (auto word: SplitIntoWords(std::string_view(docs.back()))) {
            auto& id_to_count = index[word];
            if (!id_to_count.empty() && id_to_count.back().doc_id == id_count) {
                ++(id_to_count.back().hitcount);
            } else {
                id_to_count.push_back({id_count, 1});
            }
        }
    }
}

std::vector<InvertedIndex::doc_id_t> InvertedIndex::Lookup(std::string_view word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}

