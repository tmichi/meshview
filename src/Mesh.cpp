#include "Mesh.hpp"

Mesh::Mesh ( void )
{
        return;
}

Mesh::~Mesh ( void )
{
        this->clear();
        return;
}
bool
Mesh::read ( const std::deque<Eigen::Vector3f>& v )
{
        if ( v.size() % 3 != 0 ) {
                return false; // 頂点数が不正
        }
        this->clear();
        this->_vertex.insert ( this->_vertex.end(), v.begin(), v.end() );

        const int numFaces = this->getNumFaces();
        for ( int i = 0 ; i < numFaces ; i+=1 ) {
                const Eigen::Vector3f v1 = this->getPosition ( i, 1 ) - this->getPosition ( i, 0 ) ;
                const Eigen::Vector3f v2 = this->getPosition ( i, 2 ) - this->getPosition ( i, 0 ) ;
                this->_normal.push_back ( v1.cross ( v2 ).normalized() );
        }
        return true;
}
void
Mesh::clear ( void )
{
        this->_vertex.clear();
        this->_normal.clear();
        return;
}
Eigen::Vector3f
Mesh::getPosition ( const int fid, const int vid ) const
{
        return this->_vertex.at ( fid * 3 + vid );
}
Eigen::Vector3f
Mesh::getNormal ( const int fid ) const
{
        return this->_normal.at ( fid );
};
int
Mesh::getNumFaces ( void ) const
{
        return this->_vertex.size() / 3;
}
void
Mesh::getBoundingBox ( Eigen::Vector3f& bmin, Eigen::Vector3f& bmax )
{
        bmin = this->getPosition ( 0, 0 );
        bmax = bmin;

        const int numFaces = this->getNumFaces();
        for ( int i = 0 ; i < numFaces ; i+=1 ) {
                for ( int j = 0 ; j < 3 ; j+=1 ) {
                        const Eigen::Vector3f& p = this->getPosition ( i,j );
                        if ( bmin.x() > p.x() ) bmin.x()  = p.x();
                        if ( bmax.x() < p.x() ) bmax.x()  = p.x();
                        if ( bmin.y() > p.y() ) bmin.y()  = p.y();
                        if ( bmax.y() < p.y() ) bmax.y()  = p.y();
                        if ( bmin.z() > p.z() ) bmin.z()  = p.z();
                        if ( bmax.z() < p.z() ) bmax.z()  = p.z();
                }
        }
        return;
}

