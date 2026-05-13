#include "CLabel.h"

bool CLabel::InitializeLabel(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr = NULL;

	hr = D3DXCreateFont(d3dDevice, m_height, m_width, m_weight, 1, m_italic, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_fontFamily, &m_label);
	if (FALSE(hr)) {
		return false;
	}
	return true;
}

void CLabel::ReleaseLabel()
{
	m_label->Release();
	m_label = NULL;
}

D3DXVECTOR2 CLabel::LabelCenter(int wordLength)
{
	return D3DXVECTOR2((m_width * wordLength) / 2, (m_height / 2));
}

void CLabel::DrawLabel(LPD3DXSPRITE spriteBrush, D3DXVECTOR2 panelPosition, CTransform transform)
{
	// Create a rectangle for label font
	RECT labelRect;

	labelRect.top = transform.GetPosition().y;
	labelRect.bottom = labelRect.top + m_height;
	labelRect.left = transform.GetPosition().y;
	labelRect.right = labelRect.left + (m_width * m_wordLength) * 1.25;

	// Calculate center of label
	D3DXVECTOR2 centerPoint = LabelCenter(m_wordLength) + transform.GetPosition();

	//set the position based on the panel position
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &transform.GetScaling(), &centerPoint, transform.GetRotation(), &panelPosition);
	spriteBrush->SetTransform(&matrix);

	//draw the text label
	m_label->DrawTextA(spriteBrush, m_text, m_wordLength, &labelRect, 0, D3DCOLOR_XRGB(m_colors.R, m_colors.G, m_colors.B));
}

void CLabel::DrawLabelAtPosition(LPD3DXSPRITE spriteBrush, LPCSTR drawText, int textWordLength, Colors color, CTransform transform)
{
	// Create a rectangle for label font
	RECT labelRect;

	labelRect.top = 0;
	labelRect.bottom = labelRect.top + m_height;
	labelRect.left = 0;
	labelRect.right = labelRect.left + (m_width * textWordLength) * 1.25;

	// Calculate center of label
	D3DXVECTOR2 centerPoint = LabelCenter(textWordLength) + transform.GetPosition();

	//set the position  based on the panel position
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &transform.GetScaling(), &centerPoint, transform.GetRotation(), &transform.GetPosition());
	spriteBrush->SetTransform(&matrix);

	//draw the text label
	m_label->DrawTextA(spriteBrush, drawText, textWordLength, &labelRect, 0, D3DCOLOR_XRGB(color.R, color.G, color.B));
}