#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
void setcolor(unsigned short color)
{
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hCon,color);
}
int scrflag;
int solvingflag;

struct cubie {
    char c0, c1, c2;
};

struct move {
    char m0, m1;
};

void initialize(struct cubie cube[][3][3]) {//Initializes the cube
    int i, j, k;
    char temp;
    FILE *fp;
    fp = fopen("index.txt", "r");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                fscanf(fp, "%c", &temp);
                cube[i][j][k].c0 = temp;

                fscanf(fp, "%c", &temp);
                cube[i][j][k].c1 = temp;

                fscanf(fp, "%c", &temp);
                cube[i][j][k].c2 = temp;
            }
        }
    }
    fclose(fp);
}

void printcube(struct cubie cube[][3][3]) {
    int i, j, k, m;
    char ch;
    printf("\n");
    for (i = 0; i < 3; i++)//prints U face
    {
        k = 0;
        for (j = 0; j < 6; j++) {
            if (j < 3)
                printf("  ");
            else {
                 ch=cube[2][i][k].c0;
                 switch(ch)
            {
                 case 'G':
                      setcolor(10);
                      break;
                 case 'O':
                      setcolor(12);
                      break;
                 case 'Y':
                      setcolor(14);
                      break;
                 case 'R':
                      setcolor(4);
                      break;
                 case 'W':
                      setcolor(15);
                      break;
                 case 'B':
                      setcolor(9);
                      break;
                 case 'X':
                      setcolor(8);
                 }
                printf("%c ", ch);
                k++;
            }
        }
        printf("\n");
    }

    for (i = 0; i < 3; i++)//prints L,F,R,B face
    {
        for (j = 0; j < 12; j++) {
            if (j % 3 == 0)
                m = 0;
            if (j < 3)
                k = 3;
            else if (j < 6)
                k = 0;
            else if (j < 9)
                k = 1;
            else
                k = 5;
                ch=cube[k][i][m].c0;
                 switch(ch)
            {
                 case 'G':
                      setcolor(10);
                      break;
                 case 'O':
                      setcolor(12);
                      break;
                 case 'Y':
                      setcolor(14);
                      break;
                 case 'R':
                      setcolor(4);
                      break;
                 case 'W':
                      setcolor(15);
                      break;
                 case 'B':
                      setcolor(9);
                      break;
                 case 'X':
                      setcolor(8);                  
                 }
            printf("%c ",ch);
            m++;
        }
        printf("\n");
    }

    for (i = 0; i < 3; i++)//prints D face
    {
        k = 0;
        for (j = 0; j < 6; j++) {
            if (j < 3)
                printf("  ");
            else {
                 ch=cube[4][i][k].c0;
                  switch(ch)
            {
                 case 'G':
                      setcolor(10);
                      break;
                 case 'O':
                      setcolor(12);
                      break;
                 case 'Y':
                      setcolor(14);
                      break;
                 case 'R':
                      setcolor(4);
                      break;
                 case 'W':
                      setcolor(15);
                      break;
                 case 'B':
                      setcolor(9);
                      break;
                 case 'X':
                      setcolor(8);                 
                 }
                printf("%c ", ch);
                k++;
            }
        }
        printf("\n");
    }
    printf("\n");    
    setcolor(15);
}

void rotateface(struct cubie cube[][3][3], char degree[]) {//face rotation-CW,ACW,CW2
    int i, j, k;
    struct cubie temp[3];
    //rotates all the 4 faces connected to the front face & the front face,except the back face
    for (k = 0; k < (degree[1]); k++) {
        for (i = 0; i < 3; i++)
            temp[i] = cube[3][i][2];

        for (i = 0; i < 3; i++)
            cube[3][i][2] = cube[4][0][i];
        for (i = 0, j = 2; i < 3; i++, j--)
            cube[4][0][j] = cube[1][i][0];
        for (i = 0; i < 3; i++)
            cube[1][i][0] = cube[2][2][i];
        for (i = 0, j = 2; i < 3; i++, j--)
            cube[2][2][i] = temp[j];
        //rotates front face
        for (i = 0; i < 3; i++)
            temp[i] = cube[0][i][0];

        for (i = 0; i < 3; i++)
            cube[0][i][0] = cube[0][2][i];
        for (i = 0, j = 2; i < 3; i++, j--)
            cube[0][2][i] = cube[0][j][2];
        for (j = 2; j >= 0; j--)
            cube[0][j][2] = cube[0][0][j];
        for (i = 0, j = 2; i < 3; i++, j--)
            cube[0][0][j] = temp[i];
    }
}

void rotatecube(struct cubie cube[][3][3], int tarray[]) {
    int i = tarray[0], j = tarray[1], k = tarray[2], l = tarray[3],
            m = tarray[4], n = tarray[5];
    int a, b, c;
    struct cubie temp1[3][3], temp2[3];
    if (n == 4) {
        for (a = 0; a < 3; a++)
            for (b = 0; b < 3; b++) {
                temp1[a][b] = cube[i][a][b];
                cube[i][a][b] = cube[j][a][b];
                cube[j][a][b] = cube[k][a][b];
                cube[k][a][b] = cube[l][a][b];
                cube[l][a][b] = temp1[a][b];
            }
    }
    if (n == 3) {
        for (a = 0; a < 3; a++)
            for (b = 0; b < 3; b++) {
                temp1[a][b] = cube[l][a][b];
                cube[l][a][b] = cube[i][a][b];
                cube[i][a][b] = cube[j][a][b];
            }
        cube[4][0][0] = cube[5][2][2];
        cube[4][0][1] = cube[5][2][1];
        cube[4][0][2] = cube[5][2][0];
        cube[4][1][0] = cube[5][1][2];
        cube[4][1][1] = cube[5][1][1];
        cube[4][1][2] = cube[5][1][0];
        cube[4][2][0] = cube[5][0][2];
        cube[4][2][1] = cube[5][0][1];
        cube[4][2][2] = cube[5][0][0];

        cube[5][0][0] = temp1[2][2];
        cube[5][0][1] = temp1[2][1];
        cube[5][0][2] = temp1[2][0];
        cube[5][1][0] = temp1[1][2];
        cube[5][1][1] = temp1[1][1];
        cube[5][1][2] = temp1[1][0];
        cube[5][2][0] = temp1[0][2];
        cube[5][2][1] = temp1[0][1];
        cube[5][2][2] = temp1[0][0];

    }
    //turns the face clockwise by 90 degree
    for (a = 0; a < 3; a++)
        temp2[a] = cube[m][a][0];

    for (a = 0; a < 3; a++)
        cube[m][a][0] = cube[m][2][a];
    for (a = 0, b = 2; a < 3; a++, b--)
        cube[m][2][a] = cube[m][b][2];
    for (a = 0, b = 2; a < 3; a++, b--)
        cube[m][b][2] = cube[m][0][b];
    for (a = 0, b = 2; a < 3; a++, b--)
        cube[m][0][b] = temp2[a];

    //turns the face anticlockwise by 90 degree
    for (c = 0; c < 3; c++) {
        for (a = 0; a < 3; a++)
            temp2[a] = cube[n][a][0];

        for (a = 0; a < 3; a++)
            cube[n][a][0] = cube[n][2][a];
        for (a = 0, b = 2; a < 3; a++, b--)
            cube[n][2][a] = cube[n][b][2];
        for (b = 2; b >= 0; b--)
            cube[n][b][2] = cube[n][0][b];
        for (a = 0, b = 2; a < 3; a++, b--)
            cube[n][0][b] = temp2[a];
    }
}

void transition(struct cubie cube[][3][3], char degree[]) {
    int i, j = 0;
    FILE *fp;
    if(solvingflag){
    fp=fopen("redundantmoves.txt","a");
    fprintf(fp,"%s",degree);
    fclose(fp);
    }
    if (degree[0] == 'R' || degree[0] == 'B' || degree[0] == 'L') {
        int tarray[] = {0, 1, 5, 3, 2, 4};

        if (degree[0] == 'R')
            j = 2;
        else if (degree[0] == 'B')
            j = 1;
        else if (degree[0] == 'L')
            j = 0;

        for (i = j; i < 3; i++)
            rotatecube(cube, tarray);

        rotateface(cube, degree); //face rotation of the new front face

        for (i = 0; i < j + 1; i++)//reset the modified cube with green as center
            rotatecube(cube, tarray);

    } else if (degree[0] == 'D' || degree[0] == 'U') {
        int tarray[] = {0, 4, 5, 2, 1, 3};
        if (degree[0] == 'D')
            j = 2;
        else if (degree[0] == 'U')
            j = 0;
        for (i = j; i < 3; i++)
            rotatecube(cube, tarray);

        rotateface(cube, degree); //face rotation of the new front face
        for (i = 0; i < j + 1; i++)//reset the modified cube with green as center
            rotatecube(cube, tarray);
    } else {
        rotateface(cube, degree); //face rotation of front face
    }
}

void scramble(struct cubie cube[][3][3]) {
    int a, i,k=0;
    char degree[3];
    struct move marray[20];
    char possiblemoves[]={"F1F2F3R1R2R3U1U2U3L1L2L3D1D2D3B1B2B3"};
    for (i = 0; i < 18; i++) {
        marray[i].m0 = possiblemoves[k++];
        marray[i].m1 = possiblemoves[k++];
    }
    i = 0;
    printf("The following moves have been made for scrambling:\n");
    while (i != 20) {
        a = rand() % 18;
        degree[0] = marray[a].m0;
        degree[1] = marray[a].m1;
        degree[2] = '\0';
        printf("%s ",degree);
        transition(cube, degree);
        i++;
    }
    printf("\n");
    printcube(cube);
}

void resettransition(struct cubie cube[][3][3], char degree[], int j) {
    int i;
    FILE *fp;
    if(solvingflag){
    fp=fopen("redundantmoves.txt","a");
    fprintf(fp,"T");
    fclose(fp);
    }
    if (degree[0] == 'R' || degree[0] == 'B' || degree[0] == 'L') {
        int tarray[] = {0, 1, 5, 3, 2, 4};
        for (i = 0; i < j + 1; i++)//reset the modified cube with green as center
            rotatecube(cube, tarray);

    } else if (degree[0] == 'D' || degree[0] == 'U') {
        int tarray[] = {0, 4, 5, 2, 1, 3};

        for (i = 0; i < j + 1; i++)//reset the modified cube with green as center
            rotatecube(cube, tarray);
    }
}

int settransition(struct cubie cube[][3][3], char degree[]) {
    int i, j = 0;
    FILE *fp;
    if(solvingflag){
    fp=fopen("redundantmoves.txt","a");
    fprintf(fp,"S");
    fprintf(fp,"%s",degree);
    fclose(fp);
    }
    if (degree[0] == 'R' || degree[0] == 'B' || degree[0] == 'L') {
        int tarray[] = {0, 1, 5, 3, 2, 4};

        if (degree[0] == 'R')
            j = 2;
        else if (degree[0] == 'B')
            j = 1;
        else if (degree[0] == 'L')
            j = 0;

        for (i = j; i < 3; i++)
            rotatecube(cube, tarray);

    } else if (degree[0] == 'D' || degree[0] == 'U') {
        int tarray[] = {0, 4, 5, 2, 1, 3};
        if (degree[0] == 'D')
            j = 2;
        else if (degree[0] == 'U')
            j = 0;
        for (i = j; i < 3; i++)
            rotatecube(cube, tarray);
    }
    return j;
}

int checkdaisy(struct cubie cube[][3][3]) {
    int a[4] = {0, 1, 2, 1};
    int b[4] = {1, 2, 1, 0};
    int i, m, n, count = 0;
    for (i = 0; i < 4; i++) {
        m = a[i];
        n = b[i];
        if (cube[2][m][n].c0 == 'W')
            count++;
    }
    if (count == 4)
        return (1);
    else
        return (0);
}

void usetr(struct cubie cube[][3][3]) {
    char degree[3];
    while (cube[2][1][2].c0 == 'W') {
        strcpy(degree, "U1");
        transition(cube, degree);
    }
}

void usetl(struct cubie cube[][3][3]) {
    char degree[3];
    while (cube[2][1][0].c0 == 'W') {
        strcpy(degree, "U1");
        transition(cube, degree);
    }
}

void usetm(struct cubie cube[][3][3]) {
    char degree[3];
    while (cube[2][2][1].c0 == 'W') {
        strcpy(degree, "U1");
        transition(cube, degree);
    }
}

void ysetr(struct cubie cube[][3][3]) {
    char degree[3];
    while (cube[5][1][0].c0 == 'W') {
        strcpy(degree, "B1");
        transition(cube, degree);
    }
}

void ysetl(struct cubie cube[][3][3]) {
    char degree[3];
    while (cube[5][1][2].c0 == 'W') {
        strcpy(degree, "B1");
        transition(cube, degree);
    }
}

void daisycross(struct cubie cube[][3][3]) {
    char srdegree[2], degree[3]; //set-reset degree and normal degree
    int i, j, flag;
label1:
    while (!checkdaisy(cube)) {
        for (i = 0; i < 6; i++) {
            flag = 0;
            if (i == 1)
                strcpy(srdegree, "R");
            else if (i == 3)
                strcpy(srdegree, "L");
            else if (i == 4)
                strcpy(srdegree, "D");
            else if (i == 5)
                strcpy(srdegree, "B");
            if (i != 0 && i != 2)
                j = settransition(cube, srdegree);
            if (i != 2 && i != 4) {
                if (cube[0][0][1].c0 == 'W' || cube[0][1][2].c0 == 'W' ||
                        cube[0][2][1].c0 == 'W' || cube[0][1][0].c0 == 'W') {
                    flag = 1;
                    if (cube[0][0][1].c0 == 'W') {
                        strcpy(degree, "F1");
                        transition(cube, degree);
                        usetr(cube);
                        strcpy(degree, "R1");
                        transition(cube, degree);
                    } else if (cube[0][1][2].c0 == 'W') {
                        usetr(cube);
                        strcpy(degree, "R1");
                        transition(cube, degree);
                    } else if (cube[0][2][1].c0 == 'W') {
                        usetm(cube);
                        strcpy(degree, "F1");
                        transition(cube, degree);
                        usetl(cube);
                        strcpy(degree, "L3");
                        transition(cube, degree);
                    } else if (cube[0][1][0].c0 == 'W') {
                        usetl(cube);
                        strcpy(degree, "L3");
                        transition(cube, degree);
                    }
                }
            } else if (i == 4) {
                if (cube[0][0][1].c0 == 'W' || cube[0][1][2].c0 == 'W' ||
                        cube[0][2][1].c0 == 'W' || cube[0][1][0].c0 == 'W') {
                    flag = 1;
                    if (cube[0][0][1].c0 == 'W') {
                        strcpy(degree, "F1");
                        transition(cube, degree);
                        ysetr(cube);
                        strcpy(degree, "R2");
                        transition(cube, degree);

                    } else if (cube[0][1][2].c0 == 'W') {
                        ysetr(cube);
                        strcpy(degree, "R2");
                        transition(cube, degree);
                    } else if (cube[0][2][1].c0 == 'W') {
                        strcpy(degree, "F1");
                        transition(cube, degree);
                        ysetl(cube);
                        strcpy(degree, "L2");
                        transition(cube, degree);
                    } else if (cube[0][1][0].c0 == 'W') {
                        ysetl(cube);
                        strcpy(degree, "L2");
                        transition(cube, degree);
                    }
                }
            }
            if (i != 0 && i != 2)
                resettransition(cube, srdegree, j);
            if (flag == 1)//if any move has been made
                goto label1;
        }
    }
}

int checkwhitecross(struct cubie cube[][3][3])
{
    char temp[]={"GOBR"};
    int a[4] = {0, 1, 2, 1};
    int b[4] = {1, 2, 1, 0};
    int i, m, n, count = 0;
    for (i = 0; i < 4; i++) {
        m = a[i];
        n = b[i];
        if (cube[4][m][n].c0 == 'W'&& cube[4][m][n].c1 == temp[i])
            count++;
    }
    if (count == 4)
        return (1);
    else
        return (0);
}

void whitecross(struct cubie cube[][3][3]) {
    char degree[3];
    int i, j, l, m, n, a[4] = {5, 1, 0, 3}, b[4] = {0, 1, 2, 1}, c[4] = {1, 2, 1, 0};
label1:
    if(checkwhitecross(cube))
        return;
    while (cube[2][0][1].c0 == 'W' || cube[2][1][2].c0 == 'W' ||
            cube[2][2][1].c0 == 'W' || cube[2][1][0].c0 == 'W') {
        if (cube[2][0][1].c0 == 'W')
            j = 0;
        else if (cube[2][1][2].c0 == 'W')
            j = 1;
        else if (cube[2][2][1].c0 == 'W')
            j = 2;
        else if (cube[2][1][0].c0 == 'W')
            j = 3;
        for (i = 0; i < 4; i++) {
            j = j % 4;
            m = b[j];
            n = c[j];
            l = a[j];
            if (cube[2][m][n].c1 == cube[l][1][1].c0) {
                if (l == 5) {
                    strcpy(degree, "B2");
                    transition(cube, degree);
                } else if (l == 1) {
                    strcpy(degree, "R2");
                    transition(cube, degree);
                } else if (l == 0) {
                    strcpy(degree, "F2");
                    transition(cube, degree);
                } else if (l == 3) {
                    strcpy(degree, "L2");
                    transition(cube, degree);
                }
                goto label1;
            } else {
                strcpy(degree, "U1");
                transition(cube, degree);
            }
            j++;
        }
    }
}

int checkbottomlayer(struct cubie cube[][3][3]) {
    int i, j,k=0;
    char check[]={"WRGWGXWGOWRXWXXWOXWBRWBXWOB"};

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (cube[4][i][j].c0 != check[k++])
                return 0;

            if (cube[4][i][j].c1 != check[k++])
                return 0;

            if (cube[4][i][j].c2 != check[k++])
                return 0;
        }
    }
    return 1;
}

int uc1setwhitecorner(struct cubie cube[][3][3], int i, int m, int n) {
    char a[4] = {0, 1, 5, 3};
    int l;
label:
    transition(cube, "U1");
    i--;
    if (i == -1)
        i = 3;
    l = a[i];
    if (cube[l][m][n].c1 == cube[l][1][1].c0)
        return i;
    else
        goto label;
}

int uc2setwhitecorner(struct cubie cube[][3][3], int i, int m, int n) {
    char a[4] = {0, 1, 5, 3};
    int l;
label:
    transition(cube, "U1");
    i--;
    if (i == -1)
        i = 3;
    l = a[i];
    if (cube[l][m][n].c2 == cube[l][1][1].c0)
        return i;
    else
        goto label;
}

void moveseq(struct cubie cube[][3][3], char moveseq[]) {
    char degree[3];
    int i = 0;
    while (moveseq[i] != '\0') {
        degree[0] = moveseq[i];
        degree[1] = moveseq[++i];
        degree[2] = '\0';
        i++;
        transition(cube, degree);
    }
}

void whitecorner(struct cubie cube[][3][3]) {
    char srdegree[2];
    char moveseq00[] = {"F1U1F3"}, moveseq02[] = {"F3U3F1"};
    char moveseq20[] = {"F1U1F3U3"}, moveseq22[] = {"F3U3F1U1"};
    char umoveseq00[] = {"F1U3F3U2"}, umoveseq02[] = {"F3U1F1U2"};
    char dmoveseq20[] = {"L3U3L1U1"}, dmoveseq22[] = {"R1U1R3U3"};
    int i, j, l, m, n;
    char a[4] = {0, 1, 5, 3};
label:
    while (!checkbottomlayer(cube)) {
        for (i = 0; i < 4; i++) {
            l = a[i];
            if (i == 0)
                strcpy(srdegree, "F");
            else if (i == 1)
                strcpy(srdegree, "R");
            else if (i == 2)
                strcpy(srdegree, "B");
            else if (i == 3)
                strcpy(srdegree, "L");
            //upper layer
            if (cube[l][0][0].c0 == 'W' || cube[l][0][2].c0 == 'W' ||
                    cube[l][0][0].c2 == 'W' || cube[l][0][2].c1 == 'W') {
                if (cube[l][0][0].c0 == 'W') {
                    label1:if (cube[l][0][0].c2 != cube[l][1][1].c0) {
                        m = 0;
                        n = 0;
                        i = uc2setwhitecorner(cube, i, m, n);
                    }
                    l = a[i];
                    if (i == 0)
                        strcpy(srdegree, "F");
                    else if (i == 1)
                        strcpy(srdegree, "R");
                    else if (i == 2)
                        strcpy(srdegree, "B");
                    else if (i == 3)
                        strcpy(srdegree, "L");
                    if(strcmp(srdegree,"F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, moveseq00);
                    if(strcmp(srdegree,"F"))
                        resettransition(cube, srdegree, j);
                    goto label;
                } else if (cube[l][0][2].c0 == 'W') {
                    label2:if (cube[l][0][2].c1 != cube[l][1][1].c0) {
                        m = 0;
                        n = 2;
                        i = uc1setwhitecorner(cube, i, m, n);
                    }
                    l = a[i];
                    if (i == 0)
                        strcpy(srdegree, "F");
                    else if (i == 1)
                        strcpy(srdegree, "R");
                    else if (i == 2)
                        strcpy(srdegree, "B");
                    else if (i == 3)
                        strcpy(srdegree, "L");
                    if(strcmp(srdegree,"F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, moveseq02);
                    if(strcmp(srdegree,"F"))
                        resettransition(cube, srdegree, j);
                    goto label;
                } else if (cube[l][0][0].c2 == 'W') {
                    if (cube[l][0][0].c1 != cube[l][1][1].c0) {
                        m = 0;
                        n = 0;
                        i = uc1setwhitecorner(cube, i, m, n);
                    }
                    l = a[i];
                    if (i == 0)
                        strcpy(srdegree, "F");
                    else if (i == 1)
                        strcpy(srdegree, "R");
                    else if (i == 2)
                        strcpy(srdegree, "B");
                    else if (i == 3)
                        strcpy(srdegree, "L");
                    if(strcmp(srdegree,"F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, umoveseq00);
                    moveseq(cube, moveseq00);
                    if(strcmp(srdegree,"F"))
                        resettransition(cube, srdegree, j);
                    goto label;
                } else if (cube[l][0][2].c1 == 'W') {
                    if (cube[l][0][2].c2 != cube[l][1][1].c0) {
                        m = 0;
                        n = 2;
                        i = uc2setwhitecorner(cube, i, m, n);
                    }
                    l = a[i];
                    if (i == 0)
                        strcpy(srdegree, "F");
                    else if (i == 1)
                        strcpy(srdegree, "R");
                    else if (i == 2)
                        strcpy(srdegree, "B");
                    else if (i == 3)
                        strcpy(srdegree, "L");
                    if(strcmp(srdegree,"F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, umoveseq02);
                    moveseq(cube, moveseq02);
                    if(strcmp(srdegree,"F"))
                        resettransition(cube, srdegree, j);
                    goto label;
                }
            }//bottom layer
            else if (cube[l][2][0].c0 == 'W' || cube[l][2][2].c0 == 'W'
                    || cube[l][2][0].c1 == 'W' || cube[l][2][2].c2 == 'W') {
                if (cube[l][2][0].c0 == 'W') {
                    if (strcmp(srdegree, "F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, moveseq20);
                    if (strcmp(srdegree, "F"))
                        resettransition(cube, srdegree, j);
                    goto label1;
                } else if (cube[l][2][2].c0 == 'W') {
                    if (strcmp(srdegree, "F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, moveseq22);
                    if (strcmp(srdegree, "F"))
                        resettransition(cube, srdegree, j);
                    goto label2;
                } else if (cube[l][2][0].c1 == 'W' && cube[l][2][0].c0 != cube[l][1][1].c0) {
                    if (strcmp(srdegree, "F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, dmoveseq20);
                    if (strcmp(srdegree, "F"))
                        resettransition(cube, srdegree, j);
                    goto label1;
                } else if (cube[l][2][2].c2 == 'W' && cube[l][2][2].c0 != cube[l][1][1].c0) {
                    if (strcmp(srdegree, "F"))
                        j = settransition(cube, srdegree);
                    moveseq(cube, dmoveseq22);
                    if (strcmp(srdegree, "F"))
                        resettransition(cube, srdegree, j);
                    goto label2;
                }
            }
        }
    }
}

void bottomlayer(struct cubie cube[][3][3]) {
    if (checkbottomlayer(cube))
        return;
    else if (checkwhitecross(cube)) {
        whitecorner(cube);
        return;
    } else if (checkdaisy(cube)) {
        whitecross(cube);
        whitecorner(cube);
        return;
    } else {
        daisycross(cube);
        whitecross(cube);
        whitecorner(cube);
    }
}

int checkmiddlelayer(struct cubie cube[][3][3]) {
    int a[4] = {0, 1, 5, 3};
    int i, j, l, m;
    for (i = 0; i < 4; i++) {
        l = a[i];
        if (cube[l][1][0].c0 == cube[l][1][1].c0) {
            j = i - 1;
            if (j == -1)
                j = 3;
            m = a[j];
            if (cube[l][1][0].c1 == cube[m][1][1].c0);
            else
                return 0;
        } else
            return 0;
        if (cube[l][1][2].c0 == cube[l][1][1].c0) {
            j = i + 1;
            if (j == 4)
                j = 0;
            m = a[j];
            if (cube[l][1][2].c1 == cube[m][1][1].c0);
            else
                return 0;
        } else
            return 0;
    }
    return 1;
}

int setedge(struct cubie cube[][3][3], int i) {
    char a[4] = {0, 1, 5, 3};
    int l;
label:
    transition(cube, "U1");
    i--;
    if (i == -1)
        i = 3;
    l = a[i];
    if (cube[l][0][1].c0 == cube[l][1][1].c0)
        return i;
    else
        goto label;
}

void middlelayer(struct cubie cube[][3][3]) {
    char srdegree[2];
    int i, j, k, l, m, count;
    char moveseql[] = {"U3L3U1L1U1F1U3F3"};
    char moveseqr[] = {"U1R1U3R3U3F3U1F1"};
    char a[4] = {0, 1, 5, 3};
label:
    while (!checkmiddlelayer(cube)) {
        count = 0;
        for (i = 0; i < 4; i++) {
            l = a[i];
            if (i == 0)
                strcpy(srdegree, "F");
            else if (i == 1)
                strcpy(srdegree, "R");
            else if (i == 2)
                strcpy(srdegree, "B");
            else if (i == 3)
                strcpy(srdegree, "L");
            if (cube[l][0][1].c0 == 'Y' || cube[l][0][1].c1 == 'Y')
                count++;
            else {
                if (cube[l][0][1].c0 != cube[l][1][1].c0)
                    i = setedge(cube, i);
                l = a[i];
                if (i == 0)
                    strcpy(srdegree, "F");
                else if (i == 1)
                    strcpy(srdegree, "R");
                else if (i == 2)
                    strcpy(srdegree, "B");
                else if (i == 3)
                    strcpy(srdegree, "L");
                if (strcmp(srdegree, "F"))
                    k = settransition(cube, srdegree);
                if (cube[0][0][1].c1 == cube[3][1][1].c0)
                    moveseq(cube, moveseql);
                else
                    moveseq(cube, moveseqr);
                if (strcmp(srdegree, "F"))
                    resettransition(cube, srdegree, k);
                goto label;

            }
        }

        if (count == 4) {
            for (i = 0; i < 4; i++) {
                l = a[i];
                if (i == 0)
                    strcpy(srdegree, "F");
                else if (i == 1)
                    strcpy(srdegree, "R");
                else if (i == 2)
                    strcpy(srdegree, "B");
                else if (i == 3)
                    strcpy(srdegree, "L");
                if (cube[l][1][0].c0 == cube[l][1][1].c0) {
                    j = i - 1;
                    if (j == -1)
                        j = 3;
                    m = a[j];
                    if (cube[l][1][0].c1 == cube[m][1][1].c0);
                    else {
                        if (strcmp(srdegree, "F"))
                            k = settransition(cube, srdegree);
                        moveseq(cube, moveseql);
                        if (strcmp(srdegree, "F"))
                            resettransition(cube, srdegree, k);
                        goto label;
                    }
                } else {
                    if (strcmp(srdegree, "F"))
                        k = settransition(cube, srdegree);
                    moveseq(cube, moveseql);
                    if (strcmp(srdegree, "F"))
                        resettransition(cube, srdegree, k);
                    goto label;
                }
                if (cube[l][1][2].c0 == cube[l][1][1].c0) {
                    j = i + 1;
                    if (j == 4)
                        j = 0;
                    m = a[j];
                    if (cube[l][1][2].c1 == cube[m][1][1].c0);
                    else {
                        if (strcmp(srdegree, "F"))
                            k = settransition(cube, srdegree);
                        moveseq(cube, moveseqr);
                        if (strcmp(srdegree, "F"))
                            resettransition(cube, srdegree, k);
                        goto label;
                    }
                } else {
                    if (strcmp(srdegree, "F"))
                        k = settransition(cube, srdegree);
                    moveseq(cube, moveseqr);
                    if (strcmp(srdegree, "F"))
                        resettransition(cube, srdegree, k);
                    goto label;
                }
            }
        }
    }
}

void orientedges(struct cubie cube[][3][3]) {
    char move[] = {"F1R1U1R3U3F3"};
    int j;
label:
    if (cube[2][0][1].c0 == 'Y' && cube[2][1][2].c0 == 'Y' &&
            cube[2][2][1].c0 == 'Y' && cube[2][1][0].c0 == 'Y') {
        return;
    } else if ((cube[2][1][2].c0 == 'Y' && cube[2][1][0].c0 == 'Y')
            || (cube[2][0][1].c0 == 'Y' && cube[2][2][1].c0 == 'Y')) {
        if (cube[2][1][0].c0 == 'Y' && cube[2][1][2].c0 == 'Y')
            moveseq(cube, move);
        else {
            j = settransition(cube, "R");
            moveseq(cube, move);
            resettransition(cube, "R", j);
        }

    } else if ((cube[2][1][0].c0 == 'Y' && cube[2][0][1].c0 == 'Y')
            || (cube[2][0][1].c0 == 'Y' && cube[2][1][2].c0 == 'Y')
            || (cube[2][1][2].c0 == 'Y' && cube[2][2][1].c0 == 'Y')
            || (cube[2][2][1].c0 == 'Y' && cube[2][1][0].c0 == 'Y')) {
        if (cube[2][1][0].c0 == 'Y' && cube[2][0][1].c0 == 'Y') {
            moveseq(cube, move);
            moveseq(cube, move);
        } else if (cube[2][0][1].c0 == 'Y' && cube[2][1][2].c0 == 'Y') {
            j = settransition(cube, "L");
            moveseq(cube, move);
            moveseq(cube, move);
            resettransition(cube, "L", j);
        } else if (cube[2][1][2].c0 == 'Y' && cube[2][2][1].c0 == 'Y') {
            j = settransition(cube, "B");
            moveseq(cube, move);
            moveseq(cube, move);
            resettransition(cube, "B", j);
        } else {
            j = settransition(cube, "R");
            moveseq(cube, move);
            moveseq(cube, move);
            resettransition(cube, "R", j);
        }
    } else {
        moveseq(cube, move);
        goto label;
    }
}

void orientcorners(struct cubie cube[][3][3]) {
    char move[] = {"R1U1R3U1R1U2R3"};
    char srdegree[2];
    int i, j, k, count = 0, flag = 0;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            if (cube[2][i][j].c0 == 'Y')
                count++;
        }
    if (count == 9)
        return;
label1:
    for (i = 0; i < 4; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "B");
        else if (i == 3)
            strcpy(srdegree, "L");

        if (strcmp(srdegree, "F"))
            k = settransition(cube, srdegree);

        if (
                cube[2][0][0].c2 == 'Y'
                && cube[2][0][1].c0 == 'Y'
                && cube[2][0][2].c2 == 'Y'
                && cube[2][1][0].c0 == 'Y'
                && cube[2][1][1].c0 == 'Y'
                && cube[2][1][2].c0 == 'Y'
                && cube[2][2][0].c0 == 'Y'
                && cube[2][2][1].c0 == 'Y'
                && cube[2][2][2].c2 == 'Y') {
            moveseq(cube, move);
            flag = 1;
        }
        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, k);
        if (flag == 1)
            return;
    }
label2:
    for (i = 0; i < 4; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "B");
        else if (i == 3)
            strcpy(srdegree, "L");

        if (strcmp(srdegree, "F"))
            k = settransition(cube, srdegree);

        if (
                cube[2][0][0].c1 == 'Y'
                && cube[2][0][1].c0 == 'Y'
                && cube[2][0][2].c1 == 'Y'
                && cube[2][1][0].c0 == 'Y'
                && cube[2][1][1].c0 == 'Y'
                && cube[2][1][2].c0 == 'Y'
                && cube[2][2][0].c0 == 'Y'
                && cube[2][2][1].c0 == 'Y'
                && cube[2][2][2].c1 == 'Y') {
            moveseq(cube, move);
            flag = 1;
        }
        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, k);
        if (flag == 1) {
            flag = 0;
            goto label1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "B");
        else if (i == 3)
            strcpy(srdegree, "L");

        if (strcmp(srdegree, "F"))
            k = settransition(cube, srdegree);

        if (
                cube[2][0][0].c1 == 'Y'
                && cube[2][0][1].c0 == 'Y'
                && cube[2][0][2].c1 == 'Y'
                && cube[2][1][0].c0 == 'Y'
                && cube[2][1][1].c0 == 'Y'
                && cube[2][1][2].c0 == 'Y'
                && cube[2][2][0].c2 == 'Y'
                && cube[2][2][1].c0 == 'Y'
                && cube[2][2][2].c2 == 'Y') {
            moveseq(cube, move);
            flag = 1;
        }
        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, k);
        if (flag == 1) {
            flag = 0;
            goto label1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "B");
        else if (i == 3)
            strcpy(srdegree, "L");

        if (strcmp(srdegree, "F"))
            k = settransition(cube, srdegree);

        if (
                cube[2][0][0].c1 == 'Y'
                && cube[2][0][1].c0 == 'Y'
                && cube[2][0][2].c2 == 'Y'
                && cube[2][1][0].c0 == 'Y'
                && cube[2][1][1].c0 == 'Y'
                && cube[2][1][2].c0 == 'Y'
                && cube[2][2][0].c2 == 'Y'
                && cube[2][2][1].c0 == 'Y'
                && cube[2][2][2].c1 == 'Y') {
            moveseq(cube, move);
            flag = 1;
        }
        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, k);
        if (flag == 1) {
            flag = 0;
            goto label1;
        }
    }//last condition
    for (i = 0; i < 4; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "B");
        else if (i == 3)
            strcpy(srdegree, "L");

        if (strcmp(srdegree, "F"))
            k = settransition(cube, srdegree);

        if (
                cube[2][0][0].c2 == 'Y'
                && cube[2][0][1].c0 == 'Y'
                && cube[2][0][2].c0 == 'Y'
                && cube[2][1][0].c0 == 'Y'
                && cube[2][1][1].c0 == 'Y'
                && cube[2][1][2].c0 == 'Y'
                && cube[2][2][0].c1 == 'Y'
                && cube[2][2][1].c0 == 'Y'
                && cube[2][2][2].c0 == 'Y') {
            moveseq(cube, move);
            flag = 1;
        }
        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, k);
        if (flag == 1) {
            flag = 0;
            goto label2;
        }
    }
    for (i = 0; i < 4; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "B");
        else if (i == 3)
            strcpy(srdegree, "L");

        if (strcmp(srdegree, "F"))
            k = settransition(cube, srdegree);

        if (
                cube[2][0][0].c0 == 'Y'
                && cube[2][0][1].c0 == 'Y'
                && cube[2][0][2].c2 == 'Y'
                && cube[2][1][0].c0 == 'Y'
                && cube[2][1][1].c0 == 'Y'
                && cube[2][1][2].c0 == 'Y'
                && cube[2][2][0].c1 == 'Y'
                && cube[2][2][1].c0 == 'Y'
                && cube[2][2][2].c0 == 'Y') {
            moveseq(cube, move);
            flag = 1;
        }
        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, k);
        if (flag == 1) {
            flag = 0;
            goto label2;
        }
    }
    for (i = 0; i < 4; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "B");
        else if (i == 3)
            strcpy(srdegree, "L");

        if (strcmp(srdegree, "F"))
            k = settransition(cube, srdegree);

        if (
                cube[2][0][0].c0 == 'Y'
                && cube[2][0][1].c0 == 'Y'
                && cube[2][0][2].c0 == 'Y'
                && cube[2][1][0].c0 == 'Y'
                && cube[2][1][1].c0 == 'Y'
                && cube[2][1][2].c0 == 'Y'
                && cube[2][2][0].c1 == 'Y'
                && cube[2][2][1].c0 == 'Y'
                && cube[2][2][2].c2 == 'Y') {
            moveseq(cube, move);
            flag = 1;
        }
        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, k);
        if (flag == 1) {
            flag = 0;
            goto label2;
        }
    }
}

void positioncorners(struct cubie cube[][3][3]) {
    char move[] = {"R1U2R3U3R1U2L3U1R3U3L1"};
    char a[4] = {0, 1, 5, 3};
    char b[5] = {"FRBL"};
    char srdegree[2];
    int i, j, l, count;
    int flag = 0;
label1:
    count = 0;
    for (i = 0; i < 4; i++) {
        if (i == 0)
            l = a[i];
        else if (i == 1)
            l = a[i];
        else if (i == 2)
            l = a[i];
        else if (i == 3)
            l = a[i];
        if (cube[l][0][0].c0 == cube[l][0][2].c0)
            count++;
    }
    if (count == 4) {
        while (cube[0][0][0].c0 != cube[0][1][1].c0)
            transition(cube, "U1");
        count = 0;
        return;
    }
label2:
    for (i = 0; i < 4; i++) {
        if (i == 0)
            l = a[i];
        else if (i == 1)
            l = a[i];
        else if (i == 2)
            l = a[i];
        else if (i == 3)
            l = a[i];
        if (cube[l][0][0].c0 == cube[l][0][2].c0) {
label3:
            if (cube[l][0][0].c0 == cube[l][1][1].c0) {
            } else if (1) {
                transition(cube, "U1");
                i--;
                if (i == -1)
                    i = 3;
                l = a[i];
                goto label3;
            }
            i++;
            if (i == 4)
                i = 0;
            if (b[i] != 'F') {
                srdegree[0] = b[i];
                srdegree[1] = '\0';
                j = settransition(cube, srdegree);
            }
            moveseq(cube, move);
            if (b[i] != 'F') {
                srdegree[0] = b[i];
                srdegree[1] = '\0';
                resettransition(cube, srdegree, j);
            }
            goto label1;
        }
    }
    while (cube[0][0][0].c0 != 'G' || cube[0][0][0].c1 != 'R')
        transition(cube, "U1");
    if (flag == 0) {
        flag = 1;
        moveseq(cube, move);
        goto label2;
    } else {
        j = settransition(cube, "R");
        moveseq(cube, move);
        resettransition(cube, "R", j);
        goto label2;
    }
}

void positionedges(struct cubie cube[][3][3]) {
    char move[] = {"F2U1R3L1F2L3R1U1F2"};
    char a[4] = {0, 1, 5, 3};
    char b[5] = {"FRBL"};
    char srdegree[2];
    int i, j, k, l, count;
    while (cube[0][0][0].c0 != 'G')
        transition(cube, "U1");
label:
    count = 0;
    for (i = 0; i < 4; i++) {
        if (i == 0)
            l = a[i];
        else if (i == 1)
            l = a[i];
        else if (i == 2)
            l = a[i];
        else if (i == 3)
            l = a[i];
        if (cube[l][0][0].c0 == cube[l][0][1].c0)
            if (cube[l][0][1].c0 == cube[l][0][2].c0) {
                count++;
                k = i;
            }
    }
    if (count == 4) {
        return;
    }
    if (count > 0) {
        i = k;
        i = i - 2;
        if (i == -1)
            i = 3;
        if (i == -2)
            i = 2;
        if (b[i] != 'F') {
            srdegree[0] = b[i];
            srdegree[1] = '\0';
            j = settransition(cube, srdegree);
        }
        moveseq(cube, move);
        if (b[i] != 'F') {
            srdegree[0] = b[i];
            srdegree[1] = '\0';
            resettransition(cube, srdegree, j);
            goto label;
        }
    } else
        moveseq(cube, move);
    goto label;
}

void toplayer(struct cubie cube[][3][3]) {
    orientedges(cube);
    orientcorners(cube);
    positioncorners(cube);
    positionedges(cube);
}

void moveextraction() {
    char temp, face, chdegree;
    char a[] = {"FRBL"};
    int i, j, k, degree;
    FILE *fp1, *fp2;
    fp1 = fopen("redundantmoves.txt", "r");
    fp2 = fopen("intermediate.txt", "w");
    fscanf(fp1, "%c", &temp);
    while (!feof(fp1)) {
        if (temp != 'S') {
            fprintf(fp2, "%c", temp);
            fscanf(fp1, "%c", &temp);
            fprintf(fp2, "%c", temp);
        } else if (temp == 'S') {
            fscanf(fp1, "%c", &temp);
            if (temp == 'F' || temp == 'R' || temp == 'B' || temp == 'L') {
                if (temp == 'F')
                    i = 0;
                else if (temp == 'R')
                    i = 1;
                else if (temp == 'B')
                    i = 2;
                else if (temp == 'L')
                    i = 3;
                fscanf(fp1, "%c", &temp);
                while (temp != 'T') {
                    if (temp == 'U' || temp == 'D') {
                        fprintf(fp2, "%c", temp);
                        fscanf(fp1, "%c", &temp);
                        fprintf(fp2, "%c", temp);
                        fscanf(fp1, "%c", &temp);
                    } else {
                        for (j = 0; j <= 3; j++) {
                            if (temp == a[j]) {
                                k = (i + j) % 4;
                                fprintf(fp2, "%c", a[k]);
                            }
                        }
                        fscanf(fp1, "%c", &temp);
                        fprintf(fp2, "%c", temp);
                        fscanf(fp1, "%c", &temp);
                    }
                }
            } else {
                switch (temp) {
                    case 'U':
                        fscanf(fp1, "%c", &temp);
                        while (temp != 'T') {
                            if (temp == 'F')
                                fprintf(fp2, "U");
                            else if (temp == 'R')
                                fprintf(fp2, "R");
                            else if (temp == 'U')
                                fprintf(fp2, "B");
                            else if (temp == 'L')
                                fprintf(fp2, "L");
                            else if (temp == 'D')
                                fprintf(fp2, "F");
                            else if (temp == 'B')
                                fprintf(fp2, "D");
                            fscanf(fp1, "%c", &temp);
                            fprintf(fp2, "%c", temp);
                            fscanf(fp1, "%c", &temp);
                        }
                        break;
                    case 'D':
                        fscanf(fp1, "%c", &temp);
                        while (temp != 'T') {
                            if (temp == 'F')
                                fprintf(fp2, "D");
                            else if (temp == 'R')
                                fprintf(fp2, "R");
                            else if (temp == 'U')
                                fprintf(fp2, "F");
                            else if (temp == 'L')
                                fprintf(fp2, "L");
                            else if (temp == 'D')
                                fprintf(fp2, "B");
                            else if (temp == 'B')
                                fprintf(fp2, "U");
                            fscanf(fp1, "%c", &temp);
                            fprintf(fp2, "%c", temp);
                            fscanf(fp1, "%c", &temp);
                        }
                }
            }
        }
        fscanf(fp1, "%c", &temp);
    }
    fclose(fp1);
    fclose(fp2);
    remove("redundantmoves.txt");
    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("moves.txt", "w");
    fscanf(fp1, "%c", &temp);
    face = temp;
    degree = 0;
    while (!feof(fp1)) {
        if (face == temp) {
            fscanf(fp1, "%c", &temp);
            degree = degree + (temp - '0');
            degree = degree % 4;
            fscanf(fp1, "%c", &temp);
        } else if (degree != 0) {
            fprintf(fp2, "%c", face);
            chdegree = degree + '0';
            fprintf(fp2, "%c", chdegree);
            face = temp;
            degree = 0;
        } else if (degree == 0) {
            face = temp;
            degree = 0;
        }
    }
    if (degree != 0) {
        fprintf(fp2, "%c", face);
        chdegree = degree + '0';
        fprintf(fp2, "%c", chdegree);
    }
    fclose(fp1);
    fclose(fp2);
    remove("intermediate.txt");
}

int calcmoves() {
    int count;
    char temp;
    FILE *fp;
    fp = fopen("moves.txt", "r");
    count = 0;
    fscanf(fp, "%c", &temp);
    while (!feof(fp)) {
        count++;
        fscanf(fp, "%c", &temp);
    }
    count = count / 2;
    return count;
}

void showmoves(struct cubie dupcube[][3][3]) {
    int flag = 0, lastmoveflag = 0;
    char degree[3], temp, nxt[10];
    FILE *fp;
    fp = fopen("moves.txt", "r");
ilabel:
    printf("Press ENTER to see the Move!\nPress 'C' for Complete Solution at once:");
    gets(nxt);
    if (strlen(nxt) == 0);
    else if (strlen(nxt) == 1) {
        if (!strcmp(nxt, "C")) {
            system("cls");
            printf("\nMake the following moves to get the Solved Cube!\n\n");
            flag = 1;
        } else {
            system("cls");
            printcube(dupcube);
            printf("\nInvalid Choice!\n\n");
            goto ilabel;
        }
    } else {
        system("cls");
        printcube(dupcube);
        printf("\nInvalid Choice!\n\n");
        goto ilabel;
    }
    fscanf(fp, "%c", &temp);
    while (!feof(fp)) {
clabel:
        degree[0] = temp;
        fscanf(fp, "%c", &temp);
        degree[1] = temp;
        degree[2] = '\0';
        transition(dupcube, degree);
        lastmoveflag = 1;
        if (flag == 1)
            printf("%s ", degree);
        else {
            system("cls");
            printf("\nMove:%s\n", degree);
        }
        if (flag != 1)
            printcube(dupcube);
        fscanf(fp, "%c", &temp);
        if (feof(fp)) {
            if (flag == 1) {
                printf("\n");
                printcube(dupcube);
            }
            fclose(fp);
            return;
        }
        if (flag == 1)
            goto clabel;
label:
        printf("Press ENTER to see the Move!\nPress 'C' for Complete Solution at once:");
        gets(nxt);
        if (strlen(nxt) == 0);
        else if (strlen(nxt) == 1) {
            if (!strcmp(nxt, "C")) {
                system("cls");
                printf("\nMake the following moves to get the Solved Cube!\n\n");
                flag = 1;
                goto clabel;
            } else {
                system("cls");
                printf("\nLast Move:%s\n", degree);
                printcube(dupcube);
                printf("\nInvalid Choice!\n\n");
                goto label;
            }
        } else {
            system("cls");
            printf("\nLast Move:%s\n", degree);
            printcube(dupcube);
            printf("\nInvalid Choice!\n\n");
            goto label;
        }
    }
}

void duplicatecube(struct cubie cube[][3][3], struct cubie dupcube[][3][3]) {
    int i, j, k;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                dupcube[i][j][k].c0 = cube[i][j][k].c0;
                dupcube[i][j][k].c1 = cube[i][j][k].c1;
                dupcube[i][j][k].c2 = cube[i][j][k].c2;
            }
        }
    }
}

void hlp() {
    printf("Help:\n"
            "You are provided with these options:\n"
            "1. Press 'H' for Help!\n"
            "2. Press 'S' to scramble\n"
            "3. Press 'M' to scramble Yourselves!\n"
            "4. Press 'P' to get the step by step solution of any combination of your Cube!\n"
            "5. Press 'G' to get the step by step solution of the above CUBE!\n"
            "6. Press 'E' to Exit.\n\n");
    setcolor(4);
    printf("Caution: Give all the input in CAPS!\n\n");
    setcolor(15);
}

int checkcube(struct cubie cube[][3][3]) {
    int i, j, k;
    char temp;
    FILE *fp;
    fp = fopen("index.txt", "r");
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                fscanf(fp, "%c", &temp);
                if (cube[i][j][k].c0 != temp)
                    return 0;

                fscanf(fp, "%c", &temp);
                if (cube[i][j][k].c1 != temp)
                    return 0;

                fscanf(fp, "%c", &temp);
                if (cube[i][j][k].c2 != temp)
                    return 0;
            }
        }
    }
    fclose(fp);
    return 1;
}

int checkfill(struct cubie cube[][3][3]) {
    char ch;
    int i, j, k;
    int gcount = 0, ocount = 0, ycount = 0, rcount = 0, wcount = 0, bcount = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                ch = cube[i][j][k].c0;
                switch (ch) {
                    case 'G':
                        gcount++;
                        break;
                    case 'O':
                        ocount++;
                        break;
                    case 'Y':
                        ycount++;
                        break;
                    case 'R':
                        rcount++;
                        break;
                    case 'W':
                        wcount++;
                        break;
                    case 'B':
                        bcount++;
                        break;
                }
            }
        }
    }
    if (gcount == 9 && ocount == 9 && ycount == 9 && rcount == 9 && wcount == 9 && bcount == 9) {
        for (i = 0; i < 6; i++) {
            ch = cube[i][1][1].c0;
            switch (i) {
                case 0:
                    if (ch == 'G')
                        gcount++;
                    break;
                case 1:
                    if (ch == 'O')
                        ocount++;
                    break;
                case 2:
                    if (ch == 'Y')
                        ycount++;
                    break;
                case 3:
                    if (ch == 'R')
                        rcount++;
                    break;
                case 4:
                    if (ch == 'W')
                        wcount++;
                    break;
                case 5:
                    if (ch == 'B')
                        bcount++;
                    break;
            }
        }
        if (gcount == 10 && ocount == 10 && ycount == 10 && rcount == 10 && wcount == 10 && bcount == 10)
            return 1;
        else
            return 0;
    } else
        return 0;
}

void completefill(struct cubie cube[][3][3]) {
    int i, j;
    char srdegree[2];
    for (i = 0; i < 6; i++) {
        if (i == 0)
            strcpy(srdegree, "F");
        else if (i == 1)
            strcpy(srdegree, "R");
        else if (i == 2)
            strcpy(srdegree, "U");
        else if (i == 3)
            strcpy(srdegree, "L");
        else if (i == 4)
            strcpy(srdegree, "D");
        else if (i == 5)
            strcpy(srdegree, "B");

        if (strcmp(srdegree, "F"))
            j = settransition(cube, srdegree);

        cube[0][0][0].c1 = cube[3][0][2].c0;
        cube[0][0][0].c2 = cube[2][2][0].c0;

        cube[0][0][1].c1 = cube[2][2][1].c0;

        cube[0][0][2].c1 = cube[2][2][2].c0;
        cube[0][0][2].c2 = cube[1][0][0].c0;

        cube[0][1][0].c1 = cube[3][1][2].c0;

        cube[0][1][2].c1 = cube[1][1][0].c0;

        cube[0][2][0].c1 = cube[4][0][0].c0;
        cube[0][2][0].c2 = cube[3][2][2].c0;

        cube[0][2][1].c1 = cube[4][0][1].c0;

        cube[0][2][2].c1 = cube[1][2][0].c0;
        cube[0][2][2].c2 = cube[4][0][2].c0;

        if (strcmp(srdegree, "F"))
            resettransition(cube, srdegree, j);
    }
}

void chinsinniteshfill(struct cubie cube[][3][3]) {
    int i, j, k, l;
    int a[] = {0, 1, 5, 3, 2, 4};
    char colr[10];
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                if (!(j == 1 && k == 1)) {
                    cube[i][j][k].c0 = 'X';
                    cube[i][j][k].c1 = 'X';
                    cube[i][j][k].c2 = 'X';
                }
            }
        }
    }
    system("cls");
    printcube(cube);
    printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
    "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
    setcolor(4);
    printf("Caution: Give all the input in CAPS!\n");
    setcolor(15);
    for (i = 0; i < 6; i++) {
        l = a[i];
        switch (i) {
            case 0:
                printf("\nGreen Face-The face with Green sticker at the center piece!\n\n");
                break;
            case 1:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nOrange Face-The face with Orange sticker at the center piece!\n\n");
                break;
            case 2:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\n\nBlue Face-The face with Blue sticker at the center piece!\n\n");
                break;
            case 3:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nRed Face-The face with Red sticker at the center piece!\n\n");
                break;
            case 4:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nYellow Face-The face with Yellow sticker at the center piece!\n\n");
                break;
            case 5:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nWhite Face-The face with White sticker at the center piece!\n\n");
                break;
        }
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                while (1) {
                    gets(colr);
                    if (strlen(colr) != 1) {
                        printf("Invalid Choice!\nEnter again:");
                    } else if (strcmp(colr, "G") == 0 || strcmp(colr, "O") == 0 || strcmp(colr, "Y") == 0 ||
                            strcmp(colr, "R") == 0 || strcmp(colr, "W") == 0 || strcmp(colr, "B") == 0)
                        break;
                    else {
                        printf("Invalid Choice!\nEnter again:");
                    }
                }
                cube[l][j][k].c0 = colr[0];
                switch (i) {
            case 0:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nGreen Face-The face with Green sticker at the center piece!\n\n");
                break;
            case 1:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nOrange Face-The face with Orange sticker at the center piece!\n\n");
                break;
            case 2:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\n\nBlue Face-The face with Blue sticker at the center piece!\n\n");
                break;
            case 3:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nRed Face-The face with Red sticker at the center piece!\n\n");
                break;
            case 4:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nYellow Face-The face with Yellow sticker at the center piece!\n\n");
                break;
            case 5:
                system("cls");
                printcube(cube);
                printf("Enter the colour details Row By Row from Left to Right for each stated Face!\n\n"
                "G-Green | O-orange | B-Blue\nR-Red   | Y-Yellow | W-White\n\n");
                setcolor(4);
                printf("Caution: Give all the input in CAPS!\n");
                setcolor(15);
                printf("\nWhite Face-The face with White sticker at the center piece!\n\n");
                break;
        }
            }
        }
    }
    system("cls");
    if (checkfill(cube)) {
        completefill(cube);
        printf("\nCongratulations you filled the cube successfully:)\n");
    } else{
        printf("\nYou made some Mistake while giving the Input:(\nTry again!\n");
        initialize(cube);
        }
}

int main(int nNumberofArgs, char* pszArgs[]) {
    struct cubie cube[6][3][3];
    struct cubie dupcube[6][3][3];
    int lastmoveflag, totalmoves;
    char degree[10], lastmove[3], op, ch, choice[10];
    setcolor(15);
    scrflag = 0;
    solvingflag = 0;
    initialize(cube);
    printf("\nInitialized!\n");
    printcube(cube);
    hlp();
    while (1) {
        printf("Enter the choice:");
        gets(choice);
        if (strlen(choice) != 1) {
            system("cls");
            printcube(cube);
            printf("\nInvalid Choice!\n\n");
            hlp();
            continue;
        }
        ch = choice[0];
        if (ch == 'H') {
            system("cls");
            printcube(cube);
            hlp();
        } else if (ch == 'S') {
            system("cls");
            printf("\n");
            scrflag = 1;
            scramble(cube);
            while (1) {
                printf("Do you want to scramble again?\nY|N: ");
                gets(choice);
                if (strlen(choice) != 1) {
                    system("cls");
                    printcube(cube);
                    printf("Invalid Choice!\nCube not scrambled:(\n\n");
                    continue;
                }
                op = choice[0];
                if (op == 'Y') {
                    system("cls");
                    printf("\n");
                    scramble(cube);
                    printf("Scrambled!\n");
                } else if (op == 'N') {
                    system("cls");
                    printcube(cube);
                    hlp();
                    break;
                } else {
                    system("cls");
                    printcube(cube);
                    printf("Invalid Choice!\nCube not scrambled:(\n\n");
                }
            }
        } else if (ch == 'M') {
            system("cls");
            printcube(cube);
            while (1) {
                printf("\nYou can choose any of the moves:\n\n"
                        "F-Front Face | "
                        "R-Right Face | "
                        "U-Upper Face\n"
                        "L-Left Face | "
                        "D-Down Face | "
                        "B-Back Face!\n"
                        "\nFollwed by:\n"
                        "1 for 90 degree Clockwise Move| "
                        "2 for 180 Degree Clockwise Move\n"
                        "3 for 90 degree AntiClockwise Move!\n\n"
                        "For Example: R1-90 degree clockwise turn of Right face\n"
                        "             F2-180 degree clockwise turn of front face\n"
                        "             U3-90 degree anticlockwise turn of Upper face\n");
                printf("\nEnter the Move Or 'E' to Exit to the MENU:");
                gets(degree);
                if (strlen(degree) != 2) {
                    if (strlen(degree) > 2) {
                        system("cls");
                        if (lastmoveflag == 1)
                            printf("\nLast Move:%s\n", lastmove);
                        printcube(cube);
                        printf("Invalid Move!\n\n");
                        continue;
                    } else if (strlen(degree) == 1 && degree[0] != 'E') {
                        system("cls");
                        if (lastmoveflag == 1)
                            printf("\nLast Move:%s\n", lastmove);
                        printcube(cube);
                        printf("Invalid Move!\n\n");
                        continue;
                    }
                }
                if ((degree[0] == 'F' || degree[0] == 'R' || degree[0] == 'U' ||
                        degree[0] == 'L' || degree[0] == 'D' || degree[0] == 'B')
                        && (degree[1] == '1' || degree[1] == '2' || degree[1] == '3')) {
                    strcpy(lastmove, degree);
                    lastmoveflag = 1;
                    transition(cube, degree);
                    scrflag = 1;
                    system("cls");
                    printf("\nMove:%s\n", degree);
                    printcube(cube);
                } else if (degree[0] == 'E' && strlen(degree) == 1) {
                    system("cls");
                    printcube(cube);
                    hlp();
                    break;
                } else {
                    system("cls");
                    if (lastmoveflag == 1)
                        printf("\nLast Move:%s\n", lastmove);
                    printcube(cube);
                    printf("Invalid Move!\n\n");
                }
            }
            lastmoveflag = 0;
        } else if (ch == 'G') {
            if (scrflag == 0) {
                system("cls");
                printcube(cube);
                printf("\nThe cube is in solved state.\n"
                        "You need to scramble the cube or atleast make one manual move\nto get step by step Solution!\n\n");                
                hlp();
            } else {
                if (checkcube(cube)) {
                    system("cls");
                    printcube(cube);
                    printf("Sorry! No moves required as the Cube is already in Solved state!\n\n");
                } else {
                    duplicatecube(cube, dupcube);
                    solvingflag = 1;
                    bottomlayer(cube);
                    middlelayer(cube);
                    toplayer(cube);
                    scrflag = 0;
                    solvingflag = 0;
                    moveextraction();
                    system("cls");
                    printcube(dupcube);
                    totalmoves = calcmoves();
                    setcolor(4);
                    printf("\nTotal moves required to get the Solved Cube is %d!\n\n", totalmoves);
                    setcolor(15);
                    showmoves(dupcube);
                    printf("Whooppi! The Cube is SOLVED!:)\n\n");
                    remove("moves.txt");
                }
                hlp();
            }
        } else if (ch == 'P') {
            scrflag = 1;
            chinsinniteshfill(cube);
            printcube(cube);
            hlp(); 
        } else if (ch == 'E')
            exit(0);
        else {
            system("cls");
            printcube(cube);
            printf("\nInvalid Choice!\n\n");
            hlp();
        }
    }
    system("PAUSE");
    return 0;
}
