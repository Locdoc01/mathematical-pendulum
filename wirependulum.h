#ifndef FADENPENDEL_H
#define FADENPENDEL_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtMath>


class WirePendulum : public QWidget
{
    Q_OBJECT

    friend class MainWindow;

private:
    bool mConstructed;
    double mHeight, mWidth;
    int mZoom;
    double mSphereRadius;
    double mPendulumLength;
    double mSphereRadiusPixels;
    double mPendulumLengthPixels;
    double mGravity;
    double mAmplitude;
    double mAngle;
    double mAngle_Taylor;
    double mX, mY;
    double mX_Taylor, mY_Taylor;
    int mZeroPasses;
    int mZeroPasses_Taylor;
    int mPendulumColor;
    int mPendulumColor_Taylor;
    bool mStart;
    long long int mMiliSeconds; // Enough for a run time of about 290 million years
    bool mWireVisible;
    bool mShowScale;
    bool mShowValues;
    bool mSinglePendulum;
    bool mSmallAngleApproximation;
    bool mTaylorApproximation;
    bool mInstantStart;
    int mSide;
    QTimer *mTimer;
    double mPeriod;
    double mPeriod_Taylor;

public:
    WirePendulum(double sphereRadius, double gravity, double length, int zoom, double amplitude, int color, int color_Taylor, QWidget *parent = 0);

public slots:
    void pendulumFunction();
    void setPendulumLength(double length);
    void setAmplitude(int amplitude);
    void setGravityEarth(bool gravity);
    void setGravityJupiter(bool gravity);
    void setGravityMoon(bool gravity);
    void setGravitySaturn(bool gravity);
    void setGravitySun(bool gravity);
    void setGravityManually(double gravity);
    void setSphereRadius(int sphereRadius);
    void setWireVisible(bool wireVisible);
    void setShowScale(bool showScale);
    void setShowValues(bool showValue);
    void setSinglePendulum(bool singlePendulum);
    void setSmallAngleApproximation(bool smallAngleApprox);
    void setTaylorApproximation(bool taylorApprox);
    void setInstantStart(bool instantStart);
    void setPendulumColor( int color);
    void setPendulumColor_Taylor( int color_Taylor);
    void setZoomTo1(bool zoom1);
    void setZoomTo5(bool zoom5);
    void setZoomTo10(bool zoom10);

signals:
    void coordinatesChangedAfterMouseEvent();
    void instantStart(bool instantStart);

protected:
    double getPixelsPerMeter();
    double getPixelsPerMeter(double m);
    void setCartesianCoordinates();
    void setPolarCoordinates();
    QColor getColor(int color);
    QString getTimeString();
    void getXY(QMouseEvent *event);
    void mouseMoveEvent( QMouseEvent *event);
    void mousePressEvent( QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintValues(QString string, int x, int y, int angle,int period, int zeroPasses, int offset, int color, QPainter *painter);
    void paintEvent(QPaintEvent *event);

};

#endif // FADENPENDEL_H
