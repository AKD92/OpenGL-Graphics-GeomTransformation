

/************************************************************************************
	Driver File (MAIN)
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iup.h>                /* For GUI toolkit */
#include <iupgl.h>


#define BTN_CLOSE "btnClose"
#define GL_CANVAS "GLCanvas"
#define MAIN_WINDOW "423Homework07aMainWindow"



/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/

					
struct poly_ {
	
	float x0, y0;
	float x1, y1;
	float x2, y2;
	
};


struct poly_ triangle;

char *labTitle = "Graphics Homework 07(A) (11301002)\n"
					"Geometric Transformation";
					
					

					
					
					
					
int main(void);

Ihandle * createMainWindow(void);
int repaint_cb(Ihandle *canvas);

int btnKey1_cb(Ihandle *btn);
int btnKey2_cb(Ihandle *btn);
int btnKey3_cb(Ihandle *btn);
int btnKey4_cb(Ihandle *btn);

int exit_cb(Ihandle *btn);



/*	OpenGL related functions	*/

void clipal_drawClipRectangle(void);
void mygl_drawGenericLine(float x0, float y0, float x1, float y1);






/************************************************************************************
*
*   Implementation of midpoint driver routines
*
*************************************************************************************/


Ihandle * createMainWindow(void) {

	Ihandle *bottomHbox, *mainVbox;
	Ihandle *lblTitle, *glCanvas;
	Ihandle *btnKey1, *btnKey2, *btnKey3, *btnKey4, *btnClose;
	Ihandle *dialog;

	lblTitle = IupLabel(labTitle);
	IupSetAttribute(lblTitle, "EXPAND", "HORIZONTAL");
	IupSetAttribute(lblTitle, "ALIGNMENT", "ALEFT:ACENTER");
	IupSetAttribute(lblTitle, "FONTSIZE", "10");

	glCanvas = IupGLCanvas(0);
	IupSetAttribute(glCanvas, "EXPAND", "YES");
	IupSetAttribute(glCanvas, "BORDER", "NO");
	IupSetAttribute(glCanvas, "CANFOCUS", "NO");
	IupSetCallback(glCanvas, "ACTION", (Icallback) repaint_cb);

	btnKey1 = IupButton("Key 01", 0);
	IupSetAttribute(btnKey1, "RASTERSIZE", "60x33");
	IupSetCallback(btnKey1, "ACTION", (Icallback) btnKey1_cb);
	
	btnKey2 = IupButton("Key 02", 0);
	IupSetAttribute(btnKey2, "RASTERSIZE", "60x33");
	IupSetCallback(btnKey2, "ACTION", (Icallback) btnKey2_cb);
	
	btnKey3 = IupButton("Key 03", 0);
	IupSetAttribute(btnKey3, "RASTERSIZE", "60x33");
	IupSetCallback(btnKey3, "ACTION", (Icallback) btnKey3_cb);
	
	btnKey4 = IupButton("Key 04", 0);
	IupSetAttribute(btnKey4, "RASTERSIZE", "60x33");
	IupSetCallback(btnKey4, "ACTION", (Icallback) btnKey4_cb);
	
	btnClose = IupButton("Close", 0);
	IupSetAttribute(btnClose, "RASTERSIZE", "80x33");
	IupSetCallback(btnClose, "ACTION", (Icallback) exit_cb);

	bottomHbox = IupHbox(btnKey1, btnKey2, btnKey3, btnKey4, IupFill(), btnClose, 0);
	IupSetAttribute(bottomHbox, "EXPAND", "HORIZONTAL");
	IupSetAttribute(bottomHbox, "NGAP", "5");
	IupSetAttribute(bottomHbox, "NMARGIN", "0x5");

	mainVbox = IupVbox(lblTitle, glCanvas, bottomHbox, 0);
	IupSetAttribute(mainVbox, "NMARGIN", "10x10");
	IupSetAttribute(mainVbox, "NGAP", "10");
	
	IupSetHandle(BTN_CLOSE, btnClose);
	IupSetHandle(GL_CANVAS, glCanvas);

	dialog = IupDialog(mainVbox);
	IupSetAttribute(dialog, "TITLE", "GL Labwork");
	IupSetAttribute(dialog, "RASTERSIZE", "425x550");
	IupSetAttribute(dialog, "SHRINK", "YES");
	IupSetAttribute(dialog, "DEFAULTESC", BTN_CLOSE);
	
	IupSetHandle(MAIN_WINDOW, dialog);

	return dialog;
}




int repaint_cb(Ihandle *canvas) {
	
	if (IupGLIsCurrent(canvas) == 0) {
		IupGLMakeCurrent(canvas);                   /* Declare our canvas for OpenGL */
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glPointSize(1.0);
	}
	glClear(GL_COLOR_BUFFER_BIT);

	
	/* Draw 3 sides of Triangle stored in struct poly_ triangle */
	/* Using Midpoint LineDraw Algorithm */
	glBegin(GL_POINTS);
		
		/* 1st Line (Side 1) */
		mygl_drawGenericLine(triangle.x0, triangle.y0, triangle.x1, triangle.y1);
		
		/* 2nd Line (Side 2) */
		mygl_drawGenericLine(triangle.x1, triangle.y1, triangle.x2, triangle.y2);
		
		/* 3rd Line (Side 3) */
		mygl_drawGenericLine(triangle.x2, triangle.y2, triangle.x0, triangle.y0);

	glEnd();

	glFlush();

	return IUP_DEFAULT;
}


int btnKey1_cb(Ihandle *btn) {
	
	Ihandle *canvas;
	canvas = IupGetHandle(GL_CANVAS);
	
	/* make all X coords positive */
	if (triangle.x0 < 0.0f) {
		triangle.x0 = (-1.0f) * triangle.x0;
		triangle.x1 = (-1.0f) * triangle.x1;
		triangle.x2 = (-1.0f) * triangle.x2;
	}
	
	/* make all Y coords positive */
	if (triangle.y0 < 0.0f) {
		triangle.y0 = (-1.0f) * triangle.y0;
		triangle.y1 = (-1.0f) * triangle.y1;
		triangle.y2 = (-1.0f) * triangle.y2;
	}
	
	IupRedraw(canvas, 0);
	return IUP_DEFAULT;
}


int btnKey2_cb(Ihandle *btn) {
	
	Ihandle *canvas;
	canvas = IupGetHandle(GL_CANVAS);
	
	/* make all X coords negative */
	if (triangle.x0 > 0.0f) {
		triangle.x0 = (-1.0f) * triangle.x0;
		triangle.x1 = (-1.0f) * triangle.x1;
		triangle.x2 = (-1.0f) * triangle.x2;
	}
	
	/* make all Y coords positive */
	if (triangle.y0 < 0.0f) {
		triangle.y0 = (-1.0f) * triangle.y0;
		triangle.y1 = (-1.0f) * triangle.y1;
		triangle.y2 = (-1.0f) * triangle.y2;
	}
	
	IupRedraw(canvas, 0);
	return IUP_DEFAULT;
}


int btnKey3_cb(Ihandle *btn) {
	
	Ihandle *canvas;
	canvas = IupGetHandle(GL_CANVAS);
	
	/* make all X coords negative */
	if (triangle.x0 > 0.0f) {
		triangle.x0 = (-1.0f) * triangle.x0;
		triangle.x1 = (-1.0f) * triangle.x1;
		triangle.x2 = (-1.0f) * triangle.x2;
	}
	
	/* make all Y coords negative */
	if (triangle.y0 > 0.0f) {
		triangle.y0 = (-1.0f) * triangle.y0;
		triangle.y1 = (-1.0f) * triangle.y1;
		triangle.y2 = (-1.0f) * triangle.y2;
	}
	
	IupRedraw(canvas, 0);
	return IUP_DEFAULT;
}



int btnKey4_cb(Ihandle *btn) {
	
	Ihandle *canvas;
	canvas = IupGetHandle(GL_CANVAS);
	
	/* make all X coords positive */
	if (triangle.x0 < 0.0f) {
		triangle.x0 = (-1.0f) * triangle.x0;
		triangle.x1 = (-1.0f) * triangle.x1;
		triangle.x2 = (-1.0f) * triangle.x2;
	}
	
	/* make all Y coords negative */
	if (triangle.y0 > 0.0f) {
		triangle.y0 = (-1.0f) * triangle.y0;
		triangle.y1 = (-1.0f) * triangle.y1;
		triangle.y2 = (-1.0f) * triangle.y2;
	}
	
	IupRedraw(canvas, 0);
	return IUP_DEFAULT;
}



int exit_cb(Ihandle *btn) {

	return IUP_CLOSE;
}





int main(void) {

	Ihandle *dlgMainWindow;
	
	triangle.x0 = 0.3f;
	triangle.y0 = 0.2f;
	triangle.x1 = 0.8f;
	triangle.y1 = 0.2f;
	triangle.x2 = 0.8f;
	triangle.y2 = 0.7f;
	
	IupOpen(0, 0);
		IupGLCanvasOpen();

		dlgMainWindow = createMainWindow();
		IupShowXY(dlgMainWindow, IUP_CENTER, IUP_CENTER);

		IupMainLoop();
	IupClose();
	
	return 0;
}
