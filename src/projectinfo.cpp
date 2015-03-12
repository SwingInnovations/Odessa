#include "projectinfo.h"

ProjectInfo::ProjectInfo()
{
    width = 0;
    height = 0;
    type = 0;
    dpi = 0;
    frameCount = 0;
    fps = 0;
}

ProjectInfo(const ProjectInfo &other){
    width = other.width;
    height = other.height;
    type = other.type;
    dpi = other.dpi;
    frameCount = other.frameCount;
    fps = other.fps;
}

ProjectInfo::~ProjectInfo()
{

}

