#include "helper/scene.h"
#include "helper/glslprogram.h"
#include "helper/objmesh.h"
#include "helper/skybox.h"
#include "helper/texture.h"
#include "helper/torus.h"
#include "helper/teapot.h"
#include "helper/sphere.h"
#include <glm/glm.hpp>

class Scene_DiffuseImage : public Scene
{
private:
	GLSLProgram prog, sbProg;
	GLuint diffuseCube, colourTex, cube;

	std::unique_ptr<ObjMesh> mesh;
	SkyBox skybox;

	Torus torus;
	Teapot teapot;
	Sphere sphere;

	float angle, camAngle, tPrev, rotSpeed;
	glm::vec3 camPos;

	void setMatrices(GLSLProgram &);
	void compile();

public:
	Scene_DiffuseImage();

	void initScene();
	void update(float t);
	void render();
	void resize(int, int);
};

