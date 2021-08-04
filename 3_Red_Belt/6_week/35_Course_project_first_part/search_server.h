#pragma once

#include <istream>
#include <ostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>

class InvertedIndex {
public:
    void Add(const std::string& document);
    std::list<size_t> Lookup(const std::string& word) const;

    const std::string& GetDocument(size_t id) const {
        return docs[id];
    }

private:
    std::unordered_map<std::string, std::list<size_t>> index;
    std::vector<std::string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(std::istream& document_input);
    void UpdateDocumentBase(std::istream& document_input);
    void AddQueriesStream(std::istream& query_input,
                          std::ostream& search_results_output);

private:
    InvertedIndex index;
};
