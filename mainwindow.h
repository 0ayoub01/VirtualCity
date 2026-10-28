#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include "ville.h"
#include "simulation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void construireMaison();
    void construireUsine();
    void construireParc();
    void supprimerBatiment();
    void modifierBatiment();
    void demarrerCycle();
    void afficherDetails();

private:
    Ui::MainWindow *ui;

    Ville* ville;
    Simulation* simulation;

    void mettreAJourAffichage();
    void ajouterLog(const QString& message);
};

#endif
