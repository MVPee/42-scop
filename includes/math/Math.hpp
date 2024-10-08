#ifndef MATH_HPP
# define MATH_HPP

# include "../macro.hpp"

namespace math {
    class Vec3 {
        private:
        public:
            float   _x;
            float   _y;
            float   _z;

        Vec3() : _x(0.0f), _y(0.0f), _z(0.0f) {}
        Vec3(float nbr) : _x(nbr), _y(nbr), _z(nbr) {}
        Vec3(float x, float y, float z) : _x(x), _y(y), _z(z) {}
        Vec3(const Vec3 &vec3) : _x(vec3._x), _y(vec3._y), _z(vec3._z) {}
        Vec3 &operator=(const Vec3 &vec3) {
            if (this != &vec3) {
                _x = vec3._x;
                _y = vec3._y;
                _z = vec3._z;
            }
            return *this;
        }
        Vec3 operator-(const Vec3 &vec3) const { return Vec3(_x - vec3._x, _y - vec3._y, _z - vec3._z); }
        Vec3 operator+(const Vec3 &vec3) const { return Vec3(_x + vec3._x, _y + vec3._y, _z + vec3._z); }
    };

    class Mat4 {
        public:
            float _data[4][4];
            Mat4() {
                for (int i = 0; i < 4; ++i)
                    for (int j = 0; j < 4; ++j)
                        _data[i][j] = (i == j) ? 1.0f : 0.0f;
            }
            Mat4(float data[4][4]) {
                for (int i = 0; i < 4; ++i)
                    for (int j = 0; j < 4; ++j)
                        _data[i][j] = data[i][j];
            }
            Mat4 operator*(const Mat4 &mat) const {
                Mat4 result;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        result._data[i][j] = 0;
                        for (int k = 0; k < 4; ++k)
                            result._data[i][j] += _data[i][k] * mat._data[k][j];
                    }
                }
                return result;
            }
    };

    Vec3 normalize(const Vec3 &vec3);
    Vec3 cross(const Vec3 &vec1, const Vec3 &vec2);

    Mat4 lookAt(const Vec3 &cameraPos, const Vec3 &target, const Vec3 &up);
    Mat4 perspective(float fovy, float aspect, float zNear, float zFar);

    float radians (float degrees);
}

#endif