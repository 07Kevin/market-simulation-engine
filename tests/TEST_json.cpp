#include <random>
#include <fstream>

#include "jsoncons/json.hpp"
#include "jsoncons/pretty_print.hpp"

#include "main.h"

#include "catch2/catch_amalgamated.hpp"

using jsoncons::json;

TEST_CASE("Read JSON file", "[read]")
{
   std::cout << "Test" ;
   std::ifstream ifstreamFile("D:/temp/resources/json_test/test.json");

   if( !ifstreamFile )
   {
      std::cout << "failed to open file\n";
      return;
   }

   json jsonParse = json::parse(ifstreamFile);
   ifstreamFile.close();

   std::string stringName = jsonParse["name"].as<std::string>();

   std::cout << stringName << std::endl;

   // iterate through object
   for( const auto& address_ : jsonParse["address"].object_range() )
   {
      std::string stringKey = address_.key();
      std::string stringValue = address_.value().as<std::string>();

      std::cout << stringKey << " = " << stringValue << std::endl;;
   }
}

TEST_CASE("Write JSON file", "[write]")
{
   std::ifstream ifstreamFile("D:/temp/resources/json_test/test.json");

   if( !ifstreamFile )
   {
      std::cout << "failed to open file\n";
      return;
   }

   json jsonParse = json::parse(ifstreamFile);
   ifstreamFile.close();

   jsonParse["name"] = "Lexus";       // change existing value
   jsonParse["language"] = "Swedish"; // add value

   std::ofstream ofstreamFile("D:/temp/resources/json_test/test.json");
   ofstreamFile << jsoncons::pretty_print(jsonParse);
   ofstreamFile.close();
}