# include "../../includes/object/Object.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Object::Object(std::ifstream &file) {
	_shader = new Shader();
    _shader->use();

	parseFile(file);
	parsePosition();

	glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    // Lier le VAO
    glBindVertexArray(_VAO);

    // Charger les sommets dans le VBO
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), &_vertices[0], GL_STATIC_DRAW);

    // Attribuer les pointeurs d'attributs de sommets (position et couleur)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Charger les indices dans l'EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    // Désactiver la liaison du VAO
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
	static unsigned int count = 0;
    std::string line;
    std::string value;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> value;
        if (value == "v") { //? VERTEX
            float vertex;
            while (iss >> vertex)
                _vertices.push_back(vertex);
            if (count % 3 == 0) {
                _vertices.push_back(1.0f);
                _vertices.push_back(0.0f);
                _vertices.push_back(0.0f);
            }
            else if (count % 3 == 1) {
                _vertices.push_back(0.0f);
                _vertices.push_back(1.0f);
                _vertices.push_back(0.0f);
            }
            else {
                _vertices.push_back(0.0f);
                _vertices.push_back(0.0f);
                _vertices.push_back(1.0f);
            }
            count++;
        }
        else if (value == "f") { //? INDICES
            std::vector<unsigned int> faceIndices;
            unsigned int index;
            while (iss >> index)
                faceIndices.push_back(index - 1);
            if (faceIndices.size() == 3)
                _indices.insert(_indices.end(), faceIndices.begin(), faceIndices.end());
            else if (faceIndices.size() == 4) {
                _indices.push_back(faceIndices[0]);
                _indices.push_back(faceIndices[1]);
                _indices.push_back(faceIndices[2]);
                
                _indices.push_back(faceIndices[0]);
                _indices.push_back(faceIndices[2]);
                _indices.push_back(faceIndices[3]);
            }
        }
    }
}

void Object::parsePosition() {
	float biggest[3] = {std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min()};
    float lowest[3] = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};

    for (size_t i = 0; i < _vertices.size(); i += 6) {
        for (int j = 0; j < 3; ++j) {
            if (_vertices[i + j] < lowest[j])
                lowest[j] = _vertices[i + j];
            if (_vertices[i + j] > biggest[j])
                biggest[j] = _vertices[i + j];
        }
    }

    _position = glm::vec3 (
        (lowest[0] + biggest[0]) / 2,
        (lowest[1] + biggest[1]) / 2,
        (lowest[2] + biggest[2]) / 2
    );
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

const glm::vec3 &Object::getPosition() const { return _position; }
const std::vector<float> &Object::getVertices() const { return _vertices; }
const std::vector<unsigned int> &Object::getIndices() const { return _indices; }
const unsigned int &Object::getVAO() const { return _VAO; }
Shader *Object::getShader() const { return _shader; }

/* ************************************************************************** */