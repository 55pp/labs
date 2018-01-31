#include "bulletspool.h"
#include "dropcoinuntildie.h"
#include "inputhandler.h"
#include "level.h"
#include "listentities.h"
#include "memento.h"
#include "menustring.h"
#include "renderconsole.h"
#include "renderwindow.h"
#include "shootstate.h"
#include "view.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

const std::string MAIN_PATH = "/home/konstantin/QtProjects/Pattern/src/";
const std::string MAIN_FONT_PATH = "Resource/Fonts/main_font.ttf";
const std::string BACKGROUND_IMAGE_PATH = "Resource/Images/menu_background.jpg";
const sf::Color BACKGROUND_COLOR = sf::Color(77, 83, 140);
static uint32_t WIDTH_WINDOW = 1024;
static uint32_t HEIGHT_WINDOW = 768;
static std::string TITLE = "SFML works!";
static sf::Font MAIN_FONT;

void
init(sf::RenderWindow& window, const std::string& mode = "")
{
  uint font_size = 20;
  if (!MAIN_FONT.loadFromFile(MAIN_PATH + MAIN_FONT_PATH))
    std::cerr << "Not found font: " << MAIN_PATH + MAIN_FONT_PATH << std::endl;

  std::vector<MenuString> main_menu;
  main_menu.push_back(MenuString("Continue", MAIN_FONT, font_size, 0, 0));
  if (mode == "") {
  }
  main_menu.push_back(MenuString("New game", MAIN_FONT, font_size, 0, 25));
  main_menu.push_back(MenuString("Options", MAIN_FONT, font_size, 0, 45));
  main_menu.push_back(MenuString("Exit", MAIN_FONT, font_size, 0, 65));

  sf::Texture menu_background, stub;
  menu_background.loadFromFile(MAIN_PATH + BACKGROUND_IMAGE_PATH);
  stub.loadFromFile(MAIN_PATH + "Resource/Images/stub.jpg");
  sf::Sprite menuBg(menu_background), options_stub(stub);

  //////////////////////////////МЕНЮ///////////////////
  while (window.isOpen()) {
    sf::Event event;

    std::string command_text = "";

    for (auto& menu_string : main_menu) {
      menu_string.setColor(sf::Color::White);
      sf::Text text_menu = menu_string.text();
      sf::IntRect string_rect = sf::IntRect(text_menu.getGlobalBounds());
      string_rect.top = int((string_rect.top / 768.) * window.getSize().y);
      string_rect.left = int((string_rect.left / 1024.) * window.getSize().x);
      string_rect.height =
        int((string_rect.height / 768.) * window.getSize().y);
      string_rect.width = int((string_rect.width / 1024.) * window.getSize().x);
      if (string_rect.contains(sf::Mouse::getPosition(window))) {
        menu_string.setColor(sf::Color::Blue);
        command_text = text_menu.getString();
      }
    }
    window.clear(sf::Color(129, 181, 221));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (command_text == "New game")
        return;
      if (command_text == "Options") {
        // window.setSize({ 1600, 900 });
        window.draw(options_stub);
        window.display();
        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
          ;
      }
      if (command_text == "Exit") {
        window.close();
        exit(0);
      }
    }

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.draw(menuBg);

    for (auto menu_string : main_menu) {
      window.draw(menu_string.text());
    }

    window.display();
  }
}

int
main()
{
  sf::RenderWindow window(sf::VideoMode(WIDTH_WINDOW, HEIGHT_WINDOW), TITLE,
                          sf::Style::Default);

  //  RenderWindow window({ WIDTH_WINDOW, HEIGHT_WINDOW }, "My title");
  //  RenderConsole console(WIDTH_WINDOW, HEIGHT_WINDOW);

  //  bool render = true;

  init(window);

  Level lvl(MAIN_PATH + "Resource/Level/test.tmx");
  View view(WIDTH_WINDOW, HEIGHT_WINDOW);
  InputHandler control;

  ListEntities visor(lvl);

  //  control.setRestartCommand(&visor);
  control.setSaveCommand(&visor);

  ShootState::setVisor(&visor);
  DropCoinUntilDie::setVisor(&visor);
  BulletsPool::getInstance(&lvl);

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;

    double time = clock.getElapsedTime().asMicroseconds();

    clock.restart();
    time = time / 800;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return EXIT_SUCCESS;
      }
    }

    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    //      render = true;
    //    }
    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    //      render = false;
    //    }
    //    std::cout << start_state.returnState()->getPlayer()->position_x_
    //              << std::endl;
    control.inputHandle();
    visor.update(time);
    view.setCameraOnPlayer(visor.getPlayer()->position_x_,
                           visor.getPlayer()->position_y_);

    auto score = "Score:" + std::to_string(visor.getPlayer()->score_);
    sf::Text score_in_text(score, MAIN_FONT, 36);
    auto shift_x = view.getCamera().getCenter().x - (WIDTH_WINDOW >> 1);
    auto shift_y = view.getCamera().getCenter().y - (HEIGHT_WINDOW >> 1);
    score_in_text.setPosition(shift_x, shift_y);

    auto experience = std::to_string(visor.getPlayer()->experience_) + "/" +
                      std::to_string(visor.getPlayer()->level_cap_);
    sf::Text experience_in_text(experience, MAIN_FONT, 36);
    experience_in_text.setPosition(shift_x, shift_y + 36);

    window.setView(view.getCamera());

    window.clear(BACKGROUND_COLOR);
    // lvl.Draw(window.getWindow());

    // visor.draw(window.getWindow());

    // window.display();
    //    if (render) {
    //    std::cout << visor.getPlayer()->score_ << std::endl;
    window.draw(score_in_text);
    window.draw(experience_in_text);
    lvl.Draw(window);
    visor.draw(window);
    window.display();
    //      std::cout << visor.getPlayer()->score_ << std::endl;
    //    window.draw(score_in_text);
    //    } else {
    //      lvl.Draw(console);
    //      visor.draw(console);
    //      console.display();
    //    }
  }

  return EXIT_SUCCESS;
}
