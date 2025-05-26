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


/*

3a. the worst case time complexity of the trie based algorith 
m is the number of prefixes, l the maximum length of any prefix, and k is the number of movies 
matching a given prefix (up to n, the total number of movies). For each prefix the code first walk the 
trie in a runtime proportional to l(each letter stored as a node), then gather all k matches in O(k) time, and finally sort those 
k matches by rating to find highest rated in O(k log k) time. Because code perform these steps for each of the m prefixes, the 
overall worst case running time is O(m(l + klogk)).

runtimes for each csv file(from 20 to 76920) 0.00,0.00,0.02,0.32

3b. Empirical Runtimes on CSIL
the main factor for the space complexity is the number of trie 
nodes and the total indices stored(length of titles). Let n be the number of movies and l the maximum title length. 
In the worst case, each character of every title creates a distinct node, yielding O(nl) nodes. Each node
contains a fixed array of child pointers (constant space) and, at the leaves, a list of matching movie indices
summing to n across the entire trie. Thus the extra space beyond the raw storage of titles and ratings is O(nl).

3c. my algorithm was specifically designed for low time complexity, since the leader board is only based on runtime.
However, with that said, at first I didn't think about prioritizing anything, i just chose to use a sorted vector with 
binary search because of simplicity. But when i actually submitted that to gradescope, it turns out that I ranked near
the very end of the list with average runtime close to a second. Then, i searched about data structure that will run faster
especially for this kind of prefix search, and i run into the Trie data structure, which store each letter of the title as a 
node in a tree to best efficient search of prefixes. now looking up a prefix is only O(length of prefix), while previously it was
O(logn). Although i still didnt rank really high, but the improvement was significant, with avg runtime of 0.085s, which is more than
ten times faster. However, the trade off is that on top of the vector storage of titles, trie use a huge amount of nodes, each with 26 pointers
for each alphabet, and for each letter in every title there needs to be a node, so the space usage will be more than ten times more than previous application
This assignment highlighted the fact that any small operation in an algorithm can be magnified in terms of runtime
efficiency when the input is large. Different algos can perform similarily when the burden isn't that high, but for big projects, how are
data handled can really cause huge differences in efficiency.
*/


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}