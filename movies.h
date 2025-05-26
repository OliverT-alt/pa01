#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <vector>
using namespace std;

struct Movie {
    string title;
    double rating;
};

class MovieIndex {
public:
    // Build indexes from the raw movies list
    MovieIndex(const vector<Movie>& movies);

    // Return the indices sorted alphabetically by title
    vector<int>  getAlphaOrder() const;

    // Return the indices of all movies whose title starts with 'prefix'
    vector<int>  search(const string& prefix) const;

private:
    const vector<Movie>* moviesPtr;
    vector<string>       lowerTitles;  // all titles lowercased
    vector<int>          alphaIdx;     // 0…n-1 sorted by lowerTitles[i]
    vector<int>          ratingIdx;    // 0…n-1 sorted by movies[i].rating desc, then lowerTitles[i]
};

#endif 

