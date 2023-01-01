#include "draw.h"

#include "my_math.h"
#include "vec2d.h"

double xRatio, yRatio;

void setColor(const Color& color)
{
    glColor3f(color.r, color.g, color.b);
}

void setVertex(const Vec2d& u)
{
    glVertex2f(u.x * xRatio, -1 + u.y * yRatio);
}

void initDraw(GLFWwindow* w, const Scene& scene)
{
    int width, height;

    glfwMakeContextCurrent(w);
    glfwGetFramebufferSize(w, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double min = std::min((double) width / scene.size.x * 2, (double) height / scene.size.y * 2);

    xRatio = min / width;
    yRatio = min / height;
}

void drawBackground(GLFWwindow* w, const Scene& scene)
{
    setColor(scene.backColor);

    glBegin(GL_QUADS);

    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);

    glEnd();
}

void drawCircle(const Vec2d& pos, double radius)
{
    glBegin(GL_TRIANGLES);

    const int N = 100;
    for(int i = 0; i < N; ++i)
    {
        double curr = i * TAU / N;
        double next = (i + 1) * TAU / N;

        setVertex(pos + Vec2d::fromPolar(curr, radius));
        setVertex(pos + Vec2d::fromPolar(next, radius));
        setVertex(pos);
    }
    glEnd();
}

void drawScene(GLFWwindow* w, const Scene& scene)
{
    initDraw(w, scene);
    drawBackground(w, scene);

    setColor(Color(0.1, 0.3, 0.4));
    drawCircle(Vec2d(0, 5), 10);

    setColor(Color(0.8, 0, 0));
    drawCircle(Vec2d(0, 5), 5);

    glfwSwapBuffers(w);
}
