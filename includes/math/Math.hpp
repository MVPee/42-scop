#ifndef MATH_HPP
# define MATH_HPP

# include <iostream>
# include <string>
# include <cmath>

namespace ft_math {
    class vec3 {
        private:
        public:
            float   x;
            float   y;
            float   z;

            vec3();
            vec3(float nbr);
            vec3(float x, float y, float z);
            vec3(const vec3 &vec3);
            vec3 &operator=(const vec3 &vec3);
            vec3 operator-(const vec3 &v) const;
            vec3 operator+(const vec3 &v) const;
            vec3 operator*(float scalar) const;
            vec3 &operator+=(const vec3 &v);
            vec3 &operator-=(const vec3 &v);
    };

    class mat4 {
        public:
            float _data[4][4];

            mat4();
            mat4(float data[4][4]);
            mat4 operator*(const mat4 &mat) const;
            float* value_ptr();
    };

    vec3 normalize(const vec3 &vec3);
    vec3 cross(const vec3 &vec1, const vec3 &vec2);

    mat4 lookAt(const vec3 &cameraPos, const vec3 &target, const vec3 &up);
    mat4 perspective(float fovy, float aspect, float zNear, float zFar);

    float radians (float degrees);
}

#endif