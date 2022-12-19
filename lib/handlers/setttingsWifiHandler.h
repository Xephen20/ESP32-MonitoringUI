
static esp_err_t setttingsWifiHandler(httpd_req_t *req){
    char url[100];

    int ret = httpd_req_recv(req, url, -1);
    Serial.println(url);
    char ssid[100], pass[100], ip[100];

    // Extract the value of ssid
    char *ssid_start = strstr(url, "ssid=");
    if (ssid_start != NULL) {
        ssid_start += 5; // Skip over "ssid="
        char *ssid_end = strchr(ssid_start, '&');
        if (ssid_end == NULL) {
            ssid_end = url + strlen(url);
        }
        int ssid_len = ssid_end - ssid_start;
        strncpy(ssid, ssid_start, ssid_len);
        ssid[ssid_len] = '\0';
    }

    // Extract the value of pass
    char *pass_start = strstr(url, "pass=");
    if (pass_start != NULL) {
        pass_start += 5; // Skip over "pass="
        char *pass_end = strchr(pass_start, '&');
        if (pass_end == NULL) {
            pass_end = url + strlen(url);
        }
        int pass_len = pass_end - pass_start;
        strncpy(pass, pass_start, pass_len);
        pass[pass_len] = '\0';
    }

    // Extract the value of ip
    char *ip_start = strstr(url, "ip=");
    if (ip_start != NULL) {
        ip_start += 3; // Skip over "ip="
        char *ip_end = strchr(ip_start, '&');
        if (ip_end == NULL) {
            ip_end = url + strlen(url);
        }
        int ip_len = ip_end - ip_start;
        strncpy(ip, ip_start, ip_len);
        ip[ip_len] = '\0';
    }

    printf("ssid: %s\n", ssid);
    printf("pass: %s\n", pass);
    printf("ip: %s\n", ip);
    writeFile(SD_MMC, "/ssid.txt", ssid);
    writeFile(SD_MMC, "/pass.txt", pass);
    writeFile(SD_MMC, "/ip.txt", ip);
    delay(1000);
    ESP.restart();
    char *response_message = "<!DOCTYPE html>\
        <html>\
        <head>\
            <title>ESP Wi-Fi Manager</title>\
            <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
            <link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">\
        </head>\
        <body>\
            <div class=\"topnav\">\
            <h1>ESP WEB SERVER</h1>\
            </div>\
            <div class=\"content\">\
            <div class=\"card-grid\">\
                <div class=\"card\">\
                <p class=\"card-title\">Camera will restart automatically and connect to WIFI.</p>\
                </div>\
            </div>\
            </div>\
        </body>\
        </html>\
        <style>\
        html {\
        font-family: Arial, Helvetica, sans-serif; \
        display: inline-block; \
        text-align: center;\
        }\
        h1 {\
        font-size: 1.8rem; \
        color: white;\
        }\
        p { \
        font-size: 1.4rem;\
        }\
        .topnav { \
        overflow: hidden; \
        background-color: #0A1128;\
        }\
        body {  \
        margin: 0;\
        }\
        .content { \
        padding: 5%;\
        }\
        .card-grid { \
        max-width: 800px; \
        margin: 0 auto; \
        display: grid; \
        grid-gap: 2rem; \
        grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));\
        }\
        .card { \
        background-color: white; \
        box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);\
        }\
        .card-title { \
        font-size: 1.2rem;\
        font-weight: bold;\
        color: #034078\
        }\
        input[type=submit] {\
        border: none;\
        color: #FEFCFB;\
        background-color: #034078;\
        padding: 15px 15px;\
        text-align: center;\
        text-decoration: none;\
        display: inline-block;\
        font-size: 16px;\
        width: 100px;\
        margin-right: 10px;\
        border-radius: 4px;\
        transition-duration: 0.4s;\
        }\
        input[type=submit]:hover {\
        background-color: #1282A2;\
        }\
        input[type=text], input[type=number], select {\
        width: 50%;\
        padding: 12px 20px;\
        margin: 18px;\
        display: inline-block;\
        border: 1px solid #ccc;\
        border-radius: 4px;\
        box-sizing: border-box;\
        }\
        label {\
        font-size: 1.2rem; \
        }\
        .value{\
        font-size: 1.2rem;\
        color: #1282A2;  \
        }\
        .state {\
        font-size: 1.2rem;\
        color: #1282A2;\
        }\
        button {\
        border: none;\
        color: #FEFCFB;\
        padding: 15px 32px;\
        text-align: center;\
        font-size: 16px;\
        width: 100px;\
        border-radius: 4px;\
        transition-duration: 0.4s;\
        }\
        .button-on {\
        background-color: #034078;\
        }\
        .button-on:hover {\
        background-color: #1282A2;\
        }\
        .button-off {\
        background-color: #858585;\
        }\
        .button-off:hover {\
        background-color: #252524;\
        } \
        </style>";
    httpd_resp_send(req, response_message, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}