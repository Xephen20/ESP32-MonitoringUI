//httpd_resp_send(req, std::string(file.name()).c_str(), HTTPD_RESP_USE_STRLEN);
static esp_err_t file_server_handler(httpd_req_t *req){

    char *header = "<h1>Lista plikow w katalogu: /</h1><br>\n <ul>";
    
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
    
                Serial.println(file_names[i]);
                httpd_resp_send_chunk(req, "<li>", strlen("<li>"));
                httpd_resp_send_chunk(req, file_names[i], strlen(file_names[i]));
                httpd_resp_send_chunk(req, "</li>", strlen("</li>"));
            }
        }
    }
    httpd_resp_send_chunk(req, "</ul>", strlen("</ul>"));
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