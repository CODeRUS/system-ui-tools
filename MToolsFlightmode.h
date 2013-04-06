#ifndef MTOOLSFLIGHTMODE_H
#define MTOOLSFLIGHTMODE_H

#include "MToolsWidgetAbstract.h"
#include <qmsystem2/qmdevicemode.h>

class MToolsFlightmode: public MToolsWidgetAbstract
{
    Q_OBJECT

public:
    explicit MToolsFlightmode(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    MeeGo::QmDeviceMode *m_deviceMode;

private slots:
    void onDeviceModeChanged(MeeGo::QmDeviceMode::DeviceMode mode);
};

#endif // MTOOLSFLIGHTMODE_H
