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
