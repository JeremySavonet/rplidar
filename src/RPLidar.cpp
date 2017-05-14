// Copyright (c) 2017 All Rights Reserved WestBot

#include <WestBot/RPLidar/RPLidar.hpp>

#include <WestBot/RPLidar/private/RPLidarPrivate.hpp>

using namespace WestBot::RPLidar;

RPLidar::RPLidar( const QString port, uint32_t baudrate )
    : _d( new RPLidarPrivate( port, baudrate ) )
{
}

RPLidar::~RPLidar()
{
    delete _d;
}

bool RPLidar::connect()
{
    return _d->connect();
}

void RPLidar::disconnect()
{
    _d->disconnect();
}

bool RPLidar::isConnected()
{
    return _d->isConnected();
}

bool RPLidar::reset( uint32_t timeout )
{
    return _d->reset( timeout );
}

bool RPLidar::setMotorPwm( uint16_t pwm )
{
    return _d->setMotorPwm( pwm );
}

bool RPLidar::startMotor()
{
    return _d->startMotor();
}

bool RPLidar::stopMotor()
{
    return _d->stopMotor();
}

bool RPLidar::checkMotorCtrlSupport( uint32_t timeout )
{
    return _d->checkMotorCtrlSupport( timeout );
}

bool RPLidar::startScan( bool force , bool autoExpressMode )
{
    return _d->startScan( force, autoExpressMode );
}

bool RPLidar::startScanNormal( bool force, uint32_t timeout )
{
    return _d->startScanNormal( force, timeout );
}

bool RPLidar::startScanExpress( bool fixedAngle, uint32_t timeout )
{
    return _d->startScanExpress( fixedAngle, timeout );
}

bool RPLidar::stopScan( uint32_t timeout )
{
    return _d->stopScan( timeout );
}

bool RPLidar::checkExpressScanSupported( uint32_t timeout )
{
    return _d->checkExpressScanSupported( timeout );
}

bool RPLidar::checkHealth( uint32_t timeout )
{
    return _d->checkHealth( timeout );
}

QString RPLidar::getDeviceInfo( uint32_t timeout )
{
    return _d->getDeviceInfo( timeout );
}

QString RPLidar::getSampleDurationUs( uint32_t timeout )
{
    return _d->getSampleDurationUs( timeout );
}

bool RPLidar::getFrequency(
    bool inExpressMode,
    size_t count,
    float& frequency,
    bool& is4kmode )
{
    return _d->getFrequency( inExpressMode, count, frequency, is4kmode );
}

bool RPLidar::grabScanData(
    measurementNode_t* nodeBuffer,
    size_t & count,
    uint32_t timeout )
{
    return _d->grabScanData( nodeBuffer, count, timeout );
}

bool RPLidar::ascendScanData(
    measurementNode_t* nodeBuffer,
    size_t count )
{
    return _d->ascendScanData( nodeBuffer, count );
}

