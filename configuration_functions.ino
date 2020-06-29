void writeafile() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  File file = SPIFFS.open("/test.txt", FILE_WRITE);
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return;
  }

  if (file.print("TEST steve")) {
    Serial.println("File was written");
  } else {
    Serial.println("File write failed");
  }

  file.close();
}

void readafile() {
  File file2 = SPIFFS.open("/test.txt");
  if (!file2) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("File Content:");
  while (file2.available()) {
    Serial.write(file2.read());
  }
  file2.close();
}

// based upon https://arduinojson.org/v6/example/config/
void loadConfiguration(const char *filename, Config &config) {
  Serial.println("Loading configuration from " + String(filename));

  // flag used to detect if a default value is loaded, if default value loaded initiate a save after load
  bool initiatesave = false;

  // Open file for reading
  File file = SPIFFS.open(filename);

  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  if (!SPIFFS.exists(filename)) {
    Serial.println(String(filename) + " does not exist");
  } else {
    Serial.println(String(filename) + " exists");
  }

  StaticJsonDocument<1000> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println(F("Failed to read file, using default configuration"));
  }

  // Copy values from the JsonDocument to the Config
  config.hostname = doc["hostname"].as<String>();
  if (config.hostname == "null") {
    initiatesave = true;
    config.hostname = "esp32-1.home.narco.tk";
  }

  config.device = doc["device"].as<String>();
  if (config.device == "null") {
    initiatesave = true;
    config.device = "laser";
  }

  config.appname = doc["appname"].as<String>();
  if (config.appname == "null") {
    initiatesave = true;
    config.appname = "eeh-esp32-rfid-laser";
  }

  config.ssid = doc["ssid"].as<String>();
  if (config.ssid == "null") {
    initiatesave = true;
    config.ssid = "narcotkshedtp";
  }

  config.wifipassword = doc["wifipassword"].as<String>();
  if (config.wifipassword == "null") {
    initiatesave = true;
    config.wifipassword = String(password);
  }

  config.relaypin = doc["relaypin"];
  if (config.relaypin == 0) {
    initiatesave = true;
    config.relaypin = 26;
  }

  config.ledpin = doc["ledpin"];
  if (config.ledpin == 0) {
    initiatesave = true;
    config.ledpin = 2;
  }

  config.httpuser = doc["httpuser"].as<String>();
  if (config.httpuser == "null") {
    initiatesave = true;
    config.httpuser = "admin";
  }

  config.httppassword = doc["httppassword"].as<String>();
  if (config.httppassword == "null") {
    initiatesave = true;
    config.httppassword = "admin";
  }

  config.overridecodes = doc["overridecodes"].as<String>();
  if (config.overridecodes == "null") {
    initiatesave = true;
    config.overridecodes = "defaultoverridecodes";
  }

  config.apitoken = doc["apitoken"].as<String>();
  if (config.apitoken == "null") {
    initiatesave = true;
    config.apitoken = "abcde";
  }

  config.syslogserver = doc["syslogserver"].as<String>();
  if (config.syslogserver == "null") {
    initiatesave = true;
    config.syslogserver = "192.168.10.21";
  }

  config.syslogport = doc["syslogport"];
  if (config.syslogport == 0) {
    initiatesave = true;
    config.syslogport = 514;
  }

  config.inmaintenance = doc["inmaintenance"] | false;

  config.ntptimezone = doc["ntptimezone"].as<String>();
  if (config.ntptimezone == "null") {
    initiatesave = true;
    config.ntptimezone = "Europe/London";
  }
  config.ntpsynctime = doc["ntpsynctime"];
  if (config.ntpsynctime == 0) {
    initiatesave = true;
    config.ntpsynctime = 60;
  }

  config.ntpwaitsynctime = doc["ntpwaitsynctime"];
  if (config.ntpwaitsynctime == 0) {
    initiatesave = true;
    config.ntpwaitsynctime = 5;
  }

  config.ntpserver = doc["ntpserver"].as<String>();
  if (config.ntpserver == "null") {
    initiatesave = true;
    config.ntpserver = "192.168.10.21";
  }

  config.mfrcslaveselectpin = doc["mfrcslaveselectpin"];
  if (config.mfrcslaveselectpin == 0) {
    initiatesave = true;
    config.mfrcslaveselectpin = 32;
  }

  config.mfrcresetpin = doc["mfrcresetpin"];
  if (config.mfrcresetpin == 0) {
    initiatesave = true;
    config.mfrcresetpin = 33;
  }

  config.mfrccardwaittime = doc["mfrccardwaittime"];
  if (config.mfrccardwaittime == 0) {
    initiatesave = true;
    config.mfrccardwaittime = 1;
  }

  //0x27 = int 39
  config.lcdi2caddress = doc["lcdi2caddress"];
  if (config.lcdi2caddress == 0) {
    initiatesave = true;
    config.lcdi2caddress = 39;
  }

  config.lcdwidth = doc["lcdwidth"];
  if (config.lcdwidth == 0) {
    initiatesave = true;
    config.lcdwidth = 20;
  }

  config.lcdheight = doc["lcdheight"];
  if (config.lcdheight == 0) {
    initiatesave = true;
    config.lcdheight = 4;
  }

  config.webserverporthttp = doc["webserverporthttp"];
  if (config.webserverporthttp == 0) {
    initiatesave = true;
    config.webserverporthttp = 80;
  }

  config.webserverporthttps = doc["webserverporthttps"];
  if (config.webserverporthttps == 0) {
    initiatesave = true;
    config.webserverporthttps = 443;
  }

  config.webapiwaittime = doc["webapiwaittime"];
  if (config.webapiwaittime == 0) {
    initiatesave = true;
    config.webapiwaittime = 2;
  }

  config.serverurl = doc["serverurl"].as<String>();
  if (config.serverurl == "null") {
    initiatesave = true;
    config.serverurl = "http://192.168.10.21:8180";
  }

  config.checkuserpage = doc["checkuserpage"].as<String>();
  if (config.checkuserpage == "null") {
    initiatesave = true;
    config.checkuserpage = "/check.php";
  }

  config.getuserpage = doc["getuserpage"].as<String>();
  if (config.getuserpage == "null") {
    initiatesave = true;
    config.getuserpage = "/getuser.php";
  }

  config.moduserpage = doc["moduserpage"].as<String>();
  if (config.moduserpage == "null") {
    initiatesave = true;
    config.moduserpage = "/moduser.php";
  }

  file.close();

  if (initiatesave) {
    Serial.println("Default configuration values loaded, saving configuration to " + String(filename));
    saveConfiguration(filename, config);
  }
}

void saveConfiguration(const char *filename, const Config &config) {
  // Delete existing file, otherwise the configuration is appended to the file
  SPIFFS.remove(filename);

  // Open file for writing
  File file = SPIFFS.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<2000> doc;

  // Set the values in the document
  doc["hostname"] = config.hostname;
  doc["ssid"] = config.ssid;
  doc["wifipassword"] = config.wifipassword;
  doc["relaypin"] = config.relaypin;
  doc["ledpin"] = config.ledpin;
  doc["httpuser"] = config.httpuser;
  doc["httppassword"] = config.httppassword;
  doc["overridecodes"] = config.overridecodes;
  doc["apitoken"] = config.apitoken;
  doc["syslogserver"] = config.syslogserver;
  doc["syslogport"] = config.syslogport;
  doc["inmaintenance"] = config.inmaintenance;
  doc["ntptimezone"] = config.ntptimezone;
  doc["ntpsynctime"] = config.ntpsynctime;
  doc["ntpwaitsynctime"] = config.ntpwaitsynctime;
  doc["ntpserver"] = config.ntpserver;
  doc["mfrcslaveselectpin"] = config.mfrcslaveselectpin;
  doc["mfrcresetpin"] = config.mfrcresetpin;
  doc["mfrccardwaittime"] = config.mfrccardwaittime;
  doc["lcdi2caddress"] = config.lcdi2caddress;
  doc["lcdwidth"] = config.lcdwidth;
  doc["lcdheight"] = config.lcdheight;
  doc["webserverporthttp"] = config.webserverporthttp;
  doc["webserverporthttps"] = config.webserverporthttps;
  doc["webapiwaittime"] = config.webapiwaittime;
  doc["serverurl"] = config.serverurl;
  doc["checkuserpage"] = config.checkuserpage;
  doc["getuserpage"] = config.getuserpage;
  doc["moduserpage"] = config.moduserpage;


  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // need to print out the deserialisation to discern size

  // Close the file
  file.close();
}


// Prints the content of a file to the Serial
void printFile(const char *filename) {
  // Open file for reading
  File file = SPIFFS.open(filename);
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }
  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();
  // Close the file
  file.close();
}

void printConfig() {
  Serial.print("          hostname: "); Serial.println(config.hostname);
  Serial.print("              ssid: "); Serial.println(config.ssid);
  Serial.print("      wifipassword: "); Serial.println(config.wifipassword);
  Serial.print("          relaypin: "); Serial.println(config.relaypin);
  Serial.print("            ledpin: "); Serial.println(config.ledpin);
  Serial.print("          httpuser: "); Serial.println(config.httpuser);
  Serial.print("      httppassword: "); Serial.println(config.httppassword);
  Serial.print("     overridecodes: "); Serial.println(config.overridecodes);
  Serial.print("          apitoken: "); Serial.println(config.apitoken);
  Serial.print("      syslogserver: "); Serial.println(config.syslogserver);
  Serial.print("        syslogport: "); Serial.println(config.syslogport);
  Serial.print("     inmaintenance: "); Serial.println(config.inmaintenance);
  Serial.print("       ntptimezone: "); Serial.println(config.ntptimezone);
  Serial.print("       ntpsynctime: "); Serial.println(config.ntpsynctime);
  Serial.print("   ntpwaitsynctime: "); Serial.println(config.ntpwaitsynctime);
  Serial.print("         ntpserver: "); Serial.println(config.ntpserver);
  Serial.print("mfrcslaveselectpin: "); Serial.println(config.mfrcslaveselectpin);
  Serial.print("      mfrcresetpin: "); Serial.println(config.mfrcresetpin);
  Serial.print("  mfrccardwaittime: "); Serial.println(config.mfrccardwaittime);
  Serial.print("     lcdi2caddress: "); Serial.println(config.lcdi2caddress);
  Serial.print("          lcdwidth: "); Serial.println(config.lcdwidth);
  Serial.print("         lcdheight: "); Serial.println(config.lcdheight);
  Serial.print(" webserverporthttp: "); Serial.println(config.webserverporthttp);
  Serial.print("webserverporthttps: "); Serial.println(config.webserverporthttps);
  Serial.print("    webapiwaittime: "); Serial.println(config.webapiwaittime);
  Serial.print("         serverurl: "); Serial.println(config.serverurl);
  Serial.print("     checkuserpage: "); Serial.println(config.checkuserpage);
  Serial.print("       getuserpage: "); Serial.println(config.getuserpage);
  Serial.print("       moduserpage: "); Serial.println(config.moduserpage);
}