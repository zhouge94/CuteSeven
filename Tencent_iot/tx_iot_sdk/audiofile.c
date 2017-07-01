/**
 * 这段代码的目的是用来演示：手Q向设备发送语音消息
 *
 * 手Q发送的语音消息实际上就是发送了一个AMR格式的文件。
 * 首先确保手Q与设备已经绑定，通过tx_init_file_transfer函数设置文件传输相关的回调函数。
 * 
 * 期望的结果是：
 * 设备收到文件后，ontransfercomplete函数中将有文件信息的打印，
 * tx_init_file_transfer第2个参数是接收文件的目录，该目录下将存在刚刚收到的文件。
 * 当然您也可以通过tx_send_file_to发送文件（视频，语音，图片等）给手Q。
 */
 
#include <stdio.h>
#include <string.h>

#include "TXSDKCommonDef.h"
#include "TXDeviceSDK.h"
#include "TXFileTransfer.h"
void on_send_msg_ret(const unsigned int cookie, int err_code)
{
    printf("on_send_alarm_msg_ret, cookie[%u] ret[%d]\n", cookie, err_code);
}

void cb_on_transfer_progress(unsigned long long transfer_cookie, unsigned long long transfer_progress, unsigned long long max_transfer_progress)
{
    printf("========> on file progress %f%%\n", transfer_progress * 100.0 / max_transfer_progress);
}

// 收到C2C transfer通知
void cb_on_recv_file(unsigned long long transfer_cookie, const tx_ccmsg_inst_info * inst_info, const tx_file_transfer_info * tran_info)
{
}



unsigned int *cookie;
unsigned long long* to_targetids;
unsigned int to_targetids_count=0;
int msg_id=9999;
char *text="收到";

void cb_on_transfer_complete(unsigned long long transfer_cookie, int err_code, tx_file_transfer_info * tran_info) {
char cmd[1000];
    printf("================ontransfer complete=====transfer_cookie == %lld ====================\n", transfer_cookie);
    // 这个 transfer_cookie 是SDK内部执行文件传输（接收或发送） 任务 保存的一个标记，在回调完这个函数后，transfer_cookie 将失效
    // 可以根据 transfer_cookie 查询文件的信息

    //在完成回调里直接传回 tran_info
    // tx_file_transfer_info ftInfo = {0};
    // tx_query_transfer_info(transfer_cookie, &ftInfo);

    printf("errcode %d, bussiness_name [%s], file path [%s], file type [%d]\n", err_code, tran_info->bussiness_name,  tran_info->file_path,tran_info->file_type);
    sprintf(cmd,"{\"type\":\"file\",\"bussiness_name\":\"%s\",\"errcode\":%d,\"file_path\":\"%s\"}\n\r",tran_info->bussiness_name,err_code,tran_info->file_path);
    fifo_send(cmd);
    tx_send_text_msg(msg_id, text,&on_send_msg_ret,cookie,to_targetids,to_targetids_count);

    printf(cmd);
    printf("===============================================================================\n");
}
