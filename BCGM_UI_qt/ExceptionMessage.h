// -*- C++ -*-
/**
 \file ExceptionMessage.h

 \author Jack Li
 */
#ifndef EXCEPTION_MESSAGE_H
#define EXCEPTION_MESSAGE_H

#include <QString>
#include <exception>

enum ExceptionType {
    ErrorException,
    WarningException,
    InformationException,
    ExternalProcessCrashException,
    ExternalProcessErrorException
};


class ExceptionMessage: public std::exception {
public:
    ExceptionMessage(ExceptionType _type, QString const & _title,
        QString const & _details)
    : type(_type), title(_title), details(_details),
      message(_title + "\n" + _details) {}

    virtual const char * what() const throw() { return message.toUtf8().constData(); }
	virtual ~ExceptionMessage() throw() {}

    ExceptionType type;
    QString title;
    QString details;
	// Needed because we may not return a temporary in what().
    QString message;
};


#endif // EXCEPTION_MESSAGE_H
