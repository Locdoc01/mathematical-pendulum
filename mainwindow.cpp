#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


// constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCountResizes(0)
{
    ui->setupUi(this);

    mLayoutPendulumArea = new QHBoxLayout(ui->pendulumArea);

    mPendulum = new WirePendulum(ui->spinBoxSphereRadius->value(),
                             9.81,
                             ui->dSpinBoxPendulumLength->value(),
                             10,
                             ui->spinBoxAmplitude->value(),
                             ui->comboBoxPendulumColor->currentIndex(),
                             ui->comboBoxPendulumColor_Taylor->currentIndex());

    mLayoutPendulumArea->addWidget(mPendulum);


    // signal-slot-connections for pendulum type
    connect(ui->radioSingleShpere, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setSinglePendulum(bool)));

    connect(ui->radioSingleShpere, SIGNAL(toggled(bool)),
            this, SLOT(setCheckBox(bool)));

    connect(ui->radioSingleShpere, SIGNAL(toggled(bool)),
            this, SLOT(setSphereRadius(bool)));

    connect(ui->radioSingleShpere, SIGNAL(toggled(bool)),
           ui->checkBoxShowValues, SLOT(setEnabled(bool)));

    connect(ui->radio5Shperes, SIGNAL(toggled(bool)),
            this, SLOT(checkBoxShowValuesSetChecked(bool)));


    // signal-slot-connections for pendulum functions & color
    connect(ui->checkBoxSmallAngleApprox, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setSmallAngleApproximation(bool)));

    connect(ui->checkBoxSmallAngleApprox, SIGNAL(toggled(bool)),
            this, SLOT(setCheckBoxTaylorApprox(bool)));

    connect(ui->checkBoxTaylorApprox, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setTaylorApproximation(bool)));

    connect(ui->checkBoxTaylorApprox, SIGNAL(toggled(bool)),
            this, SLOT(setCheckBoxSmallAngleApprox(bool)));

    connect(ui->checkBoxSmallAngleApprox, SIGNAL(toggled(bool)),
            ui->comboBoxPendulumColor, SLOT(setEnabled(bool)));

    connect(ui->checkBoxTaylorApprox, SIGNAL(toggled(bool)),
            ui->comboBoxPendulumColor_Taylor, SLOT(setEnabled(bool)));

    connect(ui->comboBoxPendulumColor, SIGNAL(currentIndexChanged(int)),
            mPendulum, SLOT(setPendulumColor(int)));

    connect(ui->comboBoxPendulumColor_Taylor, SIGNAL(currentIndexChanged(int)),
            mPendulum, SLOT(setPendulumColor_Taylor(int)));


    // signal-slot-connections for pendulum length
    connect(ui->dSpinBoxPendulumLength, SIGNAL(valueChanged(double)),
            this, SLOT(sliderPendulumLengthSetValueInt(double)));

    connect(ui->sliderPendulumLength, SIGNAL(valueChanged(int)),
            this, SLOT(dSpinBoxPendulumLengthSetValueDouble(int)));

    connect(ui->dSpinBoxPendulumLength, SIGNAL(valueChanged(double)),
            mPendulum, SLOT(setPendulumLength(double)));


    // signal-slot-connections for amplitude
    connect(ui->spinBoxAmplitude, SIGNAL(valueChanged(int)),
            this, SLOT(dialAmplitudeSetValue(int)));

    connect(ui->dialAmplitude, SIGNAL(valueChanged(int)),
            this, SLOT(spinBoxAmplitudeSetValue(int)));

    connect(ui->dialAmplitude, SIGNAL(sliderMoved(int)),
            this, SLOT(spinBoxAmplitudeSetValue(int)));

    connect(ui->spinBoxAmplitude, SIGNAL(valueChanged(int)),
            mPendulum, SLOT(setAmplitude(int)));


    // signal-slot-connections for gravity
    connect(ui->radioEarth, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setGravityEarth(bool)));

    connect(ui->radioJupiter, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setGravityJupiter(bool)));

    connect(ui->radioMoon, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setGravityMoon(bool)));

    connect(ui->radioSaturn, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setGravitySaturn(bool)));

    connect(ui->radioSun, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setGravitySun(bool)));

    connect(ui->radioManually, SIGNAL(toggled(bool)),
            ui->dSpinBoxGravity, SLOT(setEnabled(bool)));

    connect(ui->radioManually, SIGNAL(toggled(bool)),
            this, SLOT(radioButtonToggledManually(bool)));

    connect(this, SIGNAL(manualGravitySetting(double)),
            mPendulum, SLOT(setGravityManually(double)));

    connect(ui->dSpinBoxGravity, SIGNAL(valueChanged(double)),
            mPendulum, SLOT(setGravityManually(double)));


    // signal-slot-connections for shpere radius
    connect(ui->spinBoxSphereRadius, SIGNAL(valueChanged(int)),
            ui->sliderSphereRadius, SLOT(setValue(int)));

    connect(ui->sliderSphereRadius, SIGNAL(valueChanged(int)),
            ui->spinBoxSphereRadius, SLOT(setValue(int)));

    connect(ui->spinBoxSphereRadius, SIGNAL(valueChanged(int)),
            mPendulum, SLOT(setSphereRadius(int)));


    // signal-slot-connections for zoom
    connect(ui->radioZoom1, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setZoomTo1(bool)));

    connect(ui->radioZoom5, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setZoomTo5(bool)));

    connect(ui->radioZoom10, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setZoomTo10(bool)));

    connect(ui->radioZoom1, SIGNAL(toggled(bool)),
            this, SLOT(dSpinBoxPendulumLengthSetProperties1(bool)));

    connect(ui->radioZoom5, SIGNAL(toggled(bool)),
            this, SLOT(dSpinBoxPendulumLengthSetProperties5(bool)));

    connect(ui->radioZoom10, SIGNAL(toggled(bool)),
            this, SLOT(dSpinBoxPendulumLengthSetProperties10(bool)));


    // signal-slot-connections for options
    connect(ui->checkBoxWireVisible, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setWireVisible(bool)));

    connect(ui->checkBoxShowScale, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setShowScale(bool)));

    connect(ui->checkBoxInstantStart, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setInstantStart(bool)));

    connect(ui->checkBoxShowValues, SIGNAL(toggled(bool)),
            mPendulum, SLOT(setShowValues(bool)));


    // signal-slot-connections for start button
    connect(ui->startButton, SIGNAL(toggled(bool)),
            this, SLOT(startButtonSetText(bool)));

    connect( ui->startButton, SIGNAL(toggled(bool)),
             this, SLOT(timerStart(bool)));

    connect( mPendulum, SIGNAL(instantStart(bool)),
             ui->startButton, SLOT(setChecked(bool)));


    // signal-slot-connection for change in coordinates after MouseEevent
    connect(mPendulum, SIGNAL(coordinatesChangedAfterMouseEvent()),
            this, SLOT(setValuesAfterMouseEvent()));
}
// end constructor



MainWindow::~MainWindow()
{
    delete ui;
}


//public slots:

void MainWindow::sliderPendulumLengthSetValueInt(double value)
{
    disconnect(ui->sliderPendulumLength, SIGNAL(valueChanged(int)),
            this, SLOT(dSpinBoxPendulumLengthSetValueDouble(int)));

    if (ui->radioZoom10->isChecked())
        ui->sliderPendulumLength->setValue(value*100);
    else if (ui->radioZoom5->isChecked())
        ui->sliderPendulumLength->setValue(value*50);
    else
        ui->sliderPendulumLength->setValue(value*10);

    connect(ui->sliderPendulumLength, SIGNAL(valueChanged(int)),
            this, SLOT(dSpinBoxPendulumLengthSetValueDouble(int)));
}

void MainWindow::dSpinBoxPendulumLengthSetValueDouble(int value)
{
    disconnect(ui->dSpinBoxPendulumLength, SIGNAL(valueChanged(double)),
            this, SLOT(sliderPendulumLengthSetValueInt(double)));

    if (ui->radioZoom10->isChecked())
        ui->dSpinBoxPendulumLength->setValue((double)value/100);
    else if (ui->radioZoom5->isChecked())
        ui->dSpinBoxPendulumLength->setValue((double)value/50);
    else
        ui->dSpinBoxPendulumLength->setValue((double)value/10);

    connect(ui->dSpinBoxPendulumLength, SIGNAL(valueChanged(double)),
            this, SLOT(sliderPendulumLengthSetValueInt(double)));
}

void MainWindow::dialAmplitudeSetValue(int value)
{
    disconnect(ui->dialAmplitude, SIGNAL(valueChanged(int)),
            ui->spinBoxAmplitude, SLOT(setValue(int)));

    ui->dialAmplitude->setValue(-value);

    connect(ui->dialAmplitude, SIGNAL(valueChanged(int)),
            ui->spinBoxAmplitude, SLOT(setValue(int)));
}

void MainWindow::spinBoxAmplitudeSetValue(int value)
{
    disconnect(ui->spinBoxAmplitude, SIGNAL(valueChanged(int)),
            ui->dialAmplitude, SLOT(setValue(int)));

    ui->spinBoxAmplitude->setValue(-value);

    connect(ui->spinBoxAmplitude, SIGNAL(valueChanged(int)),
            ui->dialAmplitude, SLOT(setValue(int)));
}

void MainWindow::startButtonSetText(bool b)
{
    if (b)
    {
        ui->startButton->setText(" Stop");
        ui->startButton->setIcon(QIcon(":/images/stop48.svg"));
    }
    else
    {
        ui->startButton->setText(" Start");
        ui->startButton->setIcon(QIcon(":/images/play40.svg"));
    }
}

//If start button was pressed, some controls get disabled and the timer gets started.
//If stop button was pressed, the controls get enabled, the timer gets stopped and necessary values for the equation of motion are set to zero.
void MainWindow::timerStart(bool buttonStart)
{
    ui->framePendulumLength->setDisabled(buttonStart);
    ui->frameGravity->setDisabled(buttonStart);

    if ( buttonStart )
    {
        mPendulum->mStart = true;
        // 10ms intervalls turned out to be optimal for movement
        mPendulum->mTimer->start(10);
    }
    else
    {
        mPendulum->mTimer->stop();
        mPendulum->mStart = false;
    }
    mPendulum->mMiliSeconds = 0;
    mPendulum->mPeriod = 0;
    mPendulum->mPeriod_Taylor = 0;
    mPendulum->mZeroPasses = 0;
    mPendulum->mZeroPasses_Taylor = 0;
    mPendulum->mAngle = mPendulum->mAngle_Taylor = 0;

}

void MainWindow::radioButtonToggledManually(bool b)
{
    if (b)
        emit manualGravitySetting(ui->dSpinBoxGravity->value());
}

void MainWindow::setCheckBoxSmallAngleApprox(bool b)
{
    if (!mPendulum->mSinglePendulum)
        ui->checkBoxSmallAngleApprox->setChecked(!b);
}

void MainWindow::setCheckBoxTaylorApprox(bool b)
{
    if (!mPendulum->mSinglePendulum)
        ui->checkBoxTaylorApprox->setChecked(!b);
}


void MainWindow::setCheckBox(bool b)
{
    if (!b)
    {
        if (ui->checkBoxSmallAngleApprox->isChecked())
            ui->checkBoxTaylorApprox->setChecked(false);
        else if (ui->checkBoxTaylorApprox->isChecked())
            ui->checkBoxSmallAngleApprox->setChecked(false);
        else
            ui->checkBoxSmallAngleApprox->setChecked(true);
    }
}

void MainWindow::setSphereRadius(bool b)
{
    if (b)
    {
        ui->spinBoxSphereRadius->setMaximum(60);
        ui->sliderSphereRadius->setMaximum(60);
    }
    else
    {
        ui->spinBoxSphereRadius->setMaximum(30);
        ui->sliderSphereRadius->setMaximum(30);
    }
}

void MainWindow::dSpinBoxPendulumLengthSetProperties1(bool b)
{
    if (b)
    {
        qDebug() << "1";
        ui->dSpinBoxPendulumLength->setMaximum(20.0);
        ui->dSpinBoxPendulumLength->setSingleStep(1);
        ui->sliderPendulumLength->setValue(ui->dSpinBoxPendulumLength->value()*10);
    }
}

void MainWindow::dSpinBoxPendulumLengthSetProperties5(bool b)
{
    if (b)
    {
        qDebug() << "5";
        ui->dSpinBoxPendulumLength->setMaximum(4.0);
        ui->dSpinBoxPendulumLength->setSingleStep(0.2);
        ui->sliderPendulumLength->setValue(ui->dSpinBoxPendulumLength->value()*50);
    }
}

void MainWindow::dSpinBoxPendulumLengthSetProperties10(bool b)
{
    if (b)
    {
        ui->dSpinBoxPendulumLength->setMaximum(2.0);
        ui->dSpinBoxPendulumLength->setSingleStep(0.1);
        ui->sliderPendulumLength->setValue(ui->dSpinBoxPendulumLength->value()*100);
    }
}

void MainWindow::checkBoxShowValuesSetChecked(bool b)
{
    if (ui->radio5Shperes->isChecked())
        ui->checkBoxShowValues->setChecked(false);
}

//If mouse is pressed (and moved) polar coordinates of the pendulum (amplitude and pendulum length) get updated depending on the x,y-coordinates of the mouse event.
//Also the controls for amplitude and pendulum length get updates. The corresponding slignal-slot-connections get temporary disconnected in order to avoid visual feedback.
void MainWindow::setValuesAfterMouseEvent()
{
    mPendulum->setPolarCoordinates();

    disconnect(ui->dSpinBoxPendulumLength, SIGNAL(valueChanged(double)),
            mPendulum, SLOT(setPendulumLength(double)));
    disconnect(ui->spinBoxAmplitude, SIGNAL(valueChanged(int)),
            mPendulum, SLOT(setAmplitude(int)));

    ui->dSpinBoxPendulumLength->setValue(mPendulum->mPendulumLength);
    ui->spinBoxAmplitude->setValue(mPendulum->mAmplitude);

    connect(ui->dSpinBoxPendulumLength, SIGNAL(valueChanged(double)),
            mPendulum, SLOT(setPendulumLength(double)));
    connect(ui->spinBoxAmplitude, SIGNAL(valueChanged(int)),
            mPendulum, SLOT(setAmplitude(int)));
}

// Events:

//After resizing the main windows the x,y-coordinates of the pendulum get updated.
//mCountResizes makes sure, that this doesn't happen during window creation, since resizeEvent
//is also called during that process.
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (mCountResizes>0) {
      mPendulum->setCartesianCoordinates();
      update();
    }
    else
        mCountResizes++;
}

