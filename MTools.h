#ifndef APPLETTOOLS_H
#define APPLETTOOLS_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <MLinearLayoutPolicy>
#include <MLayout>
#include <QGraphicsSceneMouseEvent>
#include <QDBusConnection>
#include <gq/GConfItem>

#include "MToolsWidgetAbstract.h"
#include "MToolsBluetooth.h"
#include "MToolsRadio.h"
#include "MToolsWLAN.h"
#include "MToolsNFC.h"
#include "MToolsFlightmode.h"
#include "MToolsBG.h"

class MTools : public MWidget
{

   Q_OBJECT

public:
    explicit MTools(QGraphicsItem *parent = 0);
    virtual ~MTools();

private:
    MLinearLayoutPolicy *m_mainLayout;
    MLayout *m_layout;

};

#endif // APPLETTOOLS_H
