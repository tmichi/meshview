#include "ImporterMesh.hpp"
#include "Mesh.hpp"
#include <fstream>

ImporterMesh::ImporterMesh ( Mesh& mesh ) :_mesh ( mesh )
{
        return;
}
ImporterMesh::~ImporterMesh ( void )
{
        return;
}

bool
ImporterMesh::read ( const std::string& filename )
{
        std::ifstream fin;

        fin.open ( filename.c_str(), std::ios::binary );
        if ( !fin.is_open() ) {
                return false;
        }

        std::deque<Eigen::Vector3f> vec;
        char buf[80];
        fin.read ( ( char* ) &buf, 80 );

        std::string name ( buf );
        if ( name.empty() ) name = std::string ( "mesh" );

        int fsize;
        fin.read ( ( char* ) &fsize, sizeof ( unsigned int ) );

        for ( int i = 0 ; i < fsize ; i+=1 ) {
                if ( fin.bad() ) return false;
                float nx, ny, nz;
                fin.read ( ( char* ) & ( nx ), sizeof ( float ) );
                fin.read ( ( char* ) & ( ny ), sizeof ( float ) );
                fin.read ( ( char* ) & ( nz ), sizeof ( float ) );
                for ( int j = 0 ; j < 3 ; j+=1 ) {
                        float x, y, z;
                        fin.read ( ( char* ) &x, sizeof ( float ) );
                        fin.read ( ( char* ) &y, sizeof ( float ) );
                        fin.read ( ( char* ) &z, sizeof ( float ) );
                        Eigen::Vector3f v ( x,y,z );
                        vec.push_back ( v );
                }
                char buf[2];
                fin.read ( buf, 2 );
        }
        fin.close();

        if ( ! this->_mesh.read ( vec ) ) {
                return false;
        }

        return true;
};
