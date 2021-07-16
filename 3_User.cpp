#include "3_User.h"

User::User(const string &name, const map<string, vector<Movie>> &tags,
           const map<string, vector<Movie>> &genres) {
    tagsMap = tags;
    genresMap = genres;
    username = name;
}

pair<Movie, int> User::addRating(Movie movie, int score) {
    if (score < 0 || score > 5) throw ExceptionError("Invalid score");
    pair<Movie, int> rating(movie, score);
    ratings.emplace_back(rating);
    for (const auto &genre : movie.getGenres()) {
        if (!genreRatings[genre]) genreRatings[genre] = score - 3;
        else genreRatings[genre] += (score - 3) * 0.25;
    }
    for (const auto &tag : movie.getTags()) {
        if (!tagRatings[tag]) tagRatings[tag] = (score - 3) * 1.5;    // tagy maju vacsiu vahu ako zanre
        else tagRatings[tag] += (score - 3) * 0.5;   // viac hodnoteni rovnakeho ma mensiu vahu
    }
    return rating;
}

vector<Movie> User::getRecommendations(int numberOfMovies) {
    map<Movie, int> movieScores;
    set<string> wentThrough;
    for (const auto &genre : genreRatings) {
        for (const auto &movie : genresMap[genre.first]) {
            if (!getRatedMovies().count(movie) && wentThrough.count(genre.first) == 0) {
                wentThrough.insert(genre.first);
                movieScores[movie] += genre.second * genre.second;  // mocnina aby zanre/tagy s najvyssim skore boli najviac relevantne
            }
        }
    }
    for (const auto &tag : tagRatings) {
        for (const auto &movie : tagsMap[tag.first]) {
            if (!getRatedMovies().count(movie) && wentThrough.count(tag.first) == 0) {
                wentThrough.insert(tag.first);
                movieScores[movie] += tag.second * tag.second;
            }
        }
    }

    vector<Movie> recommendations;
    multimap<int, Movie> msMultimap;

    for(const auto &score : movieScores) {
        msMultimap.insert(make_pair(score.second, score.first));    // aby bola mapa usporiadana podla hodnoteni (kluc)
    }
    for (auto movie = msMultimap.rbegin(); movie != msMultimap.rend(); movie++ ) {
        recommendations.push_back(movie->second);
        if (recommendations.size() == numberOfMovies) break;
    }

    return recommendations;
}

set<Movie> User::getRatedMovies() {
    set<Movie> res;
    for (const auto &rating : ratings) {
        res.insert(rating.first);
    }
    return res;
}

string User::textRecommendations(int numberOfMovies) {
    vector<Movie> recommendations = getRecommendations(numberOfMovies);
    string res;
    for (auto &movie : recommendations) {
        res += movie.getName() + " (" + to_string(movie.getYear()) + ')' + '\n';
    }
    res = res.substr(0, res.size()-1);
    return res;
}
