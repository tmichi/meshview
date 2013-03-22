#ifndef __EXPORTER_MESH_HPP__
#define __EXPORTER_MESH_HPP__ 1
#include <string>
#include <Eigen/Dense>
#include "Mesh.hpp"
class ExporterMesh
{
private:
        const Mesh& _mesh;
public:
        ExporterMesh ( const Mesh& mesh );
        virtual ~ExporterMesh ( void );
        bool write ( const std::string& filename );
private:
        bool write_vec ( const Eigen::Vector3f& vec, std::ofstream& fout );
};
#endif // __ExPORTER_MESH_HPP__
