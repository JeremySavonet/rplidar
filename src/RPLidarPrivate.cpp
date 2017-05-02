// Copyright (c) 2017 All Rights Reserved WestBot

#include <QDebug>

#include <WestBot/RPLidar/private/RPLidarPrivate.hpp>

using namespace rp::standalone::rplidar;
using namespace WestBot::RPLidar;

namespace
{
    QString deviceInfoToString( rplidar_response_device_info_t deviceInfo )
    {
        Q_UNUSED( deviceInfo );
        return QString();
    }

    QString rateInfoToString( rplidar_response_sample_rate_t rateInfo )
    {
        Q_UNUSED( rateInfo );
        return QString();
    }
}

RPLidarPrivate::RPLidarPrivate( const QString port, uint32_t baudrate )
    : _port( port )
    , _baudrate( baudrate )
    , _lidarDriver( RPlidarDriver::CreateDriver(
                        RPlidarDriver::DRIVER_TYPE_SERIALPORT ) )
{
}

RPLidarPrivate::~RPLidarPrivate()
{
    disconnect();
    RPlidarDriver::DisposeDriver( _lidarDriver );
}

bool RPLidarPrivate::connect()
{
    if( IS_FAIL( _lidarDriver->connect(
            _port.toStdString().c_str(), _baudrate ) ) )
    {
        qWarning()
            << "Error, cannot bind to the specified serial port:" << _port;
        return false;
    }

    return true;
}

void RPLidarPrivate::disconnect()
{
    _lidarDriver->disconnect();
}

bool RPLidarPrivate::isConnected()
{
    return _lidarDriver->isConnected();
}

bool RPLidarPrivate::reset( uint32_t timeout )
{
    if( IS_FAIL( _lidarDriver->reset( timeout) ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::setMotorPwm( uint16_t pwm )
{
    if( IS_FAIL( _lidarDriver->setMotorPWM( pwm ) ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::startMotor()
{
    if( IS_FAIL( _lidarDriver->startMotor() ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::stopMotor()
{
    if( IS_FAIL( _lidarDriver->stopMotor() ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::checkMotorCtrlSupport( uint32_t timeout )
{
    bool motorCtrlSupport;
    if( IS_FAIL( _lidarDriver->checkMotorCtrlSupport(
            motorCtrlSupport, timeout ) ) )
    {
        qWarning() << "Error, cannot check motor control support.";
        return false;
    }

    return motorCtrlSupport;
}

bool RPLidarPrivate::startScan( bool force , bool autoExpressMode )
{
    if( IS_FAIL( _lidarDriver->startScan( force, autoExpressMode ) ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::startScanNormal( bool force, uint32_t timeout )
{
    if( IS_FAIL( _lidarDriver->startScanNormal( force, timeout ) ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::startScanExpress( bool fixedAngle, uint32_t timeout )
{
    if( IS_FAIL( _lidarDriver->startScanExpress( fixedAngle, timeout ) ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::stopScan( uint32_t timeout )
{
    if( IS_FAIL( _lidarDriver->stop( timeout ) ) )
    {
        return false;
    }

    return true;
}

bool RPLidarPrivate::checkExpressScanSupported( uint32_t timeout )
{
    bool expressScanSupport;
    if( IS_FAIL( _lidarDriver->checkExpressScanSupported(
            expressScanSupport, timeout ) ) )
    {
        qWarning() << "Error, cannot check express scan support.";
        return false;
    }

    return expressScanSupport;
}

bool RPLidarPrivate::checkHealth( uint32_t timeout )
{
    u_result operationResult;
    rplidar_response_device_health_t healthInfo;

    operationResult = _lidarDriver->getHealth( healthInfo, timeout );
    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot retrieve the lidar health code";
        return false;
    }

    qDebug() << "RPLidar health status:" << healthInfo.status;
    if( RPLIDAR_STATUS_ERROR == healthInfo.status )
    {
        qWarning() << "Error, rplidar internal error detected."
                      " Please reboot the device to retry.";
        reset( timeout ); // automatically reboot de device
        return false;
    }

    return true;
}

QString RPLidarPrivate::getDeviceInfo( uint32_t timeout )
{
    u_result operationResult;
    rplidar_response_device_info_t deviceInfo;

    operationResult = _lidarDriver->getDeviceInfo( deviceInfo, timeout );

    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot get device info.";
        return QString();
    }

    return deviceInfoToString( deviceInfo );
}

QString RPLidarPrivate::getSampleDurationUs( uint32_t timeout )
{
    u_result operationResult;
    rplidar_response_sample_rate_t rateInfo;

    operationResult = _lidarDriver->getSampleDuration_uS( rateInfo, timeout );

    if( IS_FAIL( operationResult ) )
    {
        qWarning() << "Error, cannot get rate info.";
        return QString();
    }

    return rateInfoToString( rateInfo );
}

bool RPLidarPrivate::getFrequency(
    bool inExpressMode,
    size_t count,
    float& frequency,
    bool& is4kmode )
{
    if( IS_FAIL( _lidarDriver->getFrequency(
            inExpressMode, count, frequency, is4kmode ) ) )
    {
        return false;
    }

    return true;
}
