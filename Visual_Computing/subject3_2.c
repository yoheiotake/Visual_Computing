//#include <stdio.h>
//#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <stdlib.h>

#define KEY_ESC 27
#define PAI 3.1415926535

float dist = 0.0;
float theta = 0.0;
float theta2 = 0.0;
float theta3 = 0.0;


/* No.0 */
static GLfloat arm0[18][3] = {
    {12.0, 4.0, 4.0}, {20.0, 4.0, 4.0}, 
    {20.0, 4.0, -20.0}, {12.0, 4.0, -20.0},
    {28.0, 4.0, 20.0}, {36.0, 4.0, 20.0}, 
    {-4.0, 4.0, 20.0}, {4.0, 4.0, 20.0},
	{16.0, 4.0, 8.0}, {12.0, -4.0, 4.0}, 
    {12.0, -4.0, -20.0}, {20.0, -4.0, -20.0},
	{20.0, -4.0, 4.0}, {36.0, -4.0, 20.0},
	{28.0, -4.0, 20.0}, {16.0, -4.0, 8.0},
	{4.0, -4.0, 20.0}, {-4.0, -4.0, 20.0}
};

/* No.1 */
static GLfloat arm1[24][3] = {
    {-12.0, 4.0, -20.0}, { -36.0, 4.0, -20.0}, // x:Left y:front z:over
    {-36.0, 4.0, -12.0}, { -12.0, 4.0, -12.0},
    {-20.0, 4.0, -12.0}, { -20.0, 4.0, 12.0}, 
    {-12.0, 4.0, 12.0}, { -28.0, 4.0, -12.0},
	{-36.0, 4.0, 12.0}, { -28.0, 4.0, 12.0}, 
    {-36.0, 4.0, 20.0}, { -12.0, 4.0, 20.0},
	{-12.0, -4.0, -20.0}, { -12.0, -4.0, -12.0}, 
    {-36.0, -4.0, -12.0}, { -36.0, -4.0, -20.0},
	{-12.0, -4.0, 12.0}, { -20.0, -4.0, 12.0}, 
    {-20.0, -4.0, -12.0}, { -28.0, -4.0, -12.0},
	{-28.0, -4.0, 12.0}, { -36.0, -4.0, 12.0}, 
    {-12.0, -4.0, 20.0}, { -36.0, -4.0, 20.0}
};

/* 視点と注視点のデータ */
static GLdouble eye[3] = { 100.0, 100.0, 100.0 };
static GLdouble center[3] = { 0.0, 0.0, 0.0 };

/* 
 *  ロボットの腕の描画
 */
void 
drawArmShadingY( GLfloat arm[18][3] )
{
    int i, j; /* カウンター */
    int index; /* 頂点のインデックス */
    GLfloat normal[3]; /* 法線ベクトル */
    double norm; /* ベクトルのノルム */
    GLfloat vec0[3], vec1[3];
    int polygon[18][4] = {
        {0, 1, 2, 3}, {0, 4, 5, 1}, {7, 8, 0, 6},
        {9, 10, 11, 12}, {9, 12, 13, 14}, {9, 15, 16, 17},
		{0, 3, 10, 9}, {2, 11, 10, 3}, {1, 12, 11, 2},
        {1, 0, 9, 12}, {0, 1, 12, 9}, {1, 5, 13, 12},
		{5, 4, 14, 13}, {4, 0, 9, 14}, {0, 8, 15, 9},
        {8, 7, 16, 15}, {7, 6, 17, 16}, {0, 9, 17, 6}
    };
	
    for ( i=0; i<18; ++i ) {
        /* 法線ベクトル */
        for ( j=0; j<3; ++j ) {
            vec0[j] = arm[ polygon[i][2] ][j] - arm[ polygon[i][1] ][j];//vec[0]:x vec[1]:y vec[2]:z
            vec1[j] = arm[ polygon[i][0] ][j] - arm[ polygon[i][1] ][j];
        }
        normal[0] = vec0[1] * vec1[2] - vec0[2] * vec1[1];
        normal[1] = vec0[2] * vec1[0] - vec0[0] * vec1[2];
        normal[2] = vec0[0] * vec1[1] - vec0[1] * vec1[0];
        norm = normal[0] * normal[0] + normal[1] * normal[1] + 
		normal[2] * normal[2];
        norm = sqrt ( norm );//平方根
        for ( j=0; j<3; ++j ) normal[j] /= norm;
		
        glBegin(GL_POLYGON); /* 多角形の描画開始 */
		glNormal3f( normal[0], normal[1], normal[2] );//法線ベクトルの成分 点(x,y,z)から原点までのベクトルの長さ=1
		for ( j=0; j<4; j++ ){
			index = polygon[i][j];
			glVertex3f(arm[index][0], arm[index][1], arm[index][2]);//面の描画
		}
		glEnd(); /* 描画終了 */
    } /* iループの終了 */
	
}



void 
drawArmShadingO( GLfloat arm[24][3] )
{
    int i, j; /* カウンター */
    int index; /* 頂点のインデックス */
    GLfloat normal[3]; /* 法線ベクトル */
    double norm; /* ベクトルのノルム */
    GLfloat vec0[3], vec1[3];
    int polygon[24][4] = {
        {0, 1, 2, 3}, {3, 4, 5, 6}, {7, 2, 8, 9},
        {6, 8, 10, 11}, {12, 13, 14, 15}, {13, 16, 17, 18},
		{19, 20, 21, 14}, {16, 22, 23, 21}, {0, 3, 13, 12},
        {0, 12, 15, 1}, {1, 15, 14, 2}, {3, 2, 14, 13},
		{3, 6, 16, 13}, {6, 5, 17, 16}, {5, 4, 18, 17},
        {3, 13, 18, 4}, {7, 19, 14, 2}, {7, 9, 20, 19},
		{9, 8, 21, 20}, {8, 2, 14, 21}, {6, 11, 22, 16},
        {11, 10, 23, 22}, {10, 8, 21, 23}, {8, 6, 16, 21}
    };
	
    for ( i=0; i<24; ++i ) {
        /* 法線ベクトル */
        for ( j=0; j<3; ++j ) {
            vec0[j] = arm[ polygon[i][2] ][j] - arm[ polygon[i][1] ][j];
            vec1[j] = arm[ polygon[i][0] ][j] - arm[ polygon[i][1] ][j];
        }
        normal[0] = vec0[1] * vec1[2] - vec0[2] * vec1[1];
        normal[1] = vec0[2] * vec1[0] - vec0[0] * vec1[2];
        normal[2] = vec0[0] * vec1[1] - vec0[1] * vec1[0];
        norm = normal[0] * normal[0] + normal[1] * normal[1] + 
		normal[2] * normal[2];
        norm = sqrt ( norm );
        for ( j=0; j<3; ++j ) normal[j] /= norm;
		
        glBegin(GL_POLYGON); /* 多角形の描画開始 */
		glNormal3f( normal[0], normal[1], normal[2] );
		for ( j=0; j<4; j++ ){
			index = polygon[i][j];
			glVertex3f(arm[index][0], arm[index][1], arm[index][2]);
		}
		glEnd(); /* 描画終了 */
    } /* iループの終了 */
	
}


/*  ロボットの腕を照明つきで描画する. */
void 
display (void)
{
	int i;
    GLfloat material_color0[4] = { 1.0, 0.0, 0.0, 1.0 }; /* 物体1の拡散反射成分 4つめは1のとき光源が位置的,0のとき指向的*/
    GLfloat material_color1[4] = { 0.0, 0.0, 1.0, 1.0 }; /* 物体2の拡散反射成分 */
    GLfloat material_specular[4] = { 0.2, 0.2, 0.2, 1.0 }; /* 鏡面反射成分 反射させる割合*/
	
    /* バッファーのクリアー*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//色と深度をクリア

    
    /* 鏡面反射成分のセット */
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	
    glPushMatrix();
	
	gluLookAt( -30.0, 30.0, -100.0, 0.0, 0.0, 0, 0.0, 1.0, 0.0 );
	glRotatef (10*sin(theta3), 1.0, 0.0, 0.0);
	glRotatef (-10*sin(theta3), 0.0, 0.0, 1.0);
	glRotatef (theta2, 0.0, 1.0, 0.0);
	glPushMatrix();
	//glTranslatef( 0.0, 50, 0.0 );
	//glRotatef (theta, 0.0, 0.0, 1.0);
    glRotatef (-90, 1.0, 0.0, 0.0);
	glTranslatef( 0.0, 0.0, 20*sin(theta3)+20 );
	//glScalef(0.5,0.5,0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_color0);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);//鏡面光の指数:光沢:大きい程ハイライトが小さくなる　アドレスではなく実数を入力:0~128
    drawArmShadingY(arm0);
	glPopMatrix();
	
    glPushMatrix();
	//glTranslatef( 2, 2.0, 2.0 );
	glRotatef (theta2, 1.0, 0.0, 0.0);
    glRotatef (-90, 1.0, 0.0, 0.0);
	//glScalef(0.5,0.5,0.5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_color1);
    drawArmShadingO(arm1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(10*sin(theta3-3), -10.0, 10*sin(theta3-3) );
	
	glTranslatef(0.0, -10.0, 0.0 );
	
	/*if(cos(theta3) > 0)*/ glRotatef (10*cos(theta3*10), 0.0, 0.0, 0.0);
	//else				glRotatef (10*cos(theta3*10), 0.0, 0.0, 0.0);
	
	glRotatef (-45, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
   	glutWireSphere( 10.0, 30, 30 );
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glNormal3f( 0, 1, 0 );
	glBegin(GL_LINES);
	for(i=-35; i< 36; i+=2) {
		glVertex3i(  i, -20,-35 );
		glVertex3i(  i, -20, 35 );
		glVertex3i(-50, -20,  i ); 
		glVertex3i( 50, -20,  i ); 
	}
	glEnd();
	
	glPopMatrix();
    glutSwapBuffers(); 
}

void 
ourInit (void) {
	
    GLfloat light0_position[] = { 0.0, 0.0, 1.0, 0.0 }; /* 照明の位置 */
    GLfloat light1_position[] = { 100.0, 100.0, 0.0, 1.0 }; /* 照明の位置 */
	
    GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; /* 拡散成分 */
    GLfloat light1_diffuse[] = { 0.5, 0.5, 0.5, 1.0 }; /* 拡散成分 */
	
    GLfloat light_specular[] = { 0.3, 0.3, 0.3, 1.0 }; /* 鏡面成分 */
	
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; /* 周囲光 */
	
    /* 照明No.0 */
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
    /* 照明No.1 */
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	
    glEnable(GL_LIGHTING);//光源を有効にする
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glDepthFunc(GL_LEQUAL);// Depthバッファの値を比較する
    glEnable(GL_DEPTH_TEST);//前後関係を有効にする
	glEnable( GL_NORMALIZE );
}


void idle(void)
{
	dist = fmod( dist + 0.05, 32.0 );
	theta = fmod( theta + 0.5, 360.0 );
	theta2 += 0.01;
	theta3 += 0.001;
	glutPostRedisplay();
}


void myKbd( unsigned char key, int x, int y )
{
    if ( key == KEY_ESC ) exit( 0 );
}


void myInit (char *progname)
{
    int width = 640, height = 480;
	float aspect = (float) width / (float) height;
	
    glutInitWindowPosition(0, 0); 
	glutInitWindowSize( width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc( myKbd );
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(60.0, aspect, 10.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); 
	myInit(argv[0]);
	ourInit();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
	glutMainLoop(); 
	return( 0 );
}