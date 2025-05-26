#include "movies.h"
#include <algorithm>
#include <cctype>
#include <numeric>  // for iota

using namespace std;

MovieIndex::MovieIndex(const vector<Movie>& movies)
  : moviesPtr(&movies)
{
    int n = movies.size();
    lowerTitles.resize(n);
    // 1) Build lowerTitles
    for (int i = 0; i < n; ++i) {
        lowerTitles[i] = movies[i].title;
        transform(lowerTitles[i].begin(),
                  lowerTitles[i].end(),
                  lowerTitles[i].begin(),
                  ::tolower);
    }

    // 2) Build alphaIdx = [0,1,...,n-1] sorted by lowerTitles[i]
    alphaIdx.resize(n);
    iota(alphaIdx.begin(), alphaIdx.end(), 0);
    sort(alphaIdx.begin(), alphaIdx.end(),
         [&](int a, int b){
             return lowerTitles[a] < lowerTitles[b];
         });

    // 3) Build ratingIdx = [0,1,...,n-1] sorted by rating desc, then title asc
    ratingIdx.resize(n);
    iota(ratingIdx.begin(), ratingIdx.end(), 0);
    sort(ratingIdx.begin(), ratingIdx.end(),
         [&](int a, int b){
             const Movie &A = (*moviesPtr)[a];
             const Movie &B = (*moviesPtr)[b];
             if (A.rating != B.rating)
                 return A.rating > B.rating;
             return lowerTitles[a] < lowerTitles[b];
         });
}

vector<int> MovieIndex::getAlphaOrder() const {
    return alphaIdx;
}

vector<int> MovieIndex::search(const string& prefix) const {
    // lowercase the prefix for case-insensitive match
    string lowP = prefix;
    transform(lowP.begin(), lowP.end(), lowP.begin(), ::tolower);

    vector<int> result;
    // scan ratingIdx in order; pick those whose lowerTitles start with lowP
    for (int idx : ratingIdx) {
        const string &lt = lowerTitles[idx];
        if (lt.size() >= lowP.size()
            && lt.compare(0, lowP.size(), lowP) == 0)
        {
            result.push_back(idx);
        }
    }
    return result;
}

