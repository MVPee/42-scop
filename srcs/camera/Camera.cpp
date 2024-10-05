# include "../../includes/camera/Camera.hpp"

/*
** ------------------------------- STATIC -------------------------------------
*/

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Camera::Camera() : _x(0), _y(0), _z(0) {}

/*
** ------------------------------- DESTRUCTOR ---------------------------------
*/

Camera::~Camera() {}

/*
** ------------------------------- OVERLOAD -----------------------------------
*/

/*
** ------------------------------- METHODS -----------------------------------
*/

void Camera::forward() { 
    //z
    // _z += 0.01;
}

void Camera::backward() { 
    //-z
    // _z -= 0.01;
}

void Camera::right() { 
    //x
    // _x += 0.01;
}

void Camera::left() { 
    //-x
    // _x -= 0.01;
}

/*
** ------------------------------- ACCESSOR ----------------------------------
*/

const float &Camera::getX() const { return _x; }
const float &Camera::getY() const { return _y; }
const float &Camera::getZ() const { return _z; }

/* ************************************************************************** */