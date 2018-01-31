#include "playsound.h"
#include "enemy.h"

void
PlaySound::visit(Enemy* target)
{
  (void)target;
  sf::SoundBuffer buffer;
  if (!buffer.loadFromFile(
        "/home/konstantin/QtProjects/Pattern/src/Resource/Sound/dieSound.wav"))
    std::cerr << "File not found" << std::endl;
  std::cout << "play" << std::endl;
  sf::Sound sound;
  sound.setBuffer(buffer);
  sound.setVolume(100);
  sound.play();
}
