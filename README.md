# eeh-esp32-rfid

A simple ESP32 Based RFID Access Control System for tools

## Components
- ESP32 Dev Board
- MFRC522 RFID Board
- Generic Relay Board
- I2C 2004 LCD

## Features
- Web Admin interface
- Short and Full Status information
- Webapi: reboot, status check, time check, full status check, refresh ntp, + more
- Upon RFID being presented eeh-esp32-rfid will check whether that card has been granted access to the device and fire the relay
- Users can be baked in to the firmware (super boss access, incase of network connectivity problems) or checked against a server (normal user access)
- Logging via syslog
- Session tracking in logs
- NTP Time synchronisation
- Multiple types of user are supported: admin, trainer, user, + more
- Support tls web api calls using JSON
- Unfire relay upon rfid card removal

## Pin Out


## Electrical Stuff to do
- the relay fires when writing the firmware
- power relay via 5v to optically isolate from the ESP32 - toggle jumper
- add I2C LCD

## Things to do
- Add unknown card found to logs
- Add status light to signify when it is checking access, in trainer mode, locked, unlocked, etc
- OTA updating of firmware
- Make json output of boss's be a struct
- Use wifimanager or IotWebConf to make configuration easier
- Enable active checking of access, regularly poll and check whether card still has access
- Make defining of serverURL and its handling less gross
- Enforce windows of operation
- Figure out sizing for JSON doc
- Figure out sizing of variable for url
- Display username on main web page
- Log off a user via the web admin
- Ban a user via the web admin
- Fix bootTime when ntp fails
- Clean up logging and debug output around granting and revoking access via web admin
- Convert to a function: Serial.print(iteration); Serial.println(" Checking access");
- Lockdown mode / Device disabled except for admin users
- Scheduled reboots
- Add output to LCD
- Change haveaccess to being: &access=grant or &access=revoke
- Regularly pull down user last from server and store in spifs
- Regularly send "in use data" back to somewhere
- Add a sensor to detect whether the laser is actually firing and ship somewhere
- Convert "if (!mfrc522.PICC_IsNewCardPresent()) {" to a function
- When revoking access, disable led and relay, access in web admin, and in full status
- Change button and slider code generation to sit within processor function
- API token implementation for accessing moduser.php
- API token implementation for laptop to esp32
- Standardise time format: https://github.com/ropg/ezTime#built-in-date-and-time-formats
- Add ability to add users: trainer beeps card, then beeps newly trained users card, eeh-esp32-rfid then posts to API and updates user database
- If bootTime = Thursday, 01-Jan-1970 00:00:16 UTC, refresh it for the most current time
- Upon boot, pull time from server, then start using utp
- If ntp sync fails 10 times, force a reboot
- NTP sync sometimes doesnt change time to correct zone, likely problem querying eztime server
- When a card is removed or presented, auto refresh the web admin page
- Clean up moduser.php result when displayed on web admin after granting or revoking access

## Done
- Add syslogs for web stuff
- Enable NTP
- Force ntp sync via api and web admin
- Fix reboot function
- Enable remote firing of relay via a web interface or api call - a remote unlock-and-lock ability
- Add requester ip details to web admin logs
- Added NTP Sync Status to fullstatus
- Remote reboot command via web interface and api
- Add syslog bootup time to capture when the device was rebooted
- Enable heartbeat capability, to be used with a canary to alert upon device failure /health
- After remote reboot, change the url to be index rather than /reboot (can cause looping reboots)
- Make variable str in line 193 have a better name
- Enable status capability, to see what the current status of the system is (whos logged in, whether leds or relay on, etc) /status
- Add fullstatus link to web admin
- Standardise logging style and mechanism
- Added internal ESP32 temp to full status
- Allow remote checking of current status of relay, to see if device is in use and by whom
