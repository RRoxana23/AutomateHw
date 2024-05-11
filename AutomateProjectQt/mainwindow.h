#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <QRegularExpression>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

private:
	QWidget* centralWidget;
	QVBoxLayout* mainLayout;
	QPushButton* nextButton;
	QLabel* summaryLabel;
	QList<QWidget*> states;
	int currentStateIndex;

	void setupUI();
	void createStates();
	void createState1();
	void createState2();
	void createState3();
	void createState4();
	void createState5();
	void createState6();

	void nextState();
	bool validateState5();
	QString generateSummary(int currentIndex);
	void updateSummary(int currentIndex);
	void closeApplication();
};

#endif