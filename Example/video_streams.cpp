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
#include <conio.h>


AVFormatContext* fmtCtx;
int vidx = -1, aidx = -1;
AVStream* vStream, * aStream;
AVCodecParameters* vPara, * aPara;
const AVCodec* vCodec, * aCodec;
AVCodecContext* vCtx, * aCtx;
AVPacket packet;
AVFrame vFrame, aFrame;

void arDump(void* array, int length)
{
	for(int i = 0; i < length; i++) {
		printf("%02X", *((unsigned char*)array + i));
	}
}

int main(void)
{
	int ret = avformat_open_input(&fmtCtx, "D:\\study\\ffmpeg\\fire.avi", NULL, NULL);

	if (ret != 0) {
		return - 1;
	}

	avformat_find_stream_info(fmtCtx, NULL);

	vidx = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	aidx = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_AUDIO, -1, vidx, NULL, 0);

	vStream = fmtCtx->streams[vidx];
	vPara = vStream->codecpar;
	vCodec = avcodec_find_decoder(vPara->codec_id);
	vCtx = avcodec_alloc_context3(vCodec);
	avcodec_parameters_to_context(vCtx, vPara);
	avcodec_open2(vCtx, vCodec, NULL);

	aStream = fmtCtx->streams[aidx];
	aPara = aStream->codecpar;
	aCodec = avcodec_find_decoder(aPara->codec_id);
	aCtx = avcodec_alloc_context3(aCodec);
	avcodec_parameters_to_context(aCtx, aPara);
	avcodec_open2(aCtx, aCodec, NULL);

	// 루프를 돌며 패킷을 모두 읽음
	int vcount = 0, acount = 0;

	while (av_read_frame(fmtCtx, &packet) == 0) {
		if (packet.stream_index == vidx) {
			avcodec_send_packet(vCtx, &packet);
			avcodec_receive_frame(vCtx, &vFrame);

			if (vcount == 0) {
				printf("Video format : %d(%d  x %d).\n", vFrame.format, vFrame.width, vFrame.height);
			}

			printf("V%-3d(pts=%3l64d, size=%d) : ", vcount++, vFrame.pts);

			for (int i = 0; i < 3; i++) {
				printf("%d", vFrame.linesize[i]);
			}

			arDump(vFrame.data[0], 4);
			arDump(vFrame.data[1], 2);
			arDump(vFrame.data[2], 2);
		}

		if (packet.stream_index == aidx) {
			avcodec_send_packet(aCtx, &packet);
			avcodec_receive_frame(aCtx, &aFrame);

			if (acount == 0) {
				printf("Audio format : %d, %d\n", aFrame.format, aFrame.sample_rate);
			}

			printf("A%-3d(pts=%3I64d) : ", acount++, aFrame.pts);

			arDump(aFrame.extended_data, 16);
		}
		
		av_packet_unref(&packet);
		printf("\n");
		if (_getch() == 27) {
			break;
		}
	}

	// 메모리 해제
	av_frame_unref(&vFrame);
	av_frame_unref(&aFrame);
	avcodec_free_context(&vCtx);
	avcodec_free_context(&aCtx);
	avformat_close_input(&fmtCtx);
}
