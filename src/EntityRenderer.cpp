#include "EntityRenderer.h"
#include "Vertex.h"
#include <cmath>
#include <memory>

EntityRenderer::EntityRenderer(TextureAtlas& textureAtlas, const std::string& currentDirectory) : model(textureAtlas.getTextureCoords(currentDirectory + "/c.png")) {}
EntityRenderer::EntityRenderer(SquareModel&& model) : model(model) {}

void EntityRenderer::render(BatchRenderer &batchRenderer, std::shared_ptr<Entity> entity, double partialTicks) {
    constexpr int verticesSize = sizeof(model.vertices) / sizeof(Vertex);
    
    std::unique_ptr<Vertex[]> vertices(new Vertex[verticesSize]);

    for (int i = 0; i < verticesSize; i++) {
        vertices[i] = model.vertices[i];
        vertices[i].position[0] += std::lerp(entity->lastX, entity->x, partialTicks);
        vertices[i].position[1] += std::lerp(entity->lastY, entity->y, partialTicks);
    }
    
    batchRenderer.addModel(vertices.get(), verticesSize, model.indices, sizeof(model.indices) / sizeof(unsigned int));;
}
