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


AVFormatContext *fmtCtx;
int vidx = -1, aidx = -1;
AVStream* vStream, * aStream;
AVCodecParameters* vPara, * aPara;


int main(void) {
    int ret = avformat_open_input(&fmtCtx, "c:\\mpstudy\\fire.avi", NULL, NULL);

    if (ret != 0) {
        return -1;
    }

    avformat_find_stream_info(fmtCtx, NULL);

    vidx = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    aidx = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_AUDIO, -1, vidx, NULL, 0);

    vStream = fmtCtx->streams[vidx];

    printf("프레임 개수 = %I64d\n", vStream->nb_frames);
    printf("프레임 레이트 = %d / %d\n", vStream->avg_frame_rate.num, vStream->avg_frame_rate.den);
    printf("타임 베이스 = %d / %d\n", vStream->time_base.num, vStream->time_base.den);

    vPara = vStream->codecpar;

    printf("폭 = %d\n", vPara->width);
    printf("높이 = %d\n", vPara->height);
    printf("색상 포맷 = %d\n", vPara->format);
    printf("코덱 = %d\n", vPara->codec_id);
    printf("--------------------------------\n");

    aStream = fmtCtx->streams[aidx];

    printf("프레임 개수 = %I64d\n", aStream->nb_frames);
    printf("타임 베이스 = %d / %d\n", aStream->time_base.num, aStream->time_base.den);

    avformat_close_input(&fmtCtx);
}

