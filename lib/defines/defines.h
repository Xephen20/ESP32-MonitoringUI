// Wifi Credentials
const char* ssid = "PLAY Internet 4G 2.4 GHz";
const char* password = "F894BDF5";

//const char* ssid = "iPhone 13 Pro (Dawid)";
//const char* password = "dupa1234";

#define PART_BOUNDARY "123456789000000000000987654321"
#define CAMERA_MODEL_AI_THINKER

// Defins pins
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// Sd card
#define EEPROM_SIZE 1

bool capture_image = false;

httpd_handle_t stream_httpd = NULL;

// NTP Server Current time

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 1;
const int   daylightOffset_sec = 3600;

struct tm timeinfo;
char time_string[128];
