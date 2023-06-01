#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double ** randm(int rows, int cols) {
    double ** matrix = (double ** ) malloc(rows * sizeof(double * ));
    if(matrix == NULL) return NULL;

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double * ) malloc(cols * sizeof(double));
        if(matrix[i] == NULL) {
            for(int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return NULL;
        }
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
    double ** result = (double ** ) malloc(rows * sizeof(double * ));
    if(result == NULL) return NULL;

    for (int i = 0; i < rows; i++) {
        result[i] = (double * ) malloc(cols * sizeof(double));
        if(result[i] == NULL) {
            for(int j = 0; j < i; j++)
                free(result[j]);
            free(result);
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrix[i][j] * coef;

            if (result[i][j] < 1.0) result[i][j] = 0;
            else result[i][j] = 1;
        }
    }
    return result;
}

double ** mirrorMatrix(double ** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = i+1; j < cols; j++) {
            if (matrix[i][j] == 1) {
                matrix[j][i] = 1;
            }
        }
    }

    return matrix;
}

double ** cloneMatrix(double ** matrix, double ** matrixToCopy, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = matrixToCopy[i][j];
        }
    }
    return matrix;
}

void print2LengthWays(double** matrix, int rows, int cols) {
    printf("\n\n-- 2 length ways --\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                for (int k = 0; k < cols; k++) {
                    if (matrix[j][k] == 1) {
                        printf("[ %d -> %d -> %d ] ", i + 1, j + 1, k + 1);
                    }
                }
            }
        }
        printf("\n\n");
    }
}

void print3LengthWays(double** matrix, int rows, int cols) {
    printf("\n\n--- 3 length ways ---\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1) {
                for (int count1 = 0; count1 < cols; count1++) {
                    if (matrix[j][count1] == 1) {
                        for (int count2 = 0; count2 < cols; count2++) {
                            if (matrix[count1][count2] == 1) {
                                printf("[ %d -> %d -> %d -> %d ] ", i + 1, j + 1, count1 + 1, count2 + 1);
                            }
                        }
                    }
                }
            }
        }
        printf("\n\n");
    }
}

void graphPower(double** matrix, double** mirror_matrix, int numVertices, int numEdges) {
    int positiveDegreeCount = 0, negativeDegreeCount = 0, hangingTopCount = 0;

    printf("Graph powesr:\n\n");

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numEdges; j++) {
            positiveDegreeCount += (int)(matrix[i][j] == 1);
        }
        printf("Top: %d, Positive degree: %d\n", i + 1, positiveDegreeCount);
        positiveDegreeCount = 0;
    }

    printf("\n");

    for (int i = 0; i < numEdges; i++) {
        for (int j = 0; j < numVertices; j++) {
            negativeDegreeCount += (int)(matrix[j][i] == 1);
        }
        printf("Top: %d, Negative degree: %d\n", i + 1, negativeDegreeCount);
        negativeDegreeCount = 0;
    }

    printf("\n");

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numEdges; j++) {
            hangingTopCount += (int)(mirror_matrix[i][j] == 1);
        }

        if (hangingTopCount == 1) {
            printf("Top: %d, Hanging top, Degree: %d\n", i + 1, hangingTopCount);
        } else if (hangingTopCount == 0) {
            printf("Top: %d, Isolated top, Degree: %d\n", i + 1, hangingTopCount);
        } else {
            printf("Top: %d, Degree: %d\n", i + 1, hangingTopCount);
        }

        hangingTopCount = 0;
    }
}

void freeMatrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Lab_4_Hundarev_IM-21";

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
                        "Lab_4_Hundarev_IM-21",
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

    void drawBrokenLine(int* nx, int* ny, int i, int j, HDC hdc) {
        bool isLeft = nx[j] < nx[i];
        bool isAbove = ny[j] < ny[i];
        bool isOnLine = nx[j] == nx[i];

        double dx = 20;
        double dy = 20;
        double halfDistY = ((ny[j] - ny[i]) / 2) + ny[i];
        double halfDistX = ((nx[j] - nx[i]) / 2) + nx[i];

        MoveToEx(hdc, nx[i] + dx / 1.5, ny[i] + dy / 1.5, NULL);
        LineTo(hdc, halfDistX, halfDistY + 30 );
        LineTo(hdc, nx[j] + dx / 1.5, ny[j]  + dy / 1.5);
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

            double coefficient2 = 1.0 - 0 * 0.005 - 4 * 0.005 - 0.27;
            double ** A = mulmr(coefficient2, T, n, n);

            double ** B_temp = randm(n, n);
            double ** B_temp2 = cloneMatrix(B_temp, A, n, n);
            double ** B = mirrorMatrix(B_temp2, n, n);

            SelectObject(hdc,KPen);

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
                                if (nx[i] + 1 * dist == nx[j] && (ny[i] == ny[j])){  // 8 -> 7
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

            void drawDirectedGraph(HDC hdc, int dist, int dx, int dy, int* nx, int* ny, int** A, int n) {
                drawLines(hdc, dist, dx, dy, nx, ny);
                brokenLines(hdc, dist, dx, dy, nx, ny);
                drawArcs(hdc, dist, dx, dy, nx, ny);
            }

            void drawUndirectedGraph(double ** graphMatrix) {
                for (int i = 0; i < n; i++) {
                    for  (int j = 0; j < n; j++) {
                        if (B[i][j] == 1 ){
                            MoveToEx(hdc, nx[i] + dx / 1.5, ny[i] + dy / 1.5, NULL);
                            LineTo(hdc, nx[j] + dx / 1.5 , ny[j] + dy / 1.5);
                        }
                        if ( A[i][j] != B[i][j]) {
                           drawBrokenLine(nx, ny, i, j, hdc);
                        }
                    }
                }
            }

            void printGraphMatrix(double ** graphMatrix) {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        printf("%g ", graphMatrix[i][j]);
                    }
                    printf("\n");

                }
                printf("\n");
            }


            double **calculationsOnMatrix(double **matrix, int rows, int cols) {
                printf("\n\nReach matrix:\n");
                double **reach = (double**) malloc(rows * sizeof(double*));
                double **transitiveMatrix = (double**) malloc(rows * sizeof(double*));
                double **connectivityMatrix = (double**) malloc(rows * sizeof(double*));

                for (int i = 0; i < rows; i++) {
                    reach[i] = (double*) malloc(cols * sizeof(double));
                    transitiveMatrix[i] = (double*) malloc(cols * sizeof(double));
                    connectivityMatrix[i] = (double*) malloc(cols * sizeof(double));

                    for (int j = 0; j < cols; j++) {
                        reach[i][j] = matrix[i][j];
                        transitiveMatrix[i][j] = matrix[j][i];
                    }
                }

                for (int k = 0; k < rows; k++) {
                    for (int i = 0; i < cols; i++) {
                        for (int j = 0; j < cols; j++) {
                            reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
                        }
                    }
                }

                // print reach matrix
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("%.0f ", reach[i][j]);
                    }
                    printf("\n");
                }

                printf("\n");

                // calculate power
                double **powered = (double**) malloc(rows * sizeof(double*) + rows * cols * sizeof(double));
                double *cur_ptr = (double*)(powered + rows);
                for (int i = 0; i < rows; i++) {
                    powered[i] = cur_ptr;
                    cur_ptr += cols;
                    for (int j = 0; j < rows; j++) {
                        powered[i][j] = 0;
                        for (int k = 0; k < rows; k++)
                            powered[i][j] += reach[i][k] * reach[k][j];
                    }
                }

                int counter = 1;
                int countery = 1;
                double **components = (double**) malloc(rows * sizeof(double*) + rows * cols * sizeof(double));
                cur_ptr = (double*)(components + rows);
                for (int i = 0; i < rows; i++) {
                    components[i] = cur_ptr;
                    cur_ptr += cols;
                }

                double **used_vertices = (double**) malloc(rows * sizeof(double*) + rows * cols * sizeof(double));
                cur_ptr = (double*)(used_vertices + rows);
                for (int i = 0; i < rows; i++) {
                    used_vertices[i] = cur_ptr;
                    cur_ptr += cols;
                }

                bool all_same_component = true;
                    int previous_component = -1;
                    for (int count = 0; count < rows; count++) {
                        counter = 1;
                        for (int i = 0; i < cols; i++) {
                            if (used_vertices[i][0] == 1) continue;
                            for (int j = 0; j < rows; j++) {
                                if (powered[count][j] != powered[i][j]) break;
                                if (j == rows - 1) {
                                    used_vertices[i][0] = 1;
                                    components[countery][i] = 1;
                                    printf("Top %d has component %d\n", i + 1, countery);
                                    counter++;
                                }
                            }
                        }
                        if (components[countery][0]) {
                            if (previous_component != -1 && previous_component != countery) {
                                all_same_component = false;
                            }
                            previous_component = countery;
                            countery++;
                        }
                    }

                        if (all_same_component) {
                    printf("All nodes of the graph are connected in such a way that they form the same link structure\n");
                    TextOut(hdc, 50, 50, "Strongly connected graph", 25);
                }

                // calculate connectivity
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < rows; j++) {
                        connectivityMatrix[i][j] = (reach[i][j] == 1 && transitiveMatrix[i][j] == 1) ? 1 : 0;
                    }
                }

                printf("\n");
                printf("Connectivity matrix:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < rows; j++) {
                        printf("%.0f ", connectivityMatrix[i][j]);
                    }
                    printf("\n");
                }

                // free memory
                for (int i = 0; i < rows; i++) {
                    free(reach[i]);
                    free(transitiveMatrix[i]);
                    free(connectivityMatrix[i]);
                }
                free(reach);
                free(transitiveMatrix);
                free(connectivityMatrix);
                free(powered);
                free(components);
                free(used_vertices);

                return connectivityMatrix;
            }

            drawDirectedGraph(hdc, dist, dx, dy, nx, ny, A, n);
            drawUndirectedGraph(B);
            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
            drawPoints(hdc, hPen, nx, ny, n, dx, dy, dtx);

            printf("Directed graph:\n");
            printGraphMatrix(A);

            printf("Undirected graph:\n");
            printGraphMatrix(B);

            graphPower(A, B, n, n);
            print2LengthWays(A, n, n);
            print3LengthWays(A, n, n);
            calculationsOnMatrix(A, n, n);

            freeMatrix(A, 10);
            freeMatrix(B, 10);
            freeMatrix(B_temp, 10);
            freeMatrix(B_temp2, 10);
            freeMatrix(T, 10);

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
