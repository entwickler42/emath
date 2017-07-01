#ifndef EMATH_GLOBAL_H
#define EMATH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EMATH_LIBRARY)
#  define EMATHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EMATHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EMATH_GLOBAL_H
