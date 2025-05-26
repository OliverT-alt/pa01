#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>
using namespace std;    

struct Movie {
    string title;
    double rating;
};

struct TrieNode {
    bool isEnd;
    vector<int> movieIds;            // indices into your movies[]
    TrieNode* children[26] = {nullptr};
    TrieNode() : isEnd(false) {}     // no more bestMovieId here
};

class MovieTrie {
public:
    MovieTrie();
    ~MovieTrie();

    // Build the trie from the full movie list
    void build(const vector<Movie>& movies);

    // Insert a lowercase title at index i
    void insert(const string& lowerTitle, int movieIndex);

    // Search by ANY-length lowercase prefix, returning all matching indices
    vector<int> search(const string& lowerPrefix) const;

private:
    TrieNode* root;
    void collectAll(TrieNode* node, vector<int>& out) const;
    void clear(TrieNode* node);
};

#endif 
