#include <stdlib.h>
#include <string.h>
#include <GL\freeglut.h>
#include <math.h>

int Width = 600, Height = 600;

// 콜백 함수 선언
void Render();
void Reshape(int w, int h);

int main(int argc, char **argv)
{
	// GLUT 초기화 및 윈도우 생성
	glutInit(&argc, argv);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("A SimpleGL Program");

	// 디스플레이 모드 초기화
	glutInitDisplayMode(GLUT_RGBA);
		
	// 콜백 함수 등록
	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);

	// 메시지 루프 진입
	glutMainLoop();
	return 0;
}

void Reshape(int w, int h)
{
	// 뷰포트 변환
	glViewport(0, 0, w, h);
	Width = w;
	Height = h;
}

void Render()
{
	// 색상 버퍼 초기화
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// 관측 공간 지정: 좌측 하단(0, 0), 우측 상단(Wdith, Height)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, Width, 0.0, Height);	//중요!

	// 모델뷰 행렬 선택 및 초기화
	glMatrixMode(GL_MODELVIEW);				//GL_PROJECTION에서 다시 변경해준다
	glLoadIdentity();

	// 예제 (1) ~ (7)
	switch (7)
	{ 
	case 1:
		// Test 1: glColor*(...).
		{
			// Draw a triangle with red color.
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2i(150, 200);
			//glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2i(350, 200);
			//glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(250, 350);
			glEnd();
			//위의 세 glColor3f를 모두 활성화 시키면 내부의 삼각형이 그러데이션으로 색칠된 삼각형이 만들어진다.


			// Draw a triangle with green color.
 			float color[3] = {0.0f, 1.0f, 0.0f};
 			glColor3fv(color);
 			glBegin(GL_TRIANGLES);
 			glVertex2i(150, 300);
 			glVertex2i(250, 150);
 			glVertex2i(350, 300);
 			glEnd();
		}
		break;

	case 2:
		// Test 2: glBlendFunc(...).
		// 첫 번째 붉은 삼각형은 알파값을 주지 않고,
		// 두 번째 초록 삼각형은 0.5의 알파값을 부여.
		// 세 번째로 그리는 노란 사각형에게도 0.5의 알파값을 부여한다.
		{
			// Draw a triangle with red color.
			glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			glEnable(GL_BLEND);
			//glBlendFunc(GL_ONE, GL_ZERO);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Draw a triangle with green color.
			glColor4f(0.0, 1.0, 0.0, 0.5);
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 300);
			glVertex2i(250, 150);
			glVertex2i(350, 300);
			glEnd();

			glColor4f(1.0, 1.0, 0.0, 0.5);
			glBegin(GL_QUADS);
			glVertex2i(50, 50);
			glVertex2i(400, 50);
			glVertex2i(400, 500);
			glVertex2i(50, 500);
			glEnd();

			glDisable(GL_BLEND);
		}
		break;

	case 3:
		// Test 3: glPointSize(...).
		// 점은 모양이 없지만, 아래의 코드에서는 네모난 모양으로 나온다.
		// 점을 동그랗게 하려면 glEnable(GL_POINT_SMOOTH)를 이용하면 된다.
		{
			// Set point attributes
			glColor3f(1.0f, 0.0f, 0.0f);
			glPointSize(15.0f);
			
			// Draw points
			glBegin(GL_POINTS);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			// Set point attributes
			glColor3f(0.0, 1.0, 0.0);
			glPointSize(30.0f);

			// Draw points
			glBegin(GL_POINTS);
			glVertex2i(150, 300);
			glVertex2i(250, 150);
			glVertex2i(350, 300);
			glEnd();


			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_POINT_SMOOTH);
			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_POINTS);
			glVertex2i(550, 300);
			glVertex2i(450, 150);
			glVertex2i(250, 300);
			glEnd();

			//glDisable(GL_BLEND);
		}
		break;

	case 4:
		// Test 4: glLineWidth(), glLineStipple().
		// 
		{
			// Set line attributes
			glColor3f(0.0f, 0.0f, 0.0f); //검은색
			glLineWidth(5.0f); //5픽셀짜리 굵기의 선을 그리겠다.

			// Draw a triangle with solid line.
			glBegin(GL_LINE_LOOP);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			glEnable(GL_LINE_STIPPLE);	//선에 패턴을 주기 위함
			
			//첫 번째 인자는 반복횟수(f와 0을 몇 번 반복할 지. 즉, 점선의 길이가 변경됨)
			//두 번째 인자는 모양(f는 그려지고, 0은 공백)
			glLineStipple(1, 0xf0f0); // 1111000011110000
			// Draw a triangle with dot-line.
			glBegin(GL_LINE_LOOP);
			glVertex2i(150, 300);
			glVertex2i(250, 150);
			glVertex2i(350, 300);
			glEnd();
			glDisable(GL_LINE_STIPPLE);
		}
		break;

	case 5:
		// Test 5: glPolygonMode().
		// 폴리곤의 특성 (앞/뒷면 구분 매우 중요)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_LINE);

			// Draw a triangle (앞면 - 색이 채워진 채로 나온다)
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 200);
			glVertex2i(350, 200);
			glVertex2i(250, 350);
			glEnd();

			// Draw a triangle (뒷면 - 색이 보이지 않고 선만 보인다)
			glBegin(GL_TRIANGLES);
			glVertex2i(150, 300);
			glVertex2i(350, 300);
			glVertex2i(250, 150);
			glEnd();
		}
		break;

	case 6:
		// Test 6: glPolygonStipple().
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glEnable(GL_POLYGON_STIPPLE);
			GLubyte fly[] = {
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x03, 0x80, 0x01, 0xC0, 0x06, 0xC0, 0x03, 0x60, 
				0x04, 0x60, 0x06, 0x20, 0x04, 0x30, 0x0C, 0x20, 
				0x04, 0x18, 0x18, 0x20, 0x04, 0x0C, 0x30, 0x20,
				0x04, 0x06, 0x60, 0x20, 0x44, 0x03, 0xC0, 0x22, 
				0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
				0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22,
				0x44, 0x01, 0x80, 0x22, 0x44, 0x01, 0x80, 0x22, 
				0x66, 0x01, 0x80, 0x66, 0x33, 0x01, 0x80, 0xCC, 
				0x19, 0x81, 0x81, 0x98, 0x0C, 0xC1, 0x83, 0x30,
				0x07, 0xe1, 0x87, 0xe0, 0x03, 0x3f, 0xfc, 0xc0, 
				0x03, 0x31, 0x8c, 0xc0, 0x03, 0x33, 0xcc, 0xc0, 
				0x06, 0x64, 0x26, 0x60, 0x0c, 0xcc, 0x33, 0x30,
				0x18, 0xcc, 0x33, 0x18, 0x10, 0xc4, 0x23, 0x08, 
				0x10, 0x63, 0xC6, 0x08, 0x10, 0x30, 0x0c, 0x08, 
				0x10, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00, 0x08};

				glPolygonStipple(fly);
				// Draw a triangle with dot-line.
				glBegin(GL_TRIANGLES);
				glVertex2i(150, 300);
				glVertex2i(250, 150);
				glVertex2i(350, 300);
				glEnd();
				glDisable(GL_POLYGON_STIPPLE);
		}
		break;

	case 7:
		// Test 7: anti-aliasing...
		// 안티앨리어싱
		{
			glColor3f(0.0f, 0.0f, 0.0f);
			glLineWidth(5.0);

			glBegin(GL_LINES);
			for (double theta = 0.0; theta <= 180.0; theta += 10.0)
			{
				double x = 300 + 300 * cos(theta * 3.141592 / 180);
				double y = 300 + 300 * sin(theta * 3.141592 / 180);	
				glVertex3f(300, 300.0, 0.0);
				glVertex3f(x, y, 0.0);
			}
			glEnd();

			glEnable(GL_LINE_SMOOTH);
 			glEnable(GL_BLEND);
 			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBegin(GL_LINES);
			for (double theta = 180.0; theta <= 360.0; theta += 10.0)
			{
				double x = 300 + 300 * cos(theta * 3.141592 / 180);
				double y = 300 + 300 * sin(theta * 3.141592 / 180);	
				glVertex3f(300, 300.0, 0.0);
				glVertex3f(x, y, 0.0);
			}
			glEnd();

			glDisable(GL_LINE_SMOOTH);
			glDisable(GL_BLEND);		

		}
		break;		
	}

	glFinish();
}


