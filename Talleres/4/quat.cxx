

void ptnScaleRotate ( float tx, float ty, float sx, float sy, char tp){
	glLoadIdentity();
	glTranslate(tx,ty,0);
	//glRotate(angle,<normal vector>) //for the sake of operation order sample, also w/e
	glScale(sx,sy,1);
	switch tp{
		case 's': //square
			DrawSquare(GL_POLYGON);
		case 'c': //circle
			DrawCircle(GL_POLYGON);
		case 't': //triangle
			DrawTrigangle(GL_POLYGON);
		
	}
	

}

