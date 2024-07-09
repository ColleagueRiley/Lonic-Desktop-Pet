#define RGFW_IMPLEMENTATION
#include "RGFW.h"

#include "render.h"
#include "event.h"


RGFW_vector velocity = RGFW_VECTOR(5, 0);
b8 flipY = 0;

void refresh(RGFW_window* win) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0x00, 0x00, 0x00, 0x00);

    /* draw the textured rectangle */
    draw(RGFW_VECTOR(velocity.x < 0, flipY));

    RGFW_window_swapBuffers(win);
}


int main(void) {
    srand(time(NULL));
    
    RGFW_window* win = RGFW_createWindow("Lonic", RGFW_RECT(0, 0, 171, 102), RGFW_NO_BORDER | RGFW_CENTER | RGFW_TRANSPARENT_WINDOW);
    RGFW_window_swapInterval(win, 1);    

    RGFW_setWindowRefreshCallback(refresh);

    glEnable(GL_TEXTURE_2D);

    createTextureFromImage("lonic.png");
    createTextureFromImage("lonic_hearts.png");

    while (RGFW_window_shouldClose(win) == 0) {
        RGFW_handleEvents(win);

        RGFW_window_move(win, RGFW_VECTOR(win->r.x + velocity.x, win->r.y + velocity.y));
            
        RGFW_area area = RGFW_getScreenSize();

        if ((u32)(win->r.x + win->r.w) > area.w) {
            if ((u32)win->r.y > area.h / 2) {
                velocity.y = 5;
            } else velocity.y = -5;

            velocity.x = -5;
        }
        else if (win->r.x <= 0) {
            if ((u32)win->r.y > area.h / 2) {
                velocity.y = 5;
            } else velocity.y = -5;

            velocity.x = 5;
        }

        if ((u32)(win->r.y + win->r.h + 50) > area.h && velocity.y)
            velocity.y = -5;
        else if (win->r.y <= 0 && velocity.y)
            velocity.y = 5;

        if ((rand() % 400) == 399) {
            if (velocity.x > 0)
                velocity.x = -5;
            else
                velocity.x = 5;
        }

        if ((rand() % 100000) == 999) {
            flipY = !flipY;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0x00, 0x00, 0x00, 0x00);

        /* draw the textured rectangle */
        draw(RGFW_VECTOR(velocity.x < 0, flipY));

        RGFW_window_swapBuffers(win);
    }

    RGFW_window_close(win);
}