#include "MToolsWidgetAbstract.h"

MToolsWidgetAbstract::MToolsWidgetAbstract(bool using_longtap, QGraphicsObject *parent):
    MImageWidget(parent)
{
    setMaximumSize(64,64);
    setMinimumSize(64,64);
    setAspectRatioMode(Qt::KeepAspectRatio);

    feedback_press = new MFeedback("priority2_static_press", this);
    feedback_release = new MFeedback("priority2_static_release", this);
    feedback_long = new MFeedback("priority2_grab", this);

    GConfItem *theme = new GConfItem("/meegotouch/theme/CurrentMeegoTheme", this);
    currentTheme = theme->value("blanco").toString();
    theme->deleteLater();

    if (using_longtap)
        grabGesture(Qt::TapAndHoldGesture);
}

void MToolsWidgetAbstract::addIcon(QString iconId)
{
    QString extraPath = QString("/home/user/.system-ui-tools/%1.png").arg(iconId);
    QString themePath = QString("/usr/share/themes/%1/meegotouch/icons/%2.png").arg(currentTheme).arg(iconId);
    if (QFile(extraPath).exists())
        m_icons.append(QImage(extraPath));
    else if (QFile(themePath).exists())
        m_icons.append(QImage(themePath));
    else
        m_icons.append(QImage(QString("/usr/share/themes/base/meegotouch/icons/%1.png").arg(iconId)));
}

void MToolsWidgetAbstract::setIcon(int index)
{
    setImage(m_icons.at(index));
}

bool MToolsWidgetAbstract::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        if (static_cast<QGestureEvent*>(event)->gesture(Qt::TapAndHoldGesture)->state() == Qt::GestureFinished && !action)
        {
            action = true;
            feedback_long->play();
            longAction();
            return true;
        }
    }
    return MImageWidget::event(event);
}

void MToolsWidgetAbstract::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    feedback_press->play();
    action = false;

    event->accept();
}

void MToolsWidgetAbstract::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!action && contentsRect().contains(event->pos()))
    {
        action = true;
        feedback_release->play();
        shortAction();

        event->accept();
    }
}
