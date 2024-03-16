#include "TriangleMesh.hpp"

#include "glad/glad.h"

#include <cstddef>
#include <vector>

struct VecPos {
  float x, y, z;
};

struct VecColor {
  float R, G, B;
};

struct Point {
  VecPos pos;
  VecColor color;
};

TriangleMesh::TriangleMesh() {
  std::vector<Point> data{
      {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // bottom left
      {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},  // bottom right
      {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},   // top left
  };

  vertex_count = data.size();

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Point), data.data(),
               GL_STATIC_DRAW);

  // position
  glVertexAttribPointer(0 /* location in vertex shader */, vertex_count,
                        GL_FLOAT, GL_FALSE, sizeof(Point) /* stride */,
                        (void *)offsetof(Point, pos));
  glEnableVertexAttribArray(0);

  // color
  glVertexAttribPointer(1 /* location in vertex shader */, vertex_count,
                        GL_FLOAT, GL_FALSE, sizeof(Point) /* stride */,
                        (void *)offsetof(Point, color));
  glEnableVertexAttribArray(1);
}

TriangleMesh::~TriangleMesh() {
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}

void TriangleMesh::draw() {
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}
