#ifndef VIEW_H
#define VIEW_H
#include <SFML/Graphics.hpp>

class View
{
public:
  View(unsigned width_window, unsigned height_window);
  void setCameraOnPlayer(const double& x_coord, const double& y_coord);
  const sf::View& getCamera();

private:
  sf::View view_;
  unsigned width_;
  unsigned height_;
};

#endif // VIEW_H
