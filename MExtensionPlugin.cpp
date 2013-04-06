#include "MExtensionPlugin.h"
#include "MExtensionController.h"

Q_EXPORT_PLUGIN2(systemuitools, MExtensionsPlugin)

MExtensionsPlugin::MExtensionsPlugin(QObject *parent) :
    statusIndicatorMenu(0),
    m_extensionsController(0)
{
    Q_UNUSED(parent)
}

void MExtensionsPlugin::setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface)
{
    statusIndicatorMenu = &menuInterface;
}

MStatusIndicatorMenuInterface *MExtensionsPlugin::statusIndicatorMenuInterface() const
{
    return statusIndicatorMenu;
}

bool MExtensionsPlugin::initialize(const QString &)
{
    m_extensionsController = new MExtensionsController(this);

    return true;
}

QGraphicsWidget *MExtensionsPlugin::widget()
{
    return m_extensionsController;
}
