#include "mainwindow.h"

#include <iostream>
#include <cmath>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window layout
    window = new QWidget(this);
    QGridLayout * wLayout = createMainLayout();

    window->setLayout(wLayout);
    this->setCentralWidget(window);

    // Set window title
    this->setWindowTitle(tr("MagniRead"));

    // Maximize window
    this->setWindowState(Qt::WindowMaximized);
}

/*
 * Change webcam mode from preview to snapshot, or vice versa
 */
void MainWindow::changeWebcamMode() {
    switch (view->getMode()) {
        case WebcamView::SNAPSHOT :
            view->setMode(WebcamView::PREVIEW);
            break;
        case WebcamView::PREVIEW :
            view->setMode(WebcamView::SNAPSHOT);
            break;
        case WebcamView::ERROR :
        default :
            // Do not change mode on error
            break;
    }
}

/*
 * Layout for displaying basic image modification buttons
 */
QVBoxLayout * MainWindow::createButtonLayout() {
    QVBoxLayout * buttonLayout = new QVBoxLayout(this);

    QLabel * buttonLabel = new QLabel("Buttons:", this);
    modeButton = new QPushButton("Change Mode", this);

    buttonLayout ->addWidget(buttonLabel);
    buttonLayout->addWidget(modeButton);

    connect(modeButton, SIGNAL (released()), this, SLOT (changeWebcamMode()));

    return buttonLayout;
}

/*
 * Layout for displaying graphics and button for advanced image modifications
 */
QVBoxLayout * MainWindow::createGraphicsLayout() {
    QVBoxLayout * graphicsLayout = new QVBoxLayout(this);

    view = new WebcamView(this);

    QPushButton * settingsButton = new QPushButton("Settings", this);

    graphicsLayout->addWidget(view);
    graphicsLayout->addWidget(settingsButton);

    connect(settingsButton, SIGNAL (released()), this, SLOT (openSettingsDialog()));

    return graphicsLayout;
}


/*
 * Entire Layout for MainWindow
 */
QGridLayout * MainWindow::createMainLayout() {
    QGridLayout * mainLayout = new QGridLayout(this);

    QVBoxLayout * graphicsLayout = createGraphicsLayout();
    QVBoxLayout * buttonLayout = createButtonLayout();

    // Image layout spans 7 of 8 columns, and all rows
    mainLayout->addLayout(graphicsLayout, 0, 0, 10, 7);
    // Button layout spans last column, and all rows
    mainLayout->addLayout(buttonLayout, 0, 7, 10, 1);

    return mainLayout;
}

/*
 * Open Dialog box for changing advanced settings
 */
void MainWindow::openSettingsDialog() {
    settingsDialog = new SettingsDialog(this);

    // Prevent main window from being interacted with until dialog closed
    settingsDialog->exec();
}

/*
 * Rescale picture to be as large as possible while keeping aspect ratio
 */
void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);

    view->rescaleImage();
}

MainWindow::~MainWindow()
{
}
