#ifndef APPLETTOOLSRADIO_H
#define APPLETTOOLSRADIO_H

#include "MToolsWidgetAbstract.h"

class MToolsRadio: public MToolsWidgetAbstract
{
    Q_OBJECT

public:
    explicit MToolsRadio(QGraphicsObject *parent);

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

#endif // APPLETTOOLSRADIO_H
