/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#include "qopen62541backend.h"
#include "qopen62541client.h"
#include "qopen62541node.h"
#include "qopen62541subscription.h"
#include "qopen62541utils.h"
#include "qopen62541valueconverter.h"
#include <private/qopcuaclient_p.h>

#include <QtCore/qloggingcategory.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qthread.h>
#include <QtCore/qurl.h>

QT_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(QT_OPCUA_PLUGINS_OPEN62541)

QOpen62541Client::QOpen62541Client(const QVariantMap &backendProperties)
    : QOpcUaClientImpl()
    , m_backend(new Open62541AsyncBackend(this))
{
    bool ok = false;
    const quint32 clientIterateInterval = backendProperties.value(QStringLiteral("clientIterateIntervalMs"), 50)
            .toUInt(&ok);

    if (ok)
        m_backend->m_clientIterateInterval = clientIterateInterval;

    const quint32 asyncRequestTimeout = backendProperties.value(QStringLiteral("asyncRequestTimeoutMs"), 15000)
            .toUInt(&ok);

    if (ok)
        m_backend->m_asyncRequestTimeout = asyncRequestTimeout;

    m_thread = new QThread();
    m_thread->setObjectName("QOpen62541Client");
    connectBackendWithClient(m_backend);
    m_backend->moveToThread(m_thread);
    connect(m_thread, &QThread::finished, m_thread, &QObject::deleteLater);
    connect(m_thread, &QThread::finished, m_backend, &QObject::deleteLater);
    m_thread->start();
}

QOpen62541Client::~QOpen62541Client()
{
    if (m_thread->isRunning())
        m_thread->quit();
}

void QOpen62541Client::connectToEndpoint(const QOpcUaEndpointDescription &endpoint)
{
    QMetaObject::invokeMethod(m_backend, "connectToEndpoint", Qt::QueuedConnection,
                                     Q_ARG(QOpcUaEndpointDescription, endpoint));
}

void QOpen62541Client::disconnectFromEndpoint()
{
    QMetaObject::invokeMethod(m_backend, "disconnectFromEndpoint", Qt::QueuedConnection);
}

QOpcUaNode *QOpen62541Client::node(const QString &nodeId)
{
    UA_NodeId uaNodeId = Open62541Utils::nodeIdFromQString(nodeId);
    if (UA_NodeId_isNull(&uaNodeId))
        return nullptr;

    auto tempNode = new QOpen62541Node(uaNodeId, this, nodeId);
    if (!tempNode->registered()) {
        qCDebug(QT_OPCUA_PLUGINS_OPEN62541) << "Failed to register node with backend, maximum number of nodes reached.";
        delete tempNode;
        return nullptr;
    }
    return new QOpcUaNode(tempNode, m_client);
}

QString QOpen62541Client::backend() const
{
    return QStringLiteral("open62541");
}

bool QOpen62541Client::requestEndpoints(const QUrl &url)
{
    return QMetaObject::invokeMethod(m_backend, "requestEndpoints", Qt::QueuedConnection, Q_ARG(QUrl, url));
}

bool QOpen62541Client::findServers(const QUrl &url, const QStringList &localeIds, const QStringList &serverUris)
{
   return QMetaObject::invokeMethod(m_backend, "findServers", Qt::QueuedConnection,
                                    Q_ARG(QUrl, url),
                                    Q_ARG(QStringList, localeIds),
                                    Q_ARG(QStringList, serverUris));
}

bool QOpen62541Client::readNodeAttributes(const QList<QOpcUaReadItem> &nodesToRead)
{
    return QMetaObject::invokeMethod(m_backend, "readNodeAttributes", Qt::QueuedConnection,
                                     Q_ARG(QList<QOpcUaReadItem>, nodesToRead));
}

bool QOpen62541Client::writeNodeAttributes(const QList<QOpcUaWriteItem> &nodesToWrite)
{
    return QMetaObject::invokeMethod(m_backend, "writeNodeAttributes", Qt::QueuedConnection,
                                     Q_ARG(QList<QOpcUaWriteItem>, nodesToWrite));
}

bool QOpen62541Client::addNode(const QOpcUaAddNodeItem &nodeToAdd)
{
    return QMetaObject::invokeMethod(m_backend, "addNode", Qt::QueuedConnection,
                                     Q_ARG(QOpcUaAddNodeItem, nodeToAdd));
}

bool QOpen62541Client::deleteNode(const QString &nodeId, bool deleteTargetReferences)
{
    return QMetaObject::invokeMethod(m_backend, "deleteNode", Qt::QueuedConnection,
                                     Q_ARG(QString, nodeId),
                                     Q_ARG(bool, deleteTargetReferences));
}

bool QOpen62541Client::addReference(const QOpcUaAddReferenceItem &referenceToAdd)
{
    return QMetaObject::invokeMethod(m_backend, "addReference", Qt::QueuedConnection,
                                     Q_ARG(QOpcUaAddReferenceItem, referenceToAdd));
}

bool QOpen62541Client::deleteReference(const QOpcUaDeleteReferenceItem &referenceToDelete)
{
    return QMetaObject::invokeMethod(m_backend, "deleteReference", Qt::QueuedConnection,
                                     Q_ARG(QOpcUaDeleteReferenceItem, referenceToDelete));
}

QStringList QOpen62541Client::supportedSecurityPolicies() const
{
    return QStringList {
        "http://opcfoundation.org/UA/SecurityPolicy#None"
#ifdef UA_ENABLE_ENCRYPTION
        , "http://opcfoundation.org/UA/SecurityPolicy#Basic128Rsa15"
        , "http://opcfoundation.org/UA/SecurityPolicy#Basic256"
        , "http://opcfoundation.org/UA/SecurityPolicy#Basic256Sha256"
#endif
    };
}

QList<QOpcUaUserTokenPolicy::TokenType> QOpen62541Client::supportedUserTokenTypes() const
{
    return QList<QOpcUaUserTokenPolicy::TokenType> {
        QOpcUaUserTokenPolicy::TokenType::Anonymous,
        QOpcUaUserTokenPolicy::TokenType::Username
    };
}

QT_END_NAMESPACE
