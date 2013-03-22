#ifndef __MESH_HPP__
#define __MESH_HPP__ 1

#include <deque>
#include <Eigen/Dense>
#include <Eigen/Geometry>

class Mesh
{
private:
        std::deque<Eigen::Vector3f> _vertex;
        std::deque<Eigen::Vector3f> _normal;
public:
        Mesh ( void ) ;
        virtual ~Mesh ( void ) ;
        bool read ( const std::deque<Eigen::Vector3f>& v );
        void clear ( void );
        Eigen::Vector3f getPosition ( const int fid, const int vid ) const ;
        Eigen::Vector3f getNormal ( const int fid ) const;
        int getNumFaces ( void ) const;
        void getBoundingBox ( Eigen::Vector3f& bmin, Eigen::Vector3f& bmax );
};
#endif //  __MESH_HPP__
