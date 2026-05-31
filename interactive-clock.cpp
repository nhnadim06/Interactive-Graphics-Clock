//============================================================
// University of Asia Pacific
// Department of Computer Science and Engineering
// Course: CSE 426 | Lab Assignment
// Title: Interactive Graphics Clock System
//
// Algorithms Used:
//   - Bresenham's Line Drawing Algorithm (Clock Hands)
//   - Midpoint Circle Drawing Algorithm (Clock Face)
//
//Developed by: Mohammad Nazmul Hossain Nadim
//Faulty: Md Rasheduzzaman | Lecturer | UAP | CSE Department
//
// Compatible: Windows & macOS
// Build with VS Code using OpenGL + GLUT/freeglut
//============================================================

#ifdef _WIN32
  #include <windows.h>
#endif

#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <cstring>

//------------------------------------------------------------
// Window & Clock Configuration
//------------------------------------------------------------
const int WIN_W = 600;
const int WIN_H = 600;
const int CX    = 300;
const int CY    = 300;
const int R_OUTER  = 240;
const int R_FACE   = 220;
const int R_INNER  = 200;
const float PI     = 3.14159265f;

//------------------------------------------------------------
// draw_pixel
//------------------------------------------------------------
void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

//------------------------------------------------------------
// Bresenham's Line Drawing Algorithm
//------------------------------------------------------------
void bresLine(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int absDx = (dx < 0) ? -dx : dx;
    int absDy = (dy < 0) ? -dy : dy;
    int incX  = (dx >= 0) ? 1 : -1;
    int incY  = (dy >= 0) ? 1 : -1;
    int x = x1, y = y1;

    if (absDx >= absDy)
    {
        int e    = 2 * absDy - absDx;
        int inc1 = 2 * (absDy - absDx);
        int inc2 = 2 * absDy;
        drawPixel(x, y);
        for (int i = 0; i < absDx; i++)
        {
            if (e >= 0) { y += incY; e += inc1; }
            else         {            e += inc2; }
            x += incX;
            drawPixel(x, y);
        }
    }
    else
    {
        int e    = 2 * absDx - absDy;
        int inc1 = 2 * (absDx - absDy);
        int inc2 = 2 * absDx;
        drawPixel(x, y);
        for (int i = 0; i < absDy; i++)
        {
            if (e >= 0) { x += incX; e += inc1; }
            else         {            e += inc2; }
            y += incY;
            drawPixel(x, y);
        }
    }
}

//------------------------------------------------------------
// Thick line — bresLine multiple times
//------------------------------------------------------------
void thickBresLine(int x1, int y1, int x2, int y2, int thickness)
{
    float dx = (float)(x2 - x1);
    float dy = (float)(y2 - y1);
    float len = sqrtf(dx*dx + dy*dy);
    if (len == 0) return;
    float px = -dy / len;
    float py =  dx / len;
    int half = thickness / 2;
    for (int t = -half; t <= half; t++)
    {
        int ox1 = x1 + (int)(px * t);
        int oy1 = y1 + (int)(py * t);
        int ox2 = x2 + (int)(px * t);
        int oy2 = y2 + (int)(py * t);
        bresLine(ox1, oy1, ox2, oy2);
    }
}

//------------------------------------------------------------
// Midpoint Circle Drawing Algorithm
//------------------------------------------------------------
void midpointCircle(int cx, int cy, int r)
{
    if (r <= 0) return;
    int x = 0;
    int y = r;
    float d = 1.25f - r;

    auto plotCirclePoints = [&](int px, int py)
    {
        drawPixel(cx + px, cy + py);
        drawPixel(cx - px, cy + py);
        drawPixel(cx + px, cy - py);
        drawPixel(cx - px, cy - py);
        drawPixel(cx + py, cy + px);
        drawPixel(cx - py, cy + px);
        drawPixel(cx + py, cy - px);
        drawPixel(cx - py, cy - px);
    };

    plotCirclePoints(x, y);
    while (x < y)
    {
        if (d < 0) { d += 2.0f * x + 3.0f; }
        else       { d += 2.0f * (x - y) + 5.0f; y--; }
        x++;
        plotCirclePoints(x, y);
    }
}

//------------------------------------------------------------
// drawClockFace
//------------------------------------------------------------
void drawClockFace()
{
    // === Orange/Gold outer glow ring ===
    glPointSize(4.0f);
    for (int i = R_FACE + 2; i <= R_FACE + 8; i++) {
        glColor3f(1.0f, 0.85f, 0.15f);
        midpointCircle(CX, CY, i);
    }
    glPointSize(3.5f);
    for (int i = R_FACE + 9; i <= R_OUTER; i++) {
        float t = (float)(i - R_FACE - 9) / (R_OUTER - R_FACE - 9);
        glColor3f(1.0f, 0.55f - 0.2f*t, 0.05f);
        midpointCircle(CX, CY, i);
    }
    glPointSize(3.0f);
    for (int i = R_OUTER + 1; i <= R_OUTER + 6; i++) {
        float t = (float)(i - R_OUTER) / 6.0f;
        glColor3f(0.65f - 0.5f*t, 0.20f - 0.15f*t, 0.0f);
        midpointCircle(CX, CY, i);
    }

    // === White face border ===
    glColor3f(0.95f, 0.95f, 1.0f);
    glPointSize(2.0f);
    midpointCircle(CX, CY, R_FACE);
    midpointCircle(CX, CY, R_FACE - 1);
    midpointCircle(CX, CY, R_FACE - 2);

    // === Hour tick marks ===
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);
    for (int h = 0; h < 12; h++)
    {
        float angle = h * 30.0f * PI / 180.0f;
        int x1 = CX + (int)((R_FACE - 5)  * sinf(angle));
        int y1 = CY + (int)((R_FACE - 5)  * cosf(angle));
        int x2 = CX + (int)((R_FACE - 22) * sinf(angle));
        int y2 = CY + (int)((R_FACE - 22) * cosf(angle));
        thickBresLine(x1, y1, x2, y2, 3);
    }

    // === Minute tick marks ===
    glColor3f(0.8f, 0.8f, 0.8f);
    glPointSize(1.0f);
    for (int m = 0; m < 60; m++)
    {
        if (m % 5 == 0) continue;
        float angle = m * 6.0f * PI / 180.0f;
        int x1 = CX + (int)((R_FACE - 5)  * sinf(angle));
        int y1 = CY + (int)((R_FACE - 5)  * cosf(angle));
        int x2 = CX + (int)((R_FACE - 13) * sinf(angle));
        int y2 = CY + (int)((R_FACE - 13) * cosf(angle));
        bresLine(x1, y1, x2, y2);
    }

    // === Hour number labels ===
    glColor3f(1.0f, 1.0f, 1.0f);
    int numR = R_FACE - 38;
    char labels[12][3] = {"12","1","2","3","4","5","6","7","8","9","10","11"};
    for (int h = 0; h < 12; h++)
    {
        float angle = h * 30.0f * PI / 180.0f;
        int offset = (h == 0 || h >= 10) ? 7 : 4;
        int tx = CX + (int)(numR * sinf(angle)) - offset;
        int ty = CY + (int)(numR * cosf(angle)) - 5;
        glRasterPos2i(tx, ty);
        for (int c = 0; labels[h][c] != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, labels[h][c]);
    }
}

//------------------------------------------------------------
// Draw clock hands
//------------------------------------------------------------
void drawHand(float angleDeg, int length, float backLen,
              float r, float g, float b, int thickness)
{
    float rad = angleDeg * PI / 180.0f;
    int x2 = CX + (int)(length  * sinf(rad));
    int y2 = CY + (int)(length  * cosf(rad));
    int xt = CX - (int)(backLen * sinf(rad));
    int yt = CY - (int)(backLen * cosf(rad));
    glColor3f(r, g, b);
    glPointSize(1.5f);
    thickBresLine(xt, yt, x2, y2, thickness);
}

//------------------------------------------------------------
// Draw center hub
//------------------------------------------------------------
void drawCenter()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(1.5f);
    for (int i = 0; i <= 8; i++) midpointCircle(CX, CY, i);
    glColor3f(1.0f, 0.15f, 0.15f);
    for (int i = 0; i <= 5; i++) midpointCircle(CX, CY, i);
}

//------------------------------------------------------------
// Get hand angles from system time
//------------------------------------------------------------
void getHandAngles(float &hourAngle, float &minAngle, float &secAngle)
{
    time_t now = time(nullptr);
    struct tm *t = localtime(&now);
    int h = t->tm_hour % 12;
    int m = t->tm_min;
    int s = t->tm_sec;
    secAngle  = s * 6.0f;
    minAngle  = m * 6.0f  + s * 0.1f;
    hourAngle = h * 30.0f + m * 0.5f + s * (0.5f / 60.0f);
}

//------------------------------------------------------------
// Display callback
//------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // === Blue gradient background ===
    glPointSize(1.0f);
    for (int i = R_FACE - 2; i >= 0; i--)
    {
        float t = (float)i / (float)(R_FACE - 2); // 1=outer, 0=center
        float r = 0.04f + 0.08f  * (1.0f - t);
        float g = 0.08f + 0.28f  * (1.0f - t);
        float b = 0.38f + 0.47f  * (1.0f - t);
        glColor3f(r, g, b);
        midpointCircle(CX, CY, i);
    }

    // Clock face (glow + border + ticks + numbers)
    drawClockFace();

    // Hand angles
    float hourAngle, minAngle, secAngle;
    getHandAngles(hourAngle, minAngle, secAngle);

    // Hour hand
    drawHand(hourAngle, 115, 20, 1.0f, 1.0f, 1.0f, 6);

    // Minute hand
    drawHand(minAngle,  160, 25, 1.0f, 1.0f, 1.0f, 4);

    // Second hand
    glColor3f(1.0f, 0.15f, 0.15f);
    glPointSize(1.0f);
    {
        float rad = secAngle * PI / 180.0f;
        int x2 = CX + (int)(170 * sinf(rad));
        int y2 = CY + (int)(170 * cosf(rad));
        int xt = CX - (int)(35  * sinf(rad));
        int yt = CY - (int)(35  * cosf(rad));
        bresLine(xt, yt, x2, y2);
    }

    // Center hub
    drawCenter();

    glFlush();
    glutSwapBuffers();
}

//------------------------------------------------------------
// Timer callback
//------------------------------------------------------------
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000, timer, 0);
}

//------------------------------------------------------------
// init
//------------------------------------------------------------
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
}

//------------------------------------------------------------
// main
//------------------------------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("CSE 426 | Interactive Graphics Clock | Developed by Nadim");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}