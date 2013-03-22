#include "ExporterCamera.hpp"
#include <fstream>

ExporterCamera::ExporterCamera ( const Camera& camera ) :_camera ( camera )
{
        return;
}

ExporterCamera::~ExporterCamera ( void )
{
        return;
}

bool
ExporterCamera::write ( const std::string& filename )
{
        std::ofstream fout;

        fout.open ( filename.c_str() );
        if ( !fout.is_open() ) {
                return false;
        }
        Eigen::Vector3f c = this->_camera.getCenter();
        float d = ( c - this->_camera.getEye() ).norm();
        Eigen::Quaternionf q = this->_camera.getRotation();
        fout<<c.x() <<" "<<c.y() <<" "<<c.z() <<std::endl;
        fout<<d<<std::endl;
        fout<<this->_camera.getFieldOfViewAngle() <<std::endl;
        fout<<q.w() <<" "<<q.x() <<" "<<q.y() <<" "<<q.z() <<std::endl;
        return true;
};
