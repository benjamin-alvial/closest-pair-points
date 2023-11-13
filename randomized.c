//Algoritmo: Array[Point] -> float
//Point es de tipo struct con campos x float, y float

float dist(float x, float y) {
return sqrt(x2+y2);
}

// d value to be used for grid dxd squares
float calculateD(Point pointArray[], int n) {

float current_min_d = 2; // 2 is greater than domain

for(int i = 0; i<n; i++) {

int index = rand(0,n);
float x = pointArray[index].x;
float y = pointArray[index].y;

d = dist(x,y);
if(d<current_min_d) {

current_min_d = d;
}

}

}
