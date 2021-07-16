#ifndef HODNOTENIEFILMOV_FILMDATABASE_H
#define HODNOTENIEFILMOV_FILMDATABASE_H
#include "1_Movie.h"
#include "3_User.h"
#include <fstream>
#include <sstream>
#include "ExceptionError.h"
#include <algorithm>

const string defaultFile = "../Database.csv";

class FilmDatabase {
    static const inline string noGenre = "(no genres listed)";
    static const inline string noTag = "NoTags";
    const int yearInStringPos = 5;
    const int nameInStringPos = 7;
    AVL<Movie> movies;
    map<string, vector<Movie>> genresMap;   // genresMap["genre"] = [movie1, movie2]
    map<string, vector<Movie>> tagsMap;     // tagsMap["tag"] = [movie1, movie2]
    set<User> users;
    map<int, Movie> moviesByID;
public:
    FilmDatabase() = default;
    explicit FilmDatabase(const string &fileName);
    static vector<vector<string>> readDatabase(const string &fileName);
    AVL<Movie> getMovies() {return movies;};
    int numberOfMovies() {return movies.getSize();};
    Movie getMovieFromID(const int &id) {return moviesByID[id];};
    Movie getMovieFromName(const string &name);
    void addMovie(int id, const string &name, const string &genres, const string &tags);
    void addAllMovies(const vector<vector<string>> &movies);
    pair<string, int> formatNameYear(const string &input) const;
    void fillGenresTagsMap();
    map<string, vector<Movie>> getMovieGenres() {return genresMap;};
    map<string, vector<Movie>> getMovieTags() {return tagsMap;};
    vector<Movie> getMoviesByGenre(const string &genre);
    vector<Movie> getMoviesByTag(const string &tag);
    User addUser(const string &name);
    User getUser(const string &name);
    int getMovieID(const string &name);
    static vector<string> split(const string &str, char delim);
    static string lower(const string &x);
    static void insertionSort(vector<string> &arr);
};


#endif //SEMESTRALNY_PROJEKT_FILMDATABASE_H
