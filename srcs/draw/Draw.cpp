# include "../../includes/draw/Draw.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Draw::Draw(Camera *camera, std::ifstream &file) : _camera(camera), _object(new Object(file)) {}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Draw::~Draw() {}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Draw::drawing() {
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 mvp;

    //? Transform (Camera)
    if (_camera->getMode() == FREELOOK)
        view = _camera->getViewMatrix();
    else {
        static float angle = 0.0f;
        angle += TURN_AROUND_SPEED;
        float camX = _object->getPosition().x + TURN_AROUND_DISTANCE * cos(angle);
        float camZ = _object->getPosition().z + TURN_AROUND_DISTANCE * sin(angle);
        float camY = _object->getPosition().y;
        view = glm::lookAt(glm::vec3(camX, camY, camZ), _object->getPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    projection = glm::perspective(glm::radians(45.0f), (float)(DEFAULT_WIDTH / DEFAULT_HEIGHT), 0.1f, 100.0f);
    mvp = projection * view;
    unsigned int transformLoc = glGetUniformLocation(_object->getShader()->getProgram(), "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mvp)); 


    //? Background
    glClearColor(2.0f, 2.0f, 2.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //? Draw
    glBindVertexArray(_object->getVAO()); // Liez le VAO
    glDrawElements(GL_TRIANGLES, _object->getIndices().size(), GL_UNSIGNED_INT, 0);
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

/* ************************************************************************** */