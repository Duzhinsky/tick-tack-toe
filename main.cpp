#include "model.h"
#include "view.h"
#include "controller.h"

#include <thread>

int main(int argc, char** argv) {
    model::GameModel gm;
    controller::GameController controller(&gm);
    view::WindowView view(&gm, &controller);
    view.wait();
    return 0;
}