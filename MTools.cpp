#include "MTools.h"

MTools::MTools(QGraphicsItem *parent):
    MWidget(parent)
{
    m_layout = new MLayout(this);
    m_mainLayout = new MLinearLayoutPolicy(m_layout, Qt::Horizontal);
    m_mainLayout->setHorizontalSpacing(12);
    m_mainLayout->setContentsMargins(0,0,0,0);

    m_mainLayout->addItem(new MToolsBluetooth(0));
    m_mainLayout->addItem(new MToolsNFC(0));
    m_mainLayout->addItem(new MToolsRadio(0));
    m_mainLayout->addItem(new MToolsWLAN(0));
    m_mainLayout->addItem(new MToolsBG(0));
    m_mainLayout->addItem(new MToolsFlightmode(0));
}

MTools::~MTools()
{
}
