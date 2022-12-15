static esp_err_t get_handler(httpd_req_t *req)
{
    char *response_message = "<html>\
<head></head>\
<body>\
    <div class=\"container\">\
        <div class=\"header contains\"><h3 class=\"header-captions\">ESP 32 Cam 1 / data / godzina / Adres IP</h3></div>\
        <div class=\"main contains\">\
            <img src=\"/capture\" alt=\"Missing stream\" width=\"90%\" class=\"center-div\">\
        </div>\
        <div class=\"buttons contains\">\
            <div class=\"button-grid\">\
                <a href=\"/files\">\
                    <div class=\"button\" id=\"button-3\">\
                        <div id=\"circle\"></div>\
                        Files\
                    </div>\
                </a>\
            </div>\
            <div class=\"button-grid\">\
                <a href=\"#\" onclick=\"capturePhoto()\">\
                    <div class=\"button\" id=\"button-3\">\
                        <div id=\"circle\"></div>\
                        Capture\
                    </div>\
                </a>\
            </div>\
            <div class=\"button-grid\">\
                <a href=\"#\">\
                    <div class=\"button\" id=\"button-3\">\
                        <div id=\"circle\"></div>\
                        Record\
                    </div>\
                </a>\
            </div>\
            <div class=\"button-grid\">\
                <a href=\"#\">\
                    <div class=\"button\" id=\"button-3\">\
                        <div id=\"circle\"></div>\
                        Settings\
                    </div>\
                </a>\
            </div>\
        </div>\
        <div class=\"footer contains\" style=\"text-align:right\">Footer &nbsp;&nbsp;</div>\
    </div>\
</body>\
</html>\
<script>\
  function capturePhoto() {\
    var xhr = new XMLHttpRequest();\
    xhr.open(\'GET\', \"/take_photo\", true);\
    xhr.send();\
    window.location.reload();\
  }\
</script>\
<style>\
    .container{\
        width: 50%;\
        height: 90vh;\
        padding-top: 1vh;\
        margin: auto;\
    }\
    .header{\
        height: 10%;\
    }\
    .main{\
        height: 75%;\
        display: flex;\
        align-items: center;\
        justify-content: center;\
    }\
    .buttons{\
        height: 9%;\
    }\
    .footer{\
        height: 4%;\
    }\
    .button-grid{\
        width: 25%;\
        float: left;\
    }\
    .contains{\
        width: 100%;\
        margin-top: 1%;\
        background-color: #f2f2f2;\
        border-radius: 5px;\
        border: 1px solid #cdcdcd;\
    }\
    .button {\
        display: inline-flex;\
        height: 45%;\
        width: 75%;\
        border: 2px solid #BFC0C0;\
        margin: 20px 20px 20px 20px;\
        color: #BFC0C0;\
        text-transform: uppercase;\
        text-decoration: none;\
        font-size: .8em;\
        letter-spacing: 1.5px;\
        align-items: center;\
        justify-content: center;\
        overflow: hidden;\
    }\
    a {\
        color: #000000;\
        text-decoration: none;\
        letter-spacing: 1px;\
    }\
    /* Third Button */\
    #button-3 {\
        color: #000000;\
        position: relative;\
        overflow: hidden;\
        cursor: pointer;\
    }\
    #button-3 a {\
        position: relative;\
        transition: all .45s ease-Out;\
    }\
    #circle {\
        width: 0%;\
        height: 0%;\
        opacity: 0;\
        line-height: 40px;\
        border-radius: 50%;\
        background: #BFC0C0;\
        position: absolute;\
        transition: all .5s ease-Out;\
        top: 20px;\
        left: 70px;\
    }\
    #button-3:hover #circle {\
        width: 200%;\
        height: 500%;\
        opacity: 1;\
        top: -70px;\
        left: -70px;\
        color: #000000;\
    }\
    #button-3:hover a {\
        color: #000000;\
    }\
    .center-div{\
        text-align: center;\
        line-height: 1.5;\
        display: inline-block;\
        vertical-align: middle;\
    }\
    .header-captions{\
        text-align:center\
    }\
</style>";
    httpd_resp_send(req, response_message, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

