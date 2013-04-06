#ifndef APPLICATIONEXTENSIONCONTROLLER_H
#define APPLICATIONEXTENSIONCONTROLLER_H

#include <MWidget>
#include <MLayout>
#include <MLinearLayoutPolicy>

#include <QObject>
#include <QDBusConnection>

#include "MExtensionPlugin.h"
#include "MTools.h"

class MStatusIndicatorMenuInterface;

class MExtensionsController : public MWidget
{
    Q_OBJECT

public:
    explicit MExtensionsController(MExtensionsPlugin *extensionsPlugin, QGraphicsItem *parent = NULL);
    virtual ~MExtensionsController();

private:
    MLayout *m_layout;
    MLinearLayoutPolicy *m_mainLayout;
    MExtensionsPlugin *m_extensionsPlugin;

    MTools *a_tools;
};

#endif // APPLICATIONEXTENSIONCONTROLLER_H
