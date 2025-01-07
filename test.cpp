#include <string>
#include <vector>
#include <iostream>
#include <fstream> // able to read the file

std::vector<std::string> tokenise(std::string csvLine, char separator)
{
    // string vector tokens ## stores the tokens
    std::vector<std::string> tokens;

    // int start, end ## used to delineate the position of the tokens
    signed int start, end;
    std::string token;

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

int main()
{
    std::ifstream csvFile{"20200317.csv"}; // creating an object, we have to see which constructors available to ifstream
    std::string line;
    std::vector<std::string> tokens;

    if (csvFile.is_open())
    {
        std::cout << "File open " << std::endl;

        while(std::getline(csvFile, line))
        {
            std::cout << "Read line " << line << std::endl;
            tokens = tokenise(line, ',');

            if (tokens.size() != 5) // something went wrong
            {
                std::cout << "Bad line " << std::endl;
                continue;
            }
            // we have 5 tokens

            try {
                double price = std::stod(tokens[3]); // stod convert string to double
                double amount = std::stod(tokens[4]);
                std::cout << price << ": " << amount << std::endl;

            }catch(std::exception& e){
                std::cout << "Bad float! " << tokens[3] << std::endl;
                std::cout << "Bad float! " << tokens[4] << std::endl;
                continue;
            }
        }

        // std::getline(csvFile, line); // I need to tell where I'm getting the line from and tell it where it gonna write it too


        csvFile.close();
    }
    else
    {
        std::cout << "Could not open file " << std::endl;
    }

    return 0;
}