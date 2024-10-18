#include "drawableObject.h"

void DrawableObject::Draw()
{
    shader->UseProgram();

    glm::mat4 m_model = glm::mat4(1.0f);
    if (t_model) m_model = t_model->apply(m_model);

    glm::mat4 m_view = glm::mat4(1.0f);
    if (t_view) m_view = t_view->apply(m_view);

    glm::mat4 m_projection = glm::mat4(1.0f);
    if (t_projection) m_projection = t_projection->apply(m_projection);

    shader->SetMatrixes(m_model, m_view, m_projection);

    model->BindVBO();
    model->BindVAO();

    glDrawArrays(GL_TRIANGLES, 0, model->GetTriangleCount());
}

DrawableObject::~DrawableObject()
{
    delete t_model;
    delete t_view;
    delete t_projection;
    delete model;
}
