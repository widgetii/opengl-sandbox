#ifndef UTILS_HPP
#define UTILS_HPP

#define GL_SILENCE_DEPRECATION 1
#include "glad/glad.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

/** Read file into string. */
inline std::string slurp(const std::string &path) {
  std::ostringstream buf;
  std::ifstream input(path);
  buf << input.rdbuf();
  return buf.str();
}
#include "utils.hpp"

inline unsigned int make_module(const std::string &filepath,
                                unsigned int module_type) {
  std::string shaderSource = slurp(filepath);
  unsigned int shaderModule = glCreateShader(module_type);
  const char *shaderSrc = shaderSource.c_str();

  glShaderSource(shaderModule, 1, &shaderSrc, NULL);
  glCompileShader(shaderModule);

  int status;
  glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &status);
  if (!status) {
    char errorLog[1024];

    glGetShaderInfoLog(shaderModule, sizeof(errorLog), NULL, errorLog);
    std::cerr << "Shader module " << filepath << " compilation error: " << errorLog << std::endl;
  }

  return shaderModule;
}

inline unsigned int make_shader(const std::string &vertex_filepath,
                                const std::string &fragment_filepath) {
  auto modules = std::vector<unsigned int>{
      make_module(vertex_filepath, GL_VERTEX_SHADER),
      make_module(fragment_filepath, GL_FRAGMENT_SHADER),
  };

  auto shader = glCreateProgram();
  for (auto shaderModule : modules) {
    glAttachShader(shader, shaderModule);
  }
  glLinkProgram(shader);

  int status;
  glGetProgramiv(shader, GL_LINK_STATUS, &status);
  if (!status) {
    char errorLog[1024];

    glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
    std::cerr << "Program link error: " << errorLog << std::endl;
  }

  for (auto shaderModule : modules) {
    glDeleteShader(shaderModule);
  }

  return shader;
}

#endif /* UTILS_HPP */
