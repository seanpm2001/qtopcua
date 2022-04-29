/****************************************************************************
**
** Copyright (C) 2015 basysKom GmbH, opensource@basyskom.com
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtOpcUa module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include "qopcuaeventfilterresult.h"
#include "qopcuacontentfilterelementresult.h"

QT_BEGIN_NAMESPACE

/*!
    \class QOpcUaEventFilterResult
    \inmodule QtOpcUa
    \brief The OPCUA EventFilterResult.

    The EventFilterResult contains status codes for all elements of the \c select clauses
    and all elements of the \c where clause.
*/

class QOpcUaEventFilterResultData : public QSharedData
{
public:
    QList<QOpcUa::UaStatusCode> selectClauseResults;
    QList<QOpcUaContentFilterElementResult> whereClauseResults;
};

QOpcUaEventFilterResult::QOpcUaEventFilterResult()
    : data(new QOpcUaEventFilterResultData)
{
}

/*!
    Constructs an event filter result from \a rhs.
*/
QOpcUaEventFilterResult::QOpcUaEventFilterResult(const QOpcUaEventFilterResult &rhs)
    : data(rhs.data)
{
}

/*!
    Sets the values from \a rhs in this event filter result.
*/
QOpcUaEventFilterResult &QOpcUaEventFilterResult::operator=(const QOpcUaEventFilterResult &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QOpcUaEventFilterResult::~QOpcUaEventFilterResult()
{
}

/*!
    Returns \c true if this event filter result is good.
*/
bool QOpcUaEventFilterResult::isGood() const
{
    for (auto status : qAsConst(data->selectClauseResults)) {
        if (status != QOpcUa::UaStatusCode::Good)
            return false;
    }
    for (QOpcUaContentFilterElementResult element : qAsConst(data->whereClauseResults)) {
        if (element.statusCode() != QOpcUa::UaStatusCode::Good)
            return false;
        for (auto status : qAsConst(element.operandStatusCodesRef())) {
            if (status != QOpcUa::UaStatusCode::Good)
                return false;
        }
    }

    return true;
}

/*!
    Returns the status codes for all elements of the \c where clause in the order that was used in the filter.
*/
QList<QOpcUaContentFilterElementResult> QOpcUaEventFilterResult::whereClauseResults() const
{
    return data->whereClauseResults;
}

/*!
    Returns a reference to the \c where clause results.

    \sa whereClauseResults()
*/
QList<QOpcUaContentFilterElementResult> &QOpcUaEventFilterResult::whereClauseResultsRef()
{
    return data->whereClauseResults;
}

/*!
    Sets the \c where clause results to \a whereClausesResult.
*/
void QOpcUaEventFilterResult::setWhereClauseResults(const QList<QOpcUaContentFilterElementResult> &whereClausesResult)
{
    data->whereClauseResults = whereClausesResult;
}

/*!
    Returns the status codes for all elements of the \c select clauses in the order that was used in the filter.
*/
QList<QOpcUa::UaStatusCode> QOpcUaEventFilterResult::selectClauseResults() const
{
    return data->selectClauseResults;
}

/*!
    Returns a reference to the \c select clause results.

    \sa selectClauseResults()
*/
QList<QOpcUa::UaStatusCode> &QOpcUaEventFilterResult::selectClauseResultsRef()
{
    return data->selectClauseResults;
}

/*!
    Sets the \c select clause results to \a selectClausesResult.
*/
void QOpcUaEventFilterResult::setSelectClauseResults(const QList<QOpcUa::UaStatusCode> &selectClausesResult)
{
    data->selectClauseResults = selectClausesResult;
}

QT_END_NAMESPACE
