#ifndef SPRITE_H__
#define SPRITE_H__

#include <SFML/Graphics.hpp>
#include <string>

class SpriteClass
{
protected:

	sf::Texture TextureSprite;
	sf::Sprite SpriteS;
	std::string SpritePath;

	std::string* Data;

public:

	SpriteClass();

	void Init(std::string _SpritePath);
	void Uninit();

	bool LoadImage(std::string _SpritePath);
	const sf::Texture& GetTexture();
	sf::Sprite& GetSprite();
	void SetSprite(sf::Sprite _NewSprite);

};

#endif