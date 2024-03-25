#include "ItemPlacementPreview.h"

#include "UI.h"
#include "../TextureLoader.h"



ItemPlacementPreview::ItemPlacementPreview(SDL_Renderer* renderer, std::vector<Turret>* listTurrets, Level* level, int x, int y, int w, int h)
	:m_PlayingZone({x, y, w, h}), m_Level(level), m_ListTurrets(listTurrets)
{
	UI* ui = UI::getInstance();
	m_ItemSelected = ui->getSelectedItem();

	m_WallPreviewTexture = TextureLoader::loadTexture(renderer, "TileWallPreview.bmp");
	m_TurretPreviewTexture = TextureLoader::loadTexture(renderer, "TurretPreview.bmp");
	SDL_SetTextureAlphaMod(m_WallPreviewTexture, 128);
	SDL_SetTextureAlphaMod(m_TurretPreviewTexture, 128);
}



ItemPlacementPreview::~ItemPlacementPreview()
{
}

void ItemPlacementPreview::draw(SDL_Renderer* renderer, int tileSize) const
{
	if (renderer != nullptr && m_PreviewPos != nullptr)
	{
		Vector2D posMouse((float)m_PreviewPos->x / tileSize, (float)m_PreviewPos->y / tileSize);
		int w, h;
		SDL_Texture* currentTexture = *m_ItemSelected == itemEnum::WallItem ? m_WallPreviewTexture : m_TurretPreviewTexture;
		SDL_QueryTexture(currentTexture, NULL, NULL, &w, &h);

		SDL_Rect rect =
		{
			(int)posMouse.x * tileSize,
			(int)posMouse.y * tileSize,
			w,
			h
		};
		SDL_RenderCopy(renderer, currentTexture, NULL, &rect);
	}

}

void ItemPlacementPreview::onMove(int x, int y)
{
	if (*m_ItemSelected != itemEnum::None && isOnPlayingZone(x, y) && 
		(*m_ItemSelected == itemEnum::WallItem && !m_Level->isTileWall(x / 32, y / 32) || 
		(*m_ItemSelected == itemEnum::TurretItem && m_Level->isTileWall(x / 32, y / 32) && !m_Level->isTurret(*m_ListTurrets, x / 32, y / 32)))
		)
	{

		std::cout << "On Playing zone : mouseX = " << x << ", mouseY = " << y << "\n";
		m_LastPreviewPos.x = x;
		m_LastPreviewPos.y = y;

		m_PreviewPos = &m_LastPreviewPos;

		
	}
	else
		m_PreviewPos = nullptr;

}


bool ItemPlacementPreview::isOnPlayingZone(int mouseX, int mouseY) const
{
	if (mouseX > m_PlayingZone.x && mouseX < (m_PlayingZone.x + m_PlayingZone.w) &&
		mouseY > m_PlayingZone.y && mouseY < (m_PlayingZone.y + m_PlayingZone.h))
		return true;

	return false;
}