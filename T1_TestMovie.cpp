#include <iostream>
#include "gtest/gtest.h"
#include "1_Movie.h"

using namespace ::testing;

const vector<string> genres = {"drama", "comedy"};
const vector<string> tags = {"long", "emotional"};
string name = "name";

TEST(Movie, Name) {
    Movie movie(1, name, 2021, genres, tags);
    ASSERT_EQ(movie.getName(), "name");
}

TEST(Movie, SetID) {
    Movie movie;
    movie.setId(10);
    ASSERT_EQ(movie.getId(), 10);
}

TEST(Movie, Empty) {
    Movie movie;
    ASSERT_EQ(movie.empty(), true);
}

TEST(Movie, LessThanOperator) {
    string n = "abc";
    Movie movie(1, name, 2021, genres, tags);
    Movie movieComp(1, n, 2021, genres, tags);
    ASSERT_EQ(movieComp < movie, true);
}

TEST(Movie, LessThanOperatorSameName) {
    Movie movie(2, name, 2021, genres, tags);
    Movie movieComp(1, name, 2021, genres, tags);
    ASSERT_EQ(movieComp < movie, true);
}

TEST(Movie, LessThanOperatorString) {
    Movie movie(2, name, 2021, genres, tags);
    string n = "z";
    ASSERT_EQ(movie < n, true);
}

TEST(Movie, GetGenres) {
    Movie movie(2, name, 2021, genres, tags);
    ASSERT_EQ(movie.getGenres()[0], "drama");
}

TEST(Movie, GetInfoGenres) {
    Movie movie(2, name, 2021, genres, tags);
    ASSERT_EQ(movie.getInfo()["genres"], "drama, comedy");
}