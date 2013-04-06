#include "MToolsNFC.h"
#define RADIO 16

MToolsNFC::MToolsNFC(QGraphicsObject *parent):
    MToolsWidgetAbstract(true, parent)
{
    addIcon("icon-tools-nfc-off");
    addIcon("icon-tools-nfc-on");

    setIcon(0);

    fs = new QFileSystemWatcher(QStringList() << QString("/var/lib/mce"), this);
    connect(fs, SIGNAL(directoryChanged(QString)), this, SLOT(mceChanged(QString)));
    mceChanged("");
}

void MToolsNFC::enterDisplayEvent()
{
}

void MToolsNFC::exitDisplayEvent()
{
}

void MToolsNFC::shortAction()
{
    int new_radio_states = RADIO;
    if (m_radioState & RADIO)
        new_radio_states = 0;
    m_radioState = new_radio_states;
    int radio_states_mask = RADIO;

    system(QString("dbus-send --print-reply --system --dest=com.nokia.mce /com/nokia/mce/request com.nokia.mce.request.req_radio_states_change uint32:%1 uint32:%2").arg(new_radio_states).arg(radio_states_mask).toAscii());
}

void MToolsNFC::longAction()
{
    QDBusInterface("com.nokia.DuiControlPanel",
                   "/",
                   "com.nokia.DuiControlPanelIf",
                   QDBusConnection::sessionBus(),
                   this).call(QDBus::NoBlock,
                              "appletPage", "Near Field Communication");
}

void MToolsNFC::mceChanged(const QString &filename)
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

