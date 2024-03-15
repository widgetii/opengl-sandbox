#ifndef TRIAGLEMESH_HPP
#define TRIAGLEMESH_HPP

class TriangleMesh {
public:
  TriangleMesh();
  void draw();
  ~TriangleMesh();

private:
  unsigned int VBO, VAO, vertex_count;
};

#endif /* TRIAGLEMESH_HPP */
