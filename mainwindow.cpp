#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "maison.h"
#include "usine.h"
#include "parc.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ville = new Ville("Ma Ville Virtuelle", 500000.0);
    simulation = new Simulation(ville);

    connect(ui->btnMaison, &QPushButton::clicked, this, &MainWindow::construireMaison);
    connect(ui->btnUsine, &QPushButton::clicked, this, &MainWindow::construireUsine);
    connect(ui->btnParc, &QPushButton::clicked, this, &MainWindow::construireParc);
    connect(ui->btnSupprimer, &QPushButton::clicked, this, &MainWindow::supprimerBatiment);
    connect(ui->btnModifier, &QPushButton::clicked, this, &MainWindow::modifierBatiment);
    connect(ui->btnCycle, &QPushButton::clicked, this, &MainWindow::demarrerCycle);
    connect(ui->listeBatiments, &QListWidget::itemDoubleClicked,
            this, &MainWindow::afficherDetails);

    ajouterLog("Bienvenue dans VirtualCity!");
    ajouterLog("Construisez votre ville et gerez ses ressources.");

    mettreAJourAffichage();
}

MainWindow::~MainWindow()
{
    delete simulation;
    delete ville;
    delete ui;
}

void MainWindow::construireMaison()
{
    bool ok;
    int capacite = QInputDialog::getInt(this, "Nouvelle Maison",
                                        "Capacite habitants (1-10):",
                                        4, 1, 10, 1, &ok);
    if (!ok) return;

    int id = ville->getProchainId();
    string nom = QInputDialog::getText(this, "Nouvelle Maison",
                                       "Nom de la maison:",
                                       QLineEdit::Normal,
                                       QString("Maison #%1").arg(id),
                                       &ok).toStdString();
    if (!ok) return;

    Maison* maison = new Maison(id, nom, capacite);

    if (ville->getBudget() < maison->getCoutConstruction()) {
        QMessageBox::warning(this, "Erreur", "Budget insuffisant!");
        delete maison;
        return;
    }

    ville->ajouterBatiment(maison);
    ville->incrementerProchainId();

    ajouterLog(QString("Maison construite: %1 (ID: %2, Capacite: %3)")
                   .arg(QString::fromStdString(nom))
                   .arg(id)
                   .arg(capacite));
    mettreAJourAffichage();
}

void MainWindow::construireUsine()
{
    bool ok;
    int id = ville->getProchainId();
    string nom = QInputDialog::getText(this, "Nouvelle Usine",
                                       "Nom de l'usine:",
                                       QLineEdit::Normal,
                                       QString("Usine #%1").arg(id),
                                       &ok).toStdString();
    if (!ok) return;

    Usine* usine = new Usine(id, nom);

    if (ville->getBudget() < usine->getCoutConstruction()) {
        QMessageBox::warning(this, "Erreur", "Budget insuffisant!");
        delete usine;
        return;
    }

    ville->ajouterBatiment(usine);
    ville->incrementerProchainId();

    ajouterLog(QString("Usine construite: %1 (ID: %2)")
                   .arg(QString::fromStdString(nom))
                   .arg(id));
    mettreAJourAffichage();
}

void MainWindow::construireParc()
{
    bool ok;
    double surface = QInputDialog::getDouble(this, "Nouveau Parc",
                                             "Surface (m2):",
                                             500.0, 100.0, 10000.0, 1, &ok);
    if (!ok) return;

    int id = ville->getProchainId();
    string nom = QInputDialog::getText(this, "Nouveau Parc",
                                       "Nom du parc:",
                                       QLineEdit::Normal,
                                       QString("Parc #%1").arg(id),
                                       &ok).toStdString();
    if (!ok) return;

    Parc* parc = new Parc(id, nom, surface);

    if (ville->getBudget() < parc->getCoutConstruction()) {
        QMessageBox::warning(this, "Erreur", "Budget insuffisant!");
        delete parc;
        return;
    }

    ville->ajouterBatiment(parc);
    ville->incrementerProchainId();

    ajouterLog(QString("Parc construit: %1 (ID: %2, Surface: %3 m2)")
                   .arg(QString::fromStdString(nom))
                   .arg(id)
                   .arg(surface));
    mettreAJourAffichage();
}

void MainWindow::supprimerBatiment()
{
    QListWidgetItem* item = ui->listeBatiments->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Erreur", "Selectionnez un batiment a supprimer");
        return;
    }

    QString text = item->text();
    int id = text.split(" ")[1].toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Voulez-vous vraiment supprimer ce batiment?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (ville->supprimerBatiment(id)) {
            ajouterLog("Batiment #" + QString::number(id) + " supprime");
            mettreAJourAffichage();
        }
    }
}

void MainWindow::modifierBatiment()
{
    QListWidgetItem* item = ui->listeBatiments->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Erreur", "Selectionnez un batiment a modifier");
        return;
    }

    QString text = item->text();
    int id = text.split(" ")[1].toInt();

    Batiment* batiment = ville->trouverBatiment(id);
    if (batiment == NULL) return;

    bool ok;
    string nouveauNom = QInputDialog::getText(this, "Modifier Batiment",
                                              "Nouveau nom:",
                                              QLineEdit::Normal,
                                              QString::fromStdString(batiment->getNom()),
                                              &ok).toStdString();
    if (ok && !nouveauNom.empty()) {
        batiment->setNom(nouveauNom);
        ajouterLog(QString("Batiment #%1 renomme: %2")
                       .arg(id)
                       .arg(QString::fromStdString(nouveauNom)));
        mettreAJourAffichage();
    }

    // Modification spécifique selon le type
    Maison* maison = dynamic_cast<Maison*>(batiment);
    if (maison != NULL) {
        int nbHabitants = QInputDialog::getInt(this, "Modifier Maison",
                                               QString("Nombre d'habitants (0-%1):").arg(maison->getCapaciteHabitants()),
                                               maison->getHabitantsActuels(),
                                               0, maison->getCapaciteHabitants(), 1, &ok);
        if (ok) {
            maison->setHabitantsActuels(nbHabitants);
            ville->calculerPopulationTotale();
            ajouterLog(QString("Maison #%1: %2 habitants").arg(id).arg(nbHabitants));
            mettreAJourAffichage();
        }
    }
}

void MainWindow::demarrerCycle()
{
    // Vérifier s'il y a des bâtiments
    if (ville->getBatiments().empty()) {
        QMessageBox::warning(this, "Erreur",
                             "Impossible de demarrer un cycle sans batiments!\n"
                             "Construisez au moins un batiment d'abord.");
        ajouterLog("ERREUR: Tentative de cycle sans batiments");
        return;
    }

    simulation->demarrerCycle();

    // Afficher les détails du cycle
    ajouterLog(QString("=== Cycle %1 demarre ===").arg(simulation->getCycleActuel()));

    double consEau, consElec;
    ville->calculerConsommationTotale(consEau, consElec);
    ajouterLog(QString("Production: +100 L eau, +150 kWh electricite"));
    ajouterLog(QString("Consommation: -%1 L eau, -%2 kWh electricite")
                   .arg(consEau, 0, 'f', 1)
                   .arg(consElec, 0, 'f', 1));
    ajouterLog(QString("Ressources restantes: %1 L eau, %2 kWh electricite")
                   .arg(ville->getEau(), 0, 'f', 1)
                   .arg(ville->getElectricite(), 0, 'f', 1));

    simulation->terminerCycle();

    ajouterLog(QString("=== Cycle %1 termine ===").arg(simulation->getCycleActuel()));
    mettreAJourAffichage();
}

void MainWindow::afficherDetails()
{
    QListWidgetItem* item = ui->listeBatiments->currentItem();
    if (!item) return;

    QString text = item->text();
    int id = text.split(" ")[1].toInt();

    Batiment* batiment = ville->trouverBatiment(id);
    if (batiment != NULL) {
        QString details = QString("=== Details du Batiment ===\n") +
                          "ID: " + QString::number(batiment->getId()) + "\n" +
                          "Nom: " + QString::fromStdString(batiment->getNom()) + "\n" +
                          "Type: " + QString::fromStdString(batiment->getType()) + "\n" +
                          "Consommation Eau: " + QString::number(batiment->getConsommationEau()) + " L/cycle\n" +
                          "Consommation Elec: " + QString::number(batiment->getConsommationElectricite()) + " kWh/cycle\n" +
                          "Effet Satisfaction: " + QString::number(batiment->getEffetSatisfaction()) + "\n" +
                          "Cout Construction: " + QString::number(batiment->getCoutConstruction()) + " $";

        Maison* maison = dynamic_cast<Maison*>(batiment);
        if (maison != NULL) {
            details += QString("\n\nCapacite: %1 habitants\nHabitants actuels: %2\nTaux occupation: %3%")
            .arg(maison->getCapaciteHabitants())
                .arg(maison->getHabitantsActuels())
                .arg((maison->getCapaciteHabitants() > 0) ?
                         (maison->getHabitantsActuels() * 100 / maison->getCapaciteHabitants()) : 0);
        }

        Usine* usine = dynamic_cast<Usine*>(batiment);
        if (usine != NULL) {
            details += QString("\n\nProduction: %1\nPollution: %2")
            .arg(usine->getProductionRessources())
                .arg(usine->getPollution());
        }

        Parc* parc = dynamic_cast<Parc*>(batiment);
        if (parc != NULL) {
            details += QString("\n\nSurface: %1 m2\nBien-etre: %2")
            .arg(parc->getSurface())
                .arg(parc->getEffetBienEtre());
        }

        QMessageBox::information(this, "Details", details);
    }
}

void MainWindow::mettreAJourAffichage()
{
    ui->labelCycle->setText("Cycle: " + QString::number(simulation->getCycleActuel()));
    ui->labelBudget->setText("Budget: " + QString::number(ville->getBudget(), 'f', 0) + " $");
    ui->labelPopulation->setText("Population: " + QString::number(ville->getPopulation()));
    ui->labelSatisfaction->setText("Satisfaction: " + QString::number(ville->getSatisfaction()) + "%");
    ui->labelEau->setText("Eau: " + QString::number(ville->getEau(), 'f', 1) + " L");
    ui->labelElectricite->setText("Electricite: " + QString::number(ville->getElectricite(), 'f', 1) + " kWh");
    ui->labelPollution->setText("Pollution: " + QString::number(ville->getPollution(), 'f', 1));

    ui->listeBatiments->clear();
    vector<Batiment*>& batiments = ville->getBatiments();
    for (int i = 0; i < batiments.size(); i++) {
        QString item = "ID " + QString::number(batiments[i]->getId()) + " - " +
                       QString::fromStdString(batiments[i]->getNom()) + " (" +
                       QString::fromStdString(batiments[i]->getType()) + ")";
        ui->listeBatiments->addItem(item);
    }
}

void MainWindow::ajouterLog(const QString& message)
{
    ui->logText->append(message);
}
