#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//draw circles using a triangle fans
//the more number of sides supplied, the more round the final circle will be
void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides)
{
    
    GLint numberOfVertices = numberOfSides + 2; 
    
    GLfloat doublePi = 2.0f * M_PI;
    GLfloat circleVerticesX[numberOfVertices];
    GLfloat circleVerticesY[numberOfVertices];
    GLfloat circleVerticesZ[numberOfVertices];
    
    //circleVerticesX[0] = x;
    //circleVerticesY[0] = y;
    //circleVerticesZ[0] = z;

    for(int index = 1; index < numberOfVertices; index++)
    {
        //high school trig
        circleVerticesX[index] = x + ( radius * cos(index * doublePi / numberOfSides));
        circleVerticesY[index] = y + ( radius * sin(index * doublePi / numberOfSides));
        circleVerticesZ[index] = z;
    }
    
    GLfloat allCircleVertices[numberOfVertices * 3];
    
    for(int index = 1; index < numberOfVertices; index++)
    {
        allCircleVertices[index * 3] = circleVerticesX[index];
        allCircleVertices[(index * 3) + 1] = circleVerticesY[index];
        allCircleVertices[(index * 3) + 2] = circleVerticesZ[index];
        
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
}

int main (void)
{
    
    GLFWwindow *window; //initializes GL window
    
    //initialize the library
    if ( !glfwInit() )
    {
        return -1;
    }
    
    //creates window mode
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT ,"Tutorial2", NULL, NULL);
    
    if (!window){
        glfwTerminate();
        return -1;
    }
    
    //make the window's context current
    glfwMakeContextCurrent(window);

    //Viewport: part of window that OPENGL will draw in pixels, from normalised to mixels
    glViewport(0.0f, 0.0f,SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION); //project matrix defines property of the camera that views object
    glLoadIdentity(); //replace current matrix with identity matrix. its liek a reset. multiplying a matrix with ID matrix
    //leaves it the same.
    
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);//multiply current matrix with an orthgraphic matrix (represent 3d with 2d)
    glMatrixMode(GL_MODELVIEW);//modelview matrix determines translation, rotation, etc...
    glLoadIdentity();
    
    /*
    GLfloat lineVertices[] =
    {
        200,100,0,
        100,300,0,
        500,50,0,
        320,100,0,
        10,40,0
    };
     */

    GLfloat polygonVertices[] = {
        20,100,0,
        100,100,0,
        500,50,0,
        320,10,0,
        40,40,0
    };
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //determines how polygons will be rasterized
    
    GLfloat triangleVertices[] = {
        320,240,0,
        370,290,0,
        420,240,0,
        370,150,0
    };
    
    //loop until user closes window
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);//clears buffer to preset values
    
        /*
        //line loop
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0,lineVertices);
        glDrawArrays(GL_LINE_LOOP,0, 5);
        glDisableClientState(GL_VERTEX_ARRAY);
        */
        
        /*
        //polygon
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0,polygonVertices);
        glDrawArrays(GL_POLYGON,0, 5);
        glDisableClientState(GL_VERTEX_ARRAY);
        */
        
        /*
        //triangle vertices
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3,GL_FLOAT,0, triangleVertices);
        glDrawArrays(GL_TRIANGLE_FAN,0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);
         */
        
        drawCircle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0,100,40);
        
        //swap front and back buffers
        glfwSwapBuffers(window);
        
        //processes events in the event queue
        glfwPollEvents();
        
    }
    
    //if user closes and leaves while loop, terminate as usual
    glfwTerminate();
    return 0;
    
}