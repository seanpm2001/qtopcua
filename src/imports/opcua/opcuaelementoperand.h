/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt OPC UA module.
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

#ifndef OPCUAELEMENTOPERAND
#define OPCUAELEMENTOPERAND

#include "opcuaoperandbase.h"
#include <QOpcUaElementOperand>

QT_BEGIN_NAMESPACE

class QOpcUaClient;

class OpcUaElementOperand : public OpcUaOperandBase, private QOpcUaElementOperand {
    Q_OBJECT
    Q_PROPERTY(quint32 index READ index WRITE setIndex)

public:
    explicit OpcUaElementOperand(QObject *parent = nullptr);
    ~OpcUaElementOperand();
    virtual QVariant toCppVariant(QOpcUaClient *client) const override;

    quint32 index() const;
    void setIndex(quint32 index);

signals:
    void dataChanged();
};

QT_END_NAMESPACE

#endif // OPCUAELEMENTOPERAND
