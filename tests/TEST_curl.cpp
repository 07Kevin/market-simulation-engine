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
   curl_easy_setopt(pCurl, CURLOPT_URL, "https://query1.finance.yahoo.com/v7/finance/quote?symbols=INVE-B.ST");
   curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, WriteCallBack);
   curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &stringResponse);
   curl_easy_setopt(pCurl, CURLOPT_USERAGENT, "Mozilla/5.0");

   // curl end
   CURLcode curlcode = curl_easy_perform(pCurl);
   curl_easy_cleanup(pCurl);

   // read json data

   std::cout << stringResponse << std::endl;

   //jsoncons::json jsonParse = jsoncons::json::parse(stringResponse);

}