#ifndef MESH_H_
#define MESH_H_

#include <memory>
#include "vrbase/Box.h"
#include <vector>
#include "vrbase/Scene.h"
#include "GL/glew.h"
#include "vrbase/Texture.h"

namespace vrbase {

class Mesh;
typedef std::shared_ptr<Mesh> MeshRef;

class Mesh : public Scene {
public:
	Mesh(const std::vector<glm::vec3> &vertices, const std::vector<unsigned int>& indices);
	Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &normals, const std::vector<unsigned int>& indices);
	virtual ~Mesh();

	const std::vector<unsigned int>& getIndices() const;
	void setIndices(const std::vector<unsigned int>& indices);
	const std::vector<glm::vec3>& getVertices() const;
	void setVertices(const std::vector<glm::vec3>& vertices);
	const std::vector<glm::vec3>& getNormals() const;
	void setNormals(const std::vector<glm::vec3>& normals);
	const std::vector<glm::vec2>& getTexCoords() const;
	void setTexCoords(const std::vector<glm::vec2>& texCoords);
	TextureRef getTexture() const;
	void setTexture(TextureRef texture);

private:
	void calculateBoundingBox();
	void calculateNormals();
	void init();

	Box* _boundingBox;
	bool _hasNormals;
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec3> _normals;
	std::vector<glm::vec2> _texCoords;
	std::vector<unsigned int> _indices;
	TextureRef _texture;

// Graphics code
public:
	const Box& getBoundingBox();
	void draw(MinVR::RenderDevice& renderDevice);

protected:
	void initContextItem();
	bool updateContextItem(bool changed);
	void cleanupContextItem();

private:
	void generateVaoAttributes(int &location);
	int bindIndices();

	void createVBO();
	void deleteVBO();

	MinVR::ContextSpecificPtr<GLuint> _vao;
	MinVR::ContextSpecificPtr<GLuint> _vbo;
	MinVR::ContextSpecificPtr<GLuint> _indexVbo;
};

} /* namespace vrbase */

#endif /* MESH_H_ */
