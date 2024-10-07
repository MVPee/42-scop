# include "../../includes/object/Object.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Object::Object(std::ifstream &file) {
	_shader = new Shader();

	parseFile(file);
	parsePosition();

	glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    //? LINK VAO
    glBindVertexArray(_VAO);

    //? LOAD SUMMITS
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertex.size() * sizeof(float), &_vertex[0], GL_STATIC_DRAW);

    //? LOAD COLOR AND ATTRIBUT WITH VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    //? LOAD INDICES
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indice.size() * sizeof(unsigned int), &_indice[0], GL_STATIC_DRAW);

    //? DELINK VAO
    glBindVertexArray(0);
}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Object::~Object() {
	glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_EBO);
    delete _shader;
}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Object::parseFile(std::ifstream &file) {
    float vertex;
    std::string line;
    std::string token;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> token;
        if (token == "v") //? VERTEX
            while (iss >> vertex)
                _vertex.push_back(vertex);
        else if (token == "vt") //? VERTEX TEXTURE
            while (iss >> vertex)
                _vertexTexture.push_back(vertex);
        else if (token == "vn") //? VERTEX NORNAL (LIGHT)
            while (iss >> vertex)
                _vertexNormal.push_back(vertex);
        else if (token == "f") { //? INDICES
            std::vector<unsigned int> faceIndices;
            std::vector<unsigned int> faceTextureIndices;
            std::vector<unsigned int> faceNormalIndices;

            if (line.find("/") == std::string::npos) {
                unsigned int index;
                while (iss >> index)
                    faceIndices.push_back(index - 1);
            }
            else {
                std::string vertexInfo;
                while (iss >> vertexInfo) {
                    std::stringstream ss(vertexInfo);
                    std::string vertexIndex, textureIndex, normalIndex;

                    if (std::getline(ss, vertexIndex, '/')) { //?v
                        unsigned int index = std::stoi(vertexIndex) - 1;
                        faceIndices.push_back(index);
                    }

                    if (std::getline(ss, textureIndex, '/')) { //?vt
                        if (!textureIndex.empty()) {
                            unsigned int texIndex = std::stoi(textureIndex) - 1;
                            faceTextureIndices.push_back(texIndex);
                        }
                    }

                    if (std::getline(ss, normalIndex)) { //?vn
                        if (!normalIndex.empty()) {
                            unsigned int normIndex = std::stoi(normalIndex) - 1;
                            faceNormalIndices.push_back(normIndex);
                        }
                    }
                }
            }

            if (faceIndices.size() == 3) {
                _indice.insert(_indice.end(), faceIndices.begin(), faceIndices.end());
            } else if (faceIndices.size() == 4) {
                _indice.push_back(faceIndices[0]);
                _indice.push_back(faceIndices[1]);
                _indice.push_back(faceIndices[2]);
                _indice.push_back(faceIndices[0]);
                _indice.push_back(faceIndices[2]);
                _indice.push_back(faceIndices[3]);
            }

            if (faceTextureIndices.size() == 3) {
                _indiceTexture.insert(_indiceTexture.end(), faceTextureIndices.begin(), faceTextureIndices.end());
            } else if (faceTextureIndices.size() == 4) {
                _indiceTexture.push_back(faceTextureIndices[0]);
                _indiceTexture.push_back(faceTextureIndices[1]);
                _indiceTexture.push_back(faceTextureIndices[2]);
                _indiceTexture.push_back(faceTextureIndices[0]);
                _indiceTexture.push_back(faceTextureIndices[2]);
                _indiceTexture.push_back(faceTextureIndices[3]);
            }

            if (faceNormalIndices.size() == 3) {
                _indiceNormal.insert(_indiceNormal.end(), faceNormalIndices.begin(), faceNormalIndices.end());
            } else if (faceNormalIndices.size() == 4) {
                _indiceNormal.push_back(faceNormalIndices[0]);
                _indiceNormal.push_back(faceNormalIndices[1]);
                _indiceNormal.push_back(faceNormalIndices[2]);
                _indiceNormal.push_back(faceNormalIndices[0]);
                _indiceNormal.push_back(faceNormalIndices[2]);
                _indiceNormal.push_back(faceNormalIndices[3]);
            }
        }
    }
}

void Object::parsePosition() {
	float biggest[3] = {std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
    float lowest[3] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

    for (size_t i = 0; i < _vertex.size(); i += 6) {
        for (int j = 0; j < 3; ++j) {
            if (_vertex[i + j] < lowest[j])
                lowest[j] = _vertex[i + j];
            if (_vertex[i + j] > biggest[j])
                biggest[j] = _vertex[i + j];
        }
    }

    _position = glm::vec3 (
        (lowest[0] + biggest[0]) / 2,
        (lowest[1] + biggest[1]) / 2,
        (lowest[2] + biggest[2]) / 2
    );
}

void Object::draw() const {
	_shader->use();
	glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indice.size(), GL_UNSIGNED_INT, 0);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

const glm::vec3 &Object::getPosition() const { return _position; }
void Object::setPosition(glm::vec3 position) { _position = position;}
const std::vector<float> &Object::getVertices() const { return _vertex; }
const std::vector<unsigned int> &Object::getIndices() const { return _indice; }
const unsigned int &Object::getVAO() const { return _VAO; }
Shader *Object::getShader() const { return _shader; }

/* ************************************************************************** */