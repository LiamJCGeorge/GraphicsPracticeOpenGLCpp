#pragma once
#include "Mesh.h"

#include <glm/glm.hpp>
#include <vector>

namespace Engine {
	class PrimitiveData {
	public:
		Mesh* square = nullptr;
		Mesh* cube = nullptr;
		//Mesh* tetrahedron = NULL;
		//Mesh* something = NULL;
		//Mesh* hourglass = NULL;

		void init() {
			//square
			std::vector<VertexMesh> squareVerts = {};
			squareVerts.emplace_back(glm::vec3(0.5f, 0.5f, 0), 1, 1);
			squareVerts.emplace_back(glm::vec3(0.5f, -0.5f, 0), 1, 0);
			squareVerts.emplace_back(glm::vec3(-0.5f, -0.5f, 0), 0, 0);
			squareVerts.emplace_back(glm::vec3(-0.5f, 0.5f, 0), 0, 1);

			std::vector<GLuint> squareEle = { 0, 1, 3, 1, 2, 3 };
			square = new Mesh(squareVerts, squareEle, "resources/textures/container.jpg");


			//cube
			std::vector<VertexMesh> cubeVerts = {};
			cubeVerts.reserve(24);
			{//top
				//near left
				glm::vec3 nl = glm::vec3(-0.5, 0.5, -0.5);
				cubeVerts.emplace_back(nl, 0, 0); //0
				cubeVerts.emplace_back(nl, 1, 1); //1
				cubeVerts.emplace_back(nl, 0, 1); //2
				//near right
				glm::vec3 nr = glm::vec3(0.5, 0.5, -0.5);
				cubeVerts.emplace_back(nr, 1, 0); //3
				cubeVerts.emplace_back(nr, 1, 1); //4
				cubeVerts.emplace_back(nr, 0, 1); //5
				// far right
				glm::vec3 fr = glm::vec3(0.5, 0.5, 0.5);
				cubeVerts.emplace_back(fr, 1, 1); //6
				cubeVerts.emplace_back(fr, 1, 1); //7
				cubeVerts.emplace_back(fr, 0, 1); //8
				// far left
				glm::vec3 fl = glm::vec3(-0.5, 0.5, 0.5);
				cubeVerts.emplace_back(fl, 0, 1); //9
				cubeVerts.emplace_back(fl, 1, 1); //10
				cubeVerts.emplace_back(fl, 0, 1); //11
			}
			{//bottom
				//near left
				glm::vec3 nl = glm::vec3(-0.5, -0.5, -0.5);
				cubeVerts.emplace_back(nl, 0, 1); //12
				cubeVerts.emplace_back(nl, 0, 0); //13
				cubeVerts.emplace_back(nl, 1, 0); //14
				//near right
				glm::vec3 nr = glm::vec3(0.5, -0.5, -0.5);
				cubeVerts.emplace_back(nr, 1, 1); //15
				cubeVerts.emplace_back(nr, 0, 0); //16
				cubeVerts.emplace_back(nr, 1, 0); //17
				// far right
				glm::vec3 fr = glm::vec3(0.5, -0.5, 0.5);
				cubeVerts.emplace_back(fr, 1, 0); //18
				cubeVerts.emplace_back(fr, 0, 0); //19
				cubeVerts.emplace_back(fr, 1, 0); //20
				// far left
				glm::vec3 fl = glm::vec3(-0.5, -0.5, 0.5);
				cubeVerts.emplace_back(fl, 0, 0); //21
				cubeVerts.emplace_back(fl, 0, 0); //22
				cubeVerts.emplace_back(fl, 1, 0); //23
			}

			std::vector<GLuint> cubeEle = { 3,6,9, 9,0,3, 15,18,21, 21,12,15, 17,4,2, 2,13,17, 23,10,8, 8,19,23, 20,7,5, 5,16,20, 14,1,11, 11,21,14 };
			cube = new Mesh(cubeVerts, cubeEle, "resources/textures/container.jpg");

			//testcube
			//Vertex testCube[24];
			//testCube[0].setPos(-0.5, 0.5, -0.5).setColor(100, 100, 100).setUV(0,0);


			/*
			//tetrahedron
			vector<Vertex> tetraVerts =  { { glm::vec3( 0.0f,     0.69282f, 0)    },//0 top
										   { glm::vec3( 0.0f,     0.0f,     0.4f) }, //1 forward center
										   { glm::vec3( 0.34641f, 0.0f,    -0.2)  },//2  right
										   { glm::vec3(-0.34641f, 0.0f,    -0.2)  } };//3 left
			vector<GLuint> tetraEle = { 0, 1, 2, 0, 2, 3, 0, 1, 3, 1, 2, 3};
			tetrahedron = new Mesh(tetraVerts, tetraEle);

			//something
			vector<Vertex> somethingVerts = { { glm::vec3( 0.5f, -0.5f, -0.5f) },//0
											  { glm::vec3( 0.5f, -0.5f,  0.5f) },//1
											  { glm::vec3( -0.5f, -0.5f,  0.5f) },//2
											  { glm::vec3(-0.5f, -0.5f,  -0.5f) },//3

											  { glm::vec3(0.75f, 0.0f,  -0.75f) },
											  { glm::vec3(0.75f, 0.0f,  0.75f) },
											  { glm::vec3(-0.75f, 0.0f,  0.75f) },
											  { glm::vec3(-0.75f, 0.0f,  -0.75f) },

											  { glm::vec3(0.5f, 0.5f,  -0.5f) },
											  { glm::vec3(0.5f, 0.5f,  0.5f) },
											  { glm::vec3(-0.5f, 0.5f,  0.5f) },
											  { glm::vec3(-0.5f, 0.5f,  -0.5f) },};
			vector<GLuint> somethingEle = { 0,1,2,  0,2,3,  8,10,9,  8,11,10,
				0,4,5,  0,1,5,  1,5,6,  1,6,2,  2,6,7,  2,7,3,  3,7,4,  3,4,0,
				8,9,4,  8,5,4,  9,10,5,  9,5,6,  10,11,6,  10,6,7,  11,8,7,  11,7,4 };
			something = new Mesh(somethingVerts, somethingEle);

			//hourglass
			vector<Vertex> hourglassVerts = {
				{ glm::vec3(0.5f, -0.5f, 0.5f) },
				{ glm::vec3(0.5f, -0.5f,  -0.5f) },
				{ glm::vec3(-0.5f, -0.5f,  -0.5f) },
				{ glm::vec3(-0.5f, -0.5f,  0.5f) },
				{ glm::vec3(0.0f, 0.0f,  0.0f) },
				{ glm::vec3(0.5f, 0.5f,  0.5f) },
				{ glm::vec3(0.5f, 0.5f,  -0.5f) },
				{ glm::vec3(-0.5f, 0.5f,  -0.5f) },
				{ glm::vec3(-0.5f, 0.5f,  0.5f) }, };
			vector<GLuint> hourglassEle = { 0,1,4,	1,2,4,	2,3,4,	3,0,4,	0,2,1, 0,3,2,
				5,4,6,	6,4,7,	7,4,8,	8,4,5,	5,6,7,	5,7,8 };
			hourglass = new Mesh(hourglassVerts, hourglassEle);

		*/
		}

	};
}