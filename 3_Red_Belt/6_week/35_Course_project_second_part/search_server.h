#pragma once

#include "synchronized.h"

#include <string_view>
#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <future>
#include <deque>
#include <list>
#include <map>

//const size_t MAX_SIZE_OF_DOCUMENT = 50000;
const size_t MAX_THREAD_OF_HARDWARE = std::thread::hardware_concurrency();

class InvertedIndex {
public:
    struct doc_id_t {
        size_t doc_id;
        size_t hitcount;
    };
    InvertedIndex() = default;
    explicit InvertedIndex(std::istream& document_input);
    std::vector<doc_id_t> Lookup(std::string_view word) const;
    size_t GetIdCount() const {
        return docs.size();
    }

private:
    std::deque<std::string> docs;
    std::map<std::string_view,
             std::vector<doc_id_t>> index;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(std::istream& document_input):
        index_serv(InvertedIndex(document_input)) {}
    void UpdateDocumentBase(std::istream& document_input);
    void AddQueriesStream(std::istream& query_input,
                          std::ostream& search_results_output);
    void FuturseGet() {
        for (auto& future: futures)
            future.get();
        futures.clear();
    }

private:
    Synchronized<InvertedIndex> index_serv;
    std::vector<std::future<void>> futures;

    void UpdateDocumentBaseSingleThread(std::istream& document_input);

    void AddQueriesStreamSingleThread(std::istream& query_input,
                                      std::ostream& search_results_output);

    void ReverseIndexPadding(const std::string& current_query,
                             std::vector<size_t>& docid_count,
                             Synchronized<InvertedIndex>::Access& access);

    void SortingIndexingArray(const std::vector<size_t>& docid_count,
                              std::vector<size_t>& ids) const;

    void WritingResultToStream(const std::vector<size_t>& docid_count,
                               const std::vector<size_t>& ids,
                               const std::string& current_query,
                               std::ostream& search_results_output) const;
};

/* author's solution
#pragma once

#include "search_server.h"
#include "synchronized.h"

#include <istream>
#include <ostream>
#include <vector>
#include <string>
#include <string_view>
#include <queue>
#include <future>
#include <map>
using namespace std;

class InvertedIndex {
public:
  struct Entry {
    size_t docid, hitcount;
  };

  InvertedIndex() = default;
  explicit InvertedIndex(istream& document_input);

  const vector<Entry>& Lookup(string_view word) const;

  const deque<string>& GetDocuments() const {
    return docs;
  }

private:
  deque<string> docs;
  map<string_view, vector<Entry>> index;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input)
    : index(InvertedIndex(document_input))
  {
  }

  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> async_tasks;
};
 */
