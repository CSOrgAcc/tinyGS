/**
 * IotWebConfESP32HTTPUpdateServer.h -- IotWebConf is an ESP8266/ESP32
 *   non blocking WiFi/AP web configuration library for Arduino.
 *   https://github.com/prampec/IotWebConf
 *
 * Copyright (C) 2020 Balazs Kelemen <prampec+arduino@gmail.com>
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 * Notes on IotWebConfESP32HTTPUpdateServer:
 * ESP32 doesn't implement a HTTPUpdateServer. However it seams, that to code
 * from ESP8266 covers nearly all the same functionality.
 * So we need to implement our own HTTPUpdateServer for ESP32, and code is
 * reused from
 * https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPUpdateServer/src/
 * version: 41de43a26381d7c9d29ce879dd5d7c027528371b
 */
#ifdef ESP32

#ifndef __HTTP_UPDATE_SERVER_H
#define __HTTP_UPDATE_SERVER_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <StreamString.h>
#include <Update.h>

#define emptyString F("")

class WebServer;

class HTTPUpdateServer
{
  public:
    HTTPUpdateServer(bool serial_debug=false);

    void setup(WebServer *server)
    {
      setup(server, emptyString, emptyString);
    }

    void setup(WebServer *server, const String& path)
    {
      setup(server, path, emptyString, emptyString);
    }

    void setup(WebServer *server, const String& username, const String& password)
    {
      setup(server, "/update", username, password);
    }

    void setup(WebServer *server, const String& path, const String& username, const String& password);

    void updateCredentials(const String& username, const String& password)
    {
      _username = username;
      _password = password;
    }

  protected:
    void _setUpdaterError();

  private:
    bool _serial_output;
    WebServer *_server;
    String _username;
    String _password;
    bool _authenticated;
    String _updaterError;
};

/////////////////////////////////////////////////////////////////////////////////

static const char serverIndex[] PROGMEM =
  R"(<html><body><form method='POST' action='' enctype='multipart/form-data'>
                  <input type='file' name='update'>
                  <input type='submit' value='Update'>
               </form>
         </body></html>)";
static const char successResponse[] PROGMEM = 
  "<META http-equiv=\"refresh\" content=\"15;URL=/\">Update Success! Rebooting...\n";

#endif

#endif
