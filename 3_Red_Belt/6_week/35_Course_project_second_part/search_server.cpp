#include "iterator_range.h"
#include "search_server.h"
//#include "test_runner.h"
//#include "profile.h"
//#include "timer.h"
#include "parse.h"

#include <string_view>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <ostream>
#include <numeric>
#include <future>

SearchServer::SearchServer(std::istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBaseSinglrTreads(std::istream& document_input) {
    InvertedIndex new_index(document_input);
    index_serv.GetAccess().ref_to_value = std::move(new_index);
}

void SearchServer::UpdateDocumentBase(std::istream& document_input) {
    std::future<void> future = std::async([this, &document_input] {
        this->UpdateDocumentBaseSinglrTreads(document_input);
    });
}

void SearchServer::ReverseIndexPadding(const std::string& current_query,
                                       std::vector<size_t>& docid_count) {
    std::vector<std::string_view> words = SplitIntoWords(current_query);
    std::fill(docid_count.begin(), docid_count.end(), 0);
    for (std::string_view word: words) {
        auto access = index_serv.GetAccess();
        for (const auto& t: access.ref_to_value.Lookup(word))
            docid_count[t.doc_id] += t.hitcount;
    }
}

void SearchServer::SortingIndexingArray(const std::vector<size_t>& docid_count,
                                        std::vector<size_t>& ids) const {
    std::iota(ids.begin(), ids.end(), 0);
    std::partial_sort(
        ids.begin(),
        Head(ids, 5).end(),
        ids.end(),
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

void SearchServer::WritingResultToString(const std::vector<size_t>& docid_count,
                                         const std::vector<size_t>& ids,
                                         const std::string& current_query,
                                         std::string& search_results_output) const {
    search_results_output += current_query + ':';
    for (auto& id: Head(ids, 5)) {
        if (docid_count[id] != 0) {
            search_results_output += " {docid: " + std::to_string(id) + ", ";
            search_results_output +=  "hitcount: " + std::to_string(docid_count[id]) + '}';
        }
    }
    search_results_output += "\n";
}
template <typename It>
void SearchServer::AddQueriesStreamSingleThreads(It begin, It end,
                                                 std::string& search_results) {
//    initialization.lock();
    std::vector<size_t> docid_count;
    std::vector<size_t> ids;
    std::string current_query;
//    initialization.unlock();
    for (It current_query = begin; current_query != end;
         current_query = std::next(current_query)) {

        docid_count.resize(index_serv.GetAccess().ref_to_value.GetIdCount());
        ids.resize(index_serv.GetAccess().ref_to_value.GetIdCount());

        ReverseIndexPadding(*current_query, docid_count);
        SortingIndexingArray(docid_count, ids);
        WritingResultToString(docid_count, ids, *current_query, search_results);
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

void SearchServer::AddQueriesStream(std::istream& query_input,
                                    std::ostream& search_results_output) {
    std::vector<std::string> query_string;
    for (std::string query; std::getline(query_input, query);)
            query_string.push_back(std::move(query));
    size_t numb_query = query_string.size();
    size_t numb_thread = std::min(query_string.size(), MAX_THREAD_OF_HARDWARE);

    std::vector<std::future<void>> futures;
    std::vector<std::string> search_results(numb_query);
    for (size_t i = 0; i < numb_thread; ++i) {
        futures.push_back(std::async([&query_string, &search_results, numb_query, numb_thread, i, this] {
            this->AddQueriesStreamSingleThreads(query_string.begin() + numb_query * i / numb_thread,
                                          query_string.begin() + numb_query * (i + 1) / numb_thread,
                                          search_results[i]);
        }));
    }

    for (auto& future: futures)
        future.get();

    for (auto& res: search_results)
        search_results_output << res;
}


/*
void TestSearchServer(vector<pair<istream, ostream*>> streams) {
    // IteratorRange — шаблон из задачи Paginator
    // random_time() — функция, которая возвращает случайный
    // промежуток времени

    LOG_DURATION("Total");
    SearchServer srv(streams.front().first);
    for (auto& [input, output] :
         IteratorRange(begin(streams) + 1, end(streams))) {
        this_thread::sleep_for(random_time());
        if (!output) {
            srv.UpdateDocumentBase(input);
        } else {
            srv.AddQueriesStream(input, *output);
        }
    }
}
*/
