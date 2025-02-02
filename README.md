# FFmpegAndroid
android端基于FFmpeg库的使用<br>
添加编译ffmpeg、shine、mp3lame、x264源码的参考脚本<br>
目前音视频相关处理：<br>

- #### 音频剪切
- #### 音频混音
- #### 音频转码
- #### 音视频合成
- #### 音频编码
- #### 视频剪切
- #### 视频转码
- #### 视频截图
- #### 视频降噪
- #### 视频抽帧
- #### 视频转GIF
- #### 视频水印
- #### 视频画面拼接
- #### 视频反序倒播
- #### 视频画中画
- #### 图片合成视频
- #### 本地直播推流
- #### 实时直播推流
- #### 音视频解码播放
- #### 音乐歌词解析
- #### 视频拖动实时预览
- #### FFmpeg的AVFilter滤镜
- #### ffprobe检测多媒体格式
- #### 使用mp3lame库进行mp3转码
- #### IjkPlayer的RTSP超低延时直播

### Usage:
### (1) Transform video format:
Select video file which you want to transform, and setting the output path.<br>
The simple command like this:<br>
ffmpeg -i %s -vcodec copy -acodec copy %s<br>
You could appoint the encoder, like this:<br>
ffmpeg -i %s -vcodec libx264 -acodec libmp3lame %s<br>
You could transform the video resolution, like this:<br>
ffmpeg -i %s -s 1080x720 %s<br>

### (2) Probing media format:
Select video or audio file from your file explorer, and click the button.<br>
When it finishes probing, the result of metadata will display on screen.<br>

### Joining the group to learn FFmpeg(1群已满):
![preview](https://github.com/xufuji456/FFmpegAndroid/blob/master/picture/ffmpeg_group.png)

### Preview thumbnail when seeking:
![preview](https://github.com/xufuji456/FFmpegAndroid/blob/master/gif/preview.gif)

***
<br><br>

