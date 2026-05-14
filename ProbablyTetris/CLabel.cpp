#include "CLabel.h"

void CLabel::SetReference(std::string* stringToObserve)
{
	m_referenceText = stringToObserve;
}

void CLabel::SetOffset(int leftOffset, int rightOffset)
{
	m_leftOffset = leftOffset;
	m_rightOffset = rightOffset;
}

bool CLabel::InitializeLabel(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr = NULL;

	hr = D3DXCreateFont(d3dDevice, m_height, m_width, m_weight, 1, m_italic, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_fontFamily.c_str(), &m_label);
	if (FALSE(hr)) {
		return false;
	}
	return true;
}

void CLabel::SetText(const std::string& newText)
{
	m_text = newText;
}

void CLabel::ReleaseLabel()
{
	m_label->Release();
	m_label = NULL;

	if (m_referenceText)
		delete m_referenceText;
}

D3DXVECTOR2 CLabel::LabelCenter(int wordLength)
{
	return D3DXVECTOR2((((m_width * wordLength) * m_baseOffset) + m_leftOffset + m_rightOffset) / 2, (m_height / 2));
}

float CLabel::GetTextWidth()
{
	return (m_width * m_text.size()) * m_baseOffset;
}

void CLabel::DrawLabel(LPD3DXSPRITE spriteBrush, D3DXVECTOR2 panelPosition, CTransform transform)
{
	// Calculate center of label
	D3DXVECTOR2 centerPoint = LabelCenter(m_text.size()) + transform.GetPosition();

	//set the position based on the panel position
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0, &transform.GetScaling(), &centerPoint, transform.GetRotation(), &panelPosition);
	spriteBrush->SetTransform(&matrix);

	// Create a rectangle for label font
	RECT labelRect;
	//draw the text label
	if (m_referenceText)
	{
		m_text = (*m_referenceText);
	}
	labelRect.top = transform.GetPosition().y;
	labelRect.bottom = labelRect.top + m_height;
	labelRect.left = transform.GetPosition().x + m_leftOffset;
	labelRect.right = labelRect.left + GetTextWidth() + m_rightOffset;
	m_label->DrawTextA(spriteBrush, m_text.c_str(), m_text.size(), &labelRect, 0, D3DCOLOR_XRGB(m_colors.R, m_colors.G, m_colors.B));
}