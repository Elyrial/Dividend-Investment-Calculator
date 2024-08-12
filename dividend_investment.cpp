#include <iostream>
#include <cmath>

int main() {
    // User specific values
    double initial_investment = 5000.0;
    double monthly_investment = 500.0;
    double target_annual_dividends = 50250.0; // Average yearly salary in Germany according to stepstone (2024)

    // Stock specific values
    double initial_dividend_yield = 0.04; // Average initial dividend yield (4%)
    double dividend_growth_rate = 0.05;
    double stock_growth_rate = 0.07;

    // Variables to keep track of the portfolio value and dividends
    double portfolio_value = initial_investment;
    double annual_dividends = initial_investment * initial_dividend_yield;
    int year = 0;
    
    while (annual_dividends < target_annual_dividends) {
        
        portfolio_value += monthly_investment * 12;

        portfolio_value *= (1 + stock_growth_rate);

        annual_dividends = portfolio_value * (initial_dividend_yield * std::pow(1 + dividend_growth_rate, year));

        portfolio_value += annual_dividends;

        year++;
    }

    // Output the results
    std::cout << "Years needed: " << year << std::endl;
    std::cout << "Final portfolio value: " << portfolio_value << " euros" << std::endl;
    std::cout << "Final annual dividends: " << annual_dividends << " euros" << std::endl;

    return 0;
}
