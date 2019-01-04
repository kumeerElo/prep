#include<iostream>
#include<vector>
#include<math.h>
#include<climits>
using namespace std;

enum AreaSign{ZERO, POSITIVE, NEGATIVE};
enum FrontOrBack{NONE, FRONT, BACK};

struct Point{
  Point():m_x(0.0),m_y(0.0){} 
  Point(double x, double y):m_x(x),m_y(y){} 
  double m_x;
  double m_y;
};

struct BSP{
  BSP(pair<Point,Point>v):m_line(v){}
  pair<Point,Point>m_line;
  BSP* m_front;
  BSP* m_back;
};

bool get_intersection(const pair<Point,Point>& mainLine, const pair<Point,Point>& otherLine,
                      Point& intersectionPoint)
{
  Point p1r = mainLine.first;
  Point p2r = mainLine.second;
  Point p1o = otherLine.first;
  Point p2o = otherLine.second;

  // matching to a1x+b1y=c1;
  double a1 = p2r.m_y - p1r.m_y;
  double b1 = p1r.m_x - p2r.m_x;
  double c1 = a1*p1r.m_x + b1*p1r.m_y; 

  double a2 = p2o.m_y - p1o.m_y;
  double b2 = p1o.m_x - p2o.m_x;
  double c2 = a2*p1o.m_x + b2*p1o.m_y; 
  
  double det = a1*b2 - b1*a2;

  if(det == 0)
    return false;
  else{
    double x = (b2*c1 - b1*c2)/det;
    double y = (a1*c2 - a2*c1)/det;
    // check if the intersection point lies on the segment -- very imporant
    if(x>=std::min(p1o.m_x,p2o.m_x) && x <= std::max(p1o.m_x,p2o.m_x) &&
       y>=std::min(p1o.m_y,p2o.m_y) && y <= std::max(p1o.m_y,p2o.m_y)){
      intersectionPoint.m_x = x;
      intersectionPoint.m_y = y;
      return true;
    }else
      return false;
  }
}

AreaSign cross_product(const pair<Point,Point>& line1, const pair<Point,Point>& line2)
{
  double dx1 = line1.first.m_x - line1.second.m_x;
  double dy1 = line1.first.m_y - line1.second.m_y;
  double dx2 = line2.first.m_x - line2.second.m_x;
  double dy2 = line2.first.m_y - line2.second.m_y;

  double area = dx1*dy2-dy1*dx2;
  if (area < 0)
    return AreaSign::NEGATIVE;
  else if (area > 0)
    return AreaSign::POSITIVE;
  else
    return AreaSign::ZERO;
}

void get_front_back_segs(const pair<Point,Point>& mainLine, const pair<Point,Point>& otherLine,
                    vector<pair<Point,Point>>&frontSegs, vector<pair<Point,Point>>&backSegs)
{
  //get normal
  Point p1 = mainLine.first;
  Point p2 = mainLine.second;
  double dx = p1.m_x-p2.m_x;
  double dy = p1.m_y-p2.m_y;
  Point normal(-dy,dx); // normal to the mainLine   
  
  AreaSign normalSign = cross_product(make_pair(p1,normal),mainLine); 

  Point intersecP(0,0);
  bool is_intersect = get_intersection(mainLine, otherLine, intersecP);

  if(is_intersect){
    //two segments will be spawned
    pair<Point,Point>seg1 = make_pair(intersecP,otherLine.first);     
    pair<Point,Point>seg2 = make_pair(intersecP,otherLine.second);      
    pair<Point,Point>armOfPGram = make_pair(p1,seg1.second);
    AreaSign signSeg1 = cross_product(armOfPGram, mainLine);
    if(signSeg1==normalSign){
      frontSegs.push_back(seg1);
      backSegs.push_back(seg2);
    }else{
      frontSegs.push_back(seg2);
      backSegs.push_back(seg1);
    }
  }else{
    pair<Point,Point>armOfPGram = make_pair(p1,otherLine.first); // it doesn't matter whether 1 or 2 
    AreaSign sign = cross_product(armOfPGram,mainLine);
    if(sign == normalSign){
      frontSegs.push_back(otherLine);
    }else{
      backSegs.push_back(otherLine);
    }
  }
}

void print_segs(const vector<pair<Point,Point>> &segments)
{
  for(int i=0; i<segments.size(); i++){
    pair<Point,Point>p=segments[i];
    cout << "(" << p.first.m_x << "," << p.first.m_y << "),"
       << "(" << p.second.m_x << "," << p.second.m_y << ")" << endl;
  }
}

void print_line(const pair<Point,Point>& line)
{
  cout << "(" << line.first.m_x << "," << line.first.m_y << "),"
       << "(" << line.second.m_x << "," << line.second.m_y << ")" << endl;
}

BSP* create_bsp(const vector<pair<Point,Point>> &segments)
{
  if(segments.size()==0)
    return nullptr;

  pair<Point,Point> line =segments[0];
  BSP* node = new BSP(line);

  /*cout << "line is: " << endl;
  print_line(line);*/

  vector<pair<Point,Point>> backSegs;
  vector<pair<Point,Point>> frontSegs;
  
  for(int i=1; i<segments.size(); i++){
    get_front_back_segs(line,segments[i], frontSegs, backSegs);
  }

  /*cout << "front segs are " << endl;
  print_segs(frontSegs);
  cout << "back segs are " << endl;
  print_segs(backSegs);*/

  node->m_front = create_bsp(frontSegs); 
  node->m_back = create_bsp(backSegs);
  return node;
}

AreaSign get_sign_of_normal(const pair<Point,Point>& line)
{
  Point p1 = line.first;
  Point p2 = line.second;
  double dx = p1.m_x-p2.m_x;
  double dy = p1.m_y-p2.m_y;
  Point normal(-dy,dx); // normal to the mainLine   
  AreaSign normalSign = cross_product(make_pair(p1,normal),line); 
  return normalSign;
}

FrontOrBack get_orienation(BSP* node, const Point& cameraRef)
{
  pair<Point,Point>line = node->m_line;
  AreaSign normalSign = get_sign_of_normal(line);

  Point p1 = line.first;
  pair<Point,Point>armOfPGram = make_pair(p1,cameraRef);
  AreaSign sign = cross_product(armOfPGram,line);

  if(sign==AreaSign::ZERO)
    return FrontOrBack::NONE;

  if(sign==normalSign)
    return FrontOrBack::FRONT;
  else
    return FrontOrBack::BACK;
}

void traverse_tree(BSP* node, const Point& cameraRef)
{
  if(node == NULL)
    return;

  FrontOrBack orientation = get_orienation(node, cameraRef);
   
  if(orientation == FrontOrBack::FRONT){
    traverse_tree(node->m_back, cameraRef);
    print_line(node->m_line);
    traverse_tree(node->m_front, cameraRef);
  }else if (orientation = FrontOrBack::BACK){
    traverse_tree(node->m_front, cameraRef);
    print_line(node->m_line);
    traverse_tree(node->m_back, cameraRef);
  }else{
    traverse_tree(node->m_back, cameraRef);
    traverse_tree(node->m_front, cameraRef);
  }
}

void inorder_print(BSP* node)
{
  if(node==NULL)
    return;
  inorder_print(node->m_front);
  pair<Point,Point>line = node->m_line; 
  print_line(line);
  inorder_print(node->m_back);
}

int main()
{
  vector<pair<Point,Point>>segments;

  // test_case_2
  segments.push_back(make_pair(Point(2,3),Point(4,3)));
  segments.push_back(make_pair(Point(2.0,2.5),Point(2.0,3.5)));
  segments.push_back(make_pair(Point(4.0,2.0),Point(4.8,4.0)));
  segments.push_back(make_pair(Point(0.5,3.5),Point(2.5,1.5)));

/* test_case_1
  segments.push_back(make_pair(Point(1,3),Point(4,3)));
  segments.push_back(make_pair(Point(2.3,4.2),Point(2.3,4.8)));
  segments.push_back(make_pair(Point(1.3,2.2),Point(1.3,2.8)));
  segments.push_back(make_pair(Point(0.5,2.0),Point(0.5,4.0)));
  segments.push_back(make_pair(Point(4.0,2.0),Point(4.8,4.0)));
*/
  BSP* node = create_bsp(segments);
  cout << "=== print ==" << endl;
  inorder_print(node);
  
  Point camera(3.5,2.5);
  cout << "===traverse tree === " << endl;
  traverse_tree(node,camera);
  return 0;
}
