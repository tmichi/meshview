#include "Camera.hpp"
Camera::Camera ( const Eigen::Vector3f center, const float distanceToCenter, const float fieldOfViewAngle )
{
        this->setCenter ( center );
        this->setFieldOfViewAngle ( fieldOfViewAngle );
        this->_distanceToCenter = distanceToCenter;
        this->_rotation.setIdentity();
        return;
}

Camera::Camera ( const Camera& that )
{
        this->copy ( that );
        return;
}

Camera&
Camera::operator = ( const Camera& that )
{
        this->copy ( that );
        return *this;
}

Camera::~Camera ( void )
{
        return;
}

void
Camera::fitPosition ( const Eigen::Vector3f& center, const float radius, const Eigen::Quaternionf& q )
{
        this->setCenter ( center );
        const float scale = 0.8f;
        this->_distanceToCenter = static_cast<float> ( radius / scale / std::sin ( this->getFieldOfViewAngle() * 3.1415926 / 180.0 ) );
        this->_rotation = q;
        return;
}
float
Camera::getFieldOfViewAngle ( void ) const
{
        return this->_fieldOfViewAngle;
}
Eigen::Vector3f
Camera::getEye ( void ) const
{
        return Eigen::Matrix3f ( this->_rotation ) * Eigen::Vector3f ( 0,0, -this->_distanceToCenter ) + this->getCenter();
}

Eigen::Vector3f
Camera::getCenter ( void ) const
{
        return this->_center;
}

Eigen::Vector3f
Camera::getUpVector ( void ) const
{
        return Eigen::Matrix3f ( this->_rotation ) * Eigen::Vector3f ( 0,1,0 );
}
Eigen::Quaternionf
Camera::getRotation ( void ) const
{
        return this->_rotation;
}
void
Camera::setFieldOfViewAngle ( const float fov )
{
        if ( 10 <= fov && fov <= 170 ) this->_fieldOfViewAngle = fov;
        return;
}

void
Camera::setCenter ( const Eigen::Vector3f& center )
{
        this->_center = center;
        return;
}

void
Camera::multiplyRotation ( const Eigen::Quaternionf& rotation )
{
        this->_rotation *= rotation;
        return;
}
void
Camera::setRotation ( const Eigen::Quaternionf& rotation )
{
        this->_rotation = rotation;
        return;
}

void
Camera::copy ( const Camera& that )
{
        this->_center = that._center;
        this->_distanceToCenter = that._distanceToCenter;
        this->_fieldOfViewAngle	= that._fieldOfViewAngle;
        this->_rotation = that._rotation;
        return;
}
