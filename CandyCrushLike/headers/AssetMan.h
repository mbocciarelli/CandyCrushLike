#pragma once

#include "map"
#include "memory"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Font.hpp"
#include "make_unique.h"

namespace Engine {
    class AssetMan {
    private:
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;
    public:
        AssetMan();
        ~AssetMan();

        void AddTexture(int id, std::string &filePath, bool wantRepeated = false);
        void AddFont(int id, const std::string &filePath);

        const sf::Texture &GetTexture(int id) const;
        const sf::Font &GetFont(int id) const;
    };

}