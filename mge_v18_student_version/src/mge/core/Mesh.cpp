#include <iostream>
#include <map>
#include <string>
#include <fstream>

#include "mge/behaviours/CollisionBehaviour.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameController.hpp"
#include "mge/core/Waypoint.hpp"

#include "mge/config.hpp"

Mesh::Mesh() : _indexBufferId(0), _vertexBufferId(0), _normalBufferId(0), _uvBufferId(0), _vertices(), _normals(), _uvs(), _indices()
{
	//ctor
}

Mesh::~Mesh()
{
	//dtor
}

/**
 * Load reads the obj data into a new mesh using C++ combined with c style coding.
 * The result is an indexed mesh for use with glDrawElements.
 * Expects a obj file with following layout v/vt/vn/f eg
 *
 * For example the obj file for a simple plane describes two triangles, based on
 * four vertices, with 4 uv's all having the same vertex normals (NOT FACE NORMALS!)
 *
 * v 10.000000 0.000000 10.000000              //vertex 1
 * v -10.000000 0.000000 10.000000             //vertex 2
 * v 10.000000 0.000000 -10.000000             //vertex 3
 * v -10.000000 0.000000 -10.000000            //vertex 4
 * vt 0.000000 0.000000                        //uv 1
 * vt 1.000000 0.000000                        //uv 2
 * vt 1.000000 1.000000                        //uv 3
 * vt 0.000000 1.000000                        //uv 4
 * vn 0.000000 1.000000 -0.000000              //normal 1 (normal for each vertex is same)
 * s off
 *
 * Using these vertices, uvs and normals we can construct faces, made up of 3 triplets (vertex, uv, normal)
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * So although this is a good format for blender and other tools reading .obj files, this is
 * not an index mechanism that OpenGL supports out of the box.
 * The reason is that OpenGL supports only one indexbuffer, and the value at a certain point in the indexbuffer, eg 3
 * refers to all three other buffers (v, vt, vn) at once,
 * eg if index[0] = 5, opengl will stream vertexBuffer[5], uvBuffer[5], normalBuffer[5] into the shader.
 *
 * So what we have to do after reading the file with all vertices, is construct unique indexes for
 * all pairs that are described by the faces in the object file, eg if you have
 * f 2/1/1 1/2/1 3/3/1                         //face 1 (triangle 1)
 * f 4/4/1 2/1/1 3/3/1                         //face 2 (triangle 2)
 *
 * v/vt/vn[0] will represent 2/1/1
 * v/vt/vn[1] will represent 1/2/1
 * v/vt/vn[2] will represent 3/3/1
 * v/vt/vn[3] will represent 4/4/1
 *
 * and that are all unique pairs, after which our index buffer can contain:
 *
 * 0,1,2,3,0,2
 *
 * So the basic process is, read ALL data into separate arrays, then use the faces to
 * create unique entries in a new set of arrays and create the indexbuffer to go along with it.
 *
 * Note that loading this mesh isn't cached like we do with texturing, this is an exercise left for the students.
 */
Mesh* Mesh::load(std::string pFileName)
{
	std::cout << "Loading " << pFileName << ".obj...";

	Mesh* mesh = new Mesh();
	mesh->materials = mesh->getMTLinfo(pFileName);
	//mesh->faces = mesh->getOBJinfo(pFileName);
	mesh->filePath = pFileName;

	mesh->materialNamesArray = new std::string[mesh->materials];
	mesh->textureNamesArray = new std::string[mesh->materials];
	//mesh->facesArray = new int*[mesh->faces];
	//int mtl = 0;
	//int f = 0;
	int objectIndex = 0;

	/*for (int i = 0; i < mesh->faces; ++i)
		mesh->facesArray[i] = new int[10];*/
	mesh->extractMTLinfo(pFileName, mesh->materialNamesArray, mesh->textureNamesArray);

	std::ifstream file(pFileName + ".obj", std::ios::in);

	if (file.is_open())
	{
		//these three vectors will contains data as taken from the obj file
		//in the order it is encountered in the object file
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uvs;

		//in addition we create a map to store the triplets found under the f(aces) section in the
		//object file and map them to an index for our index buffer (just number them sequentially
		//as we encounter them and store references to the pack
		std::map <FaceIndexTriplet, unsigned int> mappedTriplets;
		int colliderCount = 0;
		std::string line; // to store each line in
		while (getline(file, line))
		{
			// c-type string to store cmd read from obj file (cmd is v, vt, vn, f)
			char cmd[10];
			cmd[0] = 0;

			//get the first string in the line of max 10 chars (c-style)
			sscanf(line.c_str(), "%10s", cmd);

			//note that although the if statements below seem to imply that we can
			//read these different line types (eg vertex, normal, uv) in any order,
			//this is just convenience coding for us (instead of multiple while loops)
			//we assume the obj file to list ALL v lines first, then ALL vt lines,
			//then ALL vn lines and last but not least ALL f lines last

			//so... start processing lines
			//are we reading a vertex line? straightforward copy into local vertices vector
			std::string type = line.substr(0, 2);
			if (type.compare("us") == 0)
			{
				std::string l = "usemtl ";
				std::string mat = line.substr(l.size());

				for (int i = 0; i < mesh->materials;++i)
				{
					if (mat.compare(mesh->materialNamesArray[i]) == 0)
					{
						//mtl = i;
						mesh->objectTextures.push_back(Texture::load(config::MGE_TEXTURE_PATH + mesh->getMaterialTextureName(pFileName, mat)));
					}
				}
			}

			if (type.compare("g ") == 0)
			{
				std::string obj = line.substr(type.size());
				if (obj.compare("Collider") == 0 || obj.at(0) == 'w')
				{
					std::string l;
					glm::vec3 vOne;
					glm::vec3 vTwo;
					char cArr[10];
					cArr[0] = 0;
					for (int i = 0; i < 85; ++i)
					{
						getline(file, l);
						if (i == 0)
							sscanf(l.c_str(), "%10s %f %f %f", cArr, &vOne.x, &vOne.y, &vOne.z);
						else if (i == 5)
							sscanf(l.c_str(), "%10s %f %f %f", cArr, &vTwo.x, &vTwo.y, &vTwo.z);
					}

					glm::vec3 pos = glm::vec3(vOne.x + vTwo.x, vOne.y + vTwo.y, vOne.z + vTwo.z) * 0.5f;
					GameObject* col;
					if (obj.at(0) == 'w')
					{
						switch (obj.at(1))
						{
							case 'A':
							col = new Waypoint("Waypoint", pos, Waypoint::A, (int)obj.at(2));
							break;

							case 'B':
							col = new Waypoint("Waypoint", pos, Waypoint::B, (int)obj.at(2));
							break;

							case 'C':
							col = new Waypoint("Waypoint", pos, Waypoint::C, (int)obj.at(2));
							break;

							case 'D':
							col = new Waypoint("Waypoint", pos, Waypoint::D, (int)obj.at(2));
							break;

							default:
							col = new Waypoint("Waypoint", pos, Waypoint::D, (int)obj.at(2));
							break;
						}
					}
					else
						col = new GameObject("Collider", pos);

					CollisionBehaviour* objectCollider = new CollisionBehaviour(glm::vec3(glm::max(vOne.x, vTwo.x) - glm::min(vOne.x, vTwo.x),
																						  glm::max(vOne.y, vTwo.y) - glm::min(vOne.y, vTwo.y),
																						  glm::max(vOne.z, vTwo.z) - glm::min(vOne.z, vTwo.z)), true);
					col->addBehaviour(objectCollider);
					if (GameController::DrawColliders)
						objectCollider->DrawCollider();
					mesh->collidersInMesh.push_back(col);
					colliderCount++;
				}
				else
					mesh->objectVertexIndex.push_back(objectIndex);
			}

			if (strcmp(cmd, "v") == 0)
			{
				glm::vec3 vertex;
				sscanf(line.c_str(), "%10s %f %f %f ", cmd, &vertex.x, &vertex.y, &vertex.z);
				vertices.push_back(vertex);

				objectIndex++;
				//or are we reading a normal line? straightforward copy into local normal vector
			}
			else if (strcmp(cmd, "vn") == 0)
			{
				glm::vec3 normal;
				sscanf(line.c_str(), "%10s %f %f %f ", cmd, &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);

				//or are we reading a uv line? straightforward copy into local uv vector
			}
			else if (strcmp(cmd, "vt") == 0)
			{
				glm::vec2 uv;
				sscanf(line.c_str(), "%10s %f %f ", cmd, &uv.x, &uv.y);
				uvs.push_back(uv);

				//this is where it gets nasty. After having read all vertices, normals and uvs into
				//their own buffer
			}
			else if (strcmp(cmd, "f") == 0)
			{
				//an f lines looks like
				//f 2/1/1 1/2/1 3/3/1
				//in other words
				//f v1/u1/n1 v2/u2/n2 v3/u3/n3
				//for each triplet like that we need to check whether we already encountered it
				//and update our administration based on that
				glm::ivec3 vertexIndex;
				glm::ivec3 normalIndex;
				glm::ivec3 uvIndex;
				int count = sscanf(line.c_str(), "%10s %d/%d/%d %d/%d/%d %d/%d/%d", cmd,
								   &vertexIndex[0], &uvIndex[0], &normalIndex[0],
								   &vertexIndex[1], &uvIndex[1], &normalIndex[1],
								   &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				vertexIndex[0] -= 24 * colliderCount;
				vertexIndex[1] -= 24 * colliderCount;
				vertexIndex[2] -= 24 * colliderCount;
				uvIndex[0] -= 24 * colliderCount;
				uvIndex[1] -= 24 * colliderCount;
				uvIndex[2] -= 24 * colliderCount;
				normalIndex[0] -= 24 * colliderCount;
				normalIndex[1] -= 24 * colliderCount;
				normalIndex[2] -= 24 * colliderCount;

				//Have we read exactly 10 elements?
				if (count == 10)
				{
					//process 3 triplets, one for each vertex (which is first element of the triplet)
					for (int i = 0; i < 3; ++i)
					{
						//create key out of the triplet and check if we already encountered this before
						FaceIndexTriplet triplet(vertexIndex[i], uvIndex[i], normalIndex[i]);
						std::map<FaceIndexTriplet, unsigned int>::iterator found = mappedTriplets.find(triplet);

						//if iterator points at the end, we haven't found it
						if (found == mappedTriplets.end())
						{
							//so create a new index value, and map our triplet to it
							unsigned int index = mappedTriplets.size();
							mappedTriplets[triplet] = index;

							//now record this index
							mesh->_indices.push_back(index);
							//and store the corresponding vertex/normal/uv values into our own buffers
							//note the -1 is required since all values in the f triplets in the .obj file
							//are 1 based, but our vectors are 0 based
							mesh->_vertices.push_back(vertices[vertexIndex[i] - 1]);
							mesh->_normals.push_back(normals[normalIndex[i] - 1]);
							mesh->_uvs.push_back(uvs[uvIndex[i] - 1]);
						}
						else
						{
							//if the key was already present, get the index value for it
							unsigned int index = found->second;
							//and update our index buffer with it
							mesh->_indices.push_back(index);
						}
					}
				}
				else
				{
					//If we read a different amount, something is wrong
					std::cout << "Error reading obj, needing v,vn,vt" << std::endl;
					delete mesh;
					return NULL;
				}
			}

			/*if (type.compare("f ") == 0)
			{
				char* l = new char[line.size() + 1];
				std::memcpy(l, line.c_str(), line.size() + 1);

				std::strtok(l, " ");
				for (int i = 0; i < 9; i++)
					mesh->facesArray[f][i] = std::atof(std::strtok(NULL, " /"));

				mesh->facesArray[f][9] = mtl;
				delete[] l;
				f++;
			}*/
		}

		file.close();
		mesh->_buffer();

		//for (int i = 0;i < mesh->faces; ++i)
		//	delete[] mesh->facesArray[i];

		//delete[] mesh->facesArray;
		delete[] mesh->materialNamesArray;
		delete[] mesh->textureNamesArray;


		std::cout << "Mesh loaded and buffered:" << (mesh->_indices.size() / 3.0f) << " triangles." << std::endl;
		return mesh;
	}
	else
	{
		std::cout << "Could not read " << pFileName + ".obj" << std::endl;
		delete mesh;
		return NULL;
	}
}

std::string Mesh::getMaterialTextureName(std::string pFileName, std::string pMaterialName)
{
	std::string textureName;
	std::ifstream inMLT;
	inMLT.open(pFileName + ".mtl");
	if (!inMLT.good())
	{
		std::cout << "Could not open: " + pFileName + ".mtl";
		inMLT.close();
		return "land.jpg";
	}

	std::string line;
	while (!inMLT.eof())
	{
		std::getline(inMLT, line);
		std::string type = line.substr(0, 2);

		if (type.compare("ne") == 0)
		{
			std::string l = "newmtl ";
			std::string nextLine;
			if (pMaterialName.compare(line.substr(l.size())) == 0)
			{
				for (int i = 0; i < 3; ++i)
				{
					std::getline(inMLT, nextLine);
					std::string t = nextLine.substr(0, 2);
					if (t.compare("ma") == 0)
					{
						int index = nextLine.rfind("\\");
						inMLT.close();
						return nextLine.substr(index + 1);
					}
				}
			}
		}
	}

	inMLT.close();
	return "land.jpg";
}

int Mesh::getMTLinfo(std::string pFileName)
{
	int m = 0;

	std::ifstream inMTL;
	inMTL.open(pFileName + ".mtl");
	if (!inMTL.good())
	{
		std::cout << "Could not open: " + pFileName + ".mtl";
		inMTL.close();
		return 0;
	}

	std::string line;
	while (!inMTL.eof())
	{
		std::getline(inMTL, line);
		std::string type = line.substr(0, 2);

		if (type.compare("ne") == 0)
		{
			std::string l = "newmtl ";
			if (l.compare("Default-Material") != 0)
				m++;
		}
	}

	inMTL.close();
	return m;
}

void Mesh::extractMTLinfo(std::string pFileName, std::string * pMatNames, std::string* pTextureName)
{
	int m = 0;
	int t = 0;

	std::ifstream inMTL;
	inMTL.open(pFileName + ".mtl");
	if (!inMTL.good())
	{
		std::cout << "Could not open: " + pFileName + ".mtl";
		inMTL.close();
		return;
	}

	std::string line;
	while (!inMTL.eof())
	{
		std::getline(inMTL, line);
		std::string type = line.substr(0, 2);

		if (type.compare("ne") == 0)
		{
			std::string l = "newmtl ";
			if (l.compare("Default-Material") != 0)
			{
				pMatNames[m] = line.substr(l.size());
				m++;
			}
		}
		else if (type.compare("ma") == 0)
		{
			int index = line.rfind("\\");
			pTextureName[t] = line.substr(index + 1);
			t++;
		}
	}

	inMTL.close();
}

int Mesh::getOBJinfo(std::string pFileName)
{
	int f = 0;

	std::ifstream inOBJ;
	inOBJ.open(pFileName + ".obj");
	if (!inOBJ.good())
	{
		std::cout << "Could not open " + pFileName + ".obj";
		inOBJ.close();
		return 0;
	}

	std::string line;
	while (!inOBJ.eof())
	{
		std::getline(inOBJ, line);
		std::string type = line.substr(0, 2);

		if (type.compare("f ") == 0)
			f++;
	}

	inOBJ.close();
	return f;
}

void Mesh::_buffer()
{
	glGenBuffers(1, &_indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::streamToOpenGL(GLint pVerticesAttrib, GLint pNormalsAttrib, GLint pUVsAttrib)
{
	if (pVerticesAttrib != -1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
		glEnableVertexAttribArray(pVerticesAttrib);
		glVertexAttribPointer(pVerticesAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (pNormalsAttrib != -1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
		glEnableVertexAttribArray(pNormalsAttrib);
		glVertexAttribPointer(pNormalsAttrib, 3, GL_FLOAT, GL_TRUE, 0, 0);
	}

	if (pUVsAttrib != -1)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _uvBufferId);
		glEnableVertexAttribArray(pUVsAttrib);
		glVertexAttribPointer(pUVsAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);

	// no current buffer, to avoid mishaps, very important for performance

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//fix for serious performance issue
	if (pUVsAttrib != -1) glDisableVertexAttribArray(pUVsAttrib);
	if (pNormalsAttrib != -1) glDisableVertexAttribArray(pNormalsAttrib);
	if (pVerticesAttrib != -1) glDisableVertexAttribArray(pVerticesAttrib);
}

void Mesh::drawDebugInfo(const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	//demo of how to render some debug info using the good ol' direct rendering mode...
	glUseProgram(0);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(pProjectionMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(pViewMatrix * pModelMatrix));

	glBegin(GL_LINES);
	//for each index draw the normal starting at the corresponding vertex
	for (size_t i = 0; i < _indices.size(); i++)
	{
		//draw normal for vertex
		if (true)
		{
			//now get normal end
			glm::vec3 normal = _normals[_indices[i]];
			glColor3fv(glm::value_ptr(normal));

			glm::vec3 normalStart = _vertices[_indices[i]];
			glVertex3fv(glm::value_ptr(normalStart));
			glm::vec3 normalEnd = normalStart + normal * 0.2f;
			glVertex3fv(glm::value_ptr(normalEnd));
		}

	}
	glEnd();
}



