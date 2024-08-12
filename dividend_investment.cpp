#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

int main() {

    // User specific values
    double initial_investment = 5000;
    double monthly_investment = 500;
    double target_annual_dividends = 50250;

    // Stock specific values
    double initial_dividend_yield = 0.04;
    double dividend_growth_rate = 0.03;
    double stock_growth_rate = 0.05;

    // Monthly rates
    double monthly_stock_growth_rate = std::pow(1 + stock_growth_rate, 1.0/12.0) - 1;
    double monthly_dividend_growth_rate = std::pow(1 + dividend_growth_rate, 1.0/12.0) - 1;

    // Variables to keep track of the portfolio value and dividends
    double portfolio_value = initial_investment;
    double monthly_dividends = (initial_investment * initial_dividend_yield) / 12;
    double cumulative_dividends = 0;
    int months = 0;

    // Open a file to write output
    std::ofstream outfile("investment_output_data.txt");

    // Header for output table in file
    outfile << std::setw(5) << "Year" << std::setw(10) << "Month"
            << std::setw(20) << "Portfolio Value"
            << std::setw(20) << "Monthly Dividends"
            << std::setw(25) << "Cumulative Dividends" << std::endl;
    outfile << std::string(80, '-') << std::endl;

    // Simulation loop to calculate portfolio value and dividends over time
    while (monthly_dividends * 12 < target_annual_dividends) {
        portfolio_value += monthly_investment;
        portfolio_value *= (1 + monthly_stock_growth_rate);
        monthly_dividends = portfolio_value * (initial_dividend_yield * std::pow(1 + monthly_dividend_growth_rate, months)) / 12;
        portfolio_value += monthly_dividends;
        cumulative_dividends += monthly_dividends;

        // Output details for every month
        outfile << std::setw(5) << months / 12 << std::setw(10) << months % 12 + 1
                << std::setw(20) << std::fixed << std::setprecision(2) << portfolio_value
                << std::setw(20) << std::fixed << std::setprecision(2) << monthly_dividends
                << std::setw(25) << std::fixed << std::setprecision(2) << cumulative_dividends << std::endl;

        // Move to next month
        months++;
    }

    // Final output after reaching target
    outfile << "\nReached target annual dividends of " << target_annual_dividends << " euros." << std::endl;
    outfile << "Total months needed: " << months << std::endl;
    outfile << "Total time: " << months / 12 << " years and " << months % 12 << " months" << std::endl;
    outfile << "Final portfolio value: " << portfolio_value << " euros" << std::endl;
    outfile << "Final annual dividends: " << monthly_dividends * 12 << " euros" << std::endl;
    outfile << "Cumulative dividends received: " << cumulative_dividends << " euros" << std::endl;

    // Close the file
    outfile.close();

    std::cout << "Output written to investment_output.txt" << std::endl;

    return 0;
}
