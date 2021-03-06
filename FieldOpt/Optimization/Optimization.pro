include(../defaults.pri)


CONFIG   -= app_bundle
CONFIG += c++11

LIBS += -L$$OUT_PWD/../Model -lmodel
LIBS += -L$$OUT_PWD/../Simulation -lsimulation

TEMPLATE = lib

TARGET = optimization

HEADERS += \
    objective/objective.h \
    objective/weightedsum.h \
    case.h \
    optimization_exceptions.h \
    case_handler.h \
    constraints/constraint.h \
    constraints/box_constraint.h \
    constraints/constraint_handler.h \
    optimizer.h \
    optimizers/compass_search.h

SOURCES += \
    objective/objective.cpp \
    objective/weightedsum.cpp \
    case.cpp \
    case_handler.cpp \
    constraints/constraint.cpp \
    constraints/box_constraint.cpp \
    constraints/constraint_handler.cpp \
    optimizer.cpp \
    optimizers/compass_search.cpp
