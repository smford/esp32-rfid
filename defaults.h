const String default_hostname = "esp32-1.home.narco.tk";
const String default_device = "laser";
const String default_appname = "eeh-esp32-rfid-laser";
const String default_ssid = "somessid";
const String default_wifipassword = "somepassword";
const int default_relaypin = 26;
const int default_ledpin = 2;
const String default_httpuser = "admin";
const String default_httppassword = "admin";
const String default_httpapitoken = "xyz";
const String default_syslogserver = "192.168.10.21";
const int default_syslogport = 514;
const bool default_inmaintenance = true;
const String default_ntptimezone = "Europe/London";
const int default_ntpsynctime = 60;
const int default_ntpwaitsynctime = 5;
const String default_ntpserver = "192.168.10.21";
const int default_mfrcslaveselectpin = 32;
const int default_mfrcresetpin = 33;
const int default_mfrccardwaittime = 1;
const int default_lcdi2caddress = 39;
const int default_lcdwidth = 20;
const int default_lcdheight = 4;
const int default_webserverporthttp = 80;
const int default_webserverporthttps = 443;
const int default_webapiwaittime = 2;
const int default_webpagedelay = 1; // minimum should really be 1 second, if set to 0 the webadmin page often refreshes before action has completed
const String default_serverurl = "http://192.168.10.21:8180";
const String default_serverapitoken = "abcde";
const String default_checkuserpage = "/check.php";
const String default_getuserpage = "/getuser.php";
const String default_moduserpage = "/moduser.php";
const String default_overridecodes = "90379632,222222,333333";
const bool default_telegrafenable = true;
const String default_telegrafserver = "192.168.10.21";
const int default_telegrafserverport = 8094;
const int default_telegrafshiptime = 30;
const bool default_discordproxyenable = true;
const String default_discordproxyserver = "http://192.168.10.21:57000";
const String default_discordproxyapitoken = "sometoken";
