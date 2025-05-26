// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    // Read each file and store the name and rating
    vector<Movie> movies;
    string line, movieName;
    double movieRating;
    while (getline(movieFile, line) && parseLine(line, movieName, movieRating)) {
        movies.push_back({ movieName, movieRating });
    }

    movieFile.close();

    MovieTrie trie;
    trie.build(movies);

    if (argc == 2) {
        sort(movies.begin(), movies.end(),
             [](auto &a, auto &b){ return a.title < b.title; });
        for (auto &m : movies)
            cout << m.title << ", " << fixed << setprecision(1) << m.rating << "\n";
        return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    vector<string> bestLines;

       for (auto &prefix : prefixes) {
        // Lowercase the prefix for case-insensitive lookup
        string lower = prefix;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

        // Retrieve all matching movie indices
        vector<int> ids = trie.search(lower);
        // raw lowercased movie titles
static vector<string> lowerTitles;
if (lowerTitles.empty()) {
  lowerTitles.resize(movies.size());
  for (int i = 0; i < (int)movies.size(); ++i) {
    lowerTitles[i] = movies[i].title;
    transform(lowerTitles[i].begin(),
              lowerTitles[i].end(),
              lowerTitles[i].begin(),
              ::tolower);
  }
}

// filter out any ids whose raw title doesn’t start with 'lower'
vector<int> filtered;
filtered.reserve(ids.size());
for (int id : ids) {
  if (lowerTitles[id].rfind(lower, 0) == 0)  // starts_with in C++20
    filtered.push_back(id);
}
ids.swap(filtered);
                      

        if (ids.empty()) {
            cout << "No movies found with prefix " << prefix << "\n";
            continue;
        }

        // Build a list of Movie objects to sort by rating
        vector<Movie> matched;
        matched.reserve(ids.size());
        for (int idx : ids) {
            matched.push_back(movies[idx]);
        }

        // Sort: highest rating first; ties broken by title
        sort(matched.begin(), matched.end(),
             [](const Movie &a, const Movie &b) {
                 if (a.rating != b.rating)
                     return a.rating > b.rating;
                 return a.title < b.title;
             });

        // Print each match
        for (auto &m : matched) {
            cout << m.title << ", "
                 << fixed << setprecision(1)
                 << m.rating << "\n";
        }
        {
            ostringstream oss;
            oss << "Best movie with prefix " << prefix
                << " is: " << matched.front().title
                << " with rating " << fixed << setprecision(1)
                << matched.front().rating;
            bestLines.push_back(oss.str());
        }
         cout << "\n";
    }

    
       for (auto &bl : bestLines) {
        cout << bl << "\n";
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}