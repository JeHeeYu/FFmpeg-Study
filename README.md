# FFmpeg-Study


## FFmpeg이란?
FFmpeg은 Michael Niedermayer의 주도하에 개발된 동영상 라이브러리이다.
<br>
모든 동영상, 음악, 사진 포맷들의 디코딩과 인코딩을 목표로 만들어진 오픈소스 프로젝트이다.
<br>
곰, 다음팟, VLC 등의 대부분 플레이어들이 FFmpeg 라이브러리를 사용하고 있다.
<br>
<br>
FFmpeg은 GPL(General Public License) 라이센스로, 사용한 프로그램도 GPL이 되어 소스를 공개해야 한다.

<br>

## FFmpeg 실행 파일
FFmpeg 실행 파일로, bin 폴더에 3개의 exe 파일이 있다.
- ffplay.exe
- ffprobe.exe
- ffmpeg.exe

<br>

### ffplay
ffplay는 간단한 동영상 재생기이다.
<br>
인수로 파일명만 주면 바로 실행되며, 스페이스바(재생 및 정지), 방향키(감기 기능) 등 간단한 기능만 있다.
```
ffplay [file].avi
```

<br>

### ffprobe
ffprobe는 동영상 분석툴로, 파일명을 인수로 주면 동영상에 대한 정보를 보여준다.
```
ffprobe [file].avi
```

![image](https://github.com/JeHeeYu/FFmpeg-Study/assets/87363461/3d98cfa3-91ce-490f-8f18-a82608509983)

<br>

### ffmpeg
ffmpeg은 인코딩 프로그램이다.
<br>
동영상을 다른 포맷으로 변경 또는 일부를 잘라내거나 오디오 분리 등등 여러 가지 작업을 할 수 있다.
<br>
기본 형식은 다음과 같다.
```
ffmpeg [전역옵션] -i 입력파일 출력파일
```
전역 옵션은 출력 파일이 이미 있을 때 덮어 쓸지 말지를 지정하는 -y, -n 등이 있다.
<br>
전역 옵션을 쓸 일은 많지 않다.
<br>
<br>
아래 명령어는 ffmpeg의 가장 간단한 명령이다.
```
ffmpeg -i [file].avi [file].mpeg
```
[file].avi 파일을 읽어 [file].mpeg으로 바꾸라는 뜻이다.
<br>
avi 파일이 mpeg 파일로 바뀌며, 용량이 조금 늘어나는데 동영상의 내용은 같다.
<br>
<br>
압축 방법이 바뀌었으므로 화질에 차이가 있으나, 구분하기 쉽지 않다.
<br>
동영상을 컨버팅하는 옵션에는 여러 가지가 있으며, 옵션은 아래 표와 같다.
|옵션|설명|
|:---:|:---|
|-i 입력파일|컨버팅 대상 파일을 지정하며, 입력 파일 여러 개이면 -i 옵션도 여러 번 사용 가능|
|-s 해상도|해상도 지정 명령어로 폭x높이 형태 또는 vga, sxga, wvga, hd720 등의 형태 사용|
|-r n|동영상 FPS|
|-ss|시작 시간으로 초 단위 또는 HH:MM:SS 이며, 생략 시 처음부터 시작|
|-t|분할할 길이로 생략 시 끝까지 지정되며 0으로 지정하면 10초|
|-to|분할할 끝 지점|
|-aspect|비율 지정 멸영어로 4:3, 16:9 방식 또는 1.33, 1.77 사용|
|-vn|비디오 제거 명령어로 오디오만 추출되며 디코딩 후 음성만 빼 재인코딩하므로 음성 코덱이 변경됨|
|-b:a n, b:v n|오디오/비디오 Bit Rate로 320k 과 같은 방식으로 지정되며 기본 값은 128k|
|-ab n|오디오 Bit Rate|
|-ar n|오디오 Sampling Rate|
|-ac n|오디오 채널|
|-threads n|사용할 스레드 숫자 지정|
|-preset|압축률과 시간을 설정하며 fast, medium, slow 등 사용|
|-f|파일 포맷을 지정하며 확장자에 근거하여 자동으로 결정|
|-crf|화질을 결정하며 0 ~ 59까지 사용. 0이 무손실|

<br>

## FFmpeg 라이브러리 구조
FFmpeg은 단순한 컨버팅 툴이 아닌 멀티미디어를 만들 수 있는 라이브러리이다.
<br>
FFMpeg은 기능별로 다음과 같은 라이브러리를 제공한다.
|이름|설명|
|:---:|:---|
|libavutil|난수 생성기로 수학 루틴 등의 유틸리티 기능 제공|
|libavcodec|디코더 및 인코더|
|libavformat|컨테이너의 먹서로 디먹서 기능|
|libavdevice|캡처 및 랜더링 기능 제공|
|libavfilter|미디어 필터|
|libswscale|이미지 스케일링으로 색상 변환|
|libswresample|오디오 리샘플링|

어떤 프로그램을 만드는가에 따라 필요한 라이브러리 조합이 달라진다.
<br>
bin 폴더에는 각 라이브러리에 대한 DLL이 있으며, 이 DLL의 함수를 호출하면 해당 기능을 사용할 수 있다.

<br>

## 동영상 파일 열기
동영상을 재생하려면 먼저 다음 함수로 파일을 열어야 한다.
<br>
동영상 파일을 열고 헤더를 읽는다.
<br>
FFmpeg의 기능을 사용하기 위한 시작 함수이다.
```
int avformat_open_input(AVFormatContext ** ps, const char * url, ff_const59 AVInputFormat * fmt, AVDictionary ** options)
```
헤더 정보는 첫 번째 인수인 ps 구조체에 저장된다.
<br>
호출 전 AVFormatContext 구조체를 avformat_alloc_context 함수로 할당하고 이중 포인터를 전달하면 여기에 채워준다.
<br>
미리 할당할 필요 없이 NULL을 넘기면 내부에서 구조체를 할당하고 채워서 돌려준다.
<br>
그래서 이중 포인터를 받는다.
<br>
<br>
두 번째 인수로 읽을 동영상 파일의 경로이다.
<br>
유니코드 문자열은 안되며 반드시 ANSI 문자열로 경로를 지정해야 한다.
<br>
<br>
세 번째 인수로 입력 포맷을 지정하되, NULL로 지정하면 자동으로 판별한다.
<br>
<br>
네 번째 인수로 옵션값의 배열이되 필요 없으면 NULL로 지정한다.
<br>
<br>
결국 필수 인자는 두 번째 url 밖에 없으며, 첫 번째 인수는 포인터 변수에 NULL을 대입하여 전달하면 된다.
<br>
<br>
성공 시 0을 리턴하며, 실패 시 -1을 리턴한다.
<br>
동영상 파일이 없거나 읽을 수 없는 경우 또는 파일을 열지 못할 수도 있다.
<br>
<br>
동영상의 헤더 정보는 AVFormatContext 구조체로 관리한다.
<br>
이 구조체가 동영상 자체를 대표하며 모든 작업 경과를 여기에 저장한다.
<br>
파일의 핸들러 같은 존재이다.
<br>
<br>
여기서 컨텍스트는 작업중인 정보라는 뜻이다.
<br>
이 안에는 동영상에 관련된 모든 정보가 들어 있다.
<br>
<br>
이 구조체 안에는 멤버가 굉장히 많은데, 당장 알아야 하는 멤버는 아래와 같다.
|멤버|설명|
|:---:|:---|
|char[1024] filename|파일의 경로|
|AVStream **streams|스트림의 배열|
|unsigned int nb_streams|동영상에 포함된 스트림의 개수|
|__int64 duration|재생 시간으로 AV_TIME_BASE 단위|
|__int64 bit_rate|초당 비트레이트|

스트림의 개수는 헤더에 즉시 조사되지만 스트림 정보나 시간, 비트레이트는 스트림을 열어야 알 수 있다.
<br>
streams는 스트림 정보를 담는 포인터의 배열일 뿐 아직 내용은 조사되지 않았다.
<br>
<br>
strems는 다음 함수로 조사한다.
```
int avformat_find_stream_info ( AVFormatContext * ic, AVDictionary ** options ) 
```
첫 번째 인수가 스트림을 열 파일 핸들, 두 번째 인수는 각 스트림에 적용할 옵션이다.
<br>
두 번째 옵션은 미사용 시 NULL을 지정한다.
<br>
핸들을 다 사용한 후 다음 함수로 핸들을 닫는다.
<br>
<br>
파일을 열 때 내부에서 메모리를 할당하기 때문에 이 함수로 반드시 메모리를 해제해야 한다.
<br>
<br>
[예제 코드](https://github.com/JeHeeYu/FFmpeg-Study/blob/main/Example/file_info.cpp)
<br>

![image](https://github.com/JeHeeYu/FFmpeg-Study/assets/87363461/c17f1822-cf4a-49be-b087-8f43eccd36e0)

<br>

비디오, 오디오 2개의 스트림이 있고 총 시간은 10초라는 것을 알 수 있다.

<br>

## 스트림 찾기
동영상은 파일 포맷이라기보다는 스트림의 집합으로 구성된 컨테이너이다.
<br>
스트림은 연속적인 바이트를 시간 순으로 저장해 놓은 것이다.
<br>
<br>
보통은 비디오, 오디오로 구성된 2개의 스트림을 가진다.
<br>

![image](https://github.com/JeHeeYu/FFmpeg-Study/assets/87363461/46123cee-06cb-4e44-a107-afecceca6a5c)

<br>

비디오 스트림에는 시간 흐름별로 사진이 연속적으로 저장되어 있고 오디오 스트림에는 사운드 샘플이 있다.
<br>
그림을 순서대로 보여 주며 사운드를 연주하면 동영상이 재생된다.
<br>
<br>
영화는 각국 언어별로 오디오 스트림 여러 개를 포함하는 경우도 있고 자막이나 그외의 스트림을 가지기도 한다.
<br>
스트림이 몇 개나 들어 있는지는 포맷 컨텍스트의 nb_streams 멤버로 조사하며 각 스트림은 streams 멤버에 저장되어 있다.
<br>
<br>
스트림을 읽으려면 먼저 어떤 스트림이 streams 배열의 어디에 들어 있는지 첨자를 찾아야 한다.
<br>
통상 0번이 비디오, 1번이 오디오지만 정해진 것은 없다.
<br>
<br>
streams 배열을 순회하며 codecpar->code_type 멤버를 읽어 보면 오디오 스트림인지, 비디오 스트림인지 알 수 있다.
<br>
<br>
스트림에는 여러 가지 복잡한 정보가 들어 있으며 이 정보를 읽어 재생한다.
<br>
단순히 스트림의 정보를 조사하려면 다음 함수를 사용하면 된다.
```
void av_dump_format(AVFormatContext *ic, int index, const char *url, int   is_output)
```
포맷 컨텍스트 핸들과 스트림의 첨자, 파일명을 전달한다.
<br>
마지막 인수는 입력용 스트림이면 0, 출력용 스트림이면 1이다.
<br>
재생할 때는 스트림에서 정보를 읽으므로 입력용이며 인코딩할 때는 출력용이다.
<br>
<br>
아래 예제는 비디오, 오디오 스트림 정보를 출력하는 예제이다.
<br>
[예제 코드](https://github.com/JeHeeYu/FFmpeg-Study/blob/main/Example/streams_info.cpp)
<br>

![image](https://github.com/JeHeeYu/FFmpeg-Study/assets/87363461/3b09f8bb-4b96-404b-b606-2ea453625898)

<br>

포맷 컨텍스트를 연 후 nb_streams까지 루프를 돌며 각 스트림의 타입을 조사한다.
<br>
비디오면 vidx에 첨자를 대입하고, 오디오면 aidx에 첨자를 대입하여 두 스트림을 찾는다.
<br>
통상 비디오 0번, 오디오 1번이다.
<br>
<br>
검색한 스트림에 대해 조사하면 아주 복잡한 정보가 출력되는데 비디오만 조사해도 관련 오디오 정보까지 같이 나온다.
<br>
비디오 길이는 10.18초, mpeg4 코덱으로 압축, 샛ㄱ상 포맷은 yuv420p, 크기는 640x480이다.
<br>
오디오는 mp3 포맷이며 8K 모노이다.
<br>
<br>
한 타입에 대해 여러 개의 스트림이 있는 경우 어떤 스트림이 최적인지 찾아야 한다.
<br>
예를 들어 음성이 한국어와 영어 두 개로 녹음되어 있으면 시청자에 따라 맞는 음성을 골라 줘야 한다.
<br>
<br>
이 작업을 직접 하기 귀찮으면 순회할 필요 없이 다음 함수로 최적 스트림을 찾는다.
```
int av_find_best_stream(AVFormatContext *ic, enum AVMediaType type, int wanted_stream_nb, int related_stream, AVCodec **decoder_ret, int flags)
```
핸들과 스트림 종류, 원하는 스트림 번호, 관련 스트림, 코덱을 돌려 받을 변수 등을 지정한다.
<br>
대부분 -1이나 NULL을 지정하면 된다.
<br>
<br>
비디오 스트림을 먼저 찾고 이 스트림과 관련된 오디오 스트림을 찾는다.

<br>

## 스트림 정보
av_dump_format 함수는 스트림의 일부 주요 정보를 보여 주기만 한다.
<br>
동영상을 재생하려면 이 정보를 읽어 참조해야 한다.
<br>
<br>
스트림의 내부를 확인하기 위해 AVStream 구조체를 이용한다.
<br>
스트림은 AVStream 구조체로 표현되어 있으며 주요 멤버는 다음과 같다.
|멤버|설명|
|:---:|:---|
|int index|핸들에서의 스트림 순서값|
|int64_t nb_frames|프레임 개수|
|AVCodecParameters* codecpar|스트림과 관련된 코덱 파라미터|
|int64_t start_time|첫 프레임의 재생 시작 시간|
|int64_t duration|총 재생 시간|
|AVRational r_frame_rate|최소 프레임레이트 추측치|
|AVRational avg_frame_rate|평균 프레임레이트|
|AVRational display_aspecet_ratio|종횡비로, 모를 경우 0|
|AVRational time_base|스트림에 기록된 타임스탬프 단위|

오디오와 비디오를 구분하지 않고 이 구조체로 모든 정보를 표현한다.
<br>
모든 스트림에 공통적으로 해당되는 멤버도 있고 비디오 전용, 오디오 전용 멤버도 있다.
<br>
<br>
예를 들어 종횡비는 비디오에만 적용되며 오디오에는 적용되지 않는다.
<br>
이후의 구조체도 스트림 타입별로 구분되어 있지 않고 비디오와 오디오의 정보를 같이 가지는 경우가 많다.
<br>
<br>
AVCodecParameters 타입의 codecpar 멤버는 스트림을 압축하고 해제하는 코덱에 대한 정보를 가진다.
<br>
이 구조체에는 스트림에 대한 더 상세한 정보가 저장되어 있다.
|멤버|설명|
|:---:|:---|
|AVMediaType codec_type|스트림의 종류|
|int width, int height|영상의 폭과 높이이며 픽셀 단위로 비디오 스트림에만 해당|
|AVCodecID codec_id|코덱의 종류|
|int format|비디오는 AVPixelFormat 타입의 색상 포맷, 오디오는 AVSampleFormat 타입의 샘플 포맷|
|int channels|오디오 채널의 개수로 1이면 모노, 2면 스테레오|
|int sample_rate|오디오의 샘플 레이트|
<br>
아래 예제는 스트림의 주요 정보를 확인하는 예제이다.
<br>

[예제 코드](https://github.com/JeHeeYu/FFmpeg-Study/blob/main/Example/streams_info2.cpp)

<br>

![image](https://github.com/JeHeeYu/FFmpeg-Study/assets/87363461/aa36d7ce-06b8-4535-a54c-7c48f58648c0)

<br>

## 코덱 정보 조사
동영상의 스트림은 고도의 알고리즘으로 압축되어 있다.
<br>
사진이나 음성을 압축하는 장치를 인코더(Encoder), 푸는 장치를 디코더(Decoder)라고 하며 둘을 합쳐 코덱(CoDec)이라고 한다.
<br>
<br>
FFmpeg은 거의 모든 코덱을 내장하고 있다.
<br>
스트림의 정보를 읽으려면 코덱부터 구하고 생성해야 하낟.
<br>
<br>
스트림과 코덱 파라미터는 포맷 컨텍스트에서 이미 구현되어 있으며 이 안에 어떤 코덱을 사용한다는 ID가 내장되어 있다.
<br>
다음 함수로 코덱을 찾는다.
```
AVCodec* avcodec_find_decoder(enum AVCodecID id)
```
매개변수로 코덱의 ID를 주면 코덱을 찾는다.
<br>
이 ID는 stream의 codecpar의 codec_id에 저장되어 있다.
<br>
<br>
예제 파일인 fire.avi의 비디오 코덱은 12번인 AV_CODEC_ID_MPEG4로 압축되어 있으며 오디오 코덱은 0번인 MP3를 사용한다.
<br>
<br>
AVCodec 구조체는 코덱 정보를 가지며 주요 멤버는 다음과 같다.
|멤버|설명|
|:---:|:---|
|const char *name|코덱의 이름 및 식별자이며 고유한 이름을 가져야 함|
|const char *long_name|설명적인 긴 이름으로, 사용자에게 보여줄 때 이 멤버 출력|
|AVMediaType type|코덱의 종류로 비디오인지 오디오인지 구분|
|AVCodecID id|코덱끼리 구분하는 ID|
|int capabilities|코덱의 능력치로 AV_CODEC_CAP_* 플래그의 조합|

이름이나 ID를 통해 자신의 신원을 밝힌다.
<br>
supported_framerates, pix_fmts 멤버는 지원 가능한 비디오 프레임 레이트와 픽셀 포맷의 목록이며 supported_samplerates, sample_fmts는 지원 가능한 오디오 샘플 레이트와 포맷의 목록이다.
<br>
<br>
이 코덱으로 어떤 데이터를 다룰 수 있는지 나타내는데 보통은 모든 포맷을 다 지원한다는 의미로 NULL 값을 가진다.
<br>
<br>
데이터 멤버 외에 함수 포인터도 다수 포함되어 있다.
<br>
init, decode, flush, close 등의 함수 포인터는 코덱 동작 중에 호출할 함수를 가리키며 대부분 FFmpeg 라이브러리의 함수로 연결되어 있다.
<br>
보통 이대로 사용하지만 커스터마이징이 필요하면 호환 함수를 만들어 바꾸어 사용한다.
<br>
그 외에 NULL로 초기화된 함수 포인터가 많이 있는데 코드의 흐름을 변경할 수 있는 수단이다.
<br>
<br>
코덱의 내부는 복잡하나, 직접 코덱의 동작에 관여하거나 커스터마이징할 필요는 거의 없다.
<br>
코덱 포인터를 받아 두었다가 관련 함수로 전달하여 쓰기만 하면 된다.
<br>
<br>
코덱은 동작 중 수많은 함수를 호출하는데 대용량의 메모리를 사용한다.
<br>
이런 작업을 하려면 중간 작업 결과를 저장할 곳이 필요한데, 이를 코덱 컨텍스트라고 한다.
<br>
다음 함수는 압축 해제 중 사용할 컨텍스트를 할당하고 초기화한다.
```
AVCodecContext* avcodec_alloc_context3(const AVCodec *codec)
```
AVCodecContext 구조체는 코덱이 작업 결과를 저장하는 구조체이다.
<br>
예를 들어 어디까지 압축을 풀어 놨고 다음 압축 풀 위치는 어디라는 정보를 저장한다.
<br>
<br>
컨텍스트는 작업 공간일 뿐이며 코덱에 맞게 초기화한다.
<br>
다음 함수는 코덱 파라미터의 정보를 코덱 컨텍스트로 복사한다.
<br>
동영상 파일 자체에 코덱의 동작을 제어하는 여러 가지 옵션 정보가 지정되어 있는데 이 값을 코덱 컨텍스트에 채워 넣어 사용할 준비를 하는 과정이다.
```
int avcodec_parameters_to_context(AVCodecContext *codec, const AVCodecParameters *par)
```
동영상 파일에 있는 정보가 컨텍스트에 복사되고 없는 정보는 코덱의 원래 정보에 유지된다.
<br>
간단한 코덱은 별도의 옵션이 없지만 고성능 코덱은 동작에 필요한 필수 옵션이 있다.
<br>
이 정보를 복사하지 않으면 코덱이 제대로 동작하지 않아 일부 파일이 열리지 않는다.
<br>
<br>
다음 함수는 코덱을 열어 사용할 준비를 하고 컨텍스트도 코덱에 맞게 초기화한다.
```
int avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **opionts)
```
세 번째 인수는 코덱으로 전달할 옵션값이며 필요 없을 경우 NULL로 지정한다.
<br>
여기까지 진행하면 코덱과 컨텍스트가 모두 완비되어 패킷의 압축을 풀어 프레임 정보를 만들 준비가 끝난다.
<br>
<br>
그 후 코덱을 다 사용하면 다음 함수로 컨텍스트와 관련 메모리를 모두 해제한다.
```
void avcodec_free_context(AVCodecContext **avctx)
```
코덱을 찾고 컨텍스트를 할당하여 초기화하는 과정이 복잡하다.
<br>
그러나 선택의 여지없이 일관되어 그대로 절차를 밟기만 하면 된다.
<br>
<br>
비디오와 오디오 모두 코덱 관련 변수의 타입과 코덱을 여는 과정은 같다.
