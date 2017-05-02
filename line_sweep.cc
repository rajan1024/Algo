#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define pb push_back
#define mp make_pair


typedef pair<double,double> point;
typedef pair<point,point> line;
typedef pair< pair<point,int>, line> point_line;

class compare{
public:
	bool operator()(point_line p1, point_line p2){
		return p1.F.F.F < p2.F.F.F;
	}
};

int Rotation(point p1, point p2, point p3){
	//printf("Checking rotation of {%d,%d} {%d,%d} {%d,%d}...\n",p1.F,p1.S,p2.F,p2.S,p3.F,p3.S);
	auto x1 = p1.F - p2.F, y1 = p1.S-p2.S;
	auto x2 = p3.F - p2.F, y2 = p3.S-p2.S;
	auto r = (x1*y2 - x2*y1);
	if(r > 0) return 1; // p1,p2,p3 in clockwise direction...
	else if(r < 0) return -1;// p1,p2,p3 in anti-clockwise direction...
	else return 0; //collinear points....
}


bool onsegment(point p1, point p2, point p3){
	if( (p3.F <= max(p1.F,p2.F) && p3.F >= min(p1.F,p2.F)) && (p3.S <= max(p1.S,p2.S) && p3.S >= min(p1.S,p2.S)) ) return true;
	else return false;
}


int is_intersecting(line l1, line l2){
	point<T> p1=l1.F,p2=l1.S,p3=l2.F,p4=l2.S;
	int r21 = Rotation(p1,p2,p3);
	int r22 = Rotation(p1,p2,p4);
	int r11 = Rotation(p3,p4,p1);
	int r12 = Rotation(p3,p4,p2);
	if(r11*r12 == -1 && r21*r22 == -1) return 1; //proper intersection...
	else if(r11*r12*r21*r22 == 0){	//improper intersection may happen.......
		if(r11 == 0) if(onsegment(p3,p4,p1)) return -1;
		if(r12 == 0) if(onsegment(p3,p4,p2)) return -1;
		if(r21 == 0) if(onsegment(p1,p2,p3)) return -1;
		if(r22 == 0) if(onsegment(p1,p2,p4)) return -1;
		return 0; // no intersection...
	}
	else return 0; // no intersection.....
}

point intersection_point(line l1, line l2){
	int A1,B1,C1,A2,B2,C2;
	A1 = l1.S.S - l1.F.S; //y2-y1
	B1 = l1.F.F - l1.S.F; //x1-x2
	C1 = A1*l1.F.F + B1*l1.F.S; // A*x1+B*y1
	
	A2 = l2.S.S - l2.F.S; //y2-y1
	B2 = l2.F.F - l2.S.F; //x1-x2
	C2 = A2*l2.F.F + B2*l2.F.S; // A*x1+B*y1

	double delta = A1*B2 - B1*A2;
	if(delta == 0) {printf("Error lines donot intersect..\n"); exit(1); }
	point<double> p;
	double x,y;
	x = (B2*C1 - B1*C2)/delta;
        y = (A1*C2 - A2*C1)/delta;
	p = mp(x,y);
	return p;
}


int main(){
	int n,x,y;
	cin>>n;
	vector<line> line_array;
	vector<int> line_inserted(n,0);
	for(int i=0;i<n;i++){
		point p1,p2;
		line l1;
		cin>>x>>y; //starting point (x,y)
		p1 = mp(x,y);
		cin>>x>>y; //ending point (x,y)
		p2 = mp(x,y);
		l1 = mp(p1,p2);
		line_array.pb(l1);
	}
	set<point_line,compare> s;
	vector<point_line> p;
	int i = 0;
	for(line l:line_array){
		point_line pl;
		pl.F = mp(l.F,i); // "i" is line_id...
		pl.S = l;
		p.pb(pl);
		pl.F = mp(l.S,i); // "i" is line_id...
		p.pb(pl);
		i++;
	}
	sort(p.begin(),p.end());
	/*
	for(point_line pl:p){
		printf("{%lf,%lf},{%lf,%lf}\n",pl.F.F,pl.F.S,pl.S.S.F,pl.S.S.S);
	}
	*/
	for(point_line pl : p){
		int id = pl.F.S; // line_id........
		int inserted = line_inserted[id];

		if(inserted == 0){
			s.insert(pl); // if not inserted yet, insert it...
			set<point_line>::iterator it1,it2,it3;
			it1 = s.find(pl); it1++;
			it2 = s.find(pl);
			it3 = s.find(pl); it3++;
			it3++;
			if(it2 == s.begin() && s.size() > 1){
				if(it3->F.S != -1){ //second point should not be intersection point line_id -1 (invalid)...
					line l1,l2;
					l1 = it2->S;
					l2 = it2->S;
					point intersecting_point;
					if(is_intersecting(l1,l2)){
						intersecting_point = intersection_point(l1,l2);
						//Insert this special point in set with line id = -1;
						point_line = pl1;
						pl1 = pl;
						pl1.F = mp(intersection_point,-1); // line_id -1 and line is garbage value......
						s.insert(pl1);
					}
				}
				
			}
			else if(it2 == s.end() && it2 !=  )
			line_inserted[id] = 1;
		}
		else{
			
		}
	}

	return 0;
}