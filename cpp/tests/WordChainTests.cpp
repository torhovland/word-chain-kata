#include "CppUTest/TestHarness.h"
#include "../WordChain.h"

TEST_GROUP(WordChainGroup)
{
    set<string>* dict = new set<string>;

    void setup()
    {
        dict->insert("boo");
        dict->insert("foo");
        dict->insert("fox");
    }
};

TEST(WordChainGroup, Empty)
{
    auto chain = WordChain::create(dict, "", "");
    CHECK_EQUAL(0, chain.getLength());
}

TEST(WordChainGroup, OneEmpty)
{
    auto chain = WordChain::create(dict, "foo", "");
    CHECK_EQUAL(0, chain.getLength());
}

TEST(WordChainGroup, Equal)
{
    auto chain = WordChain::create(dict, "foo", "foo");
    CHECK_EQUAL(1, chain.getLength());

    auto words = chain.getWords();
    CHECK_EQUAL("foo", words[0]);
}

TEST(WordChainGroup, DifferentLength)
{
    auto chain = WordChain::create(dict, "foo", "foox");
    CHECK_EQUAL(0, chain.getLength());
}

TEST(WordChainGroup, NotInDictionary)
{
    auto chain = WordChain::create(dict, "foox", "foox");
    CHECK_EQUAL(0, chain.getLength());
}

TEST(WordChainGroup, OneStep)
{
    auto chain = WordChain::create(dict, "foo", "fox");
    CHECK_EQUAL(2, chain.getLength());

    auto words = chain.getWords();
    CHECK_EQUAL("foo", words[0]);
    CHECK_EQUAL("fox", words[1]);
}

TEST(WordChainGroup, TwoSteps)
{
    auto chain = WordChain::create(dict, "boo", "fox");
    CHECK_EQUAL(3, chain.getLength());

    auto words = chain.getWords();
    CHECK_EQUAL("boo", words[0]);
    CHECK_EQUAL("foo", words[1]);
    CHECK_EQUAL("fox", words[2]);
}


