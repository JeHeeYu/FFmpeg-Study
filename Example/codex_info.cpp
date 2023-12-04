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
AVStream* vStream, * aStream;
AVCodecParameters* vPara, * aPara;
const AVCodec* vCodec, * aCodec;
AVCodecContext* vCtx, * aCtx;


int main(void) {
    int ret = avformat_open_input(&fmtCtx, "D:\\study\\ffmpeg\\fire.avi", NULL, NULL);


    if (ret != 0) {
        return -1;
    }

    avformat_find_stream_info(fmtCtx, NULL);

    vidx = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    aidx = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_AUDIO, -1, vidx, NULL, 0);

    // 비디오 코텍 오픈
    vStream = fmtCtx->streams[vidx];
    vPara = vStream->codecpar;
    vCodec = avcodec_find_decoder(vPara->codec_id);
    vCtx = avcodec_alloc_context3(vCodec);
    avcodec_parameters_to_context(vCtx, vPara);
    avcodec_open2(vCtx, vCodec, NULL);

    // 오디오 코덱 오픈
    aStream = fmtCtx->streams[aidx];
    aPara = aStream->codecpar;
    aCodec = avcodec_find_decoder(aPara->codec_id);
    aCtx = avcodec_alloc_context3(aCodec);
    avcodec_parameters_to_context(aCtx, aPara);
    avcodec_open2(aCtx, aCodec, NULL);

    // 코덱 정보 조사
    printf("비디오 코텍 : %d %s(%s)\n", vCodec->id, vCodec->name, vCodec->long_name);
    printf("능력치 : %x\n", vCodec->capabilities);
    printf("오디오 코텍 : %d %s(%s)\n", aCodec->id, aCodec->name, aCodec->long_name);
    printf("능력치 : %x\n", aCodec->capabilities);

    avcodec_free_context(&vCtx);
    avcodec_free_context(&aCtx);
    avformat_close_input(&fmtCtx);
}
