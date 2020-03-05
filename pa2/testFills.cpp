#define CATCH_CONFIG_MAIN

#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <vector>

#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"
#include "cs221util/catch.hpp"

#include "borderColorPicker.h"
#include "center.h"
#include "fadeColorPicker.h"
#include "filler.h"
#include "point.h"
#include "solidColorPicker.h"

using namespace std;
using namespace cs221util;

// Whether to write solutions images or test
#define WRITESOLNIMAGES 0

#define IMAGEDIR "images/"
#define SOLNIMGDIR "soln_images/"

// use the following for color picker tests
#define FUNCTORTESTHEIGHT 64
#define FUNCTORTESTWIDTH 64

#define BORDERX 80
#define BORDERY 60
#define BORDERTOLERANCE 0.05
#define BORDERSIZE 3
#define BORDERTESTIMAGE "originals/cloud.png"
#define BORDERFRAMEFREQ 1400

#define FADEX 65
#define FADEY 105
#define FADETOLERANCE 0.05
#define FADETESTIMAGE "originals/canada.png"
#define FADEFRAMEFREQ 1400
#define FADERATE 0.95

#define SOLIDX1 200
#define SOLIDY1 100
#define SOLIDX2 200
#define SOLIDY2 280
#define SOLIDX3 400
#define SOLIDY3 100
#define SOLIDX4 480
#define SOLIDY4 300
#define SOLIDTOLERANCE 0.05
#define SOLIDTESTIMAGE "originals/merfish.png"
#define SOLIDFRAMEFREQ 1400

center getCenter(PNG &img, int x, int y)
{
    return center(x, y, (*img.getPixel(x, y)));
}

PNG getSolidImage()
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    for (int x = 0; x < FUNCTORTESTWIDTH; x++)
    {
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++)
        {
            HSLAPixel *p = img.getPixel(x, y);
            *p = HSLAPixel(120, 0.4, 0.8);
        }
    }
    return img;
}

void deleteConfig(filler::FillerConfig &config)
{
    for (size_t i = 0; i < config.pickers.size(); i++)
    {
        delete config.pickers[i];
    }
}

filler::FillerConfig setupSolidConfig()
{
    filler::FillerConfig config;
    config.img.readFromFile(SOLIDTESTIMAGE);
    config.frameFreq = SOLIDFRAMEFREQ;
    config.tolerance = SOLIDTOLERANCE;

    config.centers.push_back(getCenter(config.img, SOLIDX1, SOLIDY1));
    config.centers.push_back(getCenter(config.img, SOLIDX2, SOLIDY2));
    config.centers.push_back(getCenter(config.img, SOLIDX3, SOLIDY3));
    config.centers.push_back(getCenter(config.img, SOLIDX4, SOLIDY4));

    HSLAPixel fillColor(120, 0.4, 0.8);

    config.pickers.push_back(new solidColorPicker(fillColor));
    config.pickers.push_back(new solidColorPicker(fillColor));
    config.pickers.push_back(new solidColorPicker(fillColor));
    config.pickers.push_back(new solidColorPicker(fillColor));

    return config;
}

void testOrWriteFill(animation anim, string base_name)
{
    PNG result = anim.write(IMAGEDIR + base_name + ".gif");

    if (WRITESOLNIMAGES == 1)
    {
        result.writeToFile(IMAGEDIR + base_name + ".png");
    }
    else
    {
        PNG expected;
        expected.readFromFile(SOLNIMGDIR + base_name + ".png");
        REQUIRE(result == expected);
    }
}

PNG testColorPicker(PNG &img, colorPicker &picker)
{
    int x = FUNCTORTESTWIDTH / 2;
    int y = FUNCTORTESTHEIGHT / 2;
    center ctr = getCenter(img, x, y);
    HSLAPixel px;

    for (int x = 1; x < FUNCTORTESTWIDTH; x = x + x)
    {
        for (int y = 1; y < FUNCTORTESTHEIGHT; y = y + y)
        {
            point p(x, y, ctr);
            px = picker(p);
            // these create the output useful for debugging fills
            cout << "\toperator()(" << x << ", " << y << ") = {" << px.h << ", " << px.s << ", " << px.l << "}" << endl;
        }
    }

    for (int x = 0; x < FUNCTORTESTWIDTH; x++)
    {
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++)
        {
            point newpoint(x, y, ctr);
            HSLAPixel *p = img.getPixel(x, y);
            *p = picker(newpoint);
        }
    }

    return img;
}

void testOrWriteColorPicker(PNG &img, colorPicker &picker, string base_name)
{
    PNG result = testColorPicker(img, picker);
    if (WRITESOLNIMAGES == 1)
    {
        result.writeToFile(IMAGEDIR + base_name + ".png");
    }
    else
    {
        PNG expected;
        expected.readFromFile(SOLNIMGDIR + base_name + ".png");
        REQUIRE(result == expected);
    }
}

/**
 * Test Cases
 */

TEST_CASE("colorPicker::basic solid", "[weight=1][part=colorPicker]")
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    solidColorPicker picker(HSLAPixel(120, 0.4, 0.8));
    testOrWriteColorPicker(img, picker, "solidColorPickerTest");
}

TEST_CASE("colorPicker::basic fade", "[weight=1][part=colorPicker]")
{
    PNG img = getSolidImage();
    fadeColorPicker picker(FADERATE);
    testOrWriteColorPicker(img, picker, "fadeColorPickerTest");
}

TEST_CASE("colorPicker::basic border", "[weight=1][part=colorPicker]")
{
    PNG img = getSolidImage();
    borderColorPicker picker(5, HSLAPixel(240, 1.0, 0.5), img, 0.01);
    testOrWriteColorPicker(img, picker, "borderColorPickerTest");
}

TEST_CASE("fill::solid bfs", "[weight=1][part=fill]")
{

    filler::FillerConfig config = setupSolidConfig();

    animation anim = filler::fillBFS(config);

    testOrWriteFill(anim, "bfs_solid");

    deleteConfig(config);
}

TEST_CASE("fill::solid dfs", "[weight=1][part=fill]")
{

    filler::FillerConfig config = setupSolidConfig();

    animation anim = filler::fillDFS(config);

    testOrWriteFill(anim, "dfs_solid");

    deleteConfig(config);
}

TEST_CASE("fill::border bfs", "[weight=1][part=fill]")
{

    HSLAPixel fillColor(320.0, 0.8, 0.5);

    filler::FillerConfig config;
    config.img.readFromFile(BORDERTESTIMAGE);
    config.frameFreq = BORDERFRAMEFREQ;
    config.tolerance = BORDERTOLERANCE;
    config.centers.push_back(getCenter(config.img, BORDERX, BORDERY));
    config.pickers.push_back(new borderColorPicker(BORDERSIZE, fillColor, config.img, config.tolerance));

    animation anim = filler::fillBFS(config);

    testOrWriteFill(anim, "bfs_border");

    deleteConfig(config);
}

TEST_CASE("fill::border dfs", "[weight=1][part=fill]")
{

    HSLAPixel fillColor(320.0, 0.8, 0.5);

    filler::FillerConfig config;
    config.img.readFromFile(BORDERTESTIMAGE);
    config.frameFreq = BORDERFRAMEFREQ;
    config.tolerance = BORDERTOLERANCE;
    config.centers.push_back(getCenter(config.img, BORDERX, BORDERY));
    config.pickers.push_back(new borderColorPicker(BORDERSIZE, fillColor, config.img, config.tolerance));

    animation anim = filler::fillDFS(config);

    testOrWriteFill(anim, "dfs_border");

    deleteConfig(config);
}

TEST_CASE("fill::fade bfs", "[weight=1][part=fill]")
{

    filler::FillerConfig config;
    config.img.readFromFile(FADETESTIMAGE);
    config.frameFreq = FADEFRAMEFREQ;
    config.tolerance = FADETOLERANCE;
    config.centers.push_back(getCenter(config.img, FADEX, FADEY));
    config.pickers.push_back(new fadeColorPicker(FADERATE));

    animation anim = filler::fillBFS(config);

    testOrWriteFill(anim, "bfs_fade");

    deleteConfig(config);
}

TEST_CASE("fill::fade dfs", "[weight=1][part=fill]")
{

    filler::FillerConfig config;
    config.img.readFromFile(FADETESTIMAGE);
    config.frameFreq = FADEFRAMEFREQ;
    config.tolerance = FADETOLERANCE;
    config.centers.push_back(getCenter(config.img, FADEX, FADEY));
    config.pickers.push_back(new fadeColorPicker(FADERATE));

    animation anim = filler::fillDFS(config);

    testOrWriteFill(anim, "dfs_fade");

    deleteConfig(config);
}
