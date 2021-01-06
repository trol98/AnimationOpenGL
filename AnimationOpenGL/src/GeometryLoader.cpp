#include "GeometryLoader.h"

#include "vendor/glm/glm/glm.hpp"
#include "vendor/glm/glm/gtc/matrix_transform.hpp"

const glm::mat4 GeometryLoader::CORRECTION = glm::rotate(glm::mat4(), glm::radians(-90.0f), glm::vec3(1, 0, 0));