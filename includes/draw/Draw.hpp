#pragma once

# include "../macro.hpp"

class Camera;
class Object;

class Draw {
	private:
		Camera	*_camera;
		Object	*_object;
	public:
		Draw(Camera *camera, std::ifstream &file);
		~Draw();

		void drawing();
};