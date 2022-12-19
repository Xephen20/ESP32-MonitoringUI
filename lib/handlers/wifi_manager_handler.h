static esp_err_t wifi_manager_handler(httpd_req_t *req){
    char *response_message = "<!DOCTYPE html>\
        <html>\
        <head>\
        <title>ESP Wi-Fi Manager</title>\
        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
        </head>\
        <body>\
        <div class=\"topnav\">\
            <h1>ESP Wi-Fi Manager</h1>\
        </div>\
        <div class=\"content\">\
            <div class=\"card-grid\">\
            <div class=\"card\">\
                <form action=\"/credentials\" method=\"POST\">\
                <p>\
                    <label for=\"ssid\">SSID</label>\
                    <input type=\"text\" id =\"ssid\" name=\"ssid\"><br>\
                    <label for=\"pass\">Password</label>\
                    <input type=\"text\" id =\"pass\" name=\"pass\"><br>\
                    <label for=\"ip\">IP Address</label>\
                    <input type=\"text\" id =\"ip\" name=\"ip\" value=\"192.168.1.200\"><br>\
                    <input type =\"submit\" value =\"Submit\">\
                </p>\
                </form>\
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
        </style>\
        ";
    httpd_resp_send(req, response_message, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}