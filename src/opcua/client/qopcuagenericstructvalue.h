// Copyright (C) 2023 basysKom GmbH, opensource@basyskom.com
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include <QtOpcUa/qopcuastructuredefinition.h>

#include <QtCore/qhash.h>
#include <QtCore/qshareddata.h>

#ifndef QOPCUAGENERICSTRUCTVALUE_H
#define QOPCUAGENERICSTRUCTVALUE_H

QT_BEGIN_NAMESPACE

class QOpcUaGenericStructValueData;
QT_DECLARE_QSDP_SPECIALIZATION_DTOR_WITH_EXPORT(QOpcUaGenericStructValueData, Q_OPCUA_EXPORT)
class QOpcUaGenericStructValue {
public:
    Q_OPCUA_EXPORT QOpcUaGenericStructValue();
    Q_OPCUA_EXPORT ~QOpcUaGenericStructValue();
    Q_OPCUA_EXPORT QOpcUaGenericStructValue(const QString &typeName, const QString &typeId, const QOpcUaStructureDefinition &definition,
                                            const QHash<QString, QVariant> &fields = QHash<QString, QVariant>());
    Q_OPCUA_EXPORT QOpcUaGenericStructValue(const QOpcUaGenericStructValue &other);
    QOpcUaGenericStructValue(QOpcUaGenericStructValue &&other) noexcept = default;
    Q_OPCUA_EXPORT QOpcUaGenericStructValue &operator=(const QOpcUaGenericStructValue &rhs);
    void swap(QOpcUaGenericStructValue &other) noexcept
    { data.swap(other.data); }
    QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_PURE_SWAP(QOpcUaGenericStructValue)

    friend Q_OPCUA_EXPORT bool operator==(const QOpcUaGenericStructValue &lhs, const QOpcUaGenericStructValue &rhs) noexcept;
    friend inline bool operator!=(const QOpcUaGenericStructValue &lhs, const QOpcUaGenericStructValue &rhs) noexcept
    {
        return !(lhs == rhs);
    }
    Q_OPCUA_EXPORT operator QVariant() const;

    Q_OPCUA_EXPORT QString typeName() const;
    Q_OPCUA_EXPORT void setTypeName(const QString &typeName);

    Q_OPCUA_EXPORT QString typeId() const;
    Q_OPCUA_EXPORT void setTypeId(const QString &typeId);

    Q_OPCUA_EXPORT QOpcUaStructureDefinition structureDefinition() const;
    Q_OPCUA_EXPORT void setStructureDefinition(const QOpcUaStructureDefinition &structureDefinition);

    Q_OPCUA_EXPORT QHash<QString, QVariant> fields() const;
    Q_OPCUA_EXPORT QHash<QString, QVariant> &fieldsRef();
    Q_OPCUA_EXPORT void setFields(const QHash<QString, QVariant> &fields);

    Q_OPCUA_EXPORT QString toString() const;

    friend QDebug Q_OPCUA_EXPORT operator<<(QDebug debug, const QOpcUaGenericStructValue &s);

private:
    QSharedDataPointer<QOpcUaGenericStructValueData> data;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QOpcUaGenericStructValue)

#endif // QOPCUAGENERICSTRUCTVALUE_H
