static esp_err_t get_handler(httpd_req_t *req){
    const char* ip_str = WiFi.localIP().toString().c_str();

    char *header = "<!DOCTYPE html>\
      <html>\
      <head>\
        <title>ESP Camera </title>\
        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
        <link rel=\"icon\" href=\"data:,\">\
      </head>\
      <body>\
        <div class=\"topnav\">\
          <h1>ESP Camera"\
    ;

    char *bottom = "</h1>\
  </div>\
  <div class=\"content\">\
    <div class=\"card-grid\">\
      <div class=\"card\">\
        <p>\
          <img src=\"/capture\" alt=\"Missing stream\" width=\"90%\" class=\"center-div\">\
          <a href=\"/files\" class=\"Button\">Files</a>\
          <button class=\"Button\" onclick=\"capturePhoto()\">Capture</button>\
          <a href=\"#\" class=\"Button\">Record</a>\
          <a href=\"/settings\" class=\"Button\">Settings</a>\
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
  httpd_resp_set_type(req, "text/html");
  httpd_resp_send_chunk(req, header, strlen(header));
  //httpd_resp_send_chunk(req, ip_str, strlen(ip_str));
  httpd_resp_send_chunk(req, bottom, strlen(bottom));
  httpd_resp_send_chunk(req, NULL, 0);
  //httpd_resp_send(req, response_message, HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
}

