// Copyright (C) 2023 basysKom GmbH, opensource@basyskom.com
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#ifndef QOPCUAENUMDEFINITION_H
#define QOPCUAENUMDEFINITION_H

#include <QtOpcUa/qopcuaglobal.h>
#include <QtOpcUa/qopcuaenumfield.h>

#include <QtCore/qshareddata.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE

class QOpcUaEnumDefinitionData;

QT_DECLARE_QSDP_SPECIALIZATION_DTOR_WITH_EXPORT(QOpcUaEnumDefinitionData, Q_OPCUA_EXPORT)

class QOpcUaEnumDefinition
{
public:
    Q_OPCUA_EXPORT QOpcUaEnumDefinition();
    Q_OPCUA_EXPORT QOpcUaEnumDefinition(const QOpcUaEnumDefinition &other);
    void swap(QOpcUaEnumDefinition &other) noexcept
    { data.swap(other.data); }
    QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_PURE_SWAP(QOpcUaEnumDefinition)
    QOpcUaEnumDefinition(QOpcUaEnumDefinition &&other) noexcept = default;
    Q_OPCUA_EXPORT QOpcUaEnumDefinition &operator=(const QOpcUaEnumDefinition &rhs);
    friend Q_OPCUA_EXPORT bool operator==(const QOpcUaEnumDefinition &lhs, const QOpcUaEnumDefinition &rhs) noexcept;
    friend inline bool operator!=(const QOpcUaEnumDefinition &lhs, const QOpcUaEnumDefinition &rhs) noexcept
    {
        return !(lhs == rhs);
    }
    Q_OPCUA_EXPORT operator QVariant() const;
    Q_OPCUA_EXPORT ~QOpcUaEnumDefinition();

    Q_OPCUA_EXPORT QList<QOpcUaEnumField> fields() const;
    Q_OPCUA_EXPORT void setFields(const QList<QOpcUaEnumField> &fields);

private:
    QSharedDataPointer<QOpcUaEnumDefinitionData> data;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QOpcUaEnumDefinition)

#endif // QOPCUAENUMDEFINITION_H
