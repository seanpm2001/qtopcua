/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt OPC UA module.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "opcuasimpleattributeoperand.h"
#include "opcuanodeid.h"
#include "universalnode.h"
#include <QOpcUaQualifiedName>

QT_BEGIN_NAMESPACE

/*!
    \qmltype SimpleAttributeOperand
    \inqmlmodule QtOpcUa
    \brief The OPC UA SimpleAttributeOperand type.
    \since QtOpcUa 5.13

    The SimpleAttributeOperand is specified in OPC-UA part 4, 7.4.4.5.
    It is used when a node attribute is required as operand.

    For example, the following simple attribute operand represents the value
    of the "Severity" field of the base event type:

    \code
    import QtOpcUa 5.13 as QtOpcUa

    QtOpcUa.SimpleAttributeOperand {
        identifier: "Severity"
        ns: "http://opcfoundation.org/UA/"
    }
    \endcode
*/

/*!
    \qmlproperty list<OpcUaNodeId> SimpleAttributeOperand::browsePath

    Browse path to the node holding the attribute.

    \code
    import QtOpcUa 5.13 as QtOpcUa

    QtOpcUA.SimpleAttributeOperand {
        ...
        browsePath: [
            QtOpcUa.NodeId {
                identifier: "Message"
                ns: "http://opcfoundation.org/UA/"
             }
             ...
        ]
    }
*/

/*!
    \qmlproperty string SimpleAttributeOperand::indexRange

    Index range string used to identify a single value or subset of the attribute's value.

    \code
    import QtOpcUa 5.13 as QtOpcUa

    QtOpcUa.SimpleAttributeOperand {
        ...
        indexRange: "0:2"
    }
    \endcode
*/

/*!
    \qmlproperty Constants.NodeAttribute SimpleAttributeOperand::nodeAttribute

    Attribute of the node \l browsePath is pointing to.
    The default value is \c Constants.NodeAttribute.Value.

    \code
    import QtOpcUa 5.13 as QtOpcUa

    QtOpcUa.SimpleAttributeOperand {
        ...
        nodeAttribute: QtOpcUa.Constants.NodeAttribute.Value
    }
    \endcode
*/

/*!
    \qmlproperty string SimpleAttributeOperand::typeId

    Node id of the type definition node. The operand will be of the type or one of its subtypes.
    The default value is \c "ns=0;i=2041".

    \code
    import QtOpcUa 5.13 as QtOpcUa

    QtOpcUa.SimpleAttributeOperand {
        ...
        typeId: "ns=0;i=2041"
    }
    \endcode
*/

OpcUaSimpleAttributeOperand::OpcUaSimpleAttributeOperand(QObject *parent)
    : OpcUaOperandBase(parent)
{
    QOpcUaSimpleAttributeOperand::setTypeId(QStringLiteral("ns=0;i=2041"));
    QOpcUaSimpleAttributeOperand::setAttributeId(QOpcUa::NodeAttribute::Value);
}

OpcUaSimpleAttributeOperand::~OpcUaSimpleAttributeOperand() = default;

QOpcUaSimpleAttributeOperand OpcUaSimpleAttributeOperand::toSimpleAttributeOperand(QOpcUaClient *client) const
{
    QOpcUaSimpleAttributeOperand value(*this);
    for (UniversalNode i : m_browsePath) {
        i.resolveNamespaceNameToIndex(client);
        value.browsePathRef().append(i.toQualifiedName());
    }
    return value;
}

QVariant OpcUaSimpleAttributeOperand::toCppVariant(QOpcUaClient *client) const
{
    return toSimpleAttributeOperand(client);
}

QString OpcUaSimpleAttributeOperand::indexRange() const
{
    return QOpcUaSimpleAttributeOperand::indexRange();
}

void OpcUaSimpleAttributeOperand::setIndexRange(const QString &indexRange)
{
    if (indexRange != QOpcUaSimpleAttributeOperand::indexRange()) {
        QOpcUaSimpleAttributeOperand::setIndexRange(indexRange);
        emit dataChanged();
    }
}

QOpcUa::NodeAttribute OpcUaSimpleAttributeOperand::nodeAttribute() const
{
    return QOpcUaSimpleAttributeOperand::attributeId();
}

void OpcUaSimpleAttributeOperand::setNodeAttribute(QOpcUa::NodeAttribute nodeAttribute)
{
    if (nodeAttribute != QOpcUaSimpleAttributeOperand::attributeId()) {
        QOpcUaSimpleAttributeOperand::setAttributeId(nodeAttribute);
        emit dataChanged();
    }
}

QString OpcUaSimpleAttributeOperand::typeId() const
{
    return QOpcUaSimpleAttributeOperand::typeId();
}

void OpcUaSimpleAttributeOperand::setTypeId(const QString &typeId)
{
    if (typeId != QOpcUaSimpleAttributeOperand::typeId()) {
        QOpcUaSimpleAttributeOperand::setTypeId(typeId);
        emit dataChanged();
    }
}

QQmlListProperty<OpcUaNodeId> OpcUaSimpleAttributeOperand::browsePath()
{
    return QQmlListProperty<OpcUaNodeId>(this, this,
                                         &OpcUaSimpleAttributeOperand::appendBrowsePathElement,
                                         &OpcUaSimpleAttributeOperand::browsePathSize,
                                         &OpcUaSimpleAttributeOperand::browsePathElement,
                                         &OpcUaSimpleAttributeOperand::clearBrowsePath);
}

void OpcUaSimpleAttributeOperand::appendBrowsePathElement(OpcUaNodeId *nodeId)
{
    m_browsePath.append(nodeId);
    emit dataChanged();
}

int OpcUaSimpleAttributeOperand::browsePathSize() const
{
    return m_browsePath.size();
}

OpcUaNodeId *OpcUaSimpleAttributeOperand::browsePathElement(int index) const
{
    return m_browsePath.at(index);
}

void OpcUaSimpleAttributeOperand::clearBrowsePath()
{
    m_browsePath.clear();
    emit dataChanged();
}

void OpcUaSimpleAttributeOperand::appendBrowsePathElement(QQmlListProperty<OpcUaNodeId> *list, OpcUaNodeId *nodeId)
{
    reinterpret_cast<OpcUaSimpleAttributeOperand*>(list->data)->appendBrowsePathElement(nodeId);
}

qsizetype OpcUaSimpleAttributeOperand::browsePathSize(QQmlListProperty<OpcUaNodeId> *list)
{
    return reinterpret_cast<OpcUaSimpleAttributeOperand*>(list->data)->browsePathSize();
}

OpcUaNodeId *OpcUaSimpleAttributeOperand::browsePathElement(QQmlListProperty<OpcUaNodeId> *list, qsizetype index)
{
    return reinterpret_cast<OpcUaSimpleAttributeOperand*>(list->data)->browsePathElement(index);
}

void OpcUaSimpleAttributeOperand::clearBrowsePath(QQmlListProperty<OpcUaNodeId> *list)
{
    reinterpret_cast<OpcUaSimpleAttributeOperand*>(list->data)->clearBrowsePath();
}

QT_END_NAMESPACE
