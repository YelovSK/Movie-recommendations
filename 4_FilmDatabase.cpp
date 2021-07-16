#include "4_FilmDatabase.h"

using namespace std;

vector<string> FilmDatabase::split(const string &str, char delim) {
    vector<string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim))
        result.push_back(token);
    return result;
}

string FilmDatabase::lower(const string &x) {
    string res;
    for (const auto &c : x) {
        if (c >= 65 && c <= 90) res += c + ' ';
        else res += c;
    }
    return res;
}

void FilmDatabase::insertionSort(vector<string> &arr) {
    int n = arr.size();
    string key;
    int j;
    for (auto i = 1; i < n; ++i) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && lower(arr[j]) > lower(key)) {
            swap(arr[j+1], arr[j]);
            j--;
        }
    }
}

FilmDatabase::FilmDatabase(const string &fileName) {
    addAllMovies(readDatabase(fileName));
    fillGenresTagsMap();
}

vector<vector<string>> FilmDatabase::readDatabase(const string &fileName) { // predpokladam, ze subor je v spravnom formate
    ifstream file;
    file.open(fileName);
    vector<vector<string>> lines;
    string id; string name; string genres; string tags;
    if (!file) {
        throw ExceptionError("Unable to open file");
    }
    string line;
    while (getline(file, line)) {
        vector<string> movieData = split(line, ';');
        movieData[movieData.size()-1] = movieData[movieData.size()-1].substr(0, movieData[movieData.size()-1].size()-1);
        lines.push_back(movieData);
    }
    file.close();
    return lines;
}

void FilmDatabase::addAllMovies(const vector<vector<string>> &moviesVector) {
    int id = 0;
    for (const auto & movie : moviesVector) {
        addMovie(id, movie[0], movie[1], movie[2]);
        id++;
    }
}

void FilmDatabase::addMovie(int id, const string &name, const string &genres, const string &tags) {
    auto[newName, year] = formatNameYear(name);     // c++17
    vector<string> newGenres = split(genres, '|');
    vector<string> newTags = split(tags, '|');
    if (newTags[0] != noTag) insertionSort(newTags);
//    insertionSort(newGenres);   //uz su usporiadane v subore
    Movie movie(id, newName, year, newGenres, newTags);
    movies.insert(movie);
    moviesByID[id] = movie;
}

pair<string, int> FilmDatabase::formatNameYear(const string &input) const {
    string name;
    string year;
    for (auto i = input.length()-yearInStringPos; i < input.length()-1; ++i) {
        year += input[i];
    }
    for (auto i = 0; i < input.length()-nameInStringPos; ++i) {
        name += input[i];
    }
    return make_pair(name, stoi(year));
}

void FilmDatabase::fillGenresTagsMap() {
    for (const auto & movie : movies.list()) {
        for (const auto & genre : movie.getGenres()) {
            if (genre != noGenre) genresMap[genre].push_back(movie);
        }
        for (const auto & tag : movie.getTags()) {
            if (tag != noTag) tagsMap[tag].push_back(movie);
        }
    }
}

vector<Movie> FilmDatabase::getMoviesByGenre(const string &genre) {
    string genreCopy = lower(genre);
    genreCopy[0] = toupper(genreCopy[0]);
    if (genresMap[genreCopy].empty()) throw ExceptionError("Non-existent genre");
    vector<Movie> output;
    for (const auto & movie : genresMap[genreCopy]) {
        output.push_back(movie);
    }
    return output;
}

vector<Movie> FilmDatabase::getMoviesByTag(const string &tag) {
    string tagCopy = lower(tag);
    if (tagsMap[tagCopy].empty()) throw ExceptionError("Non-existent tag");
    vector<Movie> output;
    for (const auto & movie : tagsMap[tagCopy]) {
        output.push_back(movie);
    }
    return output;
}

User FilmDatabase::addUser(const string &name) {
    User user = User(name, tagsMap, genresMap);
    if (users.insert(user).second) return user;
    throw ExceptionError("User already exists");
}

Movie FilmDatabase::getMovieFromName(const string &name) {
    Movie res = movies.find(name);
    if (!res.empty()) return res;
    throw ExceptionError("Movie not found");
}

User FilmDatabase::getUser(const string &name) {
    for (const auto &user : users) {
        if (user.getName() == name) return user;
    }
    throw ExceptionError("User not found");
}

int FilmDatabase::getMovieID(const string &name) {
    for (const auto &movie : getMovies().list()) {
        if (movie.getName() == name) return movie.getId();
    }
    return -1;
}
