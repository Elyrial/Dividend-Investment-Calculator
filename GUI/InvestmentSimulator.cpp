#include "InvestmentSimulator.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <cmath>
#include <iomanip>

InvestmentSimulator::InvestmentSimulator(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Input Fields
    initialInvestmentEdit = new QLineEdit(this);
    initialInvestmentEdit->setPlaceholderText("Initial Investment");
    layout->addWidget(initialInvestmentEdit);

    monthlyInvestmentEdit = new QLineEdit(this);
    monthlyInvestmentEdit->setPlaceholderText("Monthly Investment");
    layout->addWidget(monthlyInvestmentEdit);

    targetAnnualDividendsEdit = new QLineEdit(this);
    targetAnnualDividendsEdit->setPlaceholderText("Target Annual Dividends");
    layout->addWidget(targetAnnualDividendsEdit);

    initialDividendYieldEdit = new QLineEdit(this);
    initialDividendYieldEdit->setPlaceholderText("Initial Dividend Yield");
    layout->addWidget(initialDividendYieldEdit);

    dividendGrowthRateEdit = new QLineEdit(this);
    dividendGrowthRateEdit->setPlaceholderText("Dividend Growth Rate");
    layout->addWidget(dividendGrowthRateEdit);

    stockGrowthRateEdit = new QLineEdit(this);
    stockGrowthRateEdit->setPlaceholderText("Stock Growth Rate");
    layout->addWidget(stockGrowthRateEdit);

    // Button to Run Simulation
    QPushButton *simulateButton = new QPushButton("Run Simulation", this);
    layout->addWidget(simulateButton);
    connect(simulateButton, &QPushButton::clicked, this, &InvestmentSimulator::runSimulation);

    // Text area for results
    resultTextEdit = new QTextEdit(this);
    layout->addWidget(resultTextEdit);
}

void InvestmentSimulator::runSimulation() {
    // Retrieve and validate input values
    bool ok;
    double initialInvestment = initialInvestmentEdit->text().toDouble(&ok);
    if (!ok) return;
    double monthlyInvestment = monthlyInvestmentEdit->text().toDouble(&ok);
    if (!ok) return;
    double targetAnnualDividends = targetAnnualDividendsEdit->text().toDouble(&ok);
    if (!ok) return;
    double initialDividendYield = initialDividendYieldEdit->text().toDouble(&ok);
    if (!ok) return;
    double dividendGrowthRate = dividendGrowthRateEdit->text().toDouble(&ok);
    if (!ok) return;
    double stockGrowthRate = stockGrowthRateEdit->text().toDouble(&ok);
    if (!ok) return;

    // Calculate monthly rates
    double monthlyStockGrowthRate = std::pow(1 + stockGrowthRate, 1.0/12.0) - 1;
    double monthlyDividendGrowthRate = std::pow(1 + dividendGrowthRate, 1.0/12.0) - 1;

    // Variables for simulation
    double portfolioValue = initialInvestment;
    double monthlyDividends = (initialInvestment * initialDividendYield) / 12;
    double cumulativeDividends = 0;
    int months = 0;

    // Prepare result string
    QString result;
    result += QString::asprintf("%-5s %-10s %-20s %-20s %-25s\n", "Year", "Month", "Portfolio Value", "Monthly Dividends", "Cumulative Dividends");
    result += QString("--------------------------------------------------------------------------------\n");

    // Simulation loop
    while (monthlyDividends * 12 < targetAnnualDividends) {
        portfolioValue += monthlyInvestment;
        portfolioValue *= (1 + monthlyStockGrowthRate);
        monthlyDividends = portfolioValue * (initialDividendYield * std::pow(1 + monthlyDividendGrowthRate, months)) / 12;
        portfolioValue += monthlyDividends;
        cumulativeDividends += monthlyDividends;

        result += QString::asprintf("%-5d %-10d %-20.2f %-20.2f %-25.2f\n",
                                    months / 12, months % 12 + 1, portfolioValue, monthlyDividends, cumulativeDividends);

        months++;
    }

    // Final output
    result += QString("\nReached target annual dividends of %1 euros.\n").arg(targetAnnualDividends);
    result += QString("Total months needed: %1\n").arg(months);
    result += QString("Total time: %1 years and %2 months\n").arg(months / 12).arg(months % 12);
    result += QString("Final portfolio value: %1 euros\n").arg(portfolioValue);
    result += QString("Final annual dividends: %1 euros\n").arg(monthlyDividends * 12);
    result += QString("Cumulative dividends received: %1 euros\n").arg(cumulativeDividends);

    // Display results
    resultTextEdit->setPlainText(result);

    // Optionally, save results to a file
    QFile file("investment_output_data.txt");
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << result;
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Unable to save the file.");
    }
}

