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

        static std::vector<std::string> tokenise(std::string csvLine, char separator);
        static OrderBookEntry stringsToOBE(std::string price,
                                           std::string amount,
                                           std::string timestamp,
                                           std::string product, 
                                           OrderBookType orderType);

    private:


        // converting the vector of strings that we read out from the file 
        // into the double and the OrderBookEntry data fields

        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);


};