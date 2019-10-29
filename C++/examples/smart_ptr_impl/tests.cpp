// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN  
#include <catch2/catch.hpp>
#include <string>
#include <memory>
#include "shared_ptr.hpp"
#include "unique_ptr.hpp"

using namespace kotur;

TEST_CASE( "Raw_ptr and use count test", "[shared_ptr]" ) {

    SECTION("Constructing from nullptr", "[shared_ptr]" ) {
        auto sh = shared_ptr<std::string>(nullptr);
        REQUIRE( sh.get() == nullptr );
        REQUIRE( sh.use_count() == 0 );
    }

    SECTION("Use count when moving", "[shared_ptr]" )  { 
        auto sh1 = make_shared<std::string>("Hello world");
        shared_ptr<std::string> sh2 = std::move(sh1);
        REQUIRE( sh1.get() == nullptr );
        REQUIRE( sh2.get() != nullptr );
        REQUIRE( sh1.use_count() == 0 );
        REQUIRE( sh2.use_count() == 1 );
    }

    SECTION("Use count when sharing ptr", "[shared_ptr]" )  { 
        auto sh1 = make_shared<std::string>("Hello world");
        shared_ptr<std::string> sh2 = sh1;
        REQUIRE( sh1.get() == sh2.get() );
        REQUIRE( sh1.use_count() == 2 );
        REQUIRE( sh2.use_count() == 2 );
    }


    SECTION("Swap test", "[shared_ptr]" )  { 
            shared_ptr<std::string> tmp(nullptr);
            auto sh1 = make_shared<std::string>("Hello world");
            sh1.swap(tmp);
            REQUIRE( *tmp == "Hello world" );
            REQUIRE( sh1.get() == nullptr );
            REQUIRE( tmp.get() != nullptr );
            REQUIRE( sh1.use_count() == 0 );
            REQUIRE( tmp.use_count() == 1 );
    }
}

TEST_CASE( "Move construction and assignment", "[unique_ptr]" ) {

    auto un1 = make_unique<std::string>("Hello world");
    auto un2 = std::move(un1);
    
    SECTION( "Move construction test", "[unique_ptr]" ) {
        REQUIRE( un1.get() == nullptr );
        REQUIRE( un2.get() != nullptr );
    }

    auto un3 = unique_ptr<std::string>(nullptr);
    un3 = std::move(un2);

    SECTION( "Move assignment test", "[unique_ptr]" ) {
        REQUIRE( un2.get() == nullptr );
        REQUIRE( un3.get() != nullptr );
    }
}
