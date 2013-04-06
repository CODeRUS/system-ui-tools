#include "MToolsBluetooth.h"

const int RADIO = 8;

MToolsBluetooth::MToolsBluetooth(QGraphicsObject *parent):
    MToolsWidgetAbstract(true, parent)
{
    addIcon("icon-tools-bluetooth-off");
    addIcon("icon-tools-bluetooth-on");

    setIcon(0);

    fs = new QFileSystemWatcher(QStringList() << QString("/var/lib/mce"), this);
    connect(fs, SIGNAL(directoryChanged(QString)), this, SLOT(mceChanged(QString)));
    mceChanged("");
}

void MToolsBluetooth::enterDisplayEvent()
{
}

void MToolsBluetooth::exitDisplayEvent()
{
}

void MToolsBluetooth::shortAction()
{
    int new_radio_states = RADIO;
    if (m_radioState & RADIO)
        new_radio_states = 0;

    m_radioState = new_radio_states;
    int radio_states_mask = RADIO;

    system(QString("dbus-send --print-reply --system --dest=com.nokia.mce /com/nokia/mce/request com.nokia.mce.request.req_radio_states_change uint32:%1 uint32:%2").arg(new_radio_states).arg(radio_states_mask).toAscii());
}

void MToolsBluetooth::longAction()
{
    QDBusInterface("com.nokia.DuiControlPanel",
                   "/",
                   "com.nokia.DuiControlPanelIf",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "appletPage", "Bluetooth");
}

void MToolsBluetooth::mceChanged(const QString &filename)
{
    Q_UNUSED(filename);

    QFile mce(QString("/var/lib/mce/radio_states.online"));
    mce.open(QFile::ReadOnly);
    m_radioState = mce.readAll().toInt();
    mce.close();

    if (m_radioState & RADIO)
        setIcon(1);
    else
        setIcon(0);
}
