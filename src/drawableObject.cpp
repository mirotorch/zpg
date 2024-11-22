#include "drawableObject.h"

void DrawableObject::Draw()
{
    model->SetModel();

    glm::mat4 m_model = glm::mat4(1.0f);
    if (transformation)
        m_model = transformation->apply(m_model);

    shader->UpdateModel(m_model);
    shader->SetMaterial(material);
    
    shader->UseProgram();
    glDrawArrays(GL_TRIANGLES, 0, model->GetVerticesCount());
    glUseProgram(0);
}

DrawableObject::~DrawableObject()
{
    delete transformation;
    delete model;
}
