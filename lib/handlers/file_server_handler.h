static esp_err_t file_server_handler(httpd_req_t *req){
    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, "<h1>Lista plikow</h1><br>", -1);
    
    Serial.printf("\nListing directory: %s\n", "/");

    File root = SD_MMC.open("/");
    File file = root.openNextFile();
    Serial.println(" ");
    while(file){
        if(!file.isDirectory()){
            Serial.print("\n  FILE: ");
            Serial.print(file.name());
            httpd_resp_send(req, std::string(file.name()).c_str(), HTTPD_RESP_USE_STRLEN);
            Serial.println("foo1");
        }
        file = root.openNextFile();
        Serial.println("foo2");
    }
    Serial.println("foo3");
    return ESP_OK;
}