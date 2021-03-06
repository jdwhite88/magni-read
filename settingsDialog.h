#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

// Parent class
#include <QDialog>

// Implementation classes
#include <QCameraInfo>
#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QSlider>
#include <QVBoxLayout>

#include <string>

#include "colorbutton.h"

class SettingsDialog : public QDialog {

    Q_OBJECT

private:
    QSlider * brightnessSlider;
    QSlider * contrastSlider;
    QComboBox * webcamBox;
    QComboBox * colorFilterBox;
    QSpinBox * rotateAngleBox;
    QDoubleSpinBox * minZoomBox;
    QSpinBox * maxZoomBox;
    QCheckBox * clickDragBox;
    QCheckBox * guidingLineBox;
    QSpinBox * linePosBox;
    QSpinBox * lineThicknessBox;
    ColorButton * lineColorButton;


    QPushButton * defaultButton;
    QPushButton * okButton;
    QPushButton * cancelButton;

    QVBoxLayout * createDialogLayout();
    QGridLayout * createSettingsLayout();
    QHBoxLayout * createButtonLayout();

protected:
    const double DEFAULT_BRIGHTNESS = 0;
    const double DEFAULT_CONTRAST = 1;
    const double DEFAULT_MIN_ZOOM = 1.0;
    const double DEFAULT_MAX_ZOOM = 5;
    const QString DEFAULT_FILTER = "None";
    const int DEFAULT_ANGLE = 0;
    const bool DEFAULT_CLICK_TO_DRAG = false;
    const bool DEFAULT_IS_LINE_DRAWN = false;
    const int DEFAULT_LINE_POS = 50;
    const int DEFAULT_LINE_THICKNESS = 10;
    const QColor DEFAULT_LINE_COLOR = Qt::red;

public:
    SettingsDialog();
    SettingsDialog(QWidget * parent);

signals:
    // Indicates when temporary image display values change
    void tempSettingsChanged();

private slots:
    void changeLineEnabled(int state);
    void changeTempImageSettings();
    void closeDialog();
    void saveAndCloseDialog();
    void restoreDefaults();
    void restoreWebcamDefault();

};

#endif // SETTINGSDIALOG_H
