/****************************************************************************
**
** Copyright (C) 2019 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt OPC UA module.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QDebug>
#include <QProcess>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QString serverExePath;
#ifdef Q_OS_WIN
    #ifdef QT_DEBUG
        serverExePath = app.applicationDirPath().append("/../../../../../../tests/open62541-testserver/debug/open62541-testserver.exe");
    #else
        serverExePath = app.applicationDirPath().append("/../../../../../../tests/open62541-testserver/release/open62541-testserver.exe");
    #endif
#elif defined(Q_OS_MACOS)
    serverExePath = app.applicationDirPath().append("/../../../../../../../../tests/open62541-testserver/open62541-testserver.app/Contents/MacOS/open62541-testserver");
#else
    serverExePath = app.applicationDirPath().append("/../../../../../tests/open62541-testserver/open62541-testserver");
#endif

    if (!QFile::exists(serverExePath)) {
        qWarning() << "Could not find server executable:" << serverExePath;
        return EXIT_FAILURE;
    }

    QProcess serverProcess;

    serverProcess.start(serverExePath);
    if (!serverProcess.waitForStarted()) {
        qWarning() << "Could not start server:" << serverProcess.errorString();
        return EXIT_FAILURE;
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/basic.qml")));
    if (engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
}
