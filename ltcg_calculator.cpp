#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>

// Class to represent inflation rates
class InflationRate {
public:
    InflationRate(const std::string& year, double growth, double inflation)
        : year(year), growth(growth), inflation(inflation) {}

    std::string getYear() const { return year; }
    double getGrowth() const { return growth; }
    double getInflation() const { return inflation; }

private:
    std::string year;
    double growth;
    double inflation;
};

// Class to handle inflation data and calculations
class InflationCalculator {
public:
    InflationCalculator(const std::vector<InflationRate>& rates) : rates(rates) {}

    double calculateSellingPrice(const std::string& initialYear, const std::string& sellYear, double initialPrice) const {
        auto startIt = findRateByYear(initialYear);
        auto endIt = findRateByYear(sellYear);

        if (startIt == rates.end() || endIt == rates.end() || startIt > endIt) {
            throw std::invalid_argument("Invalid year range");
        }

        double price = initialPrice;
        for (auto it = startIt; it <= endIt; ++it) {
            price *= (1 + it->getGrowth() / 100);
        }

        return price;
    }

    double calculateActualProfit(double initialPrice, double sellingPrice, const std::string& initialYear, const std::string& sellYear) const {
        auto startIt = findRateByYear(initialYear);
        auto endIt = findRateByYear(sellYear);

        if (startIt == rates.end() || endIt == rates.end() || startIt > endIt) {
            throw std::invalid_argument("Invalid year range");
        }

        double adjustedPrice = initialPrice;
        for (auto it = startIt; it <= endIt; ++it) {
            adjustedPrice *= (1 + it->getInflation() / 100);
        }

        return sellingPrice - adjustedPrice;
    }

private:
    std::vector<InflationRate> rates;

    std::vector<InflationRate>::const_iterator findRateByYear(const std::string& year) const {
        for (auto it = rates.begin(); it != rates.end(); ++it) {
            if (it->getYear().substr(0, 4) == year) {
                return it;
            }
        }
        return rates.end();
    }
};

// Class to represent a tax rate
class TaxRate {
public:
    TaxRate(double rate) : rate(rate) {}

    double apply(double amount) const {
        return amount * rate;
    }

private:
    double rate;
};

// Function to read and parse CSV file
std::vector<InflationRate> readCSV(const std::string& filePath) {
    std::vector<InflationRate> csvData;
    std::ifstream file(filePath);
    std::string line, year;
    double growth, inflation;

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::getline(iss, year, ',');
        iss >> growth;
        iss.ignore(1); // ignore comma
        iss >> inflation;
        csvData.emplace_back(year, growth, inflation);
    }

    return csvData;
}

int main() {
    std::string initialYear = "2010"; // Property purchase year
    std::string sellYear;
    double initialPrice = 5000000; // Initial price in INR (50 lakhs)
    std::string csvFilePath = "price-inflation.csv";

    std::cout << "Enter the year of selling: ";
    std::cin >> sellYear;

    try {
        auto csvData = readCSV(csvFilePath);
        InflationCalculator inflationCalculator(csvData);
        TaxRate oldTaxRate(0.20); // 20% tax rate with inflation adjustment
        TaxRate newTaxRate(0.125); // 12.5% tax rate without inflation adjustment

        double sellingPrice = inflationCalculator.calculateSellingPrice(initialYear, sellYear, initialPrice);

        // Old scheme
        double oldActualProfit = inflationCalculator.calculateActualProfit(initialPrice, sellingPrice, initialYear, sellYear);
        double oldLtcgTax = oldTaxRate.apply(oldActualProfit);

        // New scheme
        double newProfit = sellingPrice - initialPrice;
        double newLtcgTax = newTaxRate.apply(newProfit);

        // Output results
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Estimated Selling Price: Rs " << sellingPrice << std::endl;
        std::cout << "LTCG Tax to be Paid (Old Scheme 20% with inflation adjustment): Rs " << oldLtcgTax << std::endl;
        std::cout << "LTCG Tax to be Paid (New Scheme 12.5% without inflation adjustment): Rs " << newLtcgTax << std::endl;

        // Compare and output the difference
        double taxDifference = std::abs(oldLtcgTax - newLtcgTax);

        if (oldLtcgTax > newLtcgTax) {
            std::cout << "Old scheme leads to higher taxes by Rs " << taxDifference << std::endl;
        } else if (newLtcgTax > oldLtcgTax) {
            std::cout << "New scheme leads to higher taxes by Rs " << taxDifference << std::endl;
        } else {
            std::cout << "Both schemes lead to the same tax amount." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
