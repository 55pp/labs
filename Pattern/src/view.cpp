#include "view.h"

View::View(unsigned width_window, unsigned height_window)
{
  width_ = width_window;
  height_ = height_window;
  view_.reset(sf::FloatRect(0, 0, width_, height_));
}

void
View::setCameraOnPlayer(const double& x_coord, const double& y_coord)
{
  double x_tmp = x_coord;
  double y_tmp = y_coord;
  //  if (x < width / 2)
  //    x_tmp = width / 2;
  //  if (y < height / 2)
  //    y_tmp = height / 2;

  view_.setCenter(float(x_tmp), float(y_tmp));
}

const sf::View&
View::getCamera()
{
  return view_;
}
