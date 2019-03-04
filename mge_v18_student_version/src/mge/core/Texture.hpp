#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <map>
#include <string>
#include <GL/glew.h>

class Texture
{
	public:
	static Texture* load(const std::string& pTexturePath);

	GLuint getId();

	std::string getPath();
	void setPath(std::string pPath);

	protected:
	Texture();
	virtual ~Texture();

	static Texture* _loadFromFile(const std::string pTexturePath);

	//OpenGL id for texture buffer
	GLuint _id;

	std::string _path;
};

#endif // TEXTURE_HPP
