
//first sketch of quat funct
void ptnScaleRotate ( float tx, float ty, float sx, float sy, char tp){//ti traslacion en i, si escala en i,tp \in {'s','c,','t'} square circle triangle 
	glLoadIdentity();
	glTranslatef(tx,ty,0);
	//glRotatef(angle,<normal vector>) //for the sake of operation order sample, also w/e
	glScalef(sx,sy,1);
	switch (tp){
		case 's': //square
			DrawSquare(GL_POLYGON);
		case 'c': //circle
			DrawCircle(GL_POLYGON, 500);
		case 't': //triangle
			DrawTriangle(GL_POLYGON);
		
	}
	

}


