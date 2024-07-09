enum state {
    NONE = 0,
    HELD = 1,
    PET = 2,
};

enum textures {
    NO_TEXTURE = 0,
    NORMAL = 1,
    HEARTS = 2,
};

RGFWDEF void RGFW_handleEvents(RGFW_window* win);

void RGFW_handleEvents(RGFW_window* win) {
    static u32 state = 0;
    static u32 petCheck = 0;

    while (RGFW_window_checkEvent(win)) {
        switch (win->event.type) {
            case RGFW_quit: break;
            case RGFW_mouseButtonPressed:
                switch (win->event.button) {
                    case RGFW_mouseLeft:
                        state = HELD;
                        break;
                    case RGFW_mouseRight:
                        state = 0;
                        break;
                    default: break;
                }

                break;
            
            case RGFW_mouseEnter:
                petCheck = 1;
                break;
            
            case RGFW_mousePosChanged:
                if (state == HELD)
                    break;
                
                petCheck++;
                
                break;

            case RGFW_mouseLeave:
                petCheck = 0;
                break;
            
            default: break;
        }
    }

    if (petCheck == 6)
        state = PET;
    else if (state == PET && petCheck == 0)
        state = 0;

    glBindTexture(GL_TEXTURE_2D, NORMAL);

    switch (state) {
        case HELD:
            RGFW_window_moveMouse(win, RGFW_VECTOR(win->r.x + (win->r.w / 2), win->r.y + (win->r.h / 2)));
            break;
        case PET:
            glBindTexture(GL_TEXTURE_2D, HEARTS);
            break;
    }
}