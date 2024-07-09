#include <GL/gl.h>

RGFWDEF void draw(RGFW_vector flip);
RGFWDEF u32 createTextureFromImage(char* file);

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void draw(RGFW_vector flip) {
    float data[] = {
        -1, -1,
        -1, 1,     
        1, -1, 

        1, 1,      
        1, -1,   
        -1, 1,
    };
    
    size_t len = 6 * 2;

    float color[] = {0xFF, 0xFF, 0xFF, 0xFF};
    
    glBegin(GL_TRIANGLES);
    size_t i;
    for (i = 0; i < len; i += 2) {
        glColor4fv(color);
        
        glTexCoord2f(   flip.x == 0 ? (data[i] == 1) : (data[i] == -1), 
                        flip.y == 0 ? (data[i + 1] != 1) : (data[i + 1] != -1)
                    );

        glVertex2fv(&data[i]);
    }

    glEnd();
}

u32 createTextureFromImage(char* file) {
    int w, h;

    int c;
    u8* image = stbi_load(file, &w, &h, &c, 0);

    unsigned int id = 0;

    glBindTexture(GL_TEXTURE_2D, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, w);
    
    glTexImage2D(GL_TEXTURE_2D, 0, c, w, h, 0, (GL_RGB + (c == 4)), GL_UNSIGNED_BYTE, image);

    glBindTexture(GL_TEXTURE_2D, 0);

    free(image);
    return id;
}