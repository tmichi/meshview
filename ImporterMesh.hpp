#ifndef __IMPORTER_MESH_HPP__
#define __IMPORTER_MESH_HPP__ 1
#include <string>
#include <Eigen/Dense>
class Mesh;

class ImporterMesh
{
private:
        Mesh& _mesh;
public:
        ImporterMesh ( Mesh& mesh );
        virtual ~ImporterMesh ( void );

        bool read ( const std::string& filename );
};
#endif // __IMPORTER_MESH_HPP__
