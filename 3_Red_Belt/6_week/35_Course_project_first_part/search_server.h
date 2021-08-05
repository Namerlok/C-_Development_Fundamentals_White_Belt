#pragma once

#include "synchronized.h"

#include <istream>
#include <ostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <future>

const size_t MAX_SIZE_OF_DOCUMENT = 50000;
const size_t MAX_THREAD_OF_HARDWARE = std::thread::hardware_concurrency();

class InvertedIndex {
public:
    using doc_id = size_t;
    using count_doc_id = size_t;
    InvertedIndex() = default;
    InvertedIndex(std::istream& document_input);
    std::unordered_map<doc_id, count_doc_id> Lookup(const std::string& word) const;
    size_t GetIdCount() const {
        return id_count;
    }

private:
    std::unordered_map<std::string,
                       std::unordered_map<doc_id, count_doc_id>> index;
    size_t id_count = 0;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(std::istream& document_input);
    void UpdateDocumentBase(std::istream& document_input);
    void AddQueriesStream(std::istream& query_input,
                          std::ostream& search_results_output);

private:
    Synchronized<InvertedIndex> index_serv;
//    InvertedIndex index;
    std::vector<std::future<void>> futures;
};
