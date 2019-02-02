#pragma once
#include <map>
#include <cassert>
#include <utility>
#include <memory>
namespace sf { class Texture; }		/* Forward decleration of SFML */

/*
This class manages resources (Audio/Sprites/...).
Resources are identified by a chosen unique Identifier (string/int/...).
*/

template<typename Identifier>
class TextureHolder
{
public:
	TextureHolder();

	void						load(const Identifier identifier, const std::string fileName);
	sf::Texture&				get(const Identifier identifier) const;

private:
	void						insertResource(Identifier id, std::unique_ptr<sf::Texture> texture);

private:
	std::map<Identifier, std::unique_ptr<sf::Texture>> textureMap;
};

#include "TextureHolder.inl"