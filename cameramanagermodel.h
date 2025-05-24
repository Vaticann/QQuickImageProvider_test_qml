#ifndef CAMERAMANAGERMODEL_H
#define CAMERAMANAGERMODEL_H

#include <mutex>
#include <QObject>
#include <QTimer>
#include <QDebug>


// 复刻webengine添加的
#include <QImage>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>

/////// 新model必有

class CameraManagerModel: public QObject  //, public KeyboardCaller   // 热床需要键盘
{
    Q_OBJECT // 宏 必须单独放在类定义的最前面，宏会生成元对象代码（如信号、槽、属性等），
             // 这些代码需要在类定义的最前面插入，不能和其他成员混在一起。
public:
    static CameraManagerModel &instance()    // 全局单例模式要有这个static
    {
        static CameraManagerModel _instance;
        return _instance;
    }
////////


public:
    // QML可读属性，让它知道这个变量代表 当前帧图片
    Q_PROPERTY(QImage currentFrame READ currentFrame NOTIFY frameReady)

    // 显式构造函数，在类构造时，创建一个指向父对象的指针。父对象销毁时自动销毁所有子对象，包括这里
    CameraManagerModel(); 
    // explicit CameraManagerModel();
    ~CameraManagerModel(); // 声明析构函数，在类销毁时自动调用，释放资源

    // 获取当前帧
    QImage currentFrame() const;  //const 保证 currentFrame() 只是读取数据，不会修改对象内容，是安全和规范的做法。

    // QML可调用，开始拉流
    Q_INVOKABLE void startStream(const QUrl &url);
    // QML可调用，停止拉流
    Q_INVOKABLE void stopStream();

signals:
    // 通知QML，当前帧图片准备好了
    void frameReady();

private slots:
    void onReadyRead(); // 网络请求数据准备好时调用
    void onFinished(); // 网络请求结束时调用

private:
    QNetworkReply *m_reply=nullptr; // 网络请求对象
    QByteArray m_buffer; // 网络请求数据
    QImage m_currentFrame; // 当前帧图片
    bool m_isStreaming = false; // 拉流状态

    QTimer m_timer; // 定时器，用于定时获取帧
    bool m_isFirstFrame = true; // 是否是第一帧
    QUrl m_streamUrl; // 拉流地址
};

#define CAMERA_MANAGER_MODEL CameraManagerModel::instance()

#endif // CAMERAMANAGERMODEL_H
