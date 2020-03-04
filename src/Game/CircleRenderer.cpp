#include "CircleRenderer.h"

void CircleRenderer::onDraw(SDL_Renderer* _renderer)
{
	glm::vec2 position = glm::vec2(
		getEntity()->transform.position.x * nodeSize + nodeSize / 2,
		getEntity()->transform.position.z * nodeSize + nodeSize / 2);

	float size = getEntity()->transform.scale.x * nodeSize / 2;

	// Fill
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	for (float y = -size; y < size; ++y)
	{
		for (float x = -size; x < size; ++x)
		{
			if (hypotf(x, y) < size)
			{
				SDL_RenderDrawPointF(_renderer, position.x + x, position.y + y);
			}
		}
	}

	// Outline
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	for (float t = 0; t < 2 * M_PI; t += 1.0f / size)
	{
		SDL_RenderDrawPointF(_renderer, position.x + size * sinf(t), position.y + size * cosf(t));
	}
}
