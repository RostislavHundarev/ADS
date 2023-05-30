#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double ** randm(int rows, int cols) {
    double ** matrix = (double ** ) malloc(rows * sizeof(double * ));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double * ) malloc(cols * sizeof(double));
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double temp = rand() % 21;
            matrix[i][j] = temp / 10;
        }
    }
    return matrix;
}

double ** mulmr(double coef, double ** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = matrix[i][j] * coef;

            if (matrix[i][j] < 1.0) matrix[i][j] = 0;
            else matrix[i][j] = 1;
        }
    }
    return matrix;
}

void freeMatrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Lab_3_Hundarev_IM-21";

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow) {
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = WHITE_BRUSH;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass( & w)) return 0;

    hWnd = CreateWindow(ProgName,
                        "Lab_3_Hundarev_IM-21",
                        WS_OVERLAPPEDWINDOW,
                        0,
                        0,
                        1100,
                        1200,
                        (HWND) NULL,
                        (HMENU) NULL,
                        (HINSTANCE) hInstance,
                        (HINSTANCE) NULL);


    ShowWindow(hWnd, nCmdShow);

    while (GetMessage( & lpMsg, hWnd, 0, 0)) {
        TranslateMessage( & lpMsg);
        DispatchMessage( & lpMsg);
    }
    return lpMsg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT messg,
                         WPARAM wParam,
                         LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    void arrow(float fi, int px, int py, HDC hdc){
        int lx, ly, rx, ry;
        lx = px - 15 * cos(fi + 0.3);
        rx = px - 15 * cos(fi - 0.3);
        ly = py - 15 * sin(fi + 0.3);
        ry = py - 15 * sin(fi - 0.3);
        MoveToEx(hdc, px, py, NULL);
        LineTo(hdc, lx, ly);
        MoveToEx(hdc, px, py, NULL);
        LineTo(hdc, rx, ry);
}

    void drawArrow(int fromx, int fromy, int tox, int toy, int r, HDC hdc){
        float angleRad = atan2((toy-fromy), (tox-fromx));
        float px = tox - r*cos(angleRad);
        float py = toy - r*sin(angleRad);
        arrow(angleRad, px, py, hdc);
}

    switch (messg) {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, & ps);
            int n = 10;
            char * nn[10] = {"1","2","3","4","5","6","7","8","9","10"};
            int nx[10] = {};
            int ny[10] = {};
            int dist = 200;


            for (int i = 0; i < n; i++) {
                if (i == 0) {
                    nx[i] = 100;
                    ny[i] = 100;
                } else if (i < 4) {
                    nx[i] = nx[i - 1];
                    ny[i] = ny[i - 1] + dist;
                } else if (i < 8) {
                    nx[i] = nx[i - 1] + dist;
                    ny[i] = ny[i - 1];
                } else if (i < 9) {
                    nx[i] = nx[i - 1] - dist * 1.25;
                    ny[i] = ny[i - 1] - dist;
                } else{
                    nx[i] = nx[i - 1] - dist * 1.375;
                    ny[i] = ny[i - 1] - dist;
                }

            }

            int dx = 20, dy = 20, dtx = 5;
            HPEN BPen = CreatePen(PS_SOLID, 3, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            srand(2104);
            double ** T = randm(10, 10);
            double coefficient = 1.0 - 0 * 0.02 - 4 * 0.005 - 0.25;
            double ** A = mulmr(coefficient, T, 10, 10);

            void printGraphMatrix(double **A) {
                printf("Matrix graph:\n");
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        printf("%g ", A[i][j]);
                    }
                    printf("\n");
                }
            }

            void drawPoints(HDC hdc, HPEN hPen, int* nx, int* ny, int n, int dx, int dy, int dtx) {
                SelectObject(hdc, hPen);
                for (int i = 0; i < n; i++) {
                    Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
                    if (i < 9) {
                        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 1);
                    } else {
                        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2, nn[i], 2);
                    }
                }
            }

            void drawLines(HDC hdc, int dist, int dx, int dy, int* nx, int* ny) {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (A[i][j] == 1) {
                            if ((nx[j] != ny[i] + 2 * dist) && (nx[j] != nx[i] + 4 * dist - dist * 1.25)){ // not 1 -> 10
                                MoveToEx(hdc, nx[i], ny[i], NULL);
                                LineTo(hdc, nx[j], ny[j]);
                                if (A[j][i] != A[i][j]){
                                    if (nx[j] != nx[i] - 3 * dist){ // not 8 -> 5
                                        drawArrow(nx[i], ny[i], nx[j], ny[j], dx, hdc);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            void brokenLines(HDC hdc, int dist, int dx, int dy, int* nx, int* ny) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (A[i][j] == 1) {
                            double halfDistY = ((ny[j] - ny[i]) / 2) + ny[i];
                            double halfDistX = ((nx[j] - nx[i]) / 2) + nx[i];

                            if (A[i][j] == A[j][i]) {
                                if (ny[i] + 1 * dist == ny[j] && (nx[i] == nx[j])) { // 2 -> 1
                                    drawArrow(nx[i],ny[i], nx[j], ny[j], dx, hdc);
                                    MoveToEx(hdc, nx[j] + dx / 2, ny[j] + dy / 2, NULL);
                                    LineTo(hdc, nx[i] + dx * 2 , halfDistY);
                                    LineTo(hdc, nx[i], ny[i]);
                                    drawArrow(nx[i] + dx * 2 , halfDistY, nx[i], ny[i], dx, hdc);
                                } else if (nx[i] + 1 * dist == nx[j] && (ny[i] == ny[j])){  // 5 -> 4 or 8 -> 7
                                    drawArrow(nx[i],ny[i], nx[j], ny[j], dx, hdc);
                                    MoveToEx(hdc, nx[j] - dx, ny[j] - dy / 2, NULL);
                                    LineTo(hdc, halfDistX, ny[j] - dy * 2);
                                    LineTo(hdc, nx[i], ny[i]);
                                    drawArrow(halfDistX, ny[j] - dy * 2, nx[i], ny[i], dx, hdc);
                                } else if (ny[i] - dist == ny[j] && (nx[i] + 4 * dist - dist * 1.25 == nx[j])) { // 9 -> 4
                                    drawArrow(nx[i],ny[i], nx[j], ny[j], dx, hdc);
                                    MoveToEx(hdc, nx[j], ny[j], NULL);
                                    LineTo(hdc, halfDistX, halfDistY - 50);
                                    LineTo(hdc, nx[i], ny[i]);
                                    drawArrow(halfDistX, halfDistY - 50, nx[i], ny[i], dx, hdc);
                                } else if ((ny[i] + dist == ny[j]) && (nx[i] + 4 * dist == nx[j])) { // 8 -> 3
                                    drawArrow(nx[i],ny[i], nx[j], ny[j], dx, hdc);
                                    MoveToEx(hdc, nx[j], ny[j], NULL);
                                    LineTo(hdc, halfDistX, halfDistY - 150);
                                    LineTo(hdc, nx[i], ny[i]);
                                    drawArrow(halfDistX, halfDistY - 150, nx[i], ny[i], dx, hdc);
                                }
                            }
                        }
                    }
                }
            }

            void drawArcs(HDC hdc, int dist, int dx, int dy, int* nx, int* ny) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (A[i][j] == 1) {
                            if ((ny[i] == ny[j]) && (nx[j] != nx[i] + dist) && (nx[j] != nx[i] - dist)) {
                                if (nx[j] - 2 * dist == nx[i]) { // 5 -> 7
                                    Arc(hdc, nx[j] + dx / 2, ny[j] - dy * 3, nx[i], ny[i] + 40, nx[i], ny[i], nx[j], ny[j]);
                                    arrow(5.8, nx[j] - dx / 1.4 , ny[j] + dy / 1.5, hdc);
                                }
                                else if (nx[i] - 3 * dist == nx[j] && j < 5) { // 8 -> 5
                                    Arc(hdc, nx[i] + dx / 2, ny[i] - dy * 3, nx[j], ny[j] + 70, nx[j], ny[j], nx[i], ny[i]);
                                    arrow(10, nx[j] + dx / 3 , ny[j] + dy / 1.1, hdc);
                                }
                            } else if ((ny[i] + 2 * dist == ny[j]) & (i < 2) & (j > 7)){ // 1 -> 9
                                Arc(hdc, nx[j] + dist, ny[j] + dy * 2, nx[i] - dist, ny[i] - 2 * dy, nx[j], ny[j], nx[i], ny[i]);
                                arrow(2.8, nx[j] + dx / 2, ny[j] - dy / 2, hdc);
                            }
                        }
                    }
                }
            }

            printGraphMatrix(A);
            drawLines(hdc, dist, dx, dy, nx, ny);
            brokenLines(hdc, dist, dx, dy, nx, ny);
            drawArcs(hdc, dist, dx, dy, nx, ny);
            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            drawPoints(hdc, hPen, nx, ny, n, dx, dy, dtx);
            freeMatrix(T, 10);
            freeMatrix(A, 10);
            DeleteObject(hPen);

            EndPaint(hWnd, & ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
