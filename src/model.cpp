#include "model.h"

Model::Model(const float vertices[], size_t array_length, size_t vertices_count, bool textured)
    : Model(std::vector(vertices, vertices + array_length), vertices_count, textured)
{
}

Model::Model(std::string model_name)
{
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate             // Converts polygons to triangles
                                 | aiProcess_OptimizeMeshes        // Reduces the number of submeshes
                                 | aiProcess_JoinIdenticalVertices // Removes duplicate vertices
                                 | aiProcess_CalcTangentSpace;     // Computes tangents and bitangents

    const aiScene *scene = importer.ReadFile(model_path + model_name, importOptions);
    if (scene && scene->mNumMeshes > 0)
    {
        for (unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[i];
            Model::Vertex *pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);
            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions())
                {
                    pVertices[i].Position[0] = mesh->mVertices[i].x;
                    pVertices[i].Position[1] = mesh->mVertices[i].y;
                    pVertices[i].Position[2] = mesh->mVertices[i].z;
                }

                if (mesh->HasNormals())
                {
                    pVertices[i].Normal[0] = mesh->mNormals[i].x;
                    pVertices[i].Normal[1] = mesh->mNormals[i].y;
                    pVertices[i].Normal[2] = mesh->mNormals[i].z;
                }

                if (mesh->HasTextureCoords(0))
                {
                    pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                    pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                }

                if (mesh->HasTangentsAndBitangents())
                {
                    pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                    pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                    pVertices[i].Tangent[2] = mesh->mTangents[i].z;
                }
            }

            unsigned int *pIndices = nullptr;
            if (mesh->HasFaces())
            {
                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++)
                {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            glGenVertexArrays(1, &vao);

            glGenBuffers(1, &vbo);

            glGenBuffers(1, &ibo);

            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(6 * sizeof(GLfloat)));

            // Tangent for Normal Map
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(8 * sizeof(GLfloat)));

            // Index Buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(vao);

            GLuint err = glGetError();
            if (err != GL_NO_ERROR)
            {
                std::cout << "model loading GL ERROR: " << err << std::endl;
            }
            vertices_count = mesh->mNumFaces * 3;
            delete[] pVertices;
            delete[] pIndices;
        }
    }
    else
    {
        std::cerr << "error loading model " << model_name << std::endl;
        exit(1);
    }
}

Model::Model(std::vector<float> vertices, size_t vertices_count, bool textured)
{
    this->vertices_count = vertices_count;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    if (textured)
    {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 3));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 6));
    }
    else
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid *)(3 * sizeof(float)));
    }
}

void Model::SetModel()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBindVertexArray(this->vao);
}

size_t Model::GetVerticesCount()
{
    return vertices_count;
}

bool Model::HasIbo()
{
    return ibo > 0;
}

Model::~Model()
{
    glDeleteBuffers(1, &vbo);
    if (ibo > 0)
    {
        glDeleteBuffers(1, &ibo); 
    }
    glDeleteVertexArrays(1, &vao);

}