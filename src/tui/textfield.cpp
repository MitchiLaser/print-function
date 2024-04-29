#include <cstring>
#include <curses.h>
#include <string>
#include <stdexcept>

namespace tui {

class text_input {
private:
  WINDOW *win = NULL;
  std::string content;
  int cursor_position;
  int color_pair;
  int heigth = 0, width = 0;

public:
  // constructor
  text_input(int color_pair, std::string &init_str) {
    this->color_pair = color_pair;
    this->content = init_str;
    this->cursor_position = init_str.length();
  }

  // destructor
  ~text_input() {
    // TODO
  }

  /* Attach Window
   *
   * This function adds a window to the textfield object. In the beginning these objects are declared without a corresponding window 
   */
  void attach_window(WINDOW *newwin){
    this->win = newwin;
    getmaxyx(this->win, this->heigth, this->width);
    if (this->heigth != 1) {
      throw std::runtime_error("Heigth of textfield must be 1");
    }
  }

  void draw(void) {
    // TODO
  }
};

} // namespace tui
