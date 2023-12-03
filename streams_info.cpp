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
int vidx = -1, aidx = -1;

int main(void) {

    int ret = avformat_open_input(&fmtCtx, "C:\\mpstudy\\fire.avi", NULL, NULL);


    if (ret != 0) {
        return -1;
    }

    avformat_find_stream_info(fmtCtx, NULL);

    for (unsigned i = 0; i < fmtCtx->nb_streams; i++) {
        if (fmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            vidx = i;
        }
        if (fmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            aidx = i;
        }
    }

    printf("video = %d번, audio = %d번\n\n", vidx, aidx);

    av_dump_format(fmtCtx, vidx, "C:\\mpstudy\\fire.avi", 0);

    avformat_close_input(&fmtCtx);

    return 0;

}

