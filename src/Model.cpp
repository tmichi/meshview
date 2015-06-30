#include "Model.hpp"
#include "ImporterMesh.hpp"
#include "ExporterMesh.hpp"
#include "ImporterCamera.hpp"
#include "ExporterCamera.hpp"

Model::Model ( void )
{
        return;
}

Model::~Model ( void )
{
        return;
}

const Mesh&
Model::getMesh ( void )
{
        return this->_mesh;
}

const Light&
Model::getLight ( void )
{
        return this->_light;
}

const Camera&
Model::getCamera ( void )
{
        return this->_camera;
}

const Preference&
Model::getPreference ( void )
{
        return this->_preference;
}

bool
Model::initMesh ( void )
{
        this->_mesh.clear();
        return true;
}

bool
Model::openMesh ( const std::string& filename )
{
        ImporterMesh importer ( this->_mesh );
        if ( !importer.read ( filename ) ) return false;
        this->viewInit();
        return true;
}
bool
Model::saveMesh ( const std::string& filename )
{
        ExporterMesh exporter ( this->_mesh );
        return exporter.write ( filename );
}
bool
Model::openCamera ( const std::string& filename )
{
        ImporterCamera importer ( this->_camera );
        if ( !importer.read ( filename ) ) return false;
        this->_light.setPosition ( this->_camera.getEye() );
        return true;
}
bool
Model::saveCamera ( const std::string& filename )
{
        ExporterCamera exporter ( this->_camera );
        return exporter.write ( filename );
}


void
Model::setRenderingMode ( const RenderingMode mode )
{
        this->_preference.setRenderingMode ( mode );
        return;
}


void
Model::viewFit ( void )
{
        Eigen::Vector3f bmin, bmax;
        this->_mesh.getBoundingBox ( bmin, bmax );
        const Eigen::Vector3f center = this->_camera.getCenter();;
        const float radius = 1.25 * std::min ( ( bmax - center ).norm(), ( bmin - center ).norm() );
        const Eigen::Quaternionf q = this->_camera.getRotation();
        this->_camera.fitPosition ( center, radius, q );
        this->_light.setPosition ( this->_camera.getEye() );
        return;
}
void
Model::viewInit ( void )
{
        Eigen::Vector3f bmin, bmax;
        this->_mesh.getBoundingBox ( bmin, bmax );

        const Eigen::Vector3f center = 0.5 * ( bmin + bmax );
        const float radius = 1.25 * 0.5 * ( bmax - bmin ).norm();
        const Eigen::Quaternionf q ( 1,0,0,0 );
        this->_camera.fitPosition ( center, radius, q );
        this->_light.setPosition ( this->_camera.getEye() );
        return;
}

void
Model::addRotation ( const Eigen::Quaternionf& q )
{
        this->_camera.multiplyRotation ( q );
        this->_light.setPosition ( this->_camera.getEye() );
        return;
}

void
Model::getSurfaceColor ( int &r, int &g, int &b )
{
	const Color3f c = this->getPreference().getSurfaceColor();
	r = static_cast<int> ( 255 * c.x() );
	g = static_cast<int> ( 255 * c.y() );
	b = static_cast<int> ( 255 * c.z() );

}
void
Model::setSurfaceColor ( const int r, const int g, const int b )
{
	Color3f c;
	c.x() = r * 1.0 / 255;
	c.y() = g * 1.0 / 255;
	c.z() = b * 1.0 / 255;
	this->_preference.setSurfaceColor ( c );
}
