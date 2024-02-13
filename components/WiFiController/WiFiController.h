#ifndef WiFiController_h
#define WiFiController_h

typedef enum WifiControllerMessageType {
    startHTTPServer,
    connectingFromHTTPServer,
    staConnectedDidGetIP,
} WifiControllerMessageType;

typedef struct WifiControllerMessage {
    WifiControllerMessageType messageType;
} WifiControllerMessage;

BaseType_t wifiControllerSendMessage(WifiControllerMessageType messageType);

void startWifiController(void);

#endif 
