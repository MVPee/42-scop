# include "../../includes/draw/Draw.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Draw::Draw(Camera *camera, std::ifstream &file) : _camera(camera) {
    //* Load file (vertices / indices)
    parseObject(file);

    _shader = new Shader();
    _shader->use();


    //* summit (VBO)
    glGenBuffers(1, &_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);


    //* array (VBA)
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //* incides (EBO)
    glGenBuffers(1, &_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), _indices.data(), GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);
}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Draw::~Draw() {
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

void Draw::parseObject(std::ifstream &file) {
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

void Draw::drawing() {
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 mvp;

    //? Transform (Camera)
    if (_camera->getMode() == FREELOOK) {
        view = _camera->getViewMatrix();
    }
    else {
        glm::vec3 objectPosition(0.0f, 0.0f, 0.0f);
        float radius = 5.0f;
        static float angle = 0.0f;
        angle += 0.01f;
        float camX = objectPosition.x + radius * cos(angle);
        float camZ = objectPosition.z + radius * sin(angle);
        float camY = objectPosition.y;
        view = glm::lookAt(glm::vec3(camX, camY, camZ), objectPosition, glm::vec3(0.0f, 1.0f, 0.0f));
    }
    projection = glm::perspective(glm::radians(45.0f), (float)(DEFAULT_WIDTH / DEFAULT_HEIGHT), 0.1f, 100.0f);
    mvp = projection * view;
    unsigned int transformLoc = glGetUniformLocation(_shader->getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp)); 


    //? Background
    glClearColor(2.0f, 2.0f, 2.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //? Draw
    glBindVertexArray(_VAO); // Liez le VAO
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

/* ************************************************************************** */