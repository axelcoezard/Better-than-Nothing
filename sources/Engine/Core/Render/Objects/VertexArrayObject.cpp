/*
 * File: VertexArrayObject.hpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Friday, 10th March 2023 1:49:49 pm
 * Last Modified: Friday, 10th March 2023 1:49:51 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <stdexcept>
#include "Core/Render/Objects/VertexArrayObject.h"

VertexArrayObject::VertexArrayObject(void) {
	glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject(void) {

}

void VertexArrayObject::Bind(void) {
    glBindVertexArray(m_id);
}

void VertexArrayObject::UnBind(void) {
    glBindVertexArray(0);
}
