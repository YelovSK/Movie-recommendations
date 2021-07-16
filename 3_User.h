#ifndef HODNOTENIEFILMOV_USER_H
#define HODNOTENIEFILMOV_USER_H
#include <string>
#include <iostream>
#include <vector>
#include <set>
#include "1_Movie.h"
#include "2_AVL.h"
#include "ExceptionError.h"

class User {
    map<string, int> genreRatings;   // ["zaner"] = skore
    map<string, int> tagRatings; // ["tag"] = skore
    string username;
    vector<pair<Movie, int>> ratings; // (id, score)
    map<string, vector<Movie>> genresMap;   // genresMap["genre"] = [movie1, movie2]
    map<string, vector<Movie>> tagsMap;     // tagsMap["tag"] = [movie1, movie2]
public:
    User(const string &name, const map<string, vector<Movie>> &tags,
         const map<string, vector<Movie>> &genres);
    bool operator<(const User &a) const {return username < a.username;};
    pair<Movie, int> addRating(Movie movie, int score);
    vector<pair<Movie, int>> getRatings() {return ratings;};
    map<string, int> getGenreRatings() {return genreRatings;};
    map<string, int> getTagRatings() {return tagRatings;};
    string getName() const {return username;};
    set<Movie> getRatedMovies();
    vector<Movie> getRecommendations(int numberOfMovies);
    string textRecommendations(int numberOfMovies);
};


#endif //HODNOTENIEFILMOV_USER_H
