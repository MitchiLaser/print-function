#include <curses.h>
#include <list>
#include <string>

class select_printer{
  private:
    std::list<std::string> options;
    WINDOW *win;
    int heigth = 0, width = 0;  // store the height and the width of the window
    bool active = false;
  public:
    int selected;
    void attach_window(WINDOW *scr);
};
