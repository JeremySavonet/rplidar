// Copyright (c) 2017 All Rights Reserved WestBot

#ifndef WESTBOT_RPLIDAR_RPLIDARPRIVATE_HPP_
#define WESTBOT_RPLIDAR_RPLIDARPRIVATE_HPP_

#include <QString>

#include <3rdparty/rplidar_sdk/include/rplidar.h>

#include "../RPLidar.hpp"

namespace WestBot {
namespace RPLidar {

class RPLidarPrivate
{
public:
    RPLidarPrivate(
        const QString port = QString(),
        uint32_t baudrate = 115200 );
    ~RPLidarPrivate();

    bool connect();
    void disconnect();

    bool isConnected();

    bool reset( uint32_t timeout );

    bool setMotorPwm( uint16_t pwm );
    bool startMotor();
    bool stopMotor();
    bool checkMotorCtrlSupport( uint32_t timeout );

    bool startScan( bool force = false, bool autoExpressMode = true );
    bool startScanNormal( bool force, uint32_t timeout );
    bool startScanExpress( bool fixedAngle, uint32_t timeout );
    bool stopScan( uint32_t timeout );
    bool checkExpressScanSupported( uint32_t timeout );

    bool checkHealth( uint32_t timeout );
    QString getDeviceInfo( uint32_t timeout );
    QString getSampleDurationUs( uint32_t timeout );

    bool getFrequency(
        bool inExpressMode,
        size_t count,
        float& frequency,
        bool& is4kmode );

    bool grabScanData(
        measurementNode_t* nodeBuffer,
        size_t & count,
        uint32_t timeout );

    bool ascendScanData(
        measurementNode_t* nodeBuffer,
        size_t count );

private:
    QString _port;
    uint32_t _baudrate;
    rp::standalone::rplidar::RPlidarDriver* _lidarDriver;
};

}
}

#endif // WESTBOT_RPLIDAR_RPLIDARPRIVATE_HPP_
