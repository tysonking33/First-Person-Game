#include "../includes/Physics_Engine.h"

// checking if the point of interscetion in within the vertexs of the bounded plane not just the infinite plane
bool Physics_Engine::CheckDotOnBoundedPlane(glm::vec3 point_of_intersection, std::vector<glm::vec3> planeCoordinates, glm::vec3 planeNormal)
{
    // p0,p1,p2, p3 are in clockwise order starting from top left, top right, bottom right, bottom left
    glm::vec3 p0 = planeCoordinates[0];
    glm::vec3 p1 = planeCoordinates[1];
    glm::vec3 p2 = planeCoordinates[2];
    glm::vec3 p3 = planeCoordinates[3];

    /* ---------------------------triangle 1 = p0, p1, p2------------------------*/

    // find vectors
    glm::vec3 v0 = p1 - p0;
    glm::vec3 v1 = p2 - p0;
    glm::vec3 v2 = point_of_intersection - p0;

    // find dot products
    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot02 = glm::dot(v0, v2);
    float dot11 = glm::dot(v1, v1);
    float dot12 = glm::dot(v1, v2);

    // float Calculate Barycentric Coordinates
    float invDenom = 1 / (glm::dot(dot00, dot11) - glm::dot(dot01, dot01));

    float alpha = glm::dot((dot11 * dot02) - (dot01 * dot12), invDenom);
    float beta = glm::dot((dot00 * dot12) - (dot01 * dot02), invDenom);

    float yThing = 1 - alpha - beta;

    if ((alpha >= 0 && alpha <= 1) && (beta >= 0 && beta <= 1) && (alpha + beta <= 1))
    {
        return true;
    }

    /*----------------------------------------------triangle 2 = p2, p3, p0---------------------------------*/

    // find vectors
    v0 = p3 - p2;
    v1 = p0 - p2;
    v2 = point_of_intersection - p2;

    // find dot products
    dot00 = glm::dot(v0, v0);
    dot01 = glm::dot(v0, v1);
    dot02 = glm::dot(v0, v2);
    dot11 = glm::dot(v1, v1);
    dot12 = glm::dot(v1, v2);

    // float Calculate Barycentric Coordinates
    invDenom = 1 / (glm::dot(dot00, dot11) - glm::dot(dot01, dot01));

    alpha = glm::dot((dot11 * dot02) - (dot01 * dot12), invDenom);
    beta = glm::dot((dot00 * dot12) - (dot01 * dot02), invDenom);

    yThing = 1 - alpha - beta;

    if ((alpha >= 0 && alpha <= 1) && (beta >= 0 && beta <= 1) && (alpha + beta <= 1))
    {
        return true;
    }
    std::cout << "point of intersection not in plane\n";
    return false;
}

// abccda
/*pseudo code
    calculate ray equation

    for loop (0 < 6)
    {
        calculate equation of plane

        if (ray intercept with plane):
            return true
    }
    return false
*/
bool Physics_Engine::RayCast(Camera *camera, std::vector<Vertex> DataPoints)
{
    glm::vec3 rayPosition = camera->getPosition();
    glm::vec3 rayViewDirection = camera->getFront();
    float cameraYaw = camera->getYaw();
    /*-------------------------finding equation of ray-------------------------------------------*/
    // t is number of iterations
    // ray(x) = rayPosition.x + t * rayViewDirection.x
    // ray(y) = rayPosition.y + t * rayViewDirection.y
    // ray(z) = rayPosition.z + t * rayViewDirection.z

    for (int i = 0; i < 36; i += 6)
    {
        /*-------------------------find equation of a plane for every face--------------------------*/
        // chose 3 points
        glm::vec3 p1 = glm::vec3{DataPoints[i].position[0], DataPoints[i].position[1], DataPoints[i].position[2]};
        glm::vec3 p2 = glm::vec3{DataPoints[i + 1].position[0], DataPoints[i + 1].position[1], DataPoints[i + 1].position[2]};
        glm::vec3 p3 = glm::vec3{DataPoints[i + 2].position[0], DataPoints[i + 2].position[1], DataPoints[i + 2].position[2]};
        glm::vec3 p4 = glm::vec3{DataPoints[i + 4].position[0], DataPoints[i + 4].position[1], DataPoints[i + 4].position[2]};

        /*-------------------------calculating if the plane is in the viewport of the camera--------*/
        glm::vec3 planeCentriod = 0.25f * (p1 + p2 + p3 + p4);

        glm::vec3 rayOToCentroidVec = planeCentriod - rayPosition;

        glm::vec3 normalisedDir = glm::normalize(rayViewDirection);

        glm::vec3 normalisedRayToCentroid = glm::normalize(rayOToCentroidVec);

        float pointToPlaneAngle = acos(cos(glm::dot(normalisedDir, normalisedRayToCentroid)));

        // assume there is a  10 degrees angles to each side for the viewport, idk later, i.e. if yaw is 30 the viewport angle is 75 and -5
        float leftRightAngle = 180.f;
        float clockwiseAngle = cameraYaw - leftRightAngle;
        if (clockwiseAngle <= -359)
        {
            clockwiseAngle += 360;
        }

        float antiClockwiseAngle = cameraYaw + leftRightAngle;
        if (antiClockwiseAngle >= 359)
        {
            antiClockwiseAngle -= 360;
        }

        if (pointToPlaneAngle < clockwiseAngle || pointToPlaneAngle > antiClockwiseAngle)
        {
            // out of  viewport
            return false;
        }

        /*---------------------------------calculate collision------------------------------------*/
        glm::vec3 v1 = p2 - p1;
        glm::vec3 v2 = p3 - p1;

        glm::vec3 normalVector = glm::cross(v1, v2);
        glm::vec3 normalisedNormalVector = glm::normalize(normalVector);

        float normDotDir = glm::dot(normalisedNormalVector, rayViewDirection);

        std::cout << "Normal Vector: " << glm::to_string(normalisedNormalVector) << std::endl;
        std::cout << "Ray Direction: " << glm::to_string(normalisedDir) << std::endl;
        std::cout << "Dot Product: " << normDotDir << std::endl;

        const float epsilon = 1e-6f;
        if (fabs(normDotDir) < epsilon)
        {
            // no intersection, parallel
            std::cout << "no intersection, parallel\n";
            // return false;
        }

        // plane's distance from the origin along the normal vector
        float d = glm::dot(normalisedNormalVector, p1);
        float t = (d - glm::dot(normalisedNormalVector, rayPosition)) / (normDotDir);

        if (t < 0)
        {
            // behind ray origin, no collison
            std::cout << "behind ray origin, no collison\n";

            // return false;
        }
        else
        {
            glm::vec3 point_of_intersection = rayPosition + t * rayViewDirection;
            std::vector<glm::vec3> planeCoordinates;

            planeCoordinates.push_back(p1);
            planeCoordinates.push_back(p2);
            planeCoordinates.push_back(p3);
            planeCoordinates.push_back(p4);
            // collison occurs where t is positive, i.e. in front of camera
            if (CheckDotOnBoundedPlane(point_of_intersection, planeCoordinates, normalisedNormalVector) == true)
            {
                return true;
            }
        }
    }
    std::cout << "everything failed\n";
    return false;
}


bool Physics_Engine::cubeCollision(Cube *cubeA, Cube *cubeB)
{
    glm::vec3 Apos = cubeA->getCubePosition();
    float Asize = cubeA->getCubeSize();
    
    glm::vec3 Bpos = cubeB->getCubePosition();
    float Bsize = cubeB->getCubeSize();
    std::cout << "CubeA: " << Apos.x << ", " << Apos.y << ", " << Apos.z << "\n";
    std::cout << "CubeB: " << Bpos.x << ", " << Bpos.y << ", " << Bpos.z << "\n";

    /*-----------------------cubeA vertexs-------------------------------*/
    float minXA  = Apos.x - Asize/2;
    float minYA  = Apos.y - Asize/2;
    float minZA  = Apos.z - Asize/2;

    float maxXA  = Apos.x + Asize/2;
    float maxYA  = Apos.y + Asize/2;
    float maxZA  = Apos.z + Asize/2;

    /*-----------------------cubeB vertexs-------------------------------*/
    float minXB  = Bpos.x - Bsize/2;
    float minYB  = Bpos.y - Bsize/2;
    float minZB  = Bpos.z - Bsize/2;

    float maxXB  = Bpos.x + Bsize/2;
    float maxYB  = Bpos.y + Bsize/2;
    float maxZB  = Bpos.z + Bsize/2;   

    bool Xcollide = minXA <= maxXB && maxXA >= minXB;
    bool Ycollide = minYA <= maxYB && maxYA >= minYB;
    bool Zcollide = minZA <= maxZB && maxZA >= minZB;
    return (Xcollide && Ycollide && Zcollide);
}
