/*
 * remoter_messsage_gui.c
 *
 *  Created on: 2017/9/5
 *      Author: yuhang
 */

 #include "remoter_message.h"
 #include "remoter_main.h"

static int16_t ConvertGuiMsg2BtMsg(struct_remote_message *msg_gui, struct_remote_message *msg);
static int16_t ConvertGuiMsg2WifiMsg(struct_remote_message *msg_gui, struct_remote_message *msg);
static int16_t ConvertBtMsg2GuiMsg(struct_remote_message *msg, struct_remote_message *msg_gui);
static int16_t ConvertPMMsg2GuiMsg(struct remote_message *msg, struct_remote_message *msg_gui);
static int16_t ConvertWifiMsg2GuiMsg(struct_remote_message *msg, struct_remote_message *msg_gui);

int16_t ConvertGuiMsg2Msg(struct_remote_message *msg_gui, struct_remote_message *msg) {
    msg->task_src = TASK_GUI_SVC;
    ///msg->hwSrc = msg_gui->hwSrc;
    int32_t msgid = msg_gui->msg.msg_gui_req.msgid;
    PRINTF("%s, msg_id=0x%x\n", __func__, msgid);
    if (MSG_ID_GUI_BT_BEGIN < msgid && msgid < MSG_ID_GUI_BT_END) {
        return ConvertGuiMsg2BtMsg(msg_gui, msg);
    } else if (MSG_ID_GUI_WIFI_BEGIN < msgid && msgid < MSG_ID_GUI_WIFI_END) {
        return ConvertGuiMsg2WifiMsg(msg_gui, msg);
    }
    return -1;  // Todo error code
}

int16_t ConvertMsg2GuiMsg(struct_remote_message *msg, struct_remote_message *msg_gui) {
    msg_gui->task_dst = TASK_GUI;
    ///msg_gui->hwSrc = msg->hwSrc;
    PRINTF("%s, msg->task_src=%d\n", __func__, msg->task_src);
    switch (msg->task_src) {
        case TASK_BT:
            return ConvertBtMsg2GuiMsg(msg, msg_gui);
        case TASK_WIFI:
            return ConvertWifiMsg2GuiMsg(msg, msg_gui);
            break;
        case TASK_PM:
            return ConvertPMMsg2GuiMsg(msg, msg_gui);
        case TASK_TP:
            break;
//        case TASK_KEYPAD:
//            break;
        case TASK_AUDIO:
            break;
        case TASK_ZIGBEE:
            break;
        /*case TASK_DMIC:
            break;*/
        default:
            return -1;  // Todo error code
    }
    return 0;  // Todo success code
}

/* Bluetooth */
static int16_t ConvertGuiMsg2BtMsg(struct_remote_message *msg_gui, struct_remote_message *msg) {
    switch (msg_gui->msg.msg_gui_req.msgid) {
        case MSG_ID_GUI_BT_OPEN_REQ:
            msg->msg.msg_bt = msg_bt_advertising_start;
            break;
        case MSG_ID_GUI_BT_CLOSE_REQ:
            msg->msg.msg_bt = msg_bt_advertising_stop;
            break;
        case MSG_ID_GUI_BT_SCAN_START_REQ:
            msg->msg.msg_bt = msg_bt_scan_start;
            break;
        case MSG_ID_GUI_BT_SCAN_STOP_REQ:
            msg->msg.msg_bt = msg_bt_scan_stop;
            break;
        case MSG_ID_GUI_BT_CONNECT_REQ:
            msg->msg.msg_bt = msg_bt_connect;
            break;
        case MSG_ID_GUI_BT_DISCONNECT_REQ:
            msg->msg.msg_bt = msg_bt_disconnect;
            break;
        case MSG_ID_GUI_BT_SET_DEVICENAME_REQ:
            // Todo
            break;
        case MSG_ID_GUI_BT_BOND_REQ:
            // Todo
            break;
        case MSG_ID_GUI_BT_CENTRAL_UPDATE_PARAM_REQ:
            // Todo
            break;
        case MSG_ID_GUI_BT_PERIPHERAL_UPDATE_PARAM_REQ:
            // Todo
            break;
        default:
            return -1;  // Todo error code
    }
    msg->task_dst = TASK_BT;
    return 0;  // Todo success code
}

/* Wifi */
static int16_t ConvertGuiMsg2WifiMsg(struct_remote_message *msg_gui, struct_remote_message *msg) {
    switch (msg_gui->msg.msg_gui_req.msgid) {
        case MSG_ID_GUI_WIFI_OPEN_REQ:
            msg->msg.msg_wifi.msg_type = WIFI_OPEN;
            break;
        case MSG_ID_GUI_WIFI_CLOSE_REQ:
            msg->msg.msg_wifi.msg_type = WIFI_CLOSE;
            break;
        case MSG_ID_GUI_WIFI_SCAN_REQ:
            msg->msg.msg_wifi.msg_type = WIFI_SCAN;
            break;
        case MSG_ID_GUI_WIFI_CONNECT_REQ:
            msg->msg.msg_wifi.msg_type = WIFI_CONNECT;
            break;
        case MSG_ID_GUI_WIFI_DISCONNECT_REQ:
            msg->msg.msg_wifi.msg_type = WIFI_DISC;
            break;
        default:
            return -1;  // Todo error code
    }
    msg->task_dst = TASK_WIFI;
    return 0;  // Todo success code
}

/* Bluetooth */
static int16_t ConvertBtMsg2GuiMsg(struct_remote_message *msg, struct_remote_message *msg_gui) {
    PRINTF("%s, msg: msg_type=%d, msg_id=0x%x, param_len=%d\n", __func__, msg->msg.msg_bt.msg_type, msg->msg.msg_bt.msg_id, msg->msg.msg_bt.param_len);
    if (msg->msg.msg_bt.msg_type == BT_EVENT) {
        int strlen;
        memset(&msg_gui->msg.msg_gui_rsp, 0, sizeof(msg_gui->msg.msg_gui_rsp));
        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_ERR;

        switch (msg->msg.msg_bt.msg_id) {
            case BT_Event_AdvertisingComplete:
                /* Advertising command complete event
                    PAR_LEN     0x01
                    status      1: advertising started  0: advertising stopped */
                if (msg->msg.msg_bt.param_len == 0x01) {
                    if (msg->msg.msg_bt.params[0] == 0x01) {
                        msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_OPEN_RSP;
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    } else if (msg->msg.msg_bt.params[0] == 0x00) {
                        msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_CLOSE_RSP;
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    }
                }
                break;
            case BT_Event_ScanResult:
                /* scan result event
                    PAR_LEN 0x07 + n
                    bd_addr_type    1 bytes, Bluetooth device address type
                    bd_addr         6 bytes, Bluetooth device address
                    dev_name        n byte, device name of the found device */
                strlen = msg->msg.msg_bt.param_len - 0x07;
                if (strlen >= 0) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_SCAN_RESULT_IND;
                    msg_gui->msg.msg_gui_rsp.data.bt.address_type = msg->msg.msg_bt.params;
                    memcpy(msg_gui->msg.msg_gui_rsp.data.bt.address, msg->msg.msg_bt.params + 1, 6);
                    if (strlen >= BT_DEVICENAME_LEN) strlen = BT_DEVICENAME_LEN - 1;
                    memcpy(msg_gui->msg.msg_gui_rsp.data.bt.deviceName, msg->msg.msg_bt.params + 7, strlen);
                }
                break;
            case BT_Event_ScanComplete:
                /* scan complete event
                    PAR_LEN     0x01
                    num         Total found device numbers */
                if (msg->msg.msg_bt.param_len == 0x01) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_SCAN_COMPLETE_IND;
                    msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    msg_gui->msg.msg_gui_rsp.data.bt.num = msg->msg.msg_bt.params[0];
                }
                break;
            case BT_Event_Connected:
                /* Connection complete event
                    PAR_LEN     0x07
                    status       1 byte,     Connection status   0x00: success
                    bd_addr     6 bytes,    Bluetooth device address */
                if (msg->msg.msg_bt.param_len == 0x07) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_CONNECT_RSP;
                    if (msg->msg.msg_bt.params[0] == 0x00) {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    } else {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_ERR;
                    }
                    memcpy(msg_gui->msg.msg_gui_rsp.data.bt.address, msg->msg.msg_bt.params + 1, 6);
                }
                break;
            case BT_Event_Disconnected:
                /* Disconnection event
                    PAR_LEN     0x07
                    reason      1 byte,     Disconnection reason
                    bd_addr     6 bytes,    Bluetooth device address */
                if (msg->msg.msg_bt.param_len == 0x07) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_DISCONNECT_RSP;
                    msg_gui->msg.msg_gui_rsp.data.bt.reason = msg->msg.msg_bt.params[0];
                    memcpy(msg_gui->msg.msg_gui_rsp.data.bt.address, msg->msg.msg_bt.params + 1, 6);
                }
                break;
            case BT_Event_DeviceNameComplete:
                /* Set Device Name status
                    PAR_LEN     0x01
                    status      1 byte(0x00 is OK) */
                if (msg->msg.msg_bt.param_len == 0x01) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_SET_DEVICENAME_RSP;
                    if (msg->msg.msg_bt.params[0] == 0x00) {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    } else {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_ERR;
                    }
                }
                break;
            case BT_Event_BondComplete:
                if (msg->msg.msg_bt.param_len == 0x08) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_BOND_RSP;
                    if (msg->msg.msg_bt.params[0] == 0x00) {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    } else {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_ERR;
                    }
                    msg_gui->msg.msg_gui_rsp.data.bt.bonded = msg->msg.msg_bt.params[1];
                    memcpy(msg_gui->msg.msg_gui_rsp.data.bt.address, msg->msg.msg_bt.params + 2, 6);
                }
                break;
            case BT_Event_CentralUpdateParam:
                /* central update status
                    PAR_LEN     0x01
                    status      1 byte(0x00 is OK) */
                if (msg->msg.msg_bt.param_len == 0x01) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_CENTRAL_UPDATE_PARAM_RSP;
                    if (msg->msg.msg_bt.params[0] == 0x00) {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    } else {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_ERR;
                    }
                }
                break;
            case BT_Event_PeripheralUpdateParam:
                /* peripheral update status
                    PAR_LEN     0x01
                    status      1 byte(0x00 is OK) */
                if (msg->msg.msg_bt.param_len == 0x01) {
                    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_BT_PERIPHERAL_UPDATE_PARAM_RSP;
                    if (msg->msg.msg_bt.params[0] == 0x00) {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
                    } else {
                        msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_ERR;
                    }
                }
                break;
            default:
                return -1;  // Todo error code
        }
    } else if (msg->msg.msg_bt.msg_type == BT_DATA_IND) {
        // Todo
    } else {
            return -1;  // Todo error code
    }
    msg_gui->task_src = TASK_BT;
    PRINTF("%s, msg_gui: msg_id=%d, result=%d\n", __func__, msg_gui->msg.msg_gui_rsp.msgid, msg_gui->msg.msg_gui_rsp.result);
    return 0;  // Todo success code
}

/* PowerManager */
int16_t ConvertPMMsg2GuiMsg(struct remote_message *msg, struct_remote_message *msg_gui) {
    PRINTF("%s, msg: msg_type=%d, msg_id=0x%x, param_len=%d\n", __func__, msg->msg.msg_bt.msg_type, msg->msg.msg_bt.msg_id, msg->msg.msg_bt.param_len);
    memset(&msg_gui->msg.msg_gui_rsp, 0, sizeof(msg_gui->msg.msg_gui_rsp));
    msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_PM_REFRESH_IND;
    msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
    msg_gui->msg.msg_gui_rsp.data.pm.level = msg->msg.msg_pm.capacity;
    msg_gui->msg.msg_gui_rsp.data.pm.battery_temp = msg->msg.msg_pm.batt_temperature;
    msg_gui->msg.msg_gui_rsp.data.pm.charging_status = msg->msg.msg_pm.charging_status;
}

/* Wifi */
static int16_t ConvertWifiMsg2GuiMsg(struct_remote_message *msg, struct_remote_message *msg_gui) {
    PRINTF("%s, msg: msg_type=%d, msg_id=0x%x, param_len=%d\n", __func__, msg->msg.msg_bt.msg_type, msg->msg.msg_bt.msg_id, msg->msg.msg_bt.param_len);
    memset(&msg_gui->msg.msg_gui_rsp, 0, sizeof(msg_gui->msg.msg_gui_rsp));
    msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_ERR;

    switch (msg->msg.msg_wifi.msg_type) {
        case WIFI_SCAN:
            msg_gui->msg.msg_gui_rsp.msgid = MSG_ID_GUI_WIFI_SCAN_RSP;
            msg_gui->msg.msg_gui_rsp.result = MSG_RESULT_GUI_OK;
            msg_gui->msg.msg_gui_rsp.data.wifi.scan_num = msg->msg.msg_wifi.wifi_info.scan_num;
            msg_gui->msg.msg_gui_rsp.data.wifi.scan_list = msg->msg.msg_wifi.wifi_info.pWifi_Scan_List;
            break;
    }

    msg_gui->task_src = TASK_WIFI;
    PRINTF("%s, msg_gui: msg_id=%d, result=%d\n", __func__, msg_gui->msg.msg_gui_rsp.msgid, msg_gui->msg.msg_gui_rsp.result);
    return 0;  // Todo success code
}

