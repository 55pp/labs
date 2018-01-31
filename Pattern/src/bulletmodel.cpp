#include "bulletmodel.h"

BulletModel::BulletModel()
{
  std::string path_to_image =
    "/home/konstantin/QtProjects/Pattern/src/Resource/"
    "Sprites/misc/shoot.png";
  animate_ = std::make_shared<IAnimation>(path_to_image, 3);
}

void
BulletModel::update(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite,
                    int& current_frame)
{
  animate_->action(texture, sprite, current_frame);
}
