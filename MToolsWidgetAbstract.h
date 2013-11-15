#ifndef MToolsWidgetAbstract_H
#define MToolsWidgetAbstract_H

#include <MImageWidget>
#include <gq/GConfItem>
#include <QGraphicsSceneMouseEvent>
#include <QGesture>
#include <QEvent>
#include <QGestureEvent>
#include <MFeedback>
#include <QFile>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QFileSystemWatcher>

#include <mce/mode-names.h>
#include <mce/dbus-names.h>

class MToolsWidgetAbstract: public MImageWidget
{
public:
    explicit MToolsWidgetAbstract(bool using_longtap, QGraphicsObject *parent);
    void addIcon(QString iconId);
    void setIcon(int index);

protected:
    bool event(QEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    virtual void shortAction() = 0;
    virtual void longAction() = 0;

    GConfItem *m_key_status;
    GConfItem *m_key_index;

    MFeedback *feedback_press;
    MFeedback *feedback_release;
    MFeedback *feedback_long;

    QString currentTheme;

    QList<QImage> m_icons;

    bool action;
};

#endif // MToolsWidgetAbstract_H
