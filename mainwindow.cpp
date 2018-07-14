#include "mainwindow.h"

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
void MainWindow::switchWebcamMode() {
    switch (view->getMode()) {
        case WebcamView::SNAPSHOT :
            view->setMode(WebcamView::PREVIEW);

            modeButton->setToolTip(PREVIEW_TOOLTIP);
            break;
        case WebcamView::PREVIEW :
            view->setMode(WebcamView::SNAPSHOT);

            modeButton->setToolTip(SNAPSHOT_TOOLTIP);
            break;
        case WebcamView::ERROR :
        default :
            // Do not change mode on error
            break;
    }
}

/*
 * Layout for displaying interactive widgets that change the display
 */
QVBoxLayout * MainWindow::createButtonLayout() {
    QVBoxLayout * buttonLayout = new QVBoxLayout(this);

    QPushButton * fullscreenButton = new QPushButton("Fullscreen", this);
    zoomSlider = new QSlider(this);
    modeButton = new QPushButton("Change Mode", this);
    QPushButton * settingsButton = new QPushButton("Settings", this);

    zoomSlider->setTickPosition(QSlider::TicksBothSides);
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(100);
    zoomSlider->setTickInterval( static_cast<int>((zoomSlider->maximum() - zoomSlider->minimum())/10) );
    zoomSlider->setSingleStep(1);
    zoomSlider->setPageStep(10);
    zoomSlider->setSliderPosition( static_cast<int>((zoomSlider->maximum() - zoomSlider->minimum())/2) );
    zoomSlider->setTracking(true);

    buttonLayout->addWidget(fullscreenButton);
    buttonLayout->addWidget(zoomSlider);
    buttonLayout->setAlignment(zoomSlider,  Qt::AlignHCenter);
    buttonLayout->addWidget(modeButton);
    buttonLayout->addWidget(settingsButton);

    modeButton->setToolTip(SNAPSHOT_TOOLTIP);

    // "Settings" button opens dialog box for modifying advanced settings
    connect(settingsButton, SIGNAL (released()), this, SLOT (openSettingsDialog()));
    // "Change Mode" button switches from still image to video feed & vice versa
    connect(modeButton, SIGNAL (released()), this, SLOT (switchWebcamMode()));

    return buttonLayout;
}

/*
 * Layout for displaying graphics and button for advanced image modifications
 */
QVBoxLayout * MainWindow::createGraphicsLayout() {
    QVBoxLayout * graphicsLayout = new QVBoxLayout(this);

    view = new WebcamView(this);

    graphicsLayout->addWidget(view);

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
 * Bring up dialog box for changing advanced settings
 */
void MainWindow::openSettingsDialog() {
    settingsDialog = new SettingsDialog(this);

    // Process image whenever settings changed in dialog box
    connect(settingsDialog, SIGNAL (settingsChanged(webcamSettings)), this, SLOT (processImage(webcamSettings)) );

    // Prevent main window from being interacted with until dialog closed
    settingsDialog->exec();
}

/*
 * Process image with settings defined by dialog box
 */
void MainWindow::processImage(webcamSettings settings) {
    qDebug() << "Device Num: " << settings.device;
    qDebug() << "Brightness: " << settings.brightness;
    qDebug() << "Contrast: " << settings.contrast;
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
