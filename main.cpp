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

    MovieIndex index(movies);

    // 3) Part 1: no prefix file → print all alphabetically
    if (argc == 2) {
        for (int idx : index.getAlphaOrder()) {
            const auto &m = movies[idx];
            cout << m.title << ", "
                 << fixed << setprecision(1)
                 << m.rating << "\n";
        }
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
        auto ids = index.search(prefix);
        if (ids.empty()) {
            cout << "No movies found with prefix " << prefix << "\n";
            continue;  // no blank line after a no-match
        }

        // print each in rating order
        for (int idx : ids) {
            const auto &m = movies[idx];
            cout << m.title << ", "
                 << fixed << setprecision(1)
                 << m.rating << "\n";
        }
        cout << "\n";  // blank line *only* after a match block

        // store the best-movie line
        {
            ostringstream oss;
            const auto &b = movies[ids.front()];
            oss << "Best movie with prefix " << prefix
                << " is: " << b.title
                << " with rating " << fixed << setprecision(1)
                << b.rating;
            bestLines.push_back(oss.str());
        }
    }

    // 6) Print all "Best movie..." lines at the very end
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