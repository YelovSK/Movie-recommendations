#include <iostream>
#include "gtest/gtest.h"
#include "4_FilmDatabase.h"

using namespace ::testing;

TEST(User, AddUser) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    Movie movie = database.getMovieFromName("Neon Genesis Evangelion: The End of Evangelion");
    user.addRating(movie, 5);
    ASSERT_EQ(user.getName(), "user");
}

TEST(User, AddRating) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    Movie movie = database.getMovieFromName("Neon Genesis Evangelion: The End of Evangelion");
    user.addRating(movie, 5);
    ASSERT_EQ(user.getRatings()[0].first, movie);
}

TEST(User, RatingInvalidScore) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    Movie movie = database.getMovieFromName("Neon Genesis Evangelion: The End of Evangelion");
    try {
        user.addRating(movie, 123);
    }
    catch (ExceptionError &error) {
        ASSERT_EQ(error.getMessage(), "Invalid score");
    }
}

TEST(User, GenreRatings) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    Movie movie = database.getMovieFromName("Neon Genesis Evangelion: The End of Evangelion");
    user.addRating(movie, 5);
    int rating = user.getGenreRatings()["Drama"];
    ASSERT_EQ(rating, 2);
}

TEST(User, TagRatings) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    Movie movie = database.getMovieFromName("Neon Genesis Evangelion: The End of Evangelion");
    user.addRating(movie, 5);
    int rating = user.getTagRatings()["psychology"];
    ASSERT_EQ(rating, 3);
}

TEST(User, NumberOfRecommendations) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    Movie movie1 = database.getMovieFromName("Neon Genesis Evangelion: The End of Evangelion");
    Movie movie2 = database.getMovieFromName("Doom");
    user.addRating(movie1, 5);
    user.addRating(movie2, 3);
    vector<Movie> recommendations = user.getRecommendations(5);
    ASSERT_EQ(recommendations.size(), 5);

}

TEST(User, printRecommendations) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    user.addRating(database.getMovieFromName("Lion King, The"), 5);
    user.addRating(database.getMovieFromName("Aladdin"), 5);
    string recommendation = user.textRecommendations(1);
    ASSERT_EQ(recommendation, "101 Dalmatians (One Hundred and One Dalmatians) (1961)");    // disney
}

TEST(User, printRecommendations2) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    user.addRating(database.getMovieFromName("Revenant, The"), 5);
    user.addRating(database.getMovieFromName("Catch Me If You Can"), 5);
    user.addRating(database.getMovieFromName("Departed, The"), 5);
    user.addRating(database.getMovieFromName("Blood Diamond"), 5);
    user.addRating(database.getMovieFromName("Inception"), 5);
    user.addRating(database.getMovieFromName("Shutter Island"), 5);
    string recommendation = user.textRecommendations(1);
    ASSERT_EQ(recommendation, "Basketball Diaries, The (1995)");    // vo vsetkych filmoch hra DiCaprio
}