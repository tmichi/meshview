#ifndef __IMPORTER_CAMERA_HPP__
#define __IMPORTER_CAMERA_HPP__ 1
#include <string>
#include <Eigen/Dense>
class Camera;

class ImporterCamera
{
private:
        Camera& _camera;
public:
        ImporterCamera ( Camera& camera );
        virtual ~ImporterCamera ( void );

        bool read ( const std::string& filename );
};
#endif // __IMPORTER_CAMERA_HPP__
