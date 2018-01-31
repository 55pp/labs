#include "coin.h"
#include "player.h"

Coin::Coin(double x, double y, int w, int h)
  : Loot("Coin", std::move(x), std::move(y), std::move(w), std::move(h))
{
  std::string path_to_image =
    "/home/konstantin/QtProjects/Pattern/src/Resource/"
    "Sprites/misc/collect-feedback.png";
  animate_ = std::make_shared<IAnimation>(path_to_image, 4);
}

Coin::Coin(sf::FloatRect rect)
  : Loot("Coin", rect)
{
  std::string path_to_image =
    "/home/konstantin/QtProjects/Pattern/src/Resource/"
    "Sprites/misc/collect-feedback.png";
  animate_ = std::make_shared<IAnimation>(path_to_image, 4);
}

void
Coin::execute(std::shared_ptr<Player>& actor)
{
  ++actor->score_;
}
