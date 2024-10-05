#pragma once

# include "../macro.hpp"

class Camera {
	private:
		float _x;
		float _y;
		float _z;
		unsigned short int _rotation;
	public:
		Camera();
		~Camera();
	
	void forward();
	void backward();
	void right();
	void left();

	const float &getX() const;
	const float &getY() const;
	const float &getZ() const;
};