#include "MToolsBG.h"

MToolsBG::MToolsBG(QGraphicsObject *parent):
    MToolsWidgetAbstract(true, parent)
{
    addIcon("icon-tools-background-off");
    addIcon("icon-tools-background-on");

    setIcon(1);

    m_gconf_bgconn_mode = new GConfItem("/system/osso/connectivity/network_type/restricted_mode");
    connect(m_gconf_bgconn_mode, SIGNAL(valueChanged()), this, SLOT(onValueChanged()));
}

void MToolsBG::enterDisplayEvent()
{
    onValueChanged();
}

void MToolsBG::exitDisplayEvent()
{
}

void MToolsBG::shortAction()
{
    m_gconf_bgconn_mode->set(!m_gconf_bgconn_mode->value().toBool());
}

void MToolsBG::longAction()
{
    QDBusInterface("com.nokia.DuiControlPanel",
                   "/",
                   "com.nokia.DuiControlPanelIf",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "appletPage", "Internet");
}

void MToolsBG::onValueChanged()
{
    if (m_gconf_bgconn_mode->value().toBool())
        setIcon(0);
    else
        setIcon(1);
}
