#include <raylib.h>
#include <math.h>

/*
   Visualize the wagon-wheel effect
    https://en.wikipedia.org/wiki/Wagon-wheel_effect
*/

int main() {
    int w = 800;
    int h = 800;
    int fs = w/16; // fontsize

    /*Wheel parameters*/
    float center_x = w/2;
    float center_y = h/2;
    float x_radius = (2.0/3.0 * w/2); // can be elliptic
    float y_radius = (2.0/3.0 * h/2);
    int spokes = 1;

    float fps = 50.0; // target fps
    float rps = 0.0;  // rotation per second

    float angle = 0.0;

    InitWindow(w,h,"da turning wheel");
    SetTargetFPS(fps);

    while(!WindowShouldClose()) {
	BeginDrawing();
	ClearBackground(BLACK);

	DrawText(TextFormat("FPS: %.0f", fps),0,0,fs,RED);        /* FPS = frames per second  */
	DrawText(TextFormat("RPS: %.0f", rps),0,fs,fs,RED);       /* RPS = rotation per second */
	DrawText(TextFormat("FPR: %.2f", fps/rps),w/2,0,fs,RED);  /* FPR = frame per rotation */
	DrawText(TextFormat("RPF: %.2f", rps/fps),w/2,fs,fs,RED); /* RPF = rotation per frame */

	DrawEllipseLines(center_x, center_y, x_radius, y_radius, BLUE);
	for (int i = 0; i < spokes; i++) {
	    float rad_angle = (angle + (float)i/(float)spokes * 360.0) * PI / 180.0;
	    DrawLine(
		    center_x,
		    center_y,
		    center_x + x_radius * cos(rad_angle),
		    center_y + y_radius * sin(rad_angle),
		    YELLOW);
	}

	if (IsKeyPressed(KEY_D) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON))  rps+=1.0;
	if (IsKeyPressed(KEY_A) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) rps-=1.0;
	if (IsKeyPressed(KEY_W) || GetMouseWheelMove() > 0) { fps+=1.0; SetTargetFPS(fps);}
	if (IsKeyPressed(KEY_S) || GetMouseWheelMove() < 0) { fps-=1.0; SetTargetFPS(fps);}
	if (IsKeyPressed(KEY_E)) spokes+=1;
	if (IsKeyPressed(KEY_Q)) spokes-=1;

	angle += (360.0 * rps) / fps;

	EndDrawing();
    }

    return 0;
}
