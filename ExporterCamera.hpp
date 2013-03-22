#ifndef __EXPORTER_CAMERA_HPP__
#define __EXPORTER_CAMERA_HPP__ 1
#include <string>
#include <Eigen/Dense>
#include "Camera.hpp"
class ExporterCamera
{
private:
        const Camera& _camera;
public:
        ExporterCamera ( const Camera& camera );
        virtual ~ExporterCamera ( void );
        bool write ( const std::string& filename );
};
#endif // __ExPORTER_CAMERA_HPP__
