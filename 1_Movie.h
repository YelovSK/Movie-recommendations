#include <iostream>
#include <vector>
#include <map>
#ifndef HODNOTENIEFILMOV_MOVIES_H
#define HODNOTENIEFILMOV_MOVIES_H
using namespace std;

class Movie {
    int id = -1;
    string name;
    int year;
    vector<string> genres;
    vector<string> tags;
public:
    Movie() = default;
    Movie(int newId, const string &newName, int newYear, const vector<string> &newGenres, const vector<string> &newTags);
    bool operator<(const Movie &a) const {
        if (name == a.getName()) return id < a.getId();
        else return name < a.getName();
    };
    bool operator>(const Movie &a) const {return !operator<(a);};
    bool operator==(const Movie &a) const {return id == a.id;};
    bool operator<(const string &a) const {return name < a;};
    bool operator>(const string &a) const {return name > a;};
    bool operator==(const string &a) const {return name == a;};
    bool operator!=(const Movie& a) const {return !operator==(a); }
    friend ostream & operator << (ostream &out, const Movie &a);
    void setId(const int newId) {id = newId;};
    int getId() const {return id;};
    int getYear() const {return year;};
    bool empty() const {return id == -1;};
    string getName() const {return name;};
    map<string, string> getInfo() const;
    vector<string> getGenres() const;
    vector<string> getTags() const;
};

#endif //SEMESTRALNY_PROJEKT_MOVIES_H
