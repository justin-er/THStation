
idf_component_register(SRCS "HTTPServer.c"
                       EMBED_FILES "Webpage/app.css" "webpage/app.js" "webpage/favicon.ico" "webpage/index.html" "webpage/jquery-3.3.1.min.js"
                       INCLUDE_DIRS "."
                       REQUIRES "Configurations" "THReader" "WiFiController" "esp_http_server" "app_update" "esp_timer")
