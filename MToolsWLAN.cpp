#include "MToolsWLAN.h"
#define RADIO 4

MToolsWLAN::MToolsWLAN(QGraphicsObject *parent):
    MToolsWidgetAbstract(true, parent)
{
    addIcon("icon-tools-wlan-off");
    addIcon("icon-m-status-menu-no-internet-connection");
    addIcon("icon-m-common-wlan-strength5");
    addIcon("icon-m-common-wlan-strength4");
    addIcon("icon-m-common-wlan-strength3");
    addIcon("icon-m-common-wlan-strength2");
    addIcon("icon-m-common-wlan-strength1");
    addIcon("icon-m-common-packetdata");
    addIcon("icon-tools-wlan-connecting");

    setIcon(0);

    spinner = new MProgressIndicator(this, MProgressIndicator::spinnerType);
    spinner->setUnknownDuration(true);
    spinner->setStyleName("CommonListItemSpinnerInverted");
    spinner->setVisible(false);
    spinner->setPos(16,16);

    network = new QSystemNetworkInfo(this);
    nType = new ContextProperty("Internet.NetworkType", this);
    nState = new ContextProperty("Internet.NetworkState", this);

    fs = new QFileSystemWatcher(QStringList() << QString("/var/lib/mce"), this);
    connect(fs, SIGNAL(directoryChanged(QString)), this, SLOT(mceChanged(QString)));
    mceChanged("");

}

void MToolsWLAN::enterDisplayEvent()
{
    QDBusInterface("com.nokia.icd_ui",
                   "/com/nokia/icd_ui",
                   "com.nokia.icd_ui",
                   QDBusConnection::systemBus(),
                   this).call(QDBus::NoBlock,
                              "scan_req", 0);
}

void MToolsWLAN::exitDisplayEvent()
{
}

void MToolsWLAN::shortAction()
{
    int new_radio_states = RADIO;
    if (m_radioState & RADIO)
        new_radio_states = 0;
    m_radioState = new_radio_states;
    int radio_states_mask = RADIO;

    system(QString("dbus-send --print-reply --system --dest=com.nokia.mce /com/nokia/mce/request com.nokia.mce.request.req_radio_states_change uint32:%1 uint32:%2 &").arg(new_radio_states).arg(radio_states_mask).toAscii());
}

void MToolsWLAN::longAction()
{
    QDBusInterface("com.nokia.icd_ui",
                   "/com/nokia/icd_ui",
                   "com.nokia.icd_ui",
                   QDBusConnection::systemBus(),
                   this).call(QDBus::NoBlock,
                              "show_conn_dlg", true);
}

void MToolsWLAN::mceChanged(const QString &filename)
{
    Q_UNUSED(filename);

    QFile mce(QString("/var/lib/mce/radio_states.online"));
    mce.open(QFile::ReadOnly);
    m_radioState = mce.readAll().toInt();
    mce.close();

    if (m_radioState & RADIO)
    {
        networkTypeChanged();

        connect(nType, SIGNAL(valueChanged()), this, SLOT(networkTypeChanged()));
        connect(nState, SIGNAL(valueChanged()), this, SLOT(networkStateChanged()));
    }
    else
    {
        disconnect(nType, SIGNAL(valueChanged()), this, SLOT(networkTypeChanged()));
        disconnect(nState, SIGNAL(valueChanged()), this, SLOT(networkStateChanged()));

        setIcon(0);
    }
}

void MToolsWLAN::ssChanged(QSystemNetworkInfo::NetworkMode mode, int value)
{
    Q_UNUSED(value);

    if (mode == QSystemNetworkInfo::WlanMode)
    {
        if (value < 74)
            setIcon(6);
        else if (value < 77)
            setIcon(5);
        else if (value < 80)
            setIcon(4);
        else if (value < 85)
            setIcon(3);
        else
            setIcon(2);
    }
}

void MToolsWLAN::networkTypeChanged()
{
    QString type = nType->value().toString();
    if (type.startsWith(QString("WLAN")))
    {
        connect(network,
                SIGNAL(networkSignalStrengthChanged(QSystemNetworkInfo::NetworkMode,int)),
                this,
                SLOT(ssChanged(QSystemNetworkInfo::NetworkMode,int)),
                Qt::UniqueConnection);

        ssChanged(QSystemNetworkInfo::WlanMode, network->networkSignalStrength(QSystemNetworkInfo::WlanMode));
//        setIcon(2);
    }
    else
    {
        disconnect(network,
                SIGNAL(networkSignalStrengthChanged(QSystemNetworkInfo::NetworkMode,int)),
                this,
                SLOT(ssChanged(QSystemNetworkInfo::NetworkMode,int)));

        if (type == QString("GPRS"))
        {
            setIcon(7);
        }
        else
            setIcon(1);
    }
}

void MToolsWLAN::networkStateChanged()
{
    QString state = nState->value().toString();
    if (state == QString("connected"))
    {
        networkTypeChanged();
        spinner->setVisible(false);
    }
    else if (state == QString("connecting"))
    {
        setIcon(8);
        spinner->setVisible(true);
    }
    else if (state == QString("disconnected"))
    {
        setIcon(1);
        spinner->setVisible(false);
    }
}
