
#include <string.h>

void gpInit() { glClearColor(0, 0, 0, 0); }

void gpReshape(int w, int h)
{

  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10.0, 10.0, -10.0, 10.0, -10, 10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  WINDOW_WIDTH = w;
  WINDOW_HEIGHT = h;

}

// auxiliar para grafico com colunas !!!
void gpReshape_(int w, int h)
{
  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 300.0, 0.0, 300.0, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  WINDOW_WIDTH = w;
  WINDOW_HEIGHT = h;
}

double GrausParaRadianos(double angulo){ return angulo * PI / 180; }

double RadianoParaGraus(double rad){ return rad * 180 / PI; }

double PercentEmGraus(double percent)
{

  if(percent > 1)
    percent = percent / 100;

  return percent * 360;

}

void PrintString (char* str, double x, double y)
{

  str = "teste";
  glPushMatrix();
  glRasterPos2f(x, y);

  for(char* p = str; *p ; ++p)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p);

  glPopMatrix();
  glutSwapBuffers();
  glutPostRedisplay();

}

void gpDrawGraphicP ()
{

  double i, j, k, l;
  double value1 = GrausParaRadianos( PercentEmGraus( DATA[0]));
  double value2 = GrausParaRadianos( PercentEmGraus( DATA[1]));
  double value3 = GrausParaRadianos( PercentEmGraus( DATA[2]));
  double value4 = GrausParaRadianos( PercentEmGraus( DATA[3]));

  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(INICOORDX, INICOORDY);

  for(i = 0; i <= value1; i += 0.0001)
  {
    glColor3f(1, 0, 0);
    glVertex2f(GP_RADIUS * cos(i) + INICOORDX,
              GP_RADIUS * sin(i) + INICOORDY);
  }

  for(j = i; j <= value2 + value1 ; j += 0.0001)
  {
    glColor3f(0, 1, 0);
    glVertex2f(GP_RADIUS * cos(j) + INICOORDX,
              GP_RADIUS * sin(j) + INICOORDY);
  }

  for(k = j; k <= value3 + j; k += 0.0001)
  {
    glColor3f(1, 0, 1);
    glVertex2f(GP_RADIUS * cos(k) + INICOORDX,
              GP_RADIUS * sin(k) + INICOORDY);
  }

  for(l = k; l <= value4 + k ; l += 0.0001)
  {
    glColor3f(0, 0, 1);
    glVertex2f(GP_RADIUS * cos(l) + INICOORDX,
              GP_RADIUS * sin(l) + INICOORDY);
  }

  glEnd();
  glFlush();

}

void gpDrawColumn (){

  float iniY = 30.0;
  float iniX = 30.0;
  float x1 = 40;
  float x2 = 60;

  glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    PrintString("teste", 30.0, 30.0);

    // eixo y
    glVertex2f(iniY, iniY);
    glVertex2f(iniY, 250.0);

  glEnd();
  glFlush();

  for(float y = iniY; y <= 250.0; y += 20.0)
  {

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);

    // eixo x
    glVertex2f(iniX, y);
    glVertex2f(250.0, y);

    glEnd();
    glFlush();

  }

  /*
  * Desenha as colunas
  */
  for(int i = 0; i < 4; ++i)
  {

    glBegin(GL_QUADS);
    glColor3bv(&COLOURS[i]);

    glVertex2f(x1 , iniY);
    glVertex2f(x2 , iniY);

    glVertex2f(x2, (DATA[i]) + iniX);
    glVertex2f(x1, (DATA[i]) + iniX);

    glEnd();
    glFlush();

    x1 = x2 + 20;
    x2 = x1 + 20;

  }

}
