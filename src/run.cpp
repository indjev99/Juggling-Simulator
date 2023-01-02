#include "run.h"

#include "draw.h"
#include "my_math.h"
#include "pattern.h"
#include "scene.h"

#include <cassert>
#include <iostream>
#include <vector>

const double STEPS_PER_SEC = 1000;
const double INITIAL_FPS = 60;

const std::vector<Color> colors = {
    Color(1, 0, 0),
    Color(0, 1, 0),
    Color(0, 0, 1),
    Color(1, 1, 0),
    Color(1, 0, 1),
    Color(0, 1, 1),
    Color(1, 0.5, 0),
    Color(0.5, 0, 1),
    Color(0, 1, 0.5),
    Color(0.5, 1, 0),
    Color(1, 0, 0.5),
    Color(0, 0.5, 1)
};

#define NOBALL -1

void juggle(Scene& scene, const Pattern& pattern, int throws = 10000)
{
    int maxBeats = 0;

    for (int i = 0; i < (int) pattern.size(); ++i)
    {
        const PatternElem& curr = pattern[i];
        const PatternElem& prev = pattern[(i + pattern.size() - 1) % pattern.size()];

        assert(curr.beats >= 0);

        maxBeats = std::max(maxBeats, curr.beats);

        if (curr.beats == 0)
        {
            assert(curr.beatTime >= 0);
            assert(curr.holdTime == 0);
        }
        else if (curr.beats == 1)
        {
            assert(curr.beatTime > 0);
            assert(curr.holdTime > 0);
            assert(curr.holdTime <= curr.beatTime);
        }
        else if (curr.beats == 2)
        {
            assert(curr.beatTime >= 0);
            assert(curr.holdTime >= 0);
            assert(curr.holdTime < curr.beatTime + prev.beatTime);

            if (curr.holdTime == 0)
            {
                const PatternElem& next = pattern[(i + curr.beats) % pattern.size()];
                assert(curr.catchPos == next.catchPos);
                assert(curr.throwPos == next.throwPos);
            }
        }
        else
        {
            assert(curr.beatTime > 0);
            assert(curr.holdTime > 0);
            assert(curr.holdTime < curr.beatTime + prev.beatTime);
        }
    }

    double startTime = 0.1;

    Vec2d handMults[2] = {
        Vec2d(1, 1),
        Vec2d(-1, 1)
    };

    std::vector<int> beatBalls;
    std::vector<double> beatTimes = {startTime};

    for (int i = 0; i < throws + maxBeats; ++i)
    {
        const PatternElem& curr = pattern[i % pattern.size()];

        beatTimes.push_back(beatTimes.back() + curr.beatTime);

        int land = i + curr.beats;

        if ((int) beatBalls.size() <= land) beatBalls.resize(land + 1, NOBALL);

        assert(beatBalls[land] == NOBALL);
        if (curr.beats != 0 && beatBalls[i] == NOBALL)
        {
            beatBalls[i] = scene.addBall(0.05, colors[scene.getBalls().size() % colors.size()], curr.catchPos.pointwise(handMults[i % 2]));
        }

        beatBalls[land] = beatBalls[i]; 
    }

    beatTimes.erase(beatTimes.begin());

    for (int i = 0; i < throws; ++i)
    {
        const PatternElem& curr = pattern[i % pattern.size()];

        if (curr.beats == 0) continue;
        if (curr.beats == 2 && curr.holdTime == 0) continue;

        int land = i + curr.beats;
        const PatternElem& next = pattern[land % pattern.size()];

        int throwHand = i % 2;
        int catchHand = land % 2;
        Vec2d throwPos = curr.throwPos.pointwise(handMults[throwHand]);
        Vec2d catchPos = next.catchPos.pointwise(handMults[catchHand]);
        double throwTime = beatTimes[i];
        double catchTime = beatTimes[land] - next.holdTime;

        // std::cerr << beatBalls[i] << " : " << throwTime << " " << catchTime << " = " << beatTimes[land] << " - " << next.holdTime << std::endl;

        scene.addThrowCatch(beatBalls[i], throwTime, throwPos, catchTime, catchPos);
    }
}

Pattern makePattern(const std::vector<int>& siteswap, double beatTime, double holdTime)
{
    assert(holdTime < 2 * beatTime);

    Pattern pattern(siteswap.size());

    double inX = 0.085;
    double outX = 0.275;
    double handY = 1.2;

    Vec2d rInPos(inX, handY);
    Vec2d rOutPos(outX, handY);

    for (int i = 0; i < (int) pattern.size(); ++i)
    {
        pattern[i].beats = siteswap[i];
        pattern[i].beatTime = beatTime;
        if (pattern[i].beats == 0) pattern[i].holdTime = 0;
        else if (pattern[i].beats == 2) pattern[i].holdTime = 0;
        else pattern[i].holdTime = holdTime;
        pattern[i].throwPos = rInPos;
        pattern[i].catchPos = rOutPos;
    }

    return pattern;
}

std::vector<int> parseSiteswap(const std::string& siteswapStr)
{
    std::vector<int> siteswap;
    for (char c : siteswapStr)
    {
        assert(isdigit(c) || islower(c));
        if (isdigit(c)) siteswap.push_back(c - '0');
        else if (islower(c)) siteswap.push_back(c - 'a');
    }
    return siteswap;
}

void run(GLFWwindow* window)
{
    std::string siteswapStr;
    double beatTime;
    double holdTime;
    double playSpeed;

    std::cin >> siteswapStr >> beatTime >> holdTime >> playSpeed;
    std::vector<int> siteswap = parseSiteswap(siteswapStr);

    Scene scene(Vec2d(2, 3), Color(0.65, 0.65, 0.65));
    scene.setG(Vec2d(0, -9.8));

    Pattern pattern = makePattern(siteswap, beatTime, holdTime);

    juggle(scene, pattern);

    double dt = 1 / STEPS_PER_SEC;
    double fps = INITIAL_FPS;

    double nextTime = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        double time = glfwGetTime();
        drawScene(window, scene);
        nextTime += 1 / fps;
        while (scene.getTime() + dt / 2 < nextTime * playSpeed)
        {
            scene.step(dt);
        }
        double frameTime = glfwGetTime() - time;
        fps = 1 / frameTime;
    }
}
