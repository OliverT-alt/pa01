#include "movies.h"
#include <algorithm>
#include <cctype>

using namespace std;

//construct trie
MovieTrie::MovieTrie() {
    root = new TrieNode();
}

//destructor
MovieTrie::~MovieTrie() {
    clear(root);
}

void MovieTrie::clear(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 26; ++i)
        clear(node->children[i]);
    delete node;
}

//load movie list into trie
void MovieTrie::build(const vector<Movie>& movies) {
    for (int i = 0; i < (int)movies.size(); ++i) {
        string lower = movies[i].title;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        insert(lower, i);
    }
}

//insert each letter from the title as a node
void MovieTrie::insert(const string& lowerTitle, int movieIndex) {
    TrieNode* cur = root;
    for (char ch : lowerTitle) {
        if (ch < 'a' || ch > 'z') continue;
        int idx = ch - 'a';
        if (!cur->children[idx])
            cur->children[idx] = new TrieNode();
        cur = cur->children[idx];
    }
    cur->isEnd = true;
    cur->movieIds.push_back(movieIndex);
}

//search for titles
vector<int> MovieTrie::search(const string& lowerPrefix) const {
    TrieNode* cur = root;
    for (char ch : lowerPrefix) {
        if (ch < 'a' || ch > 'z') return {};       
        cur = cur->children[ch - 'a'];
        if (!cur) return {};                       
    }
    vector<int> results;
    collectAll(cur, results);
    return results;
}

//collect the complete title
void MovieTrie::collectAll(TrieNode* node, vector<int>& out) const {
    if (!node) return;
    if (node->isEnd) {
        out.insert(out.end(), node->movieIds.begin(), node->movieIds.end());
    }
    for (int i = 0; i < 26; ++i)
        collectAll(node->children[i], out);
}
