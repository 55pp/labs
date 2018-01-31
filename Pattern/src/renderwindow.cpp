#include "renderwindow.h"

RenderWindow::RenderWindow(sf::VideoMode&& video_mode, std::string&& title)
{
  window_ = std::make_shared<sf::RenderWindow>(video_mode, title);
  window_->setFramerateLimit(60);
}

void
RenderWindow::draw(sf::Sprite& sprite, std::string&& name_object)
{
  (void)name_object;
  window_->draw(sprite);
}

void
RenderWindow::display()
{
  window_->display();
}

sf::RenderWindow&
RenderWindow::getWindow()
{
  return *window_;
}

RenderWindow::~RenderWindow()
{
}
