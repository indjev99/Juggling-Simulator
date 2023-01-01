#include "draw.h"

#include "my_math.h"
#include "vec2d.h"
#include "window_size.h"

const double DEG2RAD = M_PI / 180;

void initDraw(GLFWwindow* w)
{
    float ratio;
    int width, height;

    glfwMakeContextCurrent(w);
    glfwGetFramebufferSize(w, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawCircle(const Vec2d& pos, double radius)
{
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 360; ++i)
    {
        double rad = i * DEG2RAD;
        double rad2 = (i + 1) * DEG2RAD;

        glVertex2f(cos(rad) * radius + pos.x, sin(rad) * radius + pos.y);
        glVertex2f(cos(rad2) * radius + pos.x, sin(rad2) * radius + pos.y);
        glVertex2f(pos.x, pos.y);
    }
    glEnd();
}

void drawBackground(GLFWwindow* w)
{
    double widthHeightRatio = 1.0 * windowWidth / windowHeight;

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);

    glVertex2f(-1.0 * widthHeightRatio, -1.0);
    glVertex2f(1.0 * widthHeightRatio, -1.0);
    glVertex2f(1.0 * widthHeightRatio, 1.0);
    glVertex2f(-1.0 * widthHeightRatio, 1.0);

    glEnd();
}

void drawScene(GLFWwindow* w)
{
    initDraw(w);
    drawBackground(w);

    glColor3f(1, 0, 0);
    drawCircle(Vec2d(0, 0), 0.5);

    glfwSwapBuffers(w);
}
