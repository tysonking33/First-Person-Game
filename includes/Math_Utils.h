#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <limits.h>


#include <math.h>


glm::vec2 find_equation(glm::vec2 p1, glm::vec2 p2);
glm::vec2 find_eq_intercept(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1, glm::vec2 q2);
#endif