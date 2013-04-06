TEMPLATE      = lib
QT += core dbus network
CONFIG       += plugin gui meegotouch link_pkgconfig mobility
PKGCONFIG += gq-gconf
MOBILITY += systeminfo

INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/meegotouch
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/system-ui/statusindicatormenu
INCLUDEPATH += $$(SYSROOT_DIR)/usr/include/qt4/QtSystemInfo

TARGET        = statusindicatormenu-tools
target.path = /usr/lib/meegotouch/applicationextensions

png.files = icons/icon-tools-bluetooth-off.png \
	    icons/icon-tools-bluetooth-on.png \
	    icons/icon-tools-gsm-off.png \
	    icons/icon-tools-gsm-on.png \
	    icons/icon-tools-flightmode-off.png \
	    icons/icon-tools-flightmode-on.png \
	    icons/icon-tools-nfc-off.png \
	    icons/icon-tools-nfc-on.png \
	    icons/icon-tools-background-off.png \
	    icons/icon-tools-background-on.png \
	    icons/icon-tools-wlan-connecting.png \
	    icons/icon-tools-wlan-off.png \
	    icons/icon-tools-wlan-on.png
png.path = /usr/share/themes/blanco/meegotouch/icons

desktop.files = statusindicatormenu-tools.desktop
desktop.path = /usr/share/meegotouch/applicationextensions

INSTALLS += target png desktop

HEADERS += \
    MTools.h \
    MToolsBluetooth.h \
    MToolsWidgetAbstract.h \
    MToolsRadio.h \
    MExtensionPlugin.h \
    MExtensionController.h \
    MToolsWLAN.h \
    MToolsNFC.h \
    MToolsFlightmode.h \
    MToolsBG.h

SOURCES += \
    MTools.cpp \
    MToolsBluetooth.cpp \
    MToolsWidgetAbstract.cpp \
    MToolsRadio.cpp \
    MExtensionController.cpp \
    MExtensionPlugin.cpp \
    MToolsWLAN.cpp \
    MToolsNFC.cpp \
    MToolsFlightmode.cpp \
    MToolsBG.cpp

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/prerm \
    qtc_packaging/debian_harmattan/postrm \
    qtc_packaging/debian_harmattan/preinst \
    qtc_packaging/debian_harmattan/postinst \
    qtc_packaging/debian_harmattan/changelog
