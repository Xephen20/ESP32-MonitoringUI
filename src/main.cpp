#include "imports.h"
#include "defines.h"
#include "capture_handler.h"
#include "website_handler.h"
#include "file_server_handler.h"
#include "wifi_manager_handler.h"
#include "credentials_handler.h"
#include "settings_handler.h"
#include "setttingsWifiHandler.h"

char* readFile(fs::FS &fs, const char * path) {
    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return "Fail";
    }

    // Determine the size of the file
    size_t size = file.size();

    // Allocate a buffer to hold the file contents
    char* buffer = new char[size + 1];

    // Read the entire file into the buffer
    size_t bytes_read = file.read((uint8_t*)buffer, size);
    buffer[bytes_read] = '\0'; // null-terminate the buffer

    file.close();
    return buffer;
}

void startCameraServer(){
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t index_uri = {
    .uri       = "/home",
    .method    = HTTP_GET,
    .handler   = get_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t capture_uri = {
    .uri       = "/capture",
    .method    = HTTP_GET,
    .handler   = stream_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t files_uri = {
    .uri       = "/files",
    .method    = HTTP_GET,
    .handler   = file_server_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t take_photo_uri = {
    .uri       = "/take_photo",
    .method    = HTTP_GET,
    .handler   = take_photo_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t settings_uri = {
    .uri       = "/settings",
    .method    = HTTP_GET,
    .handler   = settings_handler,
    .user_ctx  = NULL
  };

    httpd_uri_t setttingsWifiHandler_uri = {
    .uri       = "/setttingsWifiHandler",
    .method    = HTTP_POST,
    .handler   = setttingsWifiHandler,
    .user_ctx  = NULL
  };
  //Serial.printf("Starting web server on port: '%d'\n", config.server_port);
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &index_uri);
    httpd_register_uri_handler(stream_httpd, &capture_uri);
    httpd_register_uri_handler(stream_httpd, &files_uri);
    httpd_register_uri_handler(stream_httpd, &take_photo_uri);
    httpd_register_uri_handler(stream_httpd, &settings_uri);
    httpd_register_uri_handler(stream_httpd, &setttingsWifiHandler_uri);
  }
}

void setupCamera(){
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 
  config.frame_size = FRAMESIZE_SVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  
  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  startCameraServer();
}

void wifiManager(){
  Serial.println("\nNot Connected to WIFI, Setting AP (Access Point)");
  delay(200);
  // NULL sets an open Access Point
  WiFi.softAP("ESP-WIFI-MANAGER", NULL);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;

  httpd_uri_t wifi_manager = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = wifi_manager_handler,
    .user_ctx  = NULL
  };

  httpd_uri_t manager_credentials = {
    .uri       = "/credentials",
    .method    = HTTP_POST,
    .handler   = credentials_handler,
    .user_ctx  = NULL
  };
  
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &wifi_manager);
    httpd_register_uri_handler(stream_httpd, &manager_credentials);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  delay(1000);
  if(!SD_MMC.begin()){
    Serial.println("Card Mount Failed");
    return;
  }else{
    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("\nSD_MMC Card Size: %lluMB\n", cardSize);
  }
  
  // Wi-Fi connection

  const char* ssid = readFile(SD_MMC, "/ssid.txt");
  delay(100);
  const char* pass = readFile(SD_MMC, "/pass.txt");
  delay(100);
  const char* ip = readFile(SD_MMC, "/ip.txt");
  delay(100);
  // Serial.println(ssid);
  // Serial.println(pass);
  // Serial.println(ip);
  if (strlen(ssid) > 0 && strlen(pass) > 0){ // Try to connect to Wi-Fi
    WiFi.begin(ssid, pass);
    int check_conn = 0;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (check_conn == 20){
        break;
      }
      check_conn++;
    }
  }
  else {
    wifiManager();
  }
  if (WiFi.status() == WL_CONNECTED){ // Begin Program
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("Camera Stream Ready! Go to: http://");
    Serial.print(WiFi.localIP());
    setupCamera();

  } else { // Run WIFI Manager
    wifiManager();
  }
  
}

void loop() {
  delay(1);
}
