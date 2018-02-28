// tetra.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<GL/glut.h>
float v[][3]={{-1.0,-0.5,0.0},{1.0,-0.5,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};
int n;
void triangle(float *p,float *q,float *r)
{
	glVertex3fv(p);
	glVertex3fv(q);
	glVertex3fv(r);
}
void tetra(float *a,float *b,float *c,float *d)
{
	glColor3f(1,0,1);
	triangle(a,b,c);
	glColor3f(0,0,1);
	triangle(a,b,d);
	glColor3f(1,1,0);
	triangle(a,c,d);
	glColor3f(0,1,0);
	triangle(b,c,d);
}
void divide_tetra(float *a,float *b,float *c,float *d,int m)
{
	float mid[6][3];
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++)
		{
			mid[0][j]=(a[j]+b[j])/2;
			mid[1][j]=(a[j]+c[j])/2;
			mid[2][j]=(a[j]+d[j])/2;
			mid[3][j]=(b[j]+c[j])/2;
			mid[4][j]=(b[j]+d[j])/2;
			mid[5][j]=(c[j]+d[j])/2;
		}
		divide_tetra(mid[2],mid[4],mid[5],d,m-1);
		divide_tetra(a,mid[0],mid[1],mid[2],m-1);
		divide_tetra(mid[0],b,mid[3],mid[4],m-1);
		divide_tetra(mid[1],mid[3],c,mid[5],m-1);
	}
	else
	{
		tetra(a,b,c,d);
	}
}		

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0],v[1],v[2],v[3],n);
	glEnd();
	glFlush();
}
void init(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glEnable(GL_DEPTH_TEST);
}
int main()
{
	printf("Enter the no. of division\n");
	scanf("%d",&n);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutCreateWindow("gasket");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
}


