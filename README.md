moonraker
需要在在moonraker.conf里定义摄像头的配置和url，才能通过ip：/192.168.1.122/webcam/?action=stream读取到摄像头画面，然后可以传输mjpeg流。
至此，在qml可以通过双image定时缓冲法，进行帧数据传输，效果凑合，一卡一卡的。
也可以通过videooutput进行流数据传输，但是延迟居高不下。
webengine可以完美实现这个功能，但是其商用需付费，因此得自行复刻。

实现过程及代码
技术路径
① 已知摄像头传递的画面的ip地址"http://192.168.2.2/webcam/?action=stream"
② [CameraManagerModel] C++后端通过QUrl，QNetworkAccessManager，QNetworkReply拉去流数据，
③ [ImageProvider] 再通过QQuickImageProvider将帧画面实时刷新到qml前端。
刷新数据很快。
