#include "draw.h"

#include "my_math.h"

static double xRatio, yRatio;

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

void drawBall(const Ball& ball)
{
    setColor(ball.col);

    glBegin(GL_TRIANGLES);

    const int N = 100;
    for(int i = 0; i < N; ++i)
    {
        double curr = i * TAU / N;
        double next = (i + 1) * TAU / N;

        setVertex(ball.pos + Vec2d::fromPolar(curr, ball.rad));
        setVertex(ball.pos + Vec2d::fromPolar(next, ball.rad));
        setVertex(ball.pos);
    }

    glEnd();
}

void drawScene(GLFWwindow* w, const Scene& scene)
{
    initDraw(w, scene);
    drawBackground(w, scene);

    for (const Ball& ball : scene.balls)
    {
        drawBall(ball);
    }

    glfwSwapBuffers(w);
}
