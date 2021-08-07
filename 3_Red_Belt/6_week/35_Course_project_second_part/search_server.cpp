#include "iterator_range.h"
#include "search_server.h"
//#include "profile.h"
//#include "timer.h"
#include "parse.h"

#include <string_view>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <numeric>
#include <future>

//SearchServer::SearchServer(std::istream& document_input) {
//    UpdateDocumentBase(document_input);
//}

void SearchServer::UpdateDocumentBase(std::istream& document_input) {
    futures.push_back(std::async([this, &document_input] {
        this->UpdateDocumentBaseSingleThread(document_input);
    }));
}

void SearchServer::UpdateDocumentBaseSingleThread(std::istream &document_input) {
    InvertedIndex new_index(document_input);
    std::swap(index_serv.GetAccess().ref_to_value, new_index);
}

void SearchServer::ReverseIndexPadding(const std::string& current_query,
                                       std::vector<size_t>& docid_count,
                                       Synchronized<InvertedIndex>::Access& access) {

    std::vector<std::string_view> words = SplitIntoWords(std::string_view(current_query));
    for (std::string_view word: words) {
        for (const auto& t: access.ref_to_value.Lookup(word)) {
            docid_count[t.doc_id] += t.hitcount;
        }
    }
}

void SearchServer::SortingIndexingArray(const std::vector<size_t>& docid_count,
                                        std::vector<size_t>& ids) const {
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
    futures.push_back(std::async([this, &query_input, &search_results_output] {
        this->AddQueriesStreamSingleThread(query_input, search_results_output);
    }));
}

void SearchServer::AddQueriesStreamSingleThread(std::istream& query_input,
                                                std::ostream& search_results_output) {

    std::vector<size_t> docid_count;
    std::vector<size_t> ids;
    std::string current_query;

    while (getline(query_input, current_query)) {
        {
            auto access = index_serv.GetAccess();
            size_t size_id = access.ref_to_value.GetIdCount();
            docid_count.assign(size_id, 0);
            ids.resize(size_id);
            ReverseIndexPadding(current_query, docid_count, access);
        }
        SortingIndexingArray(docid_count, ids);
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

/* author's solution
#include "search_server.h"

#include "parse.h"
#include "iterator_range.h"

#include <algorithm>
#include <future>
#include <numeric>

InvertedIndex::InvertedIndex(istream& document_input) {
  for (string current_document; getline(document_input, current_document); ) {
    docs.push_back(move(current_document));
    size_t docid = docs.size() - 1;
    for (string_view word : SplitIntoWordsView(docs.back())) {
      auto& docids = index[word];
      if (!docids.empty() && docids.back().docid == docid) {
        ++docids.back().hitcount;
      } else {
        docids.push_back({docid, 1});
      }
    }
  }
}

const vector<InvertedIndex::Entry>& InvertedIndex::Lookup(string_view word) const {
  static const vector<Entry> empty;
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return empty;
  }
}

void UpdateIndex(istream& document_input, Synchronized<InvertedIndex>& index) {
  InvertedIndex new_index(document_input);
  swap(index.GetAccess().ref_to_value, new_index);
}

void ProcessSearches(
  istream& query_input,
  ostream& search_results_output,
  Synchronized<InvertedIndex>& index_handle
) {
  vector<size_t> docid_count;
  vector<int64_t> docids;

  for (string current_query; getline(query_input, current_query); ) {
    const auto words = SplitIntoWordsView(current_query);

    {
      auto access = index_handle.GetAccess();

      // В отличие от однопоточной версии мы должны при каждом обращении
      // к индексу изменять размер векторов docid_count и docids, потому что
      // между последовательными итерациями цикла индекс может быть изменён
      // параллельным запуском функции UpdateIndex. Соответственно в новой
      // версии базы может быть другое количество документов.
      const size_t doc_count = access.ref_to_value.GetDocuments().size();
      docid_count.assign(doc_count, 0);
      docids.resize(doc_count);

      auto& index = access.ref_to_value;
      for (const auto& word : words) {
        for (const auto& [docid, hit_count] : index.Lookup(word)) {
          docid_count[docid] += hit_count;
        }
      }
    }

    iota(docids.begin(), docids.end(), 0);
    {
      partial_sort(
        begin(docids),
        Head(docids, 5).end(),
        end(docids),
        [&docid_count](int64_t lhs, int64_t rhs) {
          return pair(docid_count[lhs], -lhs) > pair(docid_count[rhs], -rhs);
        }
      );
    }

    search_results_output << current_query << ':';
    for (size_t docid : Head(docids, 5)) {
      const size_t hit_count = docid_count[docid];
      if (hit_count == 0) {
        break;
      }

      search_results_output << " {"
          << "docid: " << docid << ", "
          << "hitcount: " << hit_count << '}';
    }
    search_results_output << '\n';
  }
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  async_tasks.push_back(async(UpdateIndex, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  async_tasks.push_back(
    async(
      ProcessSearches, ref(query_input), ref(search_results_output), ref(index)
    )
  );
}
 */
