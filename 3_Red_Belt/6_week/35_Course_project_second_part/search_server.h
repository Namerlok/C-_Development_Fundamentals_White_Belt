#pragma once

#include "synchronized.h"

#include <unordered_map>
#include <string_view>
#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <future>
#include <deque>
#include <list>
#include <map>

//const size_t MAX_SIZE_OF_DOCUMENT = 50.000;
//const size_t MAX_QUERY_INPUT = 500.000;
// максимальное количество потоков снижено на 1,
// так как один поток зарезервирован для обновления базы данных
const size_t MAX_THREAD_OF_HARDWARE = std::thread::hardware_concurrency();

class InvertedIndex {
public:
    struct doc_id_t {
        size_t doc_id;
        size_t hitcount;
    };
    InvertedIndex() = default;
    InvertedIndex(std::istream& document_input);
    std::vector<doc_id_t> Lookup(std::string_view word) const;
    size_t GetIdCount() const {
        return docs.size();
    }

private:
    std::deque<std::string> docs;
    std::unordered_map<std::string_view,
                       std::vector<doc_id_t>> index;
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
    std::mutex initialization;


    template <typename It>
    void AddQueriesStreamSingleThreads(It begin, It end,
                                       std::string& search_results);
    void UpdateDocumentBaseSinglrTreads(std::istream& document_input);
    void ReverseIndexPadding(const std::string& current_query,
                             std::vector<size_t>& docid_count);
    void SortingIndexingArray(const std::vector<size_t>& docid_count,
                              std::vector<size_t>& ids) const;
    void WritingResultToString(const std::vector<size_t>& docid_count,
                               const std::vector<size_t>& ids,
                               const std::string& current_query,
                               std::string& search_results_output) const;
};


