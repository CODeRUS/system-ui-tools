#include "MToolsFlightmode.h"

MToolsFlightmode::MToolsFlightmode(QGraphicsObject *parent):
    MToolsWidgetAbstract(false, parent),
    m_deviceMode(new MeeGo::QmDeviceMode(this))
{
    addIcon("icon-tools-flightmode-off");
    addIcon("icon-tools-flightmode-on");

    setIcon(0);

    connect(m_deviceMode, SIGNAL(deviceModeChanged(MeeGo::QmDeviceMode::DeviceMode)),
                this, SLOT(onDeviceModeChanged(MeeGo::QmDeviceMode::DeviceMode)));
    onDeviceModeChanged(m_deviceMode->getMode());
}

void MToolsFlightmode::enterDisplayEvent()
{
}

void MToolsFlightmode::exitDisplayEvent()
{
}

void MToolsFlightmode::shortAction()
{
    MeeGo::QmDeviceMode::DeviceMode mode = m_deviceMode->getMode();
    if (mode == MeeGo::QmDeviceMode::Flight)
        m_deviceMode->setMode(MeeGo::QmDeviceMode::Normal);
    else if (mode == MeeGo::QmDeviceMode::Normal)
        m_deviceMode->setMode(MeeGo::QmDeviceMode::Flight);
}

void MToolsFlightmode::longAction()
{
}

void MToolsFlightmode::onDeviceModeChanged(MeeGo::QmDeviceMode::DeviceMode mode)
{
    if (mode == MeeGo::QmDeviceMode::Flight)
        setIcon(1);
    else
        setIcon(0);
}

