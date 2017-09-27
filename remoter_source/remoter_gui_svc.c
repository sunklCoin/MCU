/*
 * remoter_gui_svc.c
 *
 *  Created on: 2017/08/01
 *      Author: xuke
 */

#include "remoter_gui_svc.h"

void GuiService_Task(void *pvParameters)
{
	int ret = 0;
	struct remote_message msg_recv = {0};
	struct remote_message msg_send = {0};

	PRINTF("%s\n", __func__);
    while (1)
    {
    	memset(&msg_recv, 0, sizeof(struct remote_message));
		ret = Message_Receive(&msg_recv);
		if (!ret)
		{
			PRINTF("%s, task_src=0x%x\n", __func__, msg_recv.task_src);

#if 1
                if (msg_recv.task_src == TASK_GUI) {
                    ConvertGuiMsg2Msg(&msg_recv, &msg_send);
                    Message_Send(&msg_send);
                } else if (TASK_GUI_SVC < msg_recv.task_src && msg_recv.task_src < TASK_MAX) {
                    ConvertMsg2GuiMsg(&msg_recv, &msg_send);
                    Message_Send(&msg_send);
                } else {
                    PRINTF("%s, invalid message\n", __func__);
                }
#else
			/* Get messages from UI. */
			if (msg_recv.task_src == TASK_GUI)
			{
				if (msg_recv.task_dst == TASK_BT)
				{
					msg_send.task_src = TASK_GUI_SVC;
					msg_send.task_dst = TASK_BT;
					msg_send.msg.msg_bt = msg_recv.msg.msg_bt;
				}
			}
			/* Get messages from BT. */
			else if (msg_recv.task_src == TASK_BT)
			{
				msg_send.task_src = TASK_BT;
				msg_send.task_dst = TASK_GUI;
				msg_send.msg.msg_bt = msg_recv.msg.msg_bt;
			}
			else if (msg_recv.task_src == TASK_GUI)
			{
				msg_send.task_src = TASK_GUI;
				msg_send.task_dst = TASK_GUI;
				msg_send.msg.msg_pm = msg_recv.msg.msg_pm;
			}
			else
			{
				PRINTF("%s, invalid message\n", __func__);
			}

			Message_Send(&msg_send);
#endif
		}

		vTaskSuspend(NULL);
    }
}
