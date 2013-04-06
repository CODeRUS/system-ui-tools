#ifndef MTOOLSWLAN_H
#define MTOOLSWLAN_H

#include <contextsubscriber/contextproperty.h>
#include <QSystemNetworkInfo>
#include <MProgressIndicator>
#include <MTheme>

#include "MToolsWidgetAbstract.h"

using namespace QtMobility;

class MToolsWLAN: public MToolsWidgetAbstract
{
    Q_OBJECT

public:
    explicit MToolsWLAN(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    MProgressIndicator *spinner;

    int m_radioState;
    QFileSystemWatcher *fs;

    QSystemNetworkInfo *network;
    ContextProperty *nType;
    ContextProperty *nState;

private slots:
    void mceChanged(const QString & filename);
    void ssChanged(QSystemNetworkInfo::NetworkMode mode, int value);
    void networkTypeChanged();
    void networkStateChanged();
};

#endif // MTOOLSWLAN_H
