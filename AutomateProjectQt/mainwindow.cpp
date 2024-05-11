#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), currentStateIndex(0) {
    createStates();
    setupUI();
}

void MainWindow::setupUI() {
    centralWidget = new QWidget();
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(states.at(0));
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    nextButton = new QPushButton("Următorul");
    connect(nextButton, &QPushButton::clicked, this, &MainWindow::nextState);
    mainLayout->addWidget(nextButton);
}

void MainWindow::createStates() {
    createState1();
    createState2();
    createState3();
    createState4();
    createState5();
    createState6();
}

void MainWindow::createState1() {
    QWidget* state = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* specializationLabel = new QLabel("Selectați specializarea dorită:");
    QComboBox* specializationComboBox = new QComboBox();
    specializationComboBox->addItem("Alegeti o specializare");
    specializationComboBox->addItem("Poliție Rutieră");
    specializationComboBox->addItem("Poliție de Frontieră");
    specializationComboBox->addItem("Poliție Comunitară");
    specializationComboBox->addItem("Poliție Judiciară");
    layout->addWidget(specializationLabel);
    layout->addWidget(specializationComboBox);
    state->setLayout(layout);
    states.append(state);
}

void MainWindow::createState2() {
    QWidget* state = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* nameLabel = new QLabel("Nume și prenume:");
    QLineEdit* nameInput = new QLineEdit();
    QLabel* ageLabel = new QLabel("Vârstă:");
    QSpinBox* ageInput = new QSpinBox();
    ageInput->setObjectName("ageInput");
    QLabel* sexLabel = new QLabel("Sex:");
    QHBoxLayout* sexLayout = new QHBoxLayout();
    QRadioButton* femaleRadioButton = new QRadioButton("Feminin");
    femaleRadioButton->setObjectName("femaleRadioButton");
    QRadioButton* maleRadioButton = new QRadioButton("Masculin");
    maleRadioButton->setObjectName("maleRadioButton");
    sexLayout->addWidget(femaleRadioButton);
    sexLayout->addWidget(maleRadioButton);
    layout->addWidget(nameLabel);
    layout->addWidget(nameInput);
    layout->addWidget(ageLabel);
    layout->addWidget(ageInput);
    layout->addWidget(sexLabel);
    layout->addLayout(sexLayout);
    state->setLayout(layout);
    states.append(state);
}

void MainWindow::createState3() {
    QWidget* state = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* emailLabel = new QLabel("Adresă de email:");
    QLineEdit* emailInput = new QLineEdit();
    emailInput->setObjectName("emailInput");

    QLabel* phoneLabel = new QLabel("Număr de telefon:");
    QLineEdit* phoneInput = new QLineEdit();
    phoneInput->setObjectName("phoneInput");
    layout->addWidget(emailLabel);
    layout->addWidget(emailInput);
    layout->addWidget(phoneLabel);
    layout->addWidget(phoneInput);
    state->setLayout(layout);
    states.append(state);
}

void MainWindow::createState4() {
    QWidget* state = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* heightLabel = new QLabel("Înălțime (cm):");
    QLineEdit* heightInput = new QLineEdit();
    heightInput->setObjectName("heightInput");
    QLabel* weightLabel = new QLabel("Greutate (kg):");
    QLineEdit* weightInput = new QLineEdit();
    weightInput->setObjectName("weightInput");
    layout->addWidget(heightLabel);
    layout->addWidget(heightInput);
    layout->addWidget(weightLabel);
    layout->addWidget(weightInput);
    state->setLayout(layout);
    states.append(state);
}

void MainWindow::createState5() {
    QWidget* state = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    QLabel* medicalLabel = new QLabel("Ați avut vreodată afecțiuni medicale sau intervenții chirurgicale? (da/nu)");
    QRadioButton* yesButton = new QRadioButton("Da");
    QRadioButton* noButton = new QRadioButton("Nu");
    layout->addWidget(medicalLabel);
    layout->addWidget(yesButton);
    layout->addWidget(noButton);
    state->setLayout(layout);
    states.append(state);
}

void MainWindow::createState6() {
    QWidget* state = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    summaryLabel = new QLabel("Sumar informații:");
    layout->addWidget(summaryLabel);
    state->setLayout(layout);
    states.append(state);
}

void MainWindow::nextState() {
    if (currentStateIndex < 0 || currentStateIndex >= states.size()) {
        qDebug() << "Indexul currentStateIndex este în afara intervalului valid.";
        return;
    }

    QWidget* currentStateWidget = states.at(currentStateIndex);
    if (!currentStateWidget) {
        qDebug() << "Widget-ul stării curente este invalid.";
        return;
    }

    if (currentStateIndex == 0) {
        QComboBox* specializationComboBox = currentStateWidget->findChild<QComboBox*>();
        if (!specializationComboBox) {
            qDebug() << "Nu s-a putut găsi combobox-ul pentru specializare.";
            return;
        }
        if (specializationComboBox->currentIndex() == 0) {
            QMessageBox::warning(this, "Alegere specializare", "Vă rugăm să selectați o specializare înainte de a continua.");
            return;
        }
    }

    bool allFieldsCompleted = true;
    if (currentStateIndex == 2) {
        bool allFieldsCompleted = true;
        QString errorMessage;

        for (QObject* child : currentStateWidget->children()) {
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {
                if (lineEdit->text().isEmpty()) {
                    allFieldsCompleted = false;
                    break;
                }
            }
        }

        if (allFieldsCompleted) {
            QLineEdit* emailInput = currentStateWidget->findChild<QLineEdit*>("emailInput");
            if (!emailInput) {
                qDebug() << "Nu s-a putut găsi câmpul de introducere a adresei de email.";
                return;
            }

            QString email = emailInput->text();
            QRegularExpression emailRegex("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
            if (!emailRegex.match(email).hasMatch()) {
                errorMessage = "Adresă de email invalidă.";
            }

            QLineEdit* phoneInput = currentStateWidget->findChild<QLineEdit*>("phoneInput");
            if (!phoneInput) {
                qDebug() << "Nu s-a putut găsi câmpul de introducere a numărului de telefon.";
                return;
            }

            QString phone = phoneInput->text();
            QRegularExpression phoneRegex("\\b\\d{3}[-.]?\\d{3}[-.]?\\d{4}\\b");
            if (!phoneRegex.match(phone).hasMatch()) {
                errorMessage = "Număr de telefon invalid.";
            }
        }
        else {
            errorMessage = "Vă rugăm să completați toate câmpurile.";
        }

        if (!errorMessage.isEmpty()) {
            QMessageBox::warning(this, "Validare eșuată", errorMessage);
            return;
        }
    }

    allFieldsCompleted = true;
    if (currentStateIndex == 3) {
        bool allFieldsCompleted = true;
        QString errorMessage;

        for (QObject* child : currentStateWidget->children()) {
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {
                if (lineEdit->text().isEmpty()) {
                    allFieldsCompleted = false;
                    break;
                }
            }
        }

        if (allFieldsCompleted) {
            QLineEdit* heightInput = currentStateWidget->findChild<QLineEdit*>("heightInput");
            QLineEdit* weightInput = currentStateWidget->findChild<QLineEdit*>("weightInput");

            if (!heightInput || !weightInput) {
                qDebug() << "Nu s-au putut găsi câmpurile de introducere a înălțimii și greutății.";
                return;
            }

            bool heightValid = false;
            bool weightValid = false;

            double height = heightInput->text().toDouble(&heightValid);
            double weight = weightInput->text().toDouble(&weightValid);

            if (!heightValid) {
                QMessageBox::warning(this, "Date invalide", "Vă rugăm să introduceți valori valide pentru înălțime");
                return;
            }
            if (!weightValid) {
                QMessageBox::warning(this, "Date invalide", "Vă rugăm să introduceți valori valide pentru greutate.");
                return;
            }

            QWidget* previousStateWidget = states.at(1);
            QRadioButton* femaleCheckBox = previousStateWidget->findChild<QRadioButton*>("femaleRadioButton");
            QRadioButton* maleCheckBox = previousStateWidget->findChild<QRadioButton*>("maleRadioButton");
            if (!femaleCheckBox && !maleCheckBox) {
                qDebug() << "Nu s-au putut găsi casetele de bifare pentru sex.";
                return;
            }
            bool isFemale = femaleCheckBox->isChecked();
            bool isMale = maleCheckBox->isChecked();

            if ((isFemale && height < 160) || (isMale && height < 175)) {
                QMessageBox::information(this, "Neeligibil", "Ne pare rău, dar nu sunteți eligibil pentru Academia de Poliție deoarece inaltimea dvs nu este corespunzatoare.");
                int currentIndex = currentStateIndex;
                currentStateIndex = states.size() - 1;
                QWidget* lastWidget = states.last();
                mainLayout->replaceWidget(currentStateWidget, lastWidget);
                currentStateWidget->hide();
                lastWidget->show();
                updateSummary(currentIndex);
                mainLayout->removeWidget(nextButton);
                nextButton->deleteLater();
                QPushButton* closeButton = new QPushButton("Închide");
                connect(closeButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
                mainLayout->addWidget(closeButton);
                return;
            }
        }
    }

    allFieldsCompleted = true;
    if (currentStateIndex == 1) {
        bool radioButtonChecked = false;
        for (QObject* child : currentStateWidget->children()) {
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {
                if (lineEdit->text().isEmpty()) {
                    allFieldsCompleted = false;
                    break;
                }
            }
            else if (QSpinBox* spinBox = qobject_cast<QSpinBox*>(child)) {
                if (spinBox->value() == 0) {
                    allFieldsCompleted = false;
                    break;
                }
            }
            else if (QRadioButton* radioButton = qobject_cast<QRadioButton*>(child)) {
                if (radioButton->isChecked()) {
                    radioButtonChecked = true;
                }
            }
        }
        if (!radioButtonChecked) {
            allFieldsCompleted = false;
        }

        if (allFieldsCompleted) {
            QSpinBox* ageInput = currentStateWidget->findChild<QSpinBox*>("ageInput");
            if (!ageInput) {
                qDebug() << "Nu s-a putut găsi câmpul pentru introducerea vârstei.";
                return;
            }

            int varsta = ageInput->value();
            if (varsta < 18) {
                QMessageBox::information(this, "Neeligibil", "Ne pare rău, dar nu sunteți eligibil pentru Academia de Poliție deoarece vârsta dumneavoastră este mai mică de 18 ani.");

                int currentIndex = currentStateIndex;
                currentStateIndex = states.size() - 1;
                QWidget* lastWidget = states.last();
                mainLayout->replaceWidget(currentStateWidget, lastWidget);
                currentStateWidget->hide();
                lastWidget->show();
                updateSummary(currentIndex);
                mainLayout->removeWidget(nextButton);
                nextButton->deleteLater();
                QPushButton* closeButton = new QPushButton("Închide");
                connect(closeButton, &QPushButton::clicked, qApp, &QCoreApplication::quit);
                mainLayout->addWidget(closeButton);
                return;
            }
        }
    }
    else {
        for (QObject* child : currentStateWidget->children()) {
            if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(child)) {
                if (lineEdit->text().isEmpty()) {
                    allFieldsCompleted = false;
                    break;
                }
            }
        }
    }

    if (currentStateIndex == 4 && !validateState5()) {
        QMessageBox::warning(this, "Validare eșuată", "Vă rugăm să bifați una dintre opțiunile pentru evaluarea medicală.");
        return;
    }

    if (allFieldsCompleted) {
        if (currentStateIndex < states.size() - 1) {
            ++currentStateIndex;
            QWidget* nextWidget = states.at(currentStateIndex);
            mainLayout->replaceWidget(currentStateWidget, nextWidget);
            currentStateWidget->hide();
            nextWidget->show();

            if (currentStateIndex == states.size() - 1) {
                nextButton->setText("Confirmare");
                updateSummary(currentStateIndex);
            }
            else {
                nextButton->setText("Următorul");
            }
        }
        else {
            closeApplication();
        }
    }
    else {
        QMessageBox::warning(this, "Validare eșuată", "Vă rugăm să completați toate câmpurile.");
    }
}


bool MainWindow::validateState5() {
    QWidget* state5Widget = states.at(4);
    QList<QRadioButton*> radioButtons = state5Widget->findChildren<QRadioButton*>();
    for (QRadioButton* button : radioButtons) {
        if (button->isChecked()) {
            return true;
        }
    }
    return false;
}

QString MainWindow::generateSummary(int currentIndex) {
    QString summary;
    summaryLabel->clear();

    for (int i = 0; i <= currentIndex; ++i) {
        QWidget* currentStateWidget = states.at(i);
        if (!currentStateWidget) {
            qDebug() << "Widget-ul stării curente este invalid.";
            continue;
        }

        QVBoxLayout* currentLayout = qobject_cast<QVBoxLayout*>(currentStateWidget->layout());
        if (!currentLayout) {
            qDebug() << "Layout-ul stării curente este invalid.";
            continue;
        }

        for (int j = 0; j < currentLayout->count(); ++j) {
            QWidget* widget = currentLayout->itemAt(j)->widget();
            if (QLabel* label = qobject_cast<QLabel*>(widget)) {
                summary += label->text().simplified() + " ";
            }
            else if (QLineEdit* lineEdit = qobject_cast<QLineEdit*>(widget)) {
                summary += lineEdit->text() + "\n";
            }
            else if (QRadioButton* radioButton = qobject_cast<QRadioButton*>(widget)) {
                if (radioButton->isChecked()) {
                    summary += radioButton->text() + "\n";
                }
            }
            else if (QComboBox* comboBox = qobject_cast<QComboBox*>(widget)) {
                summary += comboBox->currentText() + "\n";
            }
            else if (QSpinBox* spinBox = qobject_cast<QSpinBox*>(widget)) {
                summary += QString::number(spinBox->value()) + "\n";
            }
        }
    }
    return summary;
}

void MainWindow::updateSummary(int currentIndex) {
    QString summary = generateSummary(currentIndex);
    summaryLabel->setText("Sumar informații:\n" + summary);
}



void MainWindow::closeApplication() {
    QMessageBox::information(this, "Înregistrare finalizată", "Formularul de înregistrare a fost trimis cu succes!");
    qApp->quit();
}