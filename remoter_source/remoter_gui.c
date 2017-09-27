/*
 * remoter_gui.c
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#include "remoter_gui.h"
#include "remoter_lcd.h"

#if GUI_TYPE_EMWIN

/*******************************************************************************
 * Application implemented functions required by emWin library
 ******************************************************************************/
void LCD_X_Config(void)
{
    GUI_DEVICE_CreateAndLink(GUIDRV_LIN_16, GUICC_565, 0, 0);

    LCD_SetSizeEx(0, LCD_WIDTH, LCD_HEIGHT);
    LCD_SetVSizeEx(0, LCD_WIDTH, LCD_HEIGHT);

    LCD_SetVRAMAddrEx(0, (void *)VRAM_ADDR);
}

int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void *pData)
{
    return 0;
}

void GUI_X_Config(void)
{
    /* Assign work memory area to emWin */
    GUI_ALLOC_AssignMemory((void *)GUI_MEMORY_ADDR, GUI_NUMBYTES);

    /* Select default font */
    GUI_SetDefaultFont(GUI_FONT_6X8);
}

void GUI_X_Init(void)
{
}

/* Dummy RTOS stub required by emWin */
void GUI_X_InitOS(void)
{
}

/* Dummy RTOS stub required by emWin */
void GUI_X_Lock(void)
{
}

/* Dummy RTOS stub required by emWin */
void GUI_X_Unlock(void)
{
}

/* Dummy RTOS stub required by emWin */
U32 GUI_X_GetTaskId(void)
{
    return 0;
}

void GUI_X_ExecIdle(void)
{
}

GUI_TIMER_TIME GUI_X_GetTime(void)
{
    return 0;
}

void GUI_X_Delay(int Period)
{
}

void *emWin_memcpy(void *pDst, const void *pSrc, long size)
{
    return memcpy(pDst, pSrc, size);
}

#define CLEAR_BUTTON_ID (GUI_ID_BUTTON0)

#define COLOR_BUTTONS 8
#define COLOR_BUTTON_FIRST_ID (GUI_ID_USER)
#define COLOR_BUTTON_LAST_ID (COLOR_BUTTON_FIRST_ID + COLOR_BUTTONS - 1)

static GUI_COLOR button_color[COLOR_BUTTONS] = {GUI_WHITE,   GUI_YELLOW, GUI_ORANGE, GUI_RED,
                                                GUI_MAGENTA, GUI_BLUE,   GUI_GREEN,  GUI_BLACK};

static void cbBackgroundWin(WM_MESSAGE *pMsg)
{
    int widget_id;

    switch (pMsg->MsgId)
    {
        case WM_NOTIFY_PARENT:
            widget_id = WM_GetId(pMsg->hWinSrc);
            if (widget_id >= COLOR_BUTTON_FIRST_ID && widget_id <= COLOR_BUTTON_LAST_ID)
            {
                GUI_SetColor(button_color[widget_id - COLOR_BUTTON_FIRST_ID]);
            }
            else if (widget_id == CLEAR_BUTTON_ID && pMsg->Data.v == WM_NOTIFICATION_CLICKED)
            {
                GUI_Clear();
            }
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

static void cbCanvasWin(WM_MESSAGE *pMsg)
{
    GUI_PID_STATE *pid_state;
    static GUI_PID_STATE pid_state_0;

    switch (pMsg->MsgId)
    {
        case WM_TOUCH:
            pid_state = (GUI_PID_STATE *)pMsg->Data.p;
            if (pid_state->Pressed)
            {
                if (pid_state_0.Pressed)
                {
                    GUI_DrawLine(pid_state_0.x, pid_state_0.y, pid_state->x, pid_state->y);
                }
                else
                {
                    GUI_DrawPoint(pid_state->x, pid_state->y);
                }
            }
            pid_state_0 = *pid_state;
            break;
        default:
            WM_DefaultProc(pMsg);
    }
}

/*!
 * @brief Task responsible for running emWin.
 */
static void emWin_Task(void *pvParameters)
{
    PRINTF("emWin_task\n");

    while (1)
    {
#if 1	// For test BT message only.
    	struct remote_message msg_send = {
    		.task_src = TASK_GUI_SVC,
    		.task_dst = TASK_BT,
    		.msg.msg_bt = msg_bt_advertising_start,
    	};
    	vTaskDelay(1000);
    	Message_Send(&msg_send);
#endif
        vTaskSuspend(NULL);
    }
}

int emWin_Init(void)
{
	int i = 0, ret = 0;

    /* emWin start */
    GUI_Init();

    /* Set size and default color for the background window */
    WM_SetSize(WM_HBKWIN, LCD_WIDTH, LCD_HEIGHT);
    WM_SetDesktopColor(GUI_WHITE);

    /* Set callback for the backgroung window */
    WM_SetCallback(WM_HBKWIN, cbBackgroundWin);

    /* Solid color display */
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    BUTTON_SetReactOnLevel();

    /* Create the 'clear' button */
    BUTTON_Handle hButtonClear;
    hButtonClear = BUTTON_CreateEx(4, 2, 30, 25, 0, WM_CF_SHOW, 0, CLEAR_BUTTON_ID);
    BUTTON_SetText(hButtonClear, "CLR");

    /* Create color selection buttons */
    BUTTON_Handle hButtonColor[COLOR_BUTTONS];
    for (i = 0; i < COLOR_BUTTONS; i++)
    {
        hButtonColor[i] = BUTTON_CreateEx(4, i * 30 + 32, 30, 25, 0, WM_CF_SHOW, 0, COLOR_BUTTON_FIRST_ID + i);
        BUTTON_SetSkinClassic(hButtonColor[i]);
        BUTTON_SetBkColor(hButtonColor[i], BUTTON_CI_UNPRESSED, button_color[i]);
    }

    /* Create canvas */
    WM_HWIN hCanvas;
    hCanvas = WM_CreateWindowAsChild(35, 0, WM_GetWindowSizeX(WM_HBKWIN) - 35, WM_GetWindowSizeY(WM_HBKWIN), 0,
                                     WM_CF_SHOW, cbCanvasWin, 0);
    /* Select canvas window and leave it selected forever */
    WM_SelectWindow(hCanvas);
    GUI_SetColor(GUI_BLACK);
    GUI_SetDrawMode(GUI_DM_NORMAL);
    GUI_SetPenSize(4);
    GUI_DispStringHCenterAt("Touch and drag to draw.\nClick the CLR button to clear the canvas.",
                            WM_GetWindowSizeX(hCanvas) / 2, WM_GetWindowSizeY(hCanvas) / 2);

    WM_Exec();

    return ret;
}

#endif

void Gui_Task(void *pvParameters)
{
	void *pvParam = pvParameters;

#if GUI_TYPE_EMWIN
	emWin_Task(pvParam);
#elif GUI_TYPE_TOUCHGFX
	touchGFX_Task();
#endif
}

int Gui_Init(void)
{
	status_t status = kStatus_Success;

#if GUI_TYPE_EMWIN
	status = emWin_Init();
#elif GUI_TYPE_TOUCHGFX
	status = touchGFX_Init();
#endif

	return (status == kStatus_Success);
}
