// Copyright (c) 2017 All Rights Reserved WestBot

#ifndef WESTBOT_RPLIDAR_RPLIDAR_HPP_
#define WESTBOT_RPLIDAR_RPLIDAR_HPP_

#include <QString>

#include "Export.hpp"

namespace
{
    const uint32_t DEFAULT_TIMEOUT =  2000;
}

namespace WestBot {
namespace RPLidar {

typedef struct WESTBOT_RPLIDAR_EXPORT measurementNode
{
    uint8_t    sync_quality;      // syncbit:1;syncbit_inverse:1;quality:6;
    uint16_t   angle_q6_checkbit; // check_bit:1;angle_q6:15;
    uint16_t   distance_q2;
} __attribute__((packed)) measurementNode_t;

class RPLidarPrivate;

class WESTBOT_RPLIDAR_EXPORT RPLidar
{
public:
    RPLidar( const QString port = QString(), uint32_t baudrate = 115200 );
    ~RPLidar();

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

    bool grabScanData(
        measurementNode_t* nodeBuffer,
        size_t& count,
        uint32_t timeout = DEFAULT_TIMEOUT );

    bool ascendScanData(
        measurementNode_t* nodeBuffer,
        size_t count );

private:
    RPLidarPrivate* _d;
};

}
}

#endif // WESTBOT_RPLIDAR_RPLIDAR_HPP_
