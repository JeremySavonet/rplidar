// Copyright (c) 2017 All Rights Reserved WestBot

#ifndef WESTBOT_RPLIDAR_RPLIDAR_HPP_
#define WESTBOT_RPLIDAR_RPLIDAR_HPP_

#include <memory>

#include <QString>

#include "Export.hpp"

namespace
{
    const uint32_t DEFAULT_TIMEOUT =  2000;
}

namespace WestBot {
namespace RPLidar {

class RPLidarPrivate;

class WESTBOT_RPLIDAR_EXPORT RPLidar
{
public:
    RPLidar( const QString port = QString(), uint32_t baudrate = 115200 );

    bool connect();
    void disconnect();

    bool isConnected();

    bool reset( uint32_t timeout = DEFAULT_TIMEOUT );

    bool setMotorPwm( uint16_t pwm );
    bool startMotor();
    bool stopMotor();
    bool checkMotorCtrlSupport( uint32_t timeout = DEFAULT_TIMEOUT );

    bool startScan( bool force = false, bool autoExpressMode = true );
    bool startScanNormal( bool force, uint32_t timeout = DEFAULT_TIMEOUT );
    bool startScanExpress(
        bool fixedAngle,
        uint32_t timeout = DEFAULT_TIMEOUT );
    bool stopScan( uint32_t timeout = DEFAULT_TIMEOUT );
    bool checkExpressScanSupported( uint32_t timeout = DEFAULT_TIMEOUT );

    bool checkHealth( uint32_t timeout = DEFAULT_TIMEOUT );
    QString getDeviceInfo( uint32_t timeout = DEFAULT_TIMEOUT );
    QString getSampleDurationUs( uint32_t timeout = DEFAULT_TIMEOUT );

    bool getFrequency(
        bool inExpressMode,
        size_t count,
        float& frequency,
        bool& is4kmode );

private:
    std::unique_ptr< RPLidarPrivate > _d;
};

}
}

#endif // WESTBOT_RPLIDAR_RPLIDAR_HPP_
