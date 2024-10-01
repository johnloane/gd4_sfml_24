#pragma once
#include <memory>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;

public:
	SceneNode();
	void AttachChild(Ptr child);
	Ptr DetachChild(const SceneNode& node);

	void Update(sf::Time dt);

	sf::Vector2f GetWorldPosition() const;
	sf::Transform GetWorldTransform() const;

private:
	virtual void UpdateCurrent(sf::Time dt);
	void UpdateChildren(sf::Time dt);

	//Note draw() is from sf::Drawable and hence the name
	//Do not be tempted to call this method Draw()
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::vector<Ptr> m_children;
	SceneNode* m_parent;
};

