#ifndef INVESTMENTSIMULATOR_H
#define INVESTMENTSIMULATOR_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>

class InvestmentSimulator : public QMainWindow {
    Q_OBJECT

public:
    InvestmentSimulator(QWidget *parent = nullptr);

private slots:
    void runSimulation();

private:
    QLineEdit *initialInvestmentEdit;
    QLineEdit *monthlyInvestmentEdit;
    QLineEdit *targetAnnualDividendsEdit;
    QLineEdit *initialDividendYieldEdit;
    QLineEdit *dividendGrowthRateEdit;
    QLineEdit *stockGrowthRateEdit;
    QTextEdit *resultTextEdit;
};

#endif // INVESTMENTSIMULATOR_H

