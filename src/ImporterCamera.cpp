#include "ImporterCamera.hpp"
#include "Camera.hpp"
#include <fstream>

ImporterCamera::ImporterCamera ( Camera& camera ) :_camera ( camera )
{
        return;
}
ImporterCamera::~ImporterCamera ( void )
{
        return;
}

bool
ImporterCamera::read ( const std::string& filename )
{
        std::ifstream fin;

        fin.open ( filename.c_str() );
        if ( !fin.is_open() ) {
                return false;
        }
        float d, w,x,y,z;
        fin>>x>>y>>z;
        Eigen::Vector3f c ( x,y,z );
        fin>>d;
        float distance = d;
        fin>>d;
        float fov = d;
        fin>>w>>x>>y>>z;
        Eigen::Quaternionf q ( w,x,y,z );

        this->_camera = Camera ( c, distance, fov );
        this->_camera.setRotation ( q );
        return true;
};
