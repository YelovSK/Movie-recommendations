#include <iostream>
#include "gtest/gtest.h"
#include "4_FilmDatabase.h"

using namespace ::testing;

class FooTest : public testing::Test {
public:
    static FilmDatabase* shared_resource_ = FilmDatabase(defaultFile);
    // Per-test-suite set-up.
    // Called before the first test in this test suite.
    // Can be omitted if not needed.
    static void SetUpTestSuite() {
        shared_resource_ = new FilmDatabase(defaultFile);
    }

    static void TearDownTestSuite() {
        delete shared_resource_;
        shared_resource_ = nullptr;
    }


    // Some expensive resource shared by all tests.
    static FilmDatabase* shared_resource_;
};

FilmDatabase* FooTest::shared_resource_ = nullptr;

TEST(Database, WrongFileName) {
    FooTest::SetUpTestSuite();
    FilmDatabase db;
    try {
        FilmDatabase db("ABCD");
    } catch (ExceptionError &error) {
        ASSERT_EQ(error.getMessage(), "Unable to open file");
    }
}

TEST(Database, GenreDrama) {
    FilmDatabase database(defaultFile);
    vector<Movie> films = database.getMoviesByGenre("DRamA");
    ASSERT_EQ(films.size(), 4360);
}

TEST(Database, TagAnime) {
    FilmDatabase database(defaultFile);
    vector<Movie> anime = database.getMoviesByTag("aniME");
    ASSERT_EQ(anime.size(), 12);
}

TEST(Database, NonexistentGenre) {
    FilmDatabase database(defaultFile);
    try {
        vector<Movie> films = database.getMoviesByGenre("123");
    }
    catch (ExceptionError &error) {
        ASSERT_EQ(error.getMessage(), "Non-existent genre");
    }
}

TEST(Database, NonexistentTag) {
    FilmDatabase database(defaultFile);
    try {
        vector<Movie> films = database.getMoviesByTag("123");
    }
    catch (ExceptionError &error) {
        ASSERT_EQ(error.getMessage(), "Non-existent tag");
    }
}

TEST(Database, StringInfo) {
    FilmDatabase database(defaultFile);
    int ix = database.getMovieID("Neon Genesis Evangelion: The End of Evangelion");
    map<string, string> info = database.getMovieFromID(ix).getInfo();
    ASSERT_EQ(info["year"], "1997");
}

TEST(Database, NumOfMovies) {
    FilmDatabase database(defaultFile);
    ASSERT_EQ(database.numberOfMovies(), 9740);
}

TEST(Database, NameFromID) {
    FilmDatabase database(defaultFile);
    int ix = database.getMovieID("Neon Genesis Evangelion: The End of Evangelion");
    Movie movie = database.getMovieFromID(ix);
    ASSERT_EQ(movie.getName(), "Neon Genesis Evangelion: The End of Evangelion");
}

TEST(Database, YearFromName) {
    FilmDatabase database(defaultFile);
    Movie movie = database.getMovieFromName("Neon Genesis Evangelion: The End of Evangelion");
    ASSERT_EQ(movie.getYear(), 1997);
}

TEST(Database, movieFromName) {
    FilmDatabase database(defaultFile);
    Movie movie = database.getMovieFromName("Shawshank Redemption, The");
    ASSERT_EQ(movie.getName(), "Shawshank Redemption, The");
}

TEST(Database, movieFromNameWrong) {
    FilmDatabase database(defaultFile);
    try {
        Movie movie = database.getMovieFromName("ABCD");
    }
    catch (ExceptionError &error) {
        ASSERT_EQ(error.getMessage(), "Movie not found");
    }
}

TEST(Database, AddExistingUser) {
    FilmDatabase database(defaultFile);
    database.addUser("user");
    try {
        database.addUser("user");
    }
    catch (ExceptionError &error) {
        ASSERT_EQ(error.getMessage(), "User already exists");
    }
}

TEST(Database, GetUser) {
    FilmDatabase database(defaultFile);
    User user = database.addUser("user");
    string username = database.getUser("user").getName();
    ASSERT_EQ(username, "user");
}

TEST(Database, GetNonexistentUser) {
    FilmDatabase database(defaultFile);
    try {
        database.getUser("user").getName();
    }
    catch (ExceptionError &error) {
        ASSERT_EQ(error.getMessage(), "User not found");
    }
}