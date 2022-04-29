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

#ifndef QOPCUASIMPLEATTRIBUTEOPERAND_H
#define QOPCUASIMPLEATTRIBUTEOPERAND_H

#include <QtOpcUa/qopcuatype.h>

#include <QtCore/qshareddata.h>

QT_BEGIN_NAMESPACE

class QOpcUaQualifiedName;

// OPC-UA part 4, 7.4.4.5
class QOpcUaSimpleAttributeOperandData;
class Q_OPCUA_EXPORT QOpcUaSimpleAttributeOperand
{
public:
    QOpcUaSimpleAttributeOperand();
    QOpcUaSimpleAttributeOperand(const QOpcUaSimpleAttributeOperand &);
    QOpcUaSimpleAttributeOperand(const QString &name, quint16 namespaceIndex = 0,
                            const QString &typeId = QStringLiteral("ns=0;i=2041"), // BaseEventType
                            QOpcUa::NodeAttribute attributeId = QOpcUa::NodeAttribute::Value);
    QOpcUaSimpleAttributeOperand(QOpcUa::NodeAttribute attributeId,
                            const QString &typeId = QStringLiteral("ns=0;i=2041")); // BaseEventType
    QOpcUaSimpleAttributeOperand &operator=(const QOpcUaSimpleAttributeOperand &);
    bool operator==(const QOpcUaSimpleAttributeOperand &rhs) const;
    operator QVariant() const;
    ~QOpcUaSimpleAttributeOperand();

    QString typeId() const;
    void setTypeId(const QString &typeId);

    QList<QOpcUaQualifiedName> browsePath() const;
    QList<QOpcUaQualifiedName> &browsePathRef();
    void setBrowsePath(const QList<QOpcUaQualifiedName> &browsePath);

    QOpcUa::NodeAttribute attributeId() const;
    void setAttributeId(QOpcUa::NodeAttribute attributeId);

    QString indexRange() const;
    void setIndexRange(const QString &indexRange);

private:
    QSharedDataPointer<QOpcUaSimpleAttributeOperandData> data;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QOpcUaSimpleAttributeOperand)

#endif // QOPCUASIMPLEATTRIBUTEOPERAND_H
