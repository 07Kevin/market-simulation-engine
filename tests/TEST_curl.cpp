#include <random>
#include <fstream>

#include "jsoncons/json.hpp"
#include "jsoncons/pretty_print.hpp"

#include "main.h"

#include "curl/curl.h"

#include "catch2/catch_amalgamated.hpp"


size_t WriteCallBack(void* pContents, size_t uSize, size_t uMembers, std::string* pstringResponse)
{
   pstringResponse->append((char*)pContents, uSize * uMembers);
   return uSize * uMembers;
}

TEST_CASE("Read stock data", "[read]")
{
   CURL* pCurl = curl_easy_init();
   std::string stringResponse;
   

   // settings
   
   std::string stringStock = "NVDA"; //"AAPL"; //"INVE-B.ST";
   std::string stringAPIKey = "ID3VG6TYQPW0DGMH";
   std::string stringUrl = "https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol=" + stringStock + "&apikey=" + stringAPIKey;     //     function=TIME_SERIES_INTRADAY  / "&interval=5min&apikey="

   //curl_easy_setopt(pCurl, CURLOPT_URL, "https://query2.finance.yahoo.com/v7/finance/quote?symbols=INVE-B.ST");
   curl_easy_setopt(pCurl, CURLOPT_URL, stringUrl.c_str());
   curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, WriteCallBack);
   curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &stringResponse);
   curl_easy_setopt(pCurl, CURLOPT_USERAGENT, "Mozilla/5.0");

   // curl end
   CURLcode curlcode = curl_easy_perform(pCurl);
   curl_easy_cleanup(pCurl);                                                   
   
   if( curlcode != CURLE_OK )
   {
      std::cerr << "CURL ERROR: " << curl_easy_strerror(curlcode) << std::endl;
   }
   REQUIRE(curlcode == CURLE_OK);

   // read json data

   //std::cout << stringResponse << std::endl;

   std::cout << stringResponse << std::endl;

   jsoncons::json jsonParse = jsoncons::json::parse(stringResponse);
   std::string stringPrice = jsonParse["Global Quote"]["05. price"].as<std::string>();

   std::cout << "current price: " << stringPrice << std::endl;

}