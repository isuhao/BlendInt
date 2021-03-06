/*
 * This file is part of BlendInt (a Blender-like Interface Library in
 * OpenGL).
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is free
 * software: you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * BlendInt (a Blender-like Interface Library in OpenGL) is
 * distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with BlendInt.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Contributor(s): Freeman Zhang <zhanggyb@gmail.com>
 */

#pragma once

#include <stack>

#include <glm/glm.hpp>

#include <blendint/core/refptr.hpp>

#include <blendint/opengl/gl-buffer.hpp>
#include <blendint/opengl/glsl-program.hpp>

namespace BlendInt {

enum AttributeLayout
{
  AttributeCoord = 0, AttributeColor = 1, AttributeUV = 1
};

/**
 * @brief A class which provide pre-defined shaders
 *
 * The ShaderManager class works as a service in BlendInt and
 * provide simple pre-defined shaders for widgets.
 */
class Shaders
{
 public:

  enum LocationType
  {

    // Triangles
    WIDGET_TRIANGLE_COORD,
    WIDGET_TRIANGLE_COLOR,
    //TRIANGLE_PROJECTION,
    //TRIANGLE_VIEW,
    WIDGET_TRIANGLE_POSITION,
    WIDGET_TRIANGLE_ROTATION,
    WIDGET_TRIANGLE_SCALE,
    WIDGET_TRIANGLE_ANTI_ALIAS,
    WIDGET_TRIANGLE_GAMMA,

    WIDGET_SIMPLE_TRIANGLE_COORD,
    WIDGET_SIMPLE_TRIANGLE_POSITION,		// vec2 of outline or emboss vertices
    WIDGET_SIMPLE_TRIANGLE_COLOR,
    WIDGET_SIMPLE_TRIANGLE_GAMMA,

    WIDGET_INNER_COORD,
    WIDGET_INNER_COLOR,
    WIDGET_INNER_GAMMA,
    WIDGET_INNER_SHADED,

    WIDGET_SPLIT_INNER_COORD,
    WIDGET_SPLIT_INNER_COLOR0,	// The left or bottom color
    WIDGET_SPLIT_INNER_COLOR1,	// The right or top color
    WIDGET_SPLIT_INNER_MIDDLE,
    WIDGET_SPLIT_INNER_GAMMA,
    WIDGET_SPLIT_INNER_SHADED,

    WIDGET_OUTER_COORD,
    WIDGET_OUTER_COLOR,
    WIDGET_OUTER_OFFSET,	// for emboss

    // Text
    WIDGET_TEXT_COORD,
    //TEXT_PROJECTION,
    //TEXT_VIEW,
    WIDGET_TEXT_POSITION,
    WIDGET_TEXT_ROTATION,
    WIDGET_TEXT_TEXTURE,
    WIDGET_TEXT_COLOR,

    // Image
    WIDGET_IMAGE_COORD,
    WIDGET_IMAGE_UV,
    //IMAGE_PROJECTION,
    //IMAGE_VIEW,
    WIDGET_IMAGE_POSITION,
    WIDGET_IMAGE_ROTATION,
    WIDGET_IMAGE_TEXTURE,
    WIDGET_IMAGE_GAMMA,

    // Line
    WIDGET_LINE_COORD,
    WIDGET_LINE_COLOR,

    // AbstractRoundWidget shadow
    WIDGET_SHADOW_COORD,
    WIDGET_SHADOW_POSITION,
    WIDGET_SHADOW_VIEWPORT_POSITION,
    WIDGET_SHADOW_ANTI_ALIAS,
    WIDGET_SHADOW_SIZE,

    // Debug layout
    WIDGET_DEBUG_COORD,
    
    PRIMITIVE_COORD,
    PRIMITIVE_COLOR,
    PRIMITIVE_PROJECTION,
    PRIMITIVE_VIEW,
    PRIMITIVE_MODEL,

    FRAME_INNER_COORD,
    FRAME_INNER_COLOR,
    FRAME_INNER_POSITION,
    FRAME_INNER_GAMMA,

    FRAME_OUTER_COORD,
    FRAME_OUTER_COLOR,
    FRAME_OUTER_POSITION,	// vec2 of outline or emboss vertices

    // Frmae Image
    FRAME_IMAGE_COORD,
    FRAME_IMAGE_UV,
    FRAME_IMAGE_POSITION,
    FRAME_IMAGE_TEXTURE,
    FRAME_IMAGE_GAMMA,

    FRAME_SHADOW_COORD,
    //FRAME_SHADOW_COLOR,
    FRAME_SHADOW_POSITION,
    FRAME_SHADOW_ANTI_ALIAS,
    FRAME_SHADOW_SIZE,

    LocationLast
  };

  inline const RefPtr<GLSLProgram>& widget_text_program () const
  {
    return widget_text_program_;
  }

  inline const RefPtr<GLSLProgram>& primitive_program () const
  {
    return primitive_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_triangle_program () const
  {
    return widget_triangle_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_simple_triangle_program () const
  {
    return widget_simple_triangle_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_inner_program () const
  {
    return widget_inner_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_split_inner_program () const
  {
    return widget_split_inner_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_outer_program () const
  {
    return widget_outer_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_image_program () const
  {
    return widget_image_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_line_program () const
  {
    return widget_line_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_shadow_program () const
  {
    return widget_shadow_program_;
  }

  inline const RefPtr<GLSLProgram>& widget_debug_program () const
  {
    return widget_debug_program_;
  }
  
  inline const RefPtr<GLSLProgram>& frame_inner_program () const
  {
    return frame_inner_program_;
  }

  inline const RefPtr<GLSLProgram>& frame_outer_program () const
  {
    return frame_outer_program_;
  }

  inline const RefPtr<GLSLProgram>& frame_image_program () const
  {
    return frame_image_program_;
  }

  inline const RefPtr<GLSLProgram>& frame_shadow_program () const
  {
    return frame_shadow_program_;
  }

  inline const glm::mat4& widget_projection_matrix () const
  {
    return current_widget_projection_matrix_;
  }

  inline const glm::mat4& widget_view_matrix () const
  {
    return current_widget_view_matrix_;
  }

  inline const glm::mat3& widget_model_matrix () const
  {
    return current_widget_model_matrix_;
  }

  void SetWidgetProjectionMatrix (const glm::mat4& matrix);

  void PushWidgetProjectionMatrix ();

  void PopWidgetProjectionMatrix ();

  void SetWidgetViewMatrix (const glm::mat4& matrix);

  void PushWidgetViewMatrix ();

  void PopWidgetViewMatrix ();

  void SetWidgetModelMatrix (const glm::mat3& matrix);

  void PushWidgetModelMatrix ();

  void PopWidgetModelMatrix ();

  void SetFrameProjectionMatrix (const glm::mat4& matrix);

  void SetFrameViewMatrix (const glm::mat4& matrix);

  void SetFrameModelMatrix (const glm::mat3& matrix);

  inline const glm::mat4& current_widget_projection_matrix () const
  {
    return current_widget_projection_matrix_;
  }

  inline const glm::mat4& current_widget_view_matrix () const
  {
    return current_widget_view_matrix_;
  }

  inline const glm::mat3& current_widget_model_matrix () const
  {
    return current_widget_model_matrix_;
  }

  inline GLint location (LocationType index) const
  {
    return locations_[index];
  }

 private:

  enum
  {
    ProjectionIndex,  // 0
    ViewIndex,        // 1
    ModelIndex        // 2
  };

  friend class AbstractWindow;

  Shaders ();

  ~Shaders ();

  bool Setup ();

  bool SetupWidgetInnerProgram ();

  bool SetupWidgetSplitInnerProgram ();

  bool SetupWidgetOuterProgram ();

  bool SetupWidgetTextProgram ();

  bool SetupWidgetTriangleProgram ();

  bool SetupWidgetSimpleTriangleProgram ();

  bool SetupWidgetImageProgram ();

  bool SetupWidgetLineProgram ();

  bool SetupWidgetShadowProgram ();

  bool SetupWidgetDebugProgram ();
  
  bool SetupPrimitiveProgram ();

  bool SetupFrameInnerProgram ();

  bool SetupFrameOuterProgram ();

  bool SetupFrameImageProgram ();

  bool SetupFrameShadowProgram ();

  RefPtr<GLSLProgram> widget_text_program_;

  RefPtr<GLSLProgram> primitive_program_;

  RefPtr<GLSLProgram> widget_triangle_program_;

  RefPtr<GLSLProgram> widget_simple_triangle_program_;

  RefPtr<GLSLProgram> widget_inner_program_;

  RefPtr<GLSLProgram> widget_split_inner_program_;

  RefPtr<GLSLProgram> widget_outer_program_;

  RefPtr<GLSLProgram> widget_image_program_;

  RefPtr<GLSLProgram> widget_line_program_;

  RefPtr<GLSLProgram> widget_shadow_program_;

  RefPtr<GLSLProgram> widget_debug_program_;
  
  RefPtr<GLSLProgram> frame_inner_program_;

  RefPtr<GLSLProgram> frame_outer_program_;

  RefPtr<GLSLProgram> frame_image_program_;

  RefPtr<GLSLProgram> frame_shadow_program_;

  GLint locations_[LocationLast];

  RefPtr<GLBuffer<UNIFORM_BUFFER> > widget_matrices_ubo_;

  RefPtr<GLBuffer<UNIFORM_BUFFER> > frame_matrices_ubo_;

  // the offset of uniform block in shaders
  GLint widget_matrices_ubo_offset_[3];

  GLint widget_matrices_ubo_size_[3];

  GLint widget_matrices_ubo_type_[3];

  GLint widget_matrices_ubo_total_size_;

  GLint frame_matrices_ubo_offset_[3];

  GLint frame_matrices_ubo_size_[3];

  GLint frame_matrices_ubo_type_[3];

  GLint frame_matrices_ubo_total_size_;

  glm::mat4 current_widget_projection_matrix_;

  glm::mat4 current_widget_view_matrix_;

  glm::mat3 current_widget_model_matrix_;

  std::stack<glm::mat4> widget_projection_matrix_stack;

  std::stack<glm::mat4> widget_view_matrix_stack;

  std::stack<glm::mat3> widget_model_matrix_stack;

  static const GLuint kFrameMatricesBindingPoint = 1;

  static const GLuint kWidgetMatricesBindingPoint = 2;

  static const char* widget_text_vertex_shader;

  static const char* widget_text_fragment_shader;

  static const char* primitive_vertex_shader;

  static const char* primitive_fragment_shader;

  static const char* widget_triangle_vertex_shader;

  static const char* widget_triangle_geometry_shader;

  static const char* widget_triangle_fragment_shader;

  static const char* widget_simple_triangle_vertex_shader;

  static const char* widget_simple_triangle_fragment_shader;

  static const char* widget_inner_vertex_shader;

  static const char* widget_inner_fragment_shader;

  static const char* widget_split_inner_vertex_shader;

  static const char* widget_split_inner_fragment_shader;

  static const char* widget_outer_vertex_shader;

  static const char* widget_outer_geometry_shader;

  static const char* widget_outer_fragment_shader;

  static const char* widget_line_vertex_shader;

  static const char* widget_line_fragment_shader;

  static const char* widget_image_vertex_shader;

  static const char* widget_image_fragment_shader;

  static const char* widget_shadow_vertex_shader;

  static const char* widget_shadow_geometry_shader;

  static const char* widget_shadow_fragment_shader;

  static const char* widget_debug_vertex_shader;

  static const char* widget_debug_fragment_shader;
  
  static const char* frame_inner_vertex_shader;

  static const char* frame_inner_fragment_shader;

  static const char* frame_outer_vertex_shader;

  static const char* frame_outer_geometry_shader;

  static const char* frame_outer_fragment_shader;

  static const char* frame_image_vertex_shader;

  static const char* frame_image_fragment_shader;

  static const char* frame_shadow_vertex_shader;

  static const char* frame_shadow_geometry_shader;

  static const char* frame_shadow_fragment_shader;

  //static const char* context_vertex_shader;

  //static const char* context_fragment_shader;

};

}
