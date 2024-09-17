QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.

SOURCES += \
    calccredit.cpp \
    calcdeposit.cpp \
    form.cpp \
    main.cpp \
    mainwindow.cpp \
    ../controller/controller_calculator.cpp \
    ../model/calc_model.cpp \
    ../controller/controller_credit.cpp \
    ../model/credit_model.cpp \
    ../controller/controller_deposit.cpp \
    ../model/deposit_model.cpp \
    qcustomplot.cpp

HEADERS += \
    calccredit.h \
    calcdeposit.h \
    form.h \
    mainwindow.h \
    ../controller/controller_calculator.h \
    ../model/calc_model.h \
    ../controller/controller_credit.h \
    ../controller/controller_deposit.h \
    ../model/credit_model.h \
    ../model/deposit_model.h \
    qcustomplot.h

FORMS += \
    calccredit.ui \
    calcdeposit.ui \
    form.ui \
    mainwindow.ui

TRANSLATIONS += \
    SmartCalc_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    gary.png \
    scridward.jpg