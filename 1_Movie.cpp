#include "1_Movie.h"

#include <utility>

Movie::Movie(int newId, const string &newName, int newYear, const vector<string> &newGenres, const vector<string> &newTags) {
    id = newId;
    name = newName;
    year = newYear;
    genres = newGenres;
    tags = newTags;
}

map<string, string> Movie::getInfo() const {
    map<string, string> info;
    info["id"] = to_string(getId());
    info["name"] = getName();
    info["year"] = to_string(getYear());
    info["id"] = to_string(id);
    string genresString; string tagsString;
    int i = 0;
    for (const string &genre : getGenres()) {
        genresString += genre;
        if (i < getGenres().size()-1) genresString += ", ";
        i++;
    }
    i = 0;
    info["genres"] = genresString;
    for (const string &tag : getTags()) {
        tagsString += tag;
        if (i < getTags().size()-1) tagsString += ", ";
        i++;
    }
    info["tags"] = tagsString;
    return info;
}

vector<string> Movie::getGenres() const {
    return genres;
}

vector<string> Movie::getTags() const {
    return tags;
}

ostream &operator<<(ostream &out, const Movie &a) {
    out << a.name << " (" << a.year << ')';
    return out;
}