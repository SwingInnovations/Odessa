#ifndef PROJECTINFO_H
#define PROJECTINFO_H


class ProjectInfo
{

public:
    ProjectInfo();
    ~ProjectInfo();

    void setWidth(int w);
    void setHeight(int h);
    void setType(int t);
    void setFrameCount(int fc);
    void setFPS(int fps);

    int getWidth()const{return width;}
    int getHeight()const{return height;}
    int getDPI()const{return dpi;}
    int getType()const{return type;}
    int getFrameCount(){return frameCount;}
    int getFPS(){return fps;}

private:
    int width, height;
    int dpi;
    int type;
    int frameCount;
    int fps;
};

#endif // PROJECTINFO_H
