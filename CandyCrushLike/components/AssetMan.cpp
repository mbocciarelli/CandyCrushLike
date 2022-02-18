#include "../headers/AssetMan.h"
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

Engine::AssetMan::AssetMan(){

}
Engine::AssetMan::~AssetMan(){

}
void Engine::AssetMan::AddTexture(int id, std::string &filePath, bool wantRepeated){
    auto texture = make_unique<sf::Texture>();

    if(texture->loadFromFile(filePath)){
        texture->setRepeated(wantRepeated);
        m_textures[id] = std::move(texture);
    }
}
void Engine::AssetMan::AddFont(int id, std::string &filePath){
    auto font = make_unique<sf::Font>();

    if(font->loadFromFile(filePath)){
        m_fonts[id] = std::move(font);
    }

}
const sf::Texture &Engine::AssetMan::GetTexture(int id) const{
    return *(m_textures.at(id).get());
}
const sf::Font &Engine::AssetMan::GetFont(int id) const{
    return *(m_fonts.at(id).get());
}
