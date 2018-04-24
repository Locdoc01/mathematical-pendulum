#include "wirependulum.h"
#include <QDebug>

/*
 * constructor:
 * calculates the x,y-coordinates of the pendulum based on the initial settings, initializes the timer and connect it with the pendulum function
 */
WirePendulum::WirePendulum(double sphereRadius, double gravity, double length, int zoom, double amplitude, int color, int color_Taylor, QWidget *parent) :
    QWidget(parent),
    mConstructed(false),
    mHeight(299.0),
    mWidth(758.0),
    mZoom(zoom),
    mSphereRadius(sphereRadius),
    mPendulumLength(length),
    mGravity(gravity),
    mAmplitude(amplitude),
    mAngle(mAmplitude),
    mAngle_Taylor(mAmplitude),
    mZeroPasses(0),
    mZeroPasses_Taylor(0),
    mPendulumColor(color),
    mPendulumColor_Taylor(color_Taylor),
    mStart(false),
    mMiliSeconds(0),
    mWireVisible(true),
    mShowScale(true),
    mShowValues(false),
    mSinglePendulum(true),
    mSmallAngleApproximation(true),
    mTaylorApproximation(false),
    mInstantStart(false),
    mSide(0),
    mPeriod(0),
    mPeriod_Taylor(0)
{
    setCartesianCoordinates();
    update();
    mConstructed = true;
    mTimer = new QTimer(this);
    setCursor(Qt::CrossCursor);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(pendulumFunction()));
}



// public slots:

// Calcutates the equation of motion for the pendulum. The current angle depends on the amplitude and period of the pendulum as well as the running time.
// After this calculation the new x,y-coordinates are calculated, the time is increased and the pendulum is painted again.
void WirePendulum::pendulumFunction()
{
    double previousAngle  = mAngle;
    double previosAngle_Taylor = mAngle_Taylor;

    //small angle approximation
    mPeriod     = 2.0*M_PI*qSqrt(mPendulumLength/mGravity) * 1000.0;

    //taylor approximation, 6st order
    double amplitudeRadians = qDegreesToRadians(mAmplitude);
    mPeriod_Taylor    = 2.0*M_PI*qSqrt(mPendulumLength/mGravity)*( 1.0 +
                                                          1.0/16.0  * qPow(amplitudeRadians,2.0) +
                                                          11.0/3072.0 * qPow(amplitudeRadians,4.0) +
                                                          173.0/737280.0 * qPow(amplitudeRadians,6.0) ) * 1000.0;

    mAngle      = mAmplitude * qSin((2.0*M_PI/mPeriod*mMiliSeconds + M_PI/2));   // small angle approximation
    mAngle_Taylor     = mAmplitude * qSin((2.0*M_PI/mPeriod_Taylor*mMiliSeconds + M_PI/2)); // taylor approximation, 6st order

    //determine zeroPasses
    if (mStart)
    {

        if ((previousAngle/qFabs(previousAngle)) != mAngle/qFabs(mAngle) && (previousAngle != 0))
            mZeroPasses++;
        if ((previosAngle_Taylor/qFabs(previosAngle_Taylor)) != mAngle_Taylor/qFabs(mAngle_Taylor) && (previosAngle_Taylor != 0))
            mZeroPasses_Taylor++;
    }

    //set new x,y-coordinates for small angle approximation
    mX   = width()/2.0 + qCos(qDegreesToRadians(mAngle+90.0)) * mPendulumLengthPixels;
    mY   = qSin(qDegreesToRadians(mAngle+90.0)) * mPendulumLengthPixels;

    //set new x,y-coordinates for taylor approximation
    mX_Taylor  = width()/2.0 + qCos(qDegreesToRadians(mAngle_Taylor+90.0)) * mPendulumLengthPixels;
    mY_Taylor  = qSin(qDegreesToRadians(mAngle_Taylor+90.0)) * mPendulumLengthPixels;

    //increase time by 10 msecs
    mMiliSeconds = mMiliSeconds + 10;

    //refresh the painted pendulum
    update();
}


void WirePendulum::setPendulumLength(double length)
{
    mPendulumLength = length;
    setCartesianCoordinates();
    update();
}

void WirePendulum::setAmplitude(int amplitude)
{
    mAmplitude = amplitude;
    setCartesianCoordinates();
    update();
}

void WirePendulum::setGravityEarth(bool gravity)
{
    if (gravity)
        mGravity = 9.81;
}

void WirePendulum::setGravityJupiter(bool gravity)
{
    if (gravity)
        mGravity = 24.79;
}

void WirePendulum::setGravityMoon(bool gravity)
{
    if (gravity)
        mGravity = 1.62;
}

void WirePendulum::setGravitySaturn(bool gravity)
{
    if (gravity)
        mGravity = 10.44;
}

void WirePendulum::setGravitySun(bool gravity)
{
    if (gravity)
        mGravity = 274.0;
}

void WirePendulum::setGravityManually(double gravity)
{
    mGravity = gravity;
}

void WirePendulum::setSphereRadius(int sphereRadius)
{
    mSphereRadius = sphereRadius;
    setCartesianCoordinates();
    update();
}

void WirePendulum::setWireVisible(bool wireVisible)
{
    mWireVisible = wireVisible;
    update();
}

void WirePendulum::setShowScale(bool showScale)
{
    mShowScale = showScale;
    update();
}

void WirePendulum::setShowValues(bool showValues)
{
    mShowValues = showValues;
    update();
}

void WirePendulum::setSinglePendulum(bool singlePendulum)
{
    mSinglePendulum = singlePendulum;
    update();
}

void WirePendulum::setSmallAngleApproximation(bool smallAngleApprox)
{
    mSmallAngleApproximation = smallAngleApprox;
    update();
}

void WirePendulum::setTaylorApproximation(bool taylorApprox)
{
    mTaylorApproximation = taylorApprox;
    update();
}

void WirePendulum::setInstantStart(bool instantStart)
{
    mInstantStart = instantStart;
}

void WirePendulum::setPendulumColor( int color)
{
    mPendulumColor = color;
    update();
}

void WirePendulum::setPendulumColor_Taylor(int color_Taylor)
{
    mPendulumColor_Taylor = color_Taylor;
    update();
}

void WirePendulum::setZoomTo1(bool zoom1)
{
    if (zoom1)
        mZoom = 1;
    setCartesianCoordinates();
    update();
}
void WirePendulum::setZoomTo5(bool zoom5)
{
    if (zoom5)
        mZoom = 5;
    setCartesianCoordinates();
    update();
}

void WirePendulum::setZoomTo10(bool zoom10)
{
    if (zoom10)
        mZoom = 10;
    setCartesianCoordinates();
    update();
}
// end public slots


// protected functions:

// calculates, how many pixels are used to depict 1 meter, depending on the current zoom factor
double WirePendulum::getPixelsPerMeter()
{
    double factor;

    switch (mZoom) {
    case 10:
        // factor = MAX_PENDULUM_LENGTH + DEFAULT_SPHERE_SIZE
        factor = 1.0 + 0.2;
        break;
    case 5:
        // factor = MAX_PENDULUM_LENGTH + DEFAULT_SPHERE_SIZE
        factor = 2.0 + 0.2;
        break;
    case 1:
        // factor = MAX_PENDULUM_LENGTH + MAX_SPHERE_SIZE
        factor = 10.0 + 0.6;
        break;
    }
    return (mHeight-2.0) / factor;

}

//Calculates the cartesian coordinates from the current polar coordinates and sets the attributes for x,y-coordinates.
//The polar coordinates are used for amplitude and length of pendulum
void WirePendulum::setCartesianCoordinates()
{
    if (mConstructed) {
        mHeight = height();
        mWidth = width();
    }
    mSphereRadiusPixels   = mSphereRadius*0.01*getPixelsPerMeter();
    mPendulumLengthPixels  = mPendulumLength*getPixelsPerMeter();
    mX = mX_Taylor = mWidth/2.0 + qCos(qDegreesToRadians(mAmplitude+90.0)) * mPendulumLengthPixels;
    mY = mY_Taylor = qSin(qDegreesToRadians(mAmplitude+90.0)) * mPendulumLengthPixels;
}

//Calculates the polar coordinates for amplitude and length of pendulum
void WirePendulum::setPolarCoordinates()
{
    mPendulumLengthPixels  = qSqrt(qPow(mX - width()/2.0 , 2.0) + qPow(mY , 2.0));
    mPendulumLength    = mPendulumLengthPixels / getPixelsPerMeter();
    mAmplitude      = qRadiansToDegrees(qAcos((mX - width() / 2.0) / mPendulumLengthPixels)) - 90.0;
}


QColor WirePendulum::getColor(int color)
{
    switch (color)
    {
        case 0:
            //blue
            return QColor(20, 90, 210);
        case 1:
            //violet
            return QColor(170, 80, 210);
        case 2:
            //green
            return QColor(0, 170, 20);
        case 3:
            //red
            return QColor(210, 50, 50);
    }
}

//returns the run time as a formatted string
QString WirePendulum::getTimeString()
{
    QString hour0="";
    QString minute0="";
    QString second0="";
    QString miliSecond0="";

    int hours = mMiliSeconds/(60*60*1000);
    int minutes = (mMiliSeconds%(60*60*1000))/(60*1000);
    int seconds = ((mMiliSeconds%(60*60*1000))%(60*1000))/1000;
    int miliSeconds = (((mMiliSeconds%(60*60*1000))%(60*1000))%1000);
    if (hours < 10)
        hour0 = "0";
    if (minutes < 10)
        minute0 = "0";
    if (seconds < 10)
        second0 = "0";
    if (miliSeconds < 10)
        miliSecond0 = "00";
    else if (miliSeconds <100)
        miliSecond0 = "0";

    return QString("%1%2 : %3%4 : %5%6 : %7%8").arg(hour0).arg(hours).arg(minute0).arg(minutes).arg(second0).arg(seconds).arg(miliSecond0).arg(miliSeconds);
}

//Sets the cartesian coordinates for the pendulum depending on the x,y-coordinates of a MouseEvent.
//The Determination of the cartesian coordinates differs depending on the pendulum type and
//ensures, that the sphere of the pendulum never leaves the image boarder.
void WirePendulum::getXY(QMouseEvent *event)
{
    // single pendulum
    if (mSinglePendulum)
    {
        if (event->x() < mSphereRadiusPixels)
            mX = mX_Taylor = mSphereRadiusPixels;
        else if(event->x() > this->width()-mSphereRadiusPixels)
            mX = mX_Taylor = this->width()-mSphereRadiusPixels;
        else
            mX = mX_Taylor = event->x();
        if (event->y() < 0)
            mY = mY_Taylor =  0;
        else if(event->y() > this->height()-mSphereRadiusPixels)
            mY = mY_Taylor = this->height()-mSphereRadiusPixels;
        else
            mY = mY_Taylor = event->y();
     }
    //5 sphere pendulum
    else
    {
        if (event->x() < width()/2-4*mSphereRadiusPixels)
        {
            mSide=1;
            if (event->x() < mSphereRadiusPixels)
                mX = mSphereRadiusPixels+4*mSphereRadiusPixels;
            else
                mX = event->x()+4*mSphereRadiusPixels;
        }
        else if (event->x() > width()/2+4*mSphereRadiusPixels)
        {
            mSide=2;
            if (event->x() > this->width()-mSphereRadiusPixels)
                mX = this->width()-mSphereRadiusPixels-4*mSphereRadiusPixels;
            else
                mX = event->x()-4*mSphereRadiusPixels;
        }
        else
            mSide=0;
        if (event->y() < 0)
            mY = 0;
        else if(event->y() > this->height()-mSphereRadiusPixels)
            mY = this->height()-mSphereRadiusPixels;
        else
            mY = event->y();
    }
}

// events:

//If the pendulum is not running, mouseMoveEvent and MousePressEvent call getXY()
//to get the cartesian coordinates depending on the mouse position,
//emit a signal to update the controls and update the painted area
void WirePendulum::mouseMoveEvent(QMouseEvent *event)
{
    if (!mStart)
    {
        getXY(event);
        emit coordinatesChangedAfterMouseEvent();
        update();
    }
}

void WirePendulum::mousePressEvent(QMouseEvent *event)
{
    if (!mStart)
    {
        getXY(event);
        emit coordinatesChangedAfterMouseEvent();
        update();
    }
}

//mouseReleasEvent starts the pendulum, if instant start on mouse release is activated and the pendulum is not already running
void WirePendulum::mouseReleaseEvent(QMouseEvent *event)
{
    if (mInstantStart)
        emit instantStart(!mStart);

}

//paints the values of the pendulum
void WirePendulum::paintValues(QString string, int x, int y, int angle,int period, int zeroPasses, int offset, int color, QPainter *painter)
{
    painter->setPen(QPen(getColor(color),1));
    painter->drawText(5,height()-71-offset, string);
    painter->drawText(5,height()-60-offset, QString("--------------------------------------------"));
    painter->drawText(5,height()-49-offset, QString("x-Koordinate\t\t%1").arg(x));
    painter->drawText(5,height()-38-offset, QString("y-Koordinate\t\t%1").arg(y));
    painter->drawText(5,height()-27-offset, QString("Winkel:\t\t%1").arg(angle));
    painter->drawText(5,height()-16-offset, QString("Periode:\t\t%1").arg(period));
    painter->drawText(5,height()-5-offset, QString("Nulldurchgänge:\t%1").arg(zeroPasses));
}

//paints the pendulum
void WirePendulum::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);

    // background
    QColor colorBackground(30, 30, 30);
    QBrush brush(colorBackground);
    painter->fillRect(0,0,width(),height(),brush);

    // scale
    painter->setPen(QPen(QColor(255, 240, 120),1));
    if (mShowScale) {

        painter->drawLine(width()-24,0, width()-16,0);
        painter->drawLine(width()-20,0, width()-20, getPixelsPerMeter()); // scale
        painter->drawLine(width()-24,getPixelsPerMeter(), width()-16,getPixelsPerMeter());
        painter->drawText(width()-35,getPixelsPerMeter()+15, "1.0m");
    }

    // values as text
    if (mShowValues)
    {
        painter->drawText(5,12, QString("Laufzeit:  %1").arg(getTimeString()));
        int angleText = mAmplitude;
        if (mTaylorApproximation && !mSmallAngleApproximation)
        {
            if (mStart)
                angleText = mAngle_Taylor;
            paintValues("Taylornäherung:", mX_Taylor, mY_Taylor, angleText, mPeriod_Taylor, mZeroPasses_Taylor, 0, mPendulumColor_Taylor, painter);
        }
        else if (!mTaylorApproximation && mSmallAngleApproximation)
        {
            if (mStart)
                angleText = mAngle;
            paintValues("Kleinwinkelnäherung:", mX, mY, angleText, mPeriod, mZeroPasses, 0, mPendulumColor, painter);
        }
        else if (mSmallAngleApproximation && mTaylorApproximation)
        {
            if (mStart)
                angleText = mAngle;
            paintValues("Kleinwinkelnäherung:", mX, mY, angleText, mPeriod, mZeroPasses, 88, mPendulumColor, painter);

            if (mStart)
                angleText = mAngle;
            paintValues("Taylornäherung:", mX_Taylor, mY_Taylor, angleText, mPeriod_Taylor, mZeroPasses_Taylor, 0, mPendulumColor_Taylor, painter);
        }
    }

    // pendulum wire color
    QColor colorWire(colorBackground);
    if (mWireVisible)
        colorWire.setRgb(120,120,120);


    QColor color;
    QPoint m(mX,mY);
    QPoint m_Taylor(mX_Taylor,mY_Taylor);

    // single sphere pendulum
    if (mSinglePendulum) {
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen( QPen(colorWire, 2) );
        if (mSmallAngleApproximation)
        {
            color = getColor(mPendulumColor);
            painter->drawLine(width()/2,0, mX,mY);

            QRadialGradient sphereGradient(m.x()+mSphereRadiusPixels/4,m.y()+mSphereRadiusPixels/4,mSphereRadiusPixels*2);
            sphereGradient.setColorAt(0.0, Qt::lightGray);
            sphereGradient.setColorAt(0.2, color);
            sphereGradient.setColorAt(0.7, QColor(0,0,0));
            QPainterPath sphere;
            sphere.addEllipse(m,mSphereRadiusPixels,mSphereRadiusPixels);
            painter->fillPath(sphere,sphereGradient);
        }
        if (mTaylorApproximation)
        {
            color = getColor(mPendulumColor_Taylor);
            painter->drawLine(width()/2,0, mX_Taylor,mY_Taylor);
            QRadialGradient sphereGradient_Taylor(m_Taylor.x()+mSphereRadiusPixels/4,m_Taylor.y()+mSphereRadiusPixels/4,mSphereRadiusPixels*2);
            sphereGradient_Taylor.setColorAt(0.0, Qt::lightGray);
            sphereGradient_Taylor.setColorAt(0.2, color);
            sphereGradient_Taylor.setColorAt(0.7, QColor(0,0,0));
            QPainterPath sphere_Taylor;
            sphere_Taylor.addEllipse(m_Taylor,mSphereRadiusPixels,mSphereRadiusPixels);
            painter->fillPath(sphere_Taylor,sphereGradient_Taylor);
        }
    }

    // 5 spheres pendulum
    else
    {
        double fX, fY;
        double fAngle;
        if (mSmallAngleApproximation)
        {
            fX = mX;
            fY = mY;
            fAngle = mAngle;
            color = getColor(mPendulumColor);
        }
        else
        {
            fX = mX_Taylor;
            fY = mY_Taylor;
            fAngle = mAngle_Taylor;
            color = getColor(mPendulumColor_Taylor);
        }
        QPoint m[5];

        if ((mStart==true && fAngle<0)  || (mStart==false && mAmplitude<0 && !mSide) || (mStart==false && mSide==2))
        {
            m[0] += QPoint(width()/2-4*mSphereRadiusPixels,mPendulumLengthPixels);
            m[4] += QPoint(fX+4*mSphereRadiusPixels,fY);
        }
        else
        {
            m[0] += QPoint(fX-4*mSphereRadiusPixels,fY);
            m[4] += QPoint(width()/2+4*mSphereRadiusPixels, mPendulumLengthPixels);
        }
        mSide=0;
        m[1] += QPoint(width()/2-2*mSphereRadiusPixels, mPendulumLengthPixels);
        m[2] += QPoint(width()/2,               mPendulumLengthPixels);
        m[3] += QPoint(width()/2+2*mSphereRadiusPixels, mPendulumLengthPixels);

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen( QPen(colorWire, 2) );

        int xi=width()/2-4*mSphereRadiusPixels;
        for (int i=0 ; i<5 ; i++)
        {
            painter->drawLine(xi,0, m[i].x(),m[i].y());
            xi += 2*mSphereRadiusPixels;
        }

        QPainterPath spheres[5];
        QRadialGradient sphereGradients[5];
        for (int i=0 ; i<5 ; i++ ) {
            sphereGradients[i].setCenter(m[i].x()+mSphereRadiusPixels/4,m[i].y()+mSphereRadiusPixels/4);
            sphereGradients[i].setFocalPoint(sphereGradients[i].center());
            sphereGradients[i].setCenterRadius(mSphereRadiusPixels*2);
            sphereGradients[i].setColorAt(0.0, Qt::lightGray);
            sphereGradients[i].setColorAt(0.2, color);
            sphereGradients[i].setColorAt(0.7, QColor(0,0,0));
            spheres[i].addEllipse(m[i],mSphereRadiusPixels,mSphereRadiusPixels);
            painter->fillPath(spheres[i],sphereGradients[i]);
        }
    }
    painter->end();
}

// end protected functions
