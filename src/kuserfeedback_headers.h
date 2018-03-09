#ifndef KUSERFEEDBACK_HEADERS_H
#define KUSERFEEDBACK_HEADERS_H

// Provider - central object managing data sources and transmitting feedback to the server.
#include <kuserfeedback/core/provider.h>

// Widgets
#include <kuserfeedback/widgets/notificationpopup.h>
#include <kuserfeedback/widgets/feedbackconfigdialog.h>

// Data Sources
#include <kuserfeedback/core/applicationversionsource.h>
#include <kuserfeedback/core/compilerinfosource.h>
#include <kuserfeedback/core/cpuinfosource.h>
#include <kuserfeedback/core/localeinfosource.h>
#include <kuserfeedback/core/openglinfosource.h>
#include <kuserfeedback/core/platforminfosource.h>
#include <kuserfeedback/core/qpainfosource.h>
#include <kuserfeedback/core/qtversionsource.h>
#include <kuserfeedback/core/screeninfosource.h>
#include <kuserfeedback/core/startcountsource.h>
#include <kuserfeedback/widgets/styleinfosource.h>
#include <kuserfeedback/core/usagetimesource.h>

#include <kuserfeedback/core/propertyratiosource.h>
#include <kuserfeedback/core/selectionratiosource.h>

#endif // KUSERFEEDBACK_HEADERS_H
