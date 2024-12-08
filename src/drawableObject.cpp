#include "drawableObject.h"

int DrawableObject::cnt = 0;

DrawableObject::DrawableObject(Model* model, ShaderProgram* shader, Transformation* transformation, Material material, GLuint texture_unit, Movement* movement)
{
    this->model = model;
    this->shader = shader;
    this->transformation = transformation;
    this->material = material;
    this->texture_unit = texture_unit;
    this->movement = movement;
    this->id = cnt++;
}


DrawableObject::DrawableObject()
{
    this->id = cnt++;
}

void DrawableObject::Draw()
{
    model->SetModel();

    glm::mat4 m_model = glm::mat4(1.0f);
    if (transformation)
        m_model = transformation->apply(m_model);
    if (movement)
    {
        m_model = movement->GetNextPosition()->apply(m_model);
    }

    shader->UpdateModel(m_model);
    shader->SetMaterial(material);

    if (texture_unit > 0)
    {
        shader->SetTextureUnit(texture_unit);
    }

    shader->UseProgram();
    if (model->HasIbo()) 
        glDrawElements(GL_TRIANGLES, model->GetVerticesCount(), GL_UNSIGNED_INT, NULL);
    else
        glDrawArrays(GL_TRIANGLES, 0, model->GetVerticesCount());
    glUseProgram(0);
}

int DrawableObject::GetId()
{
    return this->id;
}

DrawableObject::~DrawableObject()
{
    delete transformation;
    delete model;
    delete movement;
}
