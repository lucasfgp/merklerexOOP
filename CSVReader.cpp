#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename}; // creating an object, we have to see which constructors available to ifstream
    std::string line; // temporary place to store the line

    if(csvFile.is_open())
    {
        while(std::getline(csvFile, line))
        {
            try {
            OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
            entries.push_back(obe);
            }catch(const std::exception& e)
            {
                std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
            }
        }
    }

    
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    // string vector tokens ## stores the tokens
    std::vector<std::string> tokens;

    // int start, end ## used to delineate the position of the tokens
    signed int start, end;
    std::string token; // variable to store temporary token

    // start = csvLine.find_first_not_of(separator) 
    start = csvLine.find_first_not_of(separator, 0); // starting at position 0

    do{
        end = csvLine.find_first_of(separator, start);
        if(start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);

        start = end + 1;
    }while(end != std::string::npos); // the most correct test because find_first_not_of return npos if it does not find the search term.
    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{

    // we saw a combination of techniques here. 
    // Catching the exception to make it clear that something went wrong, 
    // then throwing the exception to the calling function 
    // so it can decide what to do as it knows better the context. 

    double price, amount;

    if (tokens.size() != 5) // something went wrong
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens

    try {
        price = std::stod(tokens[3]); // stod convert string to double
        amount = std::stod(tokens[4]);
    }catch(const std::exception& e){
        std::cout << "Bad float! " << tokens[3] << std::endl;
        std::cout << "Bad float! " << tokens[4] << std::endl;
        throw;
    }

    OrderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType)
{
    double price, amount;
    try {
        price = std::stod(priceString); // stod convert string to double
        amount = std::stod(amountString);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString << std::endl;
        throw;
    }

    OrderBookEntry obe{price,
                    amount,
                    timestamp,
                    product,
                    orderType};

    return obe;
}