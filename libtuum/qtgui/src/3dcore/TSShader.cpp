/** @file TSShader.cpp
 *  @brief Tuum scene shader implementation.
 *
 *  @author Meelik Kiik
 *  @date 26. May 2016
 *  @version 0.1
 */

#include <iostream>

#include "tuum_logger.hpp"

#include "utils/ShaderLdr.hpp"

#include "3dcore/TSMesh.hpp"
#include "3dcore/TSShader.hpp"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_NORMAL_ATTRIBUTE 2

namespace tuum { namespace ts {

  TSOType Shader::type;

  Shader::Shader():
    m_program(nullptr)
  {

  }

  Shader::Shader(const char* fp) {
    Shader();
    loadSource(fp);
  }

  Shader::~Shader() {

  }

  int Shader::loadSource(const char* fp) {
    shldr::shader_data_t d;
    if(shldr::load_shader(fp, d) < 0) return -1;
    m_program = new QOpenGLShaderProgram();

    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, d.vert.c_str());
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, d.frag.c_str());

    m_program->bindAttributeLocation("position", PROGRAM_VERTEX_ATTRIBUTE);
    m_program->bindAttributeLocation("tex_coord", PROGRAM_TEXCOORD_ATTRIBUTE);
    m_program->bindAttributeLocation("normal", PROGRAM_NORMAL_ATTRIBUTE);

    return 0;
  }

  int Shader::init() {
    if(!m_program) return -1;
    if(!m_program->link()) return -2;
    RTXLOG("Loaded.");
    return 0;
  }

  int Shader::initAttributes(const attr_ctx ctx) {
    if(!ctx.vao->isCreated()) return -1;
    ctx.vao->bind();

    m_program->bind();
    std::cout << sizeof(Vertex) << std::endl;
    if(ctx.vertices) {
      ctx.vertices->bind();
      quintptr offset = 0;
      int stride = sizeof(Vertex);

      m_program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
      m_program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, offset, 3, stride);
      offset += sizeof(glm::vec3);

      m_program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
      m_program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, offset, 2, stride);
      offset += sizeof(glm::vec2);

      m_program->enableAttributeArray(PROGRAM_NORMAL_ATTRIBUTE);
      m_program->setAttributeBuffer(PROGRAM_NORMAL_ATTRIBUTE, GL_FLOAT, offset, 3, stride);
    }

    if(ctx.indices) {
      ctx.indices->bind();
    }

    ctx.tex->bind();
    m_program->release();
    ctx.vao->release();

    return 0;
  }

  int Shader::setupAttributes(const attr_ctx ctx) {
    if(!ctx.vao->isCreated()) return -1;
    ctx.vao->bind();

    m_program->bind();
    ctx.tex->bind();

    m_program->setUniformValue("mvp", ctx.mvp);

    return 0;
  }

  void Shader::bind() {
    m_program->bind();
  }

  void Shader::release() {
    m_program->release();
  }

  QOpenGLShaderProgram* Shader::getProgram() {
    return m_program;
  }

  TSOType* Shader::getType() const {
    return &Shader::type;
  }

}}
