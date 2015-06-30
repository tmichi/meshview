#include "View.hpp"
#include "Model.hpp"
#include <qgl.h>
#if defined(__APPLE__)
# include <OpenGL/glu.h>
#else
# include <GL/glu.h>
#endif

View::View ( Model& model ) : _model ( model )
{
        return;
}

View::~View ( void )
{
        return;
}

void
View::init ( void )
{
        ::glEnable( GL_CULL_FACE );
        ::glEnable ( GL_DEPTH_TEST );
        ::glEnable ( GL_LIGHT0 );
        ::glShadeModel ( GL_FLAT );
        const Color3f bg = this->_model.getPreference().getBackgroundColor();
        ::glClearColor ( bg.x(), bg.y(), bg.z(), 1 );
        return;
}
void
View::render ( void )
{
        ::glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        ::glLoadIdentity();

        // model view.
        const Camera& camera = this->_model.getCamera();
        Eigen::Vector3f eye = camera.getEye();
        Eigen::Vector3f center = camera.getCenter();
        Eigen::Vector3f up = camera.getUpVector();
        ::gluLookAt ( eye.x(), eye.y(), eye.z(),
                      center.x(), center.y(), center.z(),
                      up.x(), up.y(), up.z() );

        //light
        Light light = this->_model.getLight();
        this->setLight ( light );


        //draw mesh

        RenderingMode mode = this->_model.getPreference().getRenderingMode() ;
        if ( mode == WIRE ) {
                ::glDisable ( GL_LIGHTING );
                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
                const Color3f fg = this->_model.getPreference().getWireColor();
                ::glColor3f ( fg.x(), fg.y(), fg.z() );
        } else if ( mode == SURFACE ) {
                ::glEnable ( GL_LIGHTING );
                const Color3f fg = this->_model.getPreference().getSurfaceColor();

                ::glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
                GLfloat mat_ambient[4] = {fg.x(), fg.y(), fg.z(), 1.0};
                GLfloat mat_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                GLfloat mat_specular[4] = {0.2, 0.2, 0.2, 1.0};
                GLfloat mat_shininess[1] = {100.0f};

                ::glMaterialfv ( GL_FRONT, GL_AMBIENT,  mat_ambient );
                ::glMaterialfv ( GL_FRONT, GL_DIFFUSE,  mat_diffuse );
                ::glMaterialfv ( GL_FRONT, GL_SPECULAR, mat_specular );
                ::glMaterialfv ( GL_FRONT, GL_SHININESS,mat_shininess );

                GLfloat mat2_ambient[4] = {1-fg.x(), 1-fg.y(), 1-fg.z(), 1.0};
                GLfloat mat2_diffuse[4] = {0.8,0.8, 0.8, 1.0};
                GLfloat mat2_specular[4] = {0.2, 0.2, 0.2, 1.0};
                GLfloat mat2_shininess[1] = {100.0f};
                ::glMaterialfv ( GL_BACK, GL_AMBIENT,  mat2_ambient );
                ::glMaterialfv ( GL_BACK, GL_DIFFUSE,  mat2_diffuse );
                ::glMaterialfv ( GL_BACK, GL_SPECULAR, mat2_specular );
                ::glMaterialfv ( GL_BACK, GL_SHININESS,mat2_shininess );

        }
        this->render_mesh();
        return;
}
void
View::resize ( const int width, const int height )
{
        ::glViewport ( 0, 0, width, height );
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();

        const double zNear = 0.001;
        const double zFar  = 100000.0;
        const double fov = this->_model.getCamera().getFieldOfViewAngle();
        // Camera
        ::glMatrixMode ( GL_PROJECTION );
        ::glLoadIdentity();
        int viewport[4];
        ::glGetIntegerv ( GL_VIEWPORT, viewport );
        ::gluPerspective ( fov, viewport[2] * 1.0 / viewport[3],  zNear, zFar );
        ::glMatrixMode ( GL_MODELVIEW );
        return;
}

void
View::render_mesh ( void )
{
        const Mesh& mesh = this->_model.getMesh();
        ::glBegin ( GL_TRIANGLES );
        for ( int i = 0 ; i < mesh.getNumFaces() ; i++ ) {

                const Eigen::Vector3f nrm = mesh.getNormal ( i );
                ::glNormal3f ( nrm.x(),nrm.y(),nrm.z() );
                for ( int j = 0 ; j < 3 ; j+=1 ) {
                        const Eigen::Vector3f p = mesh.getPosition ( i,j );
                        ::glVertex3f ( p.x(), p.y(), p.z() );
                }
        }
        ::glEnd();
        return;
}


void
View::setLight ( const Light& light )
{

        Color3f amb = light.getAmbient();
        Color3f dif = light.getDiffuse();
        Color3f spe = light.getSpecular();
        Eigen::Vector3f eye = light.getPosition();
        GLfloat light_ambient[4] = {amb.x(), amb.y(), amb.z(), 1.0f};
        GLfloat light_diffuse[4] = {dif.x(), dif.y(), dif.z(), 1.0f};
        GLfloat light_specular[4] = {spe.x(), spe.y(), spe.z(), 1.0f};
        GLfloat light_position[4] = {eye.x(), eye.y(), eye.z(), 1.0f};
        ::glLightfv ( GL_LIGHT0, GL_AMBIENT, light_ambient );
        ::glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
        ::glLightfv ( GL_LIGHT0, GL_SPECULAR, light_specular );
        ::glLightfv ( GL_LIGHT0, GL_POSITION, light_position );
        return;
}
