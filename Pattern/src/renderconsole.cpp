#include "renderconsole.h"
#include "dummy.h"

RenderConsole::RenderConsole(const size_t& width, const size_t& height)
{
  auto width_c = width >> 4;
  auto height_c = height >> 4;
  for (size_t i = 0; i < height_c; ++i) {
    std::vector<char> line;
    for (size_t j = 0; j < width_c; ++j) {
      line.push_back(' ');
    }
    tiles_.push_back(line);
  }
  system("clear");
  s_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch());
}

void
RenderConsole::draw(sf::Sprite& sprite, std::string&& name_object)
{

  size_t pos_x = size_t(sprite.getGlobalBounds().left) >> 4;
  size_t pos_y = size_t(sprite.getGlobalBounds().top) >> 4;
  if (name_object == "Player")
    tiles_[pos_y][pos_x] = '*';
  else if (name_object == "LootBox")
    tiles_[pos_y][pos_x] = 'L';
  else if (name_object == "Bullet")
    tiles_[pos_y][pos_x] = 'B';
  else
    tiles_[pos_y][pos_x] = '1';
}

void
RenderConsole::display()
{
  msec_ = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()) -
          s_time_;
  if (msec_ < static_cast<std::chrono::milliseconds>(20)) {
    return;
  }
  s_time_ = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::system_clock::now().time_since_epoch());
  system("clear");
  for (auto line : tiles_) {
    for (auto el : line) {
      std::cout << el;
    }
    std::cout << std::endl;
  }
  clear();
}

void
RenderConsole::clear()
{
  for (auto& line : tiles_)
    for (auto& el : line)
      el = ' ';
}
