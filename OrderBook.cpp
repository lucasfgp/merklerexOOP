#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <unordered_map>

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    std::map<std::string, bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }

    // now flatten the map to a vector of strings

    for (auto const& e : prodMap)
    {
        products.push_back(e.first); // e.first is the key of the map
    }


    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                              std::string product,
                                              std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e : orders)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp)
            {
                orders_sub.push_back(e);
            }
    }
    return orders_sub;
}
std::vector<OrderBookEntry> OrderBook::getOrdersTest(OrderBookType type,
                                              std::string product,
                                              std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    int count = 0;
    for(OrderBookEntry& e : orders)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp)
            {
                orders_sub.push_back(e);
                count++;

                if(count == 10)
                {
                    break;
                }
            }
    }
    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if(e.price > max)max = e.price;

    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if(e.price < min)min = e.price;

    }
    return min;
}

double OrderBook::getAvgPrice(std::vector<OrderBookEntry>& orders)
{
    double avg;
    double price_sum = 0;
    for (OrderBookEntry& e : orders)
    {
        price_sum+= e.price;
    }
    return price_sum/orders.size();
}

// double OrderBook::getVolumePrice(std::vector<OrderBookEntry>& orders)
// {
//     double targetPrice;
//     double totalVolume = 0;

//     for (OrderBookEntry& e : orders)
//     {
//         if(e.price = targetPrice) {
//             totalVolume += e.amount;
//         }
//     }
//     return totalVolume;
// }

double OrderBook::getWeightedAvgPrice(std::vector<OrderBookEntry>& orders)
{
    double sum_price_volume = 0;
    double sum_volume = 0;
    double avg;
    double p, v;


    for (OrderBookEntry& e : orders)
    {
        p = e.price;
        v = e.amount;

        sum_price_volume+= (p * v);
        sum_volume+= v;
    }

    double wavp = sum_price_volume / sum_volume;
    return wavp;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for(OrderBookEntry& e : orders)
    {
        if(e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if(next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}