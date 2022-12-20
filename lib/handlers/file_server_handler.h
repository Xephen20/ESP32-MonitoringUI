//httpd_resp_send(req, std::string(file.name()).c_str(), HTTPD_RESP_USE_STRLEN);
static esp_err_t file_server_handler(httpd_req_t *req){

    char *header = "<!DOCTYPE html>\
        <html>\
        <head>\
        <title>ESP Camera</title>\
        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
        <link rel=\"icon\" href=\"data:,\">\
        </head>\
        <body>\
        <div class=\"topnav\">\
            <h1>ESP Camera</h1>\
        </div>\
        <div class=\"content\">\
            <div class=\"card-grid\">\
            <div class=\"card\">\
                <h2>List of files</h2>\
                <p>\
                <ul style=\"list-style-type: square;\">";
    
    char *stylization = "</ul>\
                <a href=\"/home\" class=\"Button\">Go Back</a>\
                </p>        \
            </div>\
            </div>\
        </div>\
        </body>\
        </html>\
        <script>\
        function capturePhoto() {\
            var xhr = new XMLHttpRequest();\
            xhr.open(\'GET\', \"take_photo\", true);\
            xhr.send();\
            window.location.reload();\
        }\
        </script>\
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
        .Button{\
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
        .Button:hover {\
        background-color: #1282A2;\
        }\
        label {\
        font-size: 1.2rem; \
        }\
        .value{\
        font-size: 1.2rem;\
        color: #1282A2;  \
        }\
        </style>\
        ";
    int MAX_FILES = 10;

    char *file_names[MAX_FILES];
    File root = SD_MMC.open("/");
    File file = root.openNextFile();
    size_t file_count = 0;
    while (file && file_count < MAX_FILES) {
        if (!file.isDirectory()) {
            size_t size = strlen(file.name()) + 1;
            file_names[file_count] = (char *) malloc(sizeof(char) * size);
            strncpy(file_names[file_count], file.name(), size);
            file_count++;
        }

        file = root.openNextFile();
    }
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send_chunk(req, header, strlen(header));

    for (size_t i = 0; i < file_count; i++) {
        if (file_names[i]) {
            if (strncmp(file_names[i], "._", 2) != 0) {
                if (!strcmp(strrchr(file_names[i], '\0') - 4, ".jpg")){
                    //Serial.println(file_names[i]);
                    httpd_resp_send_chunk(req, "<li>", strlen("<li>"));
                    httpd_resp_send_chunk(req, file_names[i], strlen(file_names[i]));
                    httpd_resp_send_chunk(req, "</li>", strlen("</li>"));
                }
            }
        }
    }
    httpd_resp_send_chunk(req, stylization, strlen(stylization));
    httpd_resp_send_chunk(req, NULL, 0);
    // Free memory
    for (size_t i = 0; i < file_count; i++) {
        if (file_names[i]) {
            free(file_names[i]);
        }
    }
    return ESP_OK;
}

static esp_err_t take_photo_handler(httpd_req_t *req){
    Serial.println("take_photo");
    capture_image = true;
    return ESP_OK;
}