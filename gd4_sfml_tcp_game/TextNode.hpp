#pragma once
#include "SceneNode.hpp"
#include "ResourceIdentifiers.hpp"

class TextNode : public SceneNode
{
public:
	explicit TextNode(const FontHolder& fonts, std::string& text);
	void SetString(const std::string& text);

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Text m_text;
};

