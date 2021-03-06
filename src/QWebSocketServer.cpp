/*
 * Copyright (c) 2013, Vivek Galatage
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
 */

#include "QWebSocketServer.h"
#include "../third-party/websocketpp/src/websocketpp.hpp"

using websocketpp::server;

class QWebSocketServerPrivate : public server::handler
{
    friend class QWebSocketServer;

public:
    QWebSocketServerPrivate(int port);

    // Methods from websocketpp::server::handler
    void on_message(connection_ptr conn, message_ptr message);

    void listen();

private:
    int m_port;
    server::handler::ptr m_handler;
    server m_server;
};


QWebSocketServerPrivate::QWebSocketServerPrivate(int port)
    : m_port(port)
    , m_handler(this)
    , m_server(m_handler)
{
}

void QWebSocketServerPrivate::on_message(connection_ptr conn, message_ptr message)
{
    conn->send(message->get_payload(), message->get_opcode());
}

void QWebSocketServerPrivate::listen()
{
    m_server.listen(m_port);
}

QWebSocketServer::QWebSocketServer(int port)
    : d(new QWebSocketServerPrivate(port))
{

}

void QWebSocketServer::listen()
{
    d->listen();
}

inline int QWebSocketServer::port() const
{
    return d->m_port;
}

