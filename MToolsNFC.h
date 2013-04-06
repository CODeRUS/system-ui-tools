#ifndef MTOOLSNFC_H
#define MTOOLSNFC_H

#include "MToolsWidgetAbstract.h"

class MToolsNFC: public MToolsWidgetAbstract
{
    Q_OBJECT

public:
    explicit MToolsNFC(QGraphicsObject *parent);

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

#endif // MTOOLSNFC_H
