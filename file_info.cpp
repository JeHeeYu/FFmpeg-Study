extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavdevice/avdevice.h>
#include <libavfilter/avfilter.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
}

#include <stdio.h>
#include <Windows.h>


AVFormatContext* fmtCtx;

int main(void) {

    int ret = avformat_open_input(&fmtCtx, "C:\\mpstudy\\fire.avi", NULL, NULL);


    if (ret != 0) {
        return -1;
    }

    avformat_find_stream_info(fmtCtx, NULL);

    printf("스트림 개수 = %d\n", fmtCtx->nb_streams);
    printf("시간 = %I64d초\n", fmtCtx->duration / AV_TIME_BASE);
    printf("비트레이트 = %I64d\n", fmtCtx->bit_rate);

    avformat_close_input(&fmtCtx);

    return 0;

}

