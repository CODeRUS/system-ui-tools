#ifndef MToolsBluetooth_H
#define MToolsBluetooth_H

#include "MToolsWidgetAbstract.h"

class MToolsBluetooth: public MToolsWidgetAbstract
{
    Q_OBJECT

public:
    explicit MToolsBluetooth(QGraphicsObject *parent);

protected:
    void enterDisplayEvent();
    void exitDisplayEvent();

private:
    void shortAction();
    void longAction();

    int m_radioState;

    QFileSystemWatcher *fs;

private slots:
    void mceChanged(const QString & filename);
};

#endif // MToolsBluetooth_H
