#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wirependulum.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    WirePendulum *mPendulum;
    QHBoxLayout *mLayoutPendulumArea;
    int mCountResizes;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void sliderPendulumLengthSetValueInt(double v);
    void dSpinBoxPendulumLengthSetValueDouble(int v);
    void dialAmplitudeSetValue(int v);
    void spinBoxAmplitudeSetValue(int v);
    void startButtonSetText(bool b);
    void timerStart(bool buttonstart);
    void radioButtonToggledManually(bool b);
    void setCheckBoxSmallAngleApprox(bool b);
    void setCheckBoxTaylorApprox(bool b);
    void setCheckBox(bool b);
    void setSphereRadius(bool b);
    void dSpinBoxPendulumLengthSetProperties1(bool b);
    void dSpinBoxPendulumLengthSetProperties5(bool b);
    void dSpinBoxPendulumLengthSetProperties10(bool b);
    void checkBoxShowValuesSetChecked(bool b);
    void setValuesAfterMouseEvent();

signals:
    void manualGravitySetting(double);

protected:
    void resizeEvent( QResizeEvent *event);



};

#endif // MAINWINDOW_H
