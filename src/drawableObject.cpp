#include "drawableObject.h"

void DrawableObject::Draw()
{
    shader->UseProgram();
    model->SetModel();

    glm::mat4 m_model = glm::mat4(1.0f);
    if (transformation)
        m_model = transformation->apply(m_model);

    shader->UpdateModel(m_model);

    glDrawArrays(GL_TRIANGLES, 0, model->GetVerticesCount());
}

DrawableObject::~DrawableObject()
{
    delete transformation;
    delete model;
}
