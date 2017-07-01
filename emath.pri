INCLUDEPATH += $$PWD

SOURCES += $$PWD/emath.cpp \
			  $$PWD/emsi.cpp

HEADERS += $$PWD/emath_global.h \
				$$PWD/emath.h \
				$$PWD/emsi.h

DEFINES += EMATH_LIBRARY

OTHER_FILES += GPLv2 LICENSE README
