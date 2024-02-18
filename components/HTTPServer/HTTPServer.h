#ifndef HTTPServer_h
#define HTTPServer_h

#define otaUpdatePending 0
#define otaUpdateSuccessful 1
#define otaUpdateFailed -1

typedef enum HTTPServerWifiConnectionStatus {
    none = 0,
    connecting,
    connectionFailed,
    connected,
    disconnect,
} HTTPServerWifiConnectionState;

typedef enum HTTPServerMessageType
{
    httpServerWifiConnect = 0,
    httpServerWifiConnentDidSucceed,
    httpServerWifiConnentDidFail,
    httpServerWifiDisonnect,
    httpServerOTADidUpdate,
    httpServerOTADidFailUpdate,
    httpServerDidInitializeTimeService,
} HTTPServerMessageType;

typedef struct HTTPServerMessage {
    HTTPServerMessageType message;
} HTTPServerMessage;

BaseType_t httpServerMonitorSendMessage(HTTPServerMessage message);
void httpServerStart(void);
void httpServerStop(void);
void http_server_fw_update_reset_callback(void *arg);

#endif 
