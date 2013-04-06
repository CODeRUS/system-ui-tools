#ifndef MTOOLSSETTINGS_H
#define MTOOLSSETTINGS_H

#include "MToolsWidgetAbstract.h"

class MToolsBG: public MToolsWidgetAbstract
{
    Q_OBJECT

public:
    explicit MToolsBG(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    GConfItem *m_gconf_bgconn_mode;

private slots:
    void onValueChanged();
};

#endif // MTOOLSSETTINGS_H
