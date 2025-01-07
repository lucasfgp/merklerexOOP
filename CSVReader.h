#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();

        // this function will not rely on anything else having been created beforehand
        // So that means I can make it into a static function, 
        // and so that means that we can call it without needing to create an instance of the CSV reader before hand
        static std::vector<OrderBookEntry> readCSV(std::string csvFile);

    private:
        static std::vector<std::string> tokenise(std::string csvLine, char separator);

        // converting the vector of strings that we read out from the file 
        // into the double and the OrderBookEntry data fields

        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);


};