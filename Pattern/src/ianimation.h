#ifndef IANIMATION_H
#define IANIMATION_H
#include <SFML/Graphics.hpp>
#include <memory>

class IAnimation
{
public:
  IAnimation(const std::string& file_name, int&& frame_count,
             bool repeat = true);
  IAnimation(const std::string& file_name, int&& frame_count, int&& start_frame,
             int&& end_frame, bool repeat = true);
  void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite);
  void action(std::shared_ptr<sf::Texture>& texture, sf::Sprite& sprite,
              int& current_frame);
  ~IAnimation() {}
private:
  int width_frame_;
  int height_frame_;
  int start_frame_;
  int end_frame_;
  int current_frame_;
  bool repeat_;
  std::shared_ptr<sf::Texture> texture_;
};

#endif // IANIMATION_H
