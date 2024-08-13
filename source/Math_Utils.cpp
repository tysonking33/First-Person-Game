#include "../includes/Math_Utils.h"

glm::vec2 find_equation(glm::vec2 p1, glm::vec2 p2)
{
    glm::vec2 result;
    if (p2.x - p1.x != 0){
        float gradient = (p2.y - p1.y) / (p2.x - p1.x);
        float b = p1.y - (gradient * p1.x);
        
        //y = gradientx+b
        //std::cout << "equation of p1: (" << p1.x << ", " << p1.y << ") and p2: (" << p2.x << ", " << p2.y << ") is\n" ;
        //std::cout << "y = " << gradient << "x + " << b << std::endl;

        result = glm::vec2(gradient, b);
    }
    else
    {
        //std::cout << "equation of p1: (" << p1.x << ", " << p1.y << ") and p2: (" << p2.x << ", " << p2.y << ") is\n" ;
        //std::cout << "x = " << p1.x << std::endl;
        result = glm::vec2(p1.x, std::numeric_limits<float>::infinity());
    }
    return result;


}

glm::vec2 find_eq_intercept(glm::vec2 p1, glm::vec2 p2, glm::vec2 q1, glm::vec2 q2)
{

    glm::vec2 eq1= find_equation(p1, p2);
    glm::vec2 eq2= find_equation(q1, q2);
    
    glm::vec2 result;

    if (eq1.y == std::numeric_limits<float>::infinity() && eq1.y == std::numeric_limits<float>::infinity())
    {
        std::cout << "both lines are vertical";
        result = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    }
    else if (eq1.y == std::numeric_limits<float>::infinity())
    {
        float x = eq1.x;
        float y = eq2.x * x + eq2.y;
        result = glm::vec2(x, y);
    }
    else if (eq2.y == std::numeric_limits<float>::infinity())
    {
        float x = eq2.x;
        float y = eq1.x * x + eq1.y;
        result = glm::vec2(x, y);
    }
    else
    {
        float a1 = -eq1.x;
        float b1 = 1;
        float c1 = eq1.y;

        float a2 = -eq2.x;
        float b2 = 1;
        float c2 = eq2.y;

        float determinant = a1 * b2 - a2 * b1;
        if (determinant == 0) {
            std::cout << "Lines are parallel";
            result = glm::vec2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
        } else {
            float x = (c1 * b2 - c2 * b1) / determinant;
            float y = (a1 * c2 - a2 * c1) / determinant;
            result = glm::vec2(x, y);
        }
    }

    std::cout << "intersection of\n";
    std::cout << "eq1) y = " <<  eq1.x << "x + " <<  eq1.y << std::endl;
    std::cout << "eq2) y = " <<  eq2.x << "x + " <<  eq2.y << std::endl;
    std::cout << "is: (" << result.x << ", " << result.y << ")\n";



    return result;


}
