#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "anagram.h"

TEST_CASE("recognizes shuffled alphabets as anagrams") {
    REQUIRE(Anagram::WordPairIsAnagram("restful", "fluster") == true);
    REQUIRE(Anagram::WordPairIsAnagram("forty five", "over fifty") == true);
}

TEST_CASE("reports non-anagrams") {
    REQUIRE(Anagram::WordPairIsAnagram("something", "else") == false);
}

TEST_CASE("recognizes anagrams when there are case- and space- differences") {
    REQUIRE(Anagram::WordPairIsAnagram("New York Times", "monkeys write")
        == true);
}

TEST_CASE("selects anagrams of a word") {
    auto selection = Anagram::SelectAnagrams("master",
        {"stream", "something", "maters"});
    REQUIRE(selection == std::vector<std::string>{"stream", "maters"});
}
