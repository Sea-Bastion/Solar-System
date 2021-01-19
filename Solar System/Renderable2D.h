#ifndef Renderable2D_H
#define Renderable2D_H
#include <glm.hpp>

struct Texture {
	unsigned char* image;
	int width;
	int height;
};

class Renderable2D {

public:
	Renderable2D(glm::vec2 size, glm::vec3 pos, Texture texture);
	virtual ~Renderable2D();

	virtual void setPosition(glm::vec3 pos);
	virtual void addPosition(glm::vec3 pos);
	virtual glm::vec3 getPosition();

	virtual void setRotation(int degrees);
	virtual void addRotation(int degrees);
	virtual int getRotation();
	
	virtual void setScale(glm::vec2 scale);
	virtual void setScale(float scale);
	virtual glm::vec2 getScale();

	virtual bool Draw();
	virtual bool Update() = 0;


private:

	glm::vec4 position = glm::vec4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);



};

#endif