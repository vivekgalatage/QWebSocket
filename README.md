QWebSocket
==========

WebSocket server and client library


Getting the source and building
===============================

  $ git clone --recursive https://github.com/vivekgalatage/QWebSocket.git
  $ cd QWebSocket
  $ qmake
  $ make


Test echo_server
================
Execute ./out/bin/echo_server which by default listens on localhost:9002

* Open http://www.websocket.org/echo.html in a browser which supports WebSockets (chrome, firefox, safari etc.) 
* Enter location as: ws://localhost:9002
* Click connect 
* See that the CONNECTED message is shown in log
* Enter some sample message in the text box and click send
* See that the message is echoed in the log
