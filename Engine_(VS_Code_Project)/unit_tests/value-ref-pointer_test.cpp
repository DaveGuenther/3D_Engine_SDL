#include <iostream>
#include <SDL2/SDL.h>

class Vec3dClassD{
    public:
        Vec3dClassD(){x=0.0f, y=0.0f, x=0.0f;}
        Vec3dClassD(const float &x, const float &y, const float &z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
        float x;
        float y;
        float z;
};

class TriangleClassD{
    public:
        TriangleClassD(){}
        TriangleClassD(const Vec3dClassD &p0, const Vec3dClassD &p1, const Vec3dClassD &p2){
        p[0]=p0;
        p[1]=p1;
        p[2]=p2;
    }       
        Vec3dClassD p[3];

};

class Vec3dClassI{
    public:
        Vec3dClassI(){x=0.0f, y=0.0f, x=0.0f;}
        Vec3dClassI(const float &x, const float &y, const float &z){
        this->x=x;
        this->y=y;
        this->z=z;
    }
        float getX() const{return x;}
        float getY() const{return y;}
        float getZ() const{return z;}

        void setX(float x) {this->x=x;}
        void setY(float y) {this->y=y;}
        void setZ(float z) {this->z=z;}        
    
    private:
        float x;
        float y;
        float z;
};




class TriangleClassI{
    public: 
        TriangleClassI(){}
        TriangleClassI(Vec3dClassI &p0,Vec3dClassI &p1, Vec3dClassI &p2){
            p[0]=p0;
            p[1]=p1;
            p[2]=p2;
        }       
    const Vec3dClassI& getPoint(int point) {
        return this->p[point];
    }
    void setPoint(int point, const Vec3dClassI data){
        this->p[point]=data;
    }
    private:
        Vec3dClassI p[3];
};

class TriangleClassP{
    public: 
        TriangleClassP(){}
        TriangleClassP(Vec3dClassI &p0,Vec3dClassI &p1, Vec3dClassI &p2){
            p[0]=p0;
            p[1]=p1;
            p[2]=p2;
        }       
    Vec3dClassI* getPoint(int point) {
        return &(this->p[point]);
    }
    void setPoint(int point, Vec3dClassI* data){
        this->p[point]=*data;
    }
    private:
        Vec3dClassI p[3];
};

void testDirectAccess(int i){
    Vec3dClassD p[3]={Vec3dClassD(i,i*2,i*3),Vec3dClassD(i*4,i*5,i*6),Vec3dClassD(i*7,i*8,i*9)};
    TriangleClassD this_triangle(p[0],p[1],p[2]);

    this_triangle.p[1].y=this_triangle.p[1].y+1;


}

void testIndirectAccess(float i){
    Vec3dClassI p[3]={Vec3dClassI(i,i*2,i*3),Vec3dClassI(i*4,i*5,i*6),Vec3dClassI(i*7,i*8,i*9)};
    TriangleClassI this_triangle(p[0],p[1],p[2]);

    
    this_triangle.setPoint(1, Vec3dClassI(( (this_triangle.getPoint(1)).getX()),
                                        ((this_triangle.getPoint(1)).getY()+1),
                                        ((this_triangle.getPoint(1)).getZ())));

}

void testPointerAccess(float i){
    Vec3dClassI p[3]={Vec3dClassI(i,i*2,i*3),Vec3dClassI(i*4,i*5,i*6),Vec3dClassI(i*7,i*8,i*9)};
    TriangleClassP this_triangle(p[0],p[1],p[2]);

    Vec3dClassI* vec_ptr=this_triangle.getPoint(1);
    vec_ptr->setY(vec_ptr->getY()+1);
    //this_triangle.setPoint(1, vec_ptr);
    
}

int main (int argv, char** args){
    Uint32 start_time, end_time;

    for (int x=0;x<10;x++){
        start_time=SDL_GetTicks();
        for (float i=1.0f;i<=10000000.0f;i=i+1.0f){
            testDirectAccess(i);
        }    
        end_time=SDL_GetTicks();
        std::cout << "DirectAccess: " << end_time-start_time << "ms";

        start_time=SDL_GetTicks();
        for (float i=1.0f;i<=10000000.0f;i=i+1.0f){
            testIndirectAccess(i);
        }   
        end_time=SDL_GetTicks();
        std::cout << "     IndirectCopyAccess: " << end_time-start_time << "ms";

        start_time=SDL_GetTicks();
        for (float i=1.0f;i<=10000000.0f;i=i+1.0f){
            testPointerAccess(i);
        }   
        end_time=SDL_GetTicks();
        std::cout << "     IndirectPointerAccess: " << end_time-start_time << "ms" << std::endl;

    }
    return 0;

};