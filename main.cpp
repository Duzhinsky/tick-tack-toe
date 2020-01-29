#include "model.h"
#include "view.h"
#include "controller.h"

#include <thread>

int main(int argc, char** argv) {
    model::GameModel gm(3);
    controller::GameController controller(&gm);
    view::WindowView view(&gm, &controller);
    while(view.is_running()) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}