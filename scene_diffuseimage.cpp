#include "scene_diffuseimage.h"

#include <iostream>


using std::cerr;
using std::endl;

#include <glm/gtc/matrix_transform.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;


Scene_DiffuseImage::Scene_DiffuseImage(): tPrev(0.0f), camAngle(glm::half_pi<float>()), rotSpeed(0.5f), camPos(0, 4, 7), torus(0.7f * 1.5f, 0.3f * 1.5f, 50, 50), teapot(14, mat4(1.0f)), sphere(2.0f, 50, 50)
{

}

void Scene_DiffuseImage::initScene()
{
	compile();

	//mesh = ObjMesh::load("../COMP301Textures/media/pig_triangulated.obj");
	//mesh = ObjMesh::load("../COMP301Textures/media/bunny.obj");
	//mesh = ObjMesh::load("../COMP301Textures/media/material_sphere.obj");

	glEnable(GL_DEPTH_TEST);

	model = mat4(1.0f);

	diffuseCube = Texture::loadHdrCubeMap("../COMP301Textures/media/texture/cube/pisa-hdr/pisa");
	cube = Texture::loadHdrCubeMap("../COMP301Textures/media/texture/cube/pisa-hdr/pisa");
}

void Scene_DiffuseImage::compile()
{
	try {
		prog.compileShader("shader/diffuse_image.vert");
		prog.compileShader("shader/diffuse_image.frag");
		prog.link();

		sbProg.compileShader("shader/skybox_texture.vert");
		sbProg.compileShader("shader/skybox_texture.frag");
		sbProg.link();
	}
	catch (GLSLProgramException& e)
	{
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Scene_DiffuseImage::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Skybox
	// First cube for the skybox
	model = mat4(1.0f);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube);
	sbProg.use();
	setMatrices(sbProg);
	skybox.render();

	// Model light configuration
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, diffuseCube);


	prog.use();
	prog.setUniform("CamPos", camPos);
	prog.setUniform("Material.Colour", vec3(0.2f, 0.7f, 0.8f));

	model = mat4(1.0f);
	model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	setMatrices(prog);
	sphere.render();

	/*prog.use();
	prog.setUniform("CamPos", camPos);
	prog.setUniform("Material.Colour", vec3(0.7f, 0.6f, 0.2f));

	model = mat4(1.0f);
	model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	setMatrices(prog);
	mesh->render();*/
}

void Scene_DiffuseImage::update(float t)
{
	// Object rotation
	float deltaT = t - tPrev;
	if (tPrev == 0.0f)
		deltaT = 0.0f;

	tPrev = t;

	// Rotating camera 
	if (animating()) {
		camAngle = glm::mod(camAngle + deltaT * rotSpeed, glm::two_pi<float>());
		camPos.x = glm::cos(camAngle) * 5.0f;
		camPos.y = 0.0f;
		camPos.z = glm::sin(camAngle) * 5.0f;
	}
	view = glm::lookAt(
		camPos,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

void Scene_DiffuseImage::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	projection = glm::perspective(glm::radians(50.0f), (float)w / h, 0.3f, 100.0f);
}



void Scene_DiffuseImage::setMatrices(GLSLProgram& p)
{
	mat4 mv = view * model;
	p.setUniform("ModelMatrix", model);
	p.setUniform("ModelViewMatrix", mv);
	p.setUniform("NormalMatrix", glm::mat3(mv));
	p.setUniform("MVP", projection * mv);
}

