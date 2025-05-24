#include "cameramanagermodel.h"

// C++文件定义构造函数和析构函数和其他函数

CameraManagerModel::CameraManagerModel(){qDebug() << "CameraManagerModel constructed";}     
CameraManagerModel::~CameraManagerModel(){stopStream();} // 析构函数中调用stopStream()

QImage CameraManagerModel::currentFrame() const
{
    return m_currentFrame;
}

void CameraManagerModel::startStream(const QUrl &url)
{   
    qDebug() << "startStream called, url:" << url;
    if (m_isStreaming) {
        qDebug() << "Already streaming, return.";
        return; // 如果正在拉流，就不再拉流
    }
    m_isStreaming = true;

    // 创建网络管理器
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    // 创建网络请求
    QNetworkRequest request(url);
    // 设置请求头
    m_reply = manager->get(request);

    // 连接信号槽
    connect(m_reply, &QNetworkReply::readyRead, this, &CameraManagerModel::onReadyRead);  // 此处声明onreadyRead()，定义在下方
    connect(m_reply, &QNetworkReply::finished, this, &CameraManagerModel::onFinished); // 此处声明onFinished()，定义在下方

    qDebug() << "Network request sent, waiting for data...";
}

void CameraManagerModel::stopStream()
{
    if (!m_isStreaming) return; // 如果没在拉流，就不停止
    m_isStreaming = false; // 将状态设置为停止拉流
    if (m_reply) {          // 执行停止拉流的动作
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}

void CameraManagerModel::onReadyRead()
{
    // 追加新到的数据
    m_buffer.append(m_reply->readAll());

    // 确认是否有数据到达
    // qDebug() << "onReadyRead called, bytes available:" << m_reply->bytesAvailable();
    // qDebug() << "Buffer size after append:" << m_buffer.size();

    // 查找JPEG帧的起始和结束标志
    while (true) {
        int startPos = m_buffer.indexOf(QByteArray("\xff\xd8")); // JPEG起始
        int end = m_buffer.indexOf(QByteArray("\xff\xd9")); // JPEG结束
        if (startPos == -1 || end == -1) { // 没找到
            break;
        }
        
        // 取出一帧图片
        QByteArray frameData = m_buffer.mid(startPos, end - startPos + 2);
        m_buffer.remove(0, end + 2); // 移除已取出的帧

        // 解码为QImage
        QImage img;
        if (img.loadFromData(frameData, "JPEG")) {
            m_currentFrame = img;
            qDebug() << "Decoded one JPEG frame, size:" << img.size();
            emit frameReady(); // 通知QMl有新帧
        } else{
            qDebug() << "Failed to decode JPEG frame, data size:" << frameData.size();
        }

    }
}

void CameraManagerModel::onFinished()
{
    // 停止拉流
    stopStream();
}









// int CameraManagerModel::getLeftNozzleTemper() const
// {
//     return _leftNozzleTemperObj.curTemp;
// }

// void CameraManagerModel::setLeftNozzleTemper(int temper, int target)
// {
//     _leftNozzleTemperObj.curTemp = temper;
//     _leftNozzleTemperObj.targetTemp = target;
//     emit leftNozzleTemperChanged();
// }

// void CameraManagerModel::editLeftNozzleTemperature()
// {
//     if (!KEYBOARD_MODEL.openNumberKeyboard(this, tr("Target Temperature"), MIN_NOZZLE_TEMPERATURE, MAX_NOZZLE_TEMPERATURE, 
//     _leftNozzleTemperObj.curTemp, true, true)) 
//     {
//         return;
//     }
//     _editingItem = LEFT_NOZZLE_TEMPERATURE;
//     _leftNozzleTemperObj.targetTemp = _leftNozzleTemperObj.curTemp;   
// }

// QVariantMap CameraManagerModel::getTemperature() const
// {
//     QVariantMap map;
//     map["left"] = _leftNozzleTemperObj.curTemp;
//     map["leftTarget"] = _leftNozzleTemperObj.targetTemp;
//     // map["right"] = _rightNozzleTemperObj.curTemp;
//     // map["rightTarget"] = _rightNozzleTemperObj.targetTemp;
//     map["bed"] = _bedTemperObj.curTemp;
//     map["bedTarget"] = _bedTemperObj.targetTemp;
//     // map["chamber"] = _chamberTemperObj.curTemp;
//     // map["chamberTarget"] = _chamberTemperObj.targetTemp;
//     return map;
// }






// int CameraManagerModel::getBedTemper() const
// {
//     return _bedTemperObj.curTemp;
// }

// void CameraManagerModel::setBedTemper(int temper, int target)
// {
//     _bedTemperObj.curTemp = temper;
//     _bedTemperObj.targetTemp = target;
//     emit bedTemperChanged();
// }

// void CameraManagerModel::editBedTemperature()
// {
//     if (!KEYBOARD_MODEL.openNumberKeyboard(this, tr("Target Temperature"), MIN_BED_TEMPERATURE, MAX_BED_TEMPERATURE,
//     _bedTemperObj.curTemp, true, true)) 
//     {
//         return;
//     }
//     _editingItem = BED_TEMPERATURE;
//     _bedTemperObj.targetTemp = _bedTemperObj.curTemp;
// }

// int CameraManagerModel::confirmKeyboardInput(QString value)
// {
//     qDebug() << "==============confirmKeyboardInput" << value;
//     bool ok;
//     int targetTemp = value.toInt(&ok);
//     if (!ok) {
//         return -1;
//     }
//     switch (_editingItem) {
//     case LEFT_NOZZLE_TEMPERATURE:
//         if ((targetTemp < MIN_NOZZLE_TEMPERATURE) || (targetTemp > MAX_NOZZLE_TEMPERATURE)) {
//             return -1;
//         }
//         sigEditTargetLeftNozzleTemper(targetTemp);
//         break;
//     case BED_TEMPERATURE:
//         if ((targetTemp < MIN_BED_TEMPERATURE) || (targetTemp > MAX_BED_TEMPERATURE)) {
//             return -1;
//         }
//         sigEditTargetBedTemper(targetTemp);
//         break;  
//     default:
//         break;
//     }
//     _editingItem = NONE;
//     return 0;
// }






// QVariantMap CameraManagerModel::getFanSpeed() const
// {
//     QVariantMap map;
//     map["left"] = _leftCoolingFanSpeed;
//     // map["right"] = _rightCoolingFanSpeed;
//     // map["chamber"] = _chamberCoolingFanSpeed;
//     // map["heater"] = _heaterFanSpeed;
//     return map;
// }

// void CameraManagerModel::setLeftCoolingFanSpeed(float speed)
// {
//     if (_leftCoolingFanSpeed != speed) {
//         _leftCoolingFanSpeed = speed;
//         emit fanSpeedChanged();
//     }
// }


// void CameraManagerModel::setLeftFanSpeed(float speed)
// {
//     if (speed < 0.0f || speed > 1.0f) {
//         return;
//     }
// }

// void CameraManagerModel::onSensorStatusUpdate(const QJsonObject &rootObj)
// {
//     QJsonObject resultObj = rootObj.value("result").toObject();
//     if (!resultObj.isEmpty())
//     {   
//         QJsonObject statusObj = resultObj.value("status").toObject();
//         if (!statusObj.isEmpty())
//         {

            
//             // Parse extruder object
//             QJsonObject extruderObj = statusObj.value("extruder").toObject();
//             if (!extruderObj.isEmpty()) {
//                 double temperature = extruderObj.value("temperature").toDouble();
//                 double target = extruderObj.value("target").toDouble();
//                 setLeftNozzleTemper(temperature, target);
//                 // 定义了 温度结构体定义，含有两个参数
//                 // 定义了 左喷头的温度结构体
//                 // 定义了 设置左喷头的温度结构体的函数，包括设置参数，发出信号到qml端
//                 // 通过websocket接受moonraker的信号
//                 // 从中将左喷头现在的温度传输到这里
//                 // 调用函数设置左喷头的温度结构体，并且发出信号
//                 // qml端接受信号，修改画面。


//                 qDebug() << "extruder temperature:" << temperature;
//                 qDebug() << "extruder target:" << target;
//             }



//             // Parse heater_bed object
//             QJsonObject heaterBedObj = statusObj.value("heater_bed").toObject();
//             if (!heaterBedObj.isEmpty()) {
//                 double temperature = heaterBedObj.value("temperature").toDouble();
//                 double target = heaterBedObj.value("target").toDouble();
//                 setBedTemper(temperature, target);
//                 qDebug() << "heater_bed temperature:" << temperature;
//                 qDebug() << "heater_bed target:" << target;
//             }



            

//             // Parse fan data
//             QJsonObject fanObj = statusObj.value("fan").toObject();
//             if (!fanObj.isEmpty()) {
//                 double speed = fanObj.value("speed").toDouble();
//                 setLeftCoolingFanSpeed(speed);
//                 qDebug() << "fan speed:" << speed;
//             }


//         }
//     }
// }
