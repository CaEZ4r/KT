#include <wx/wx.h>
#include <wx/image.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

// Класс Image - наследник "системного" класса wxImage
// wxImage "умеет" работать с картинками
class Image:public wxImage{
  wxColor pen; // цвет линий
  wxColor fill; // цвет красить
  int w,h; // размер картинки
  public:
// Создать картину из файла (имя - в строке wxString)
   Image(string); 
// создать пустую картину, с фоном back
   Image(int w, int h, wxColor back); 
// деструктор
   ~Image();
   void DrawRec(wxPoint, wxPoint);
// рисование линии по двум точкам
   void DrawLine(wxPoint one, wxPoint sec);
// установить цвет линий
   void setPen(wxColor a);
// установить цвет заливки
   void setFill(wxColor a);
   
   void DrawCirc(wxPoint, int, Image*);
   void DrawTri(wxPoint, wxPoint, wxPoint);
   
// закрасить точку p цветом a
   void ColorPoint(wxPoint p, wxColor a);
// закрасить прямоугольник цветом а, внутри которого точка p
   void FillRec(wxPoint p, wxColor a);
// сохранить картинку в файл. Имя файла в строке
   void saveToFile(string);
};


// Абстрактный класс
class Fig{
   wxPoint center;
protected:
// объекту нужен указатель на картинку (на чем будет рисовать)
  Image *im;
public:
    Fig(Image*);
// Виртуальные функции
    virtual void Draw()=0;
};

class Line:public Fig{
  wxPoint one,sec; // концы отрезка
public:
// Конструктор с указателем на картинку
   Line(Image*);
// Установка концов отрезка
   void setPoints(wxPoint a, wxPoint b);
// Цвет линии
   void setColor(wxColor cl);
// Переопределение виртуальной функции Draw()
   void Draw();
//переопределить самостоятельно
      void moveTo(wxPoint);
      void Fill(wxColor);
};

class Rec:public Fig{
	wxPoint one, sec;
public:
	Rec(Image*);
	void setPoints(wxPoint, wxPoint);
	void setColor(wxColor);
	void Draw();
};

class Tri:public Fig{
	wxPoint one, sec, thd;
public:
	Tri(Image*);
	void setPoints(wxPoint, wxPoint, wxPoint);
	void setColor(wxColor);
	void Draw();
};

class Circ:public Fig{
	wxPoint cent;
	int R;
public:
	Circ(Image*);
	void setPointnRad(wxPoint, int);
	void setColor(wxColor);
	void Draw();
};



// Получаем указатель на картинку
Fig::Fig(Image* m){
   im = m;
};

Circ::Circ(Image* a):Fig(a){};
void Circ::setPointnRad(wxPoint a, int b){
	R = b;
	cent = a;
};
void Circ::setColor(wxColor cl){	
	im->setPen(cl);
};
void Circ::Draw(){
	im->DrawCirc(cent, R, im);
};

Tri::Tri(Image *a):Fig(a){};
void Tri::setPoints(wxPoint a, wxPoint b, wxPoint c){
	one = a;
	sec = b;
	thd = c;
};
void Tri::setColor(wxColor cl){
	im->setPen(cl);
};
void Tri::Draw(){
	im->DrawTri(one, sec, thd);
};

Rec::Rec(Image *a):Fig(a){};
void Rec::setPoints(wxPoint a, wxPoint b){
	one = a;
	sec = b;
};

void Rec::setColor(wxColor cl){
	im->setFill(cl);
};
void Rec::Draw(){
	im->DrawRec(one, sec);
};
// Конструктор. Передача адреса картинки
Line::Line(Image* a):Fig(a){};
// Установка точек
void Line::setPoints(wxPoint a, wxPoint b){
  one = a;
  sec = b;
};
// Установка цвета
void Line::setColor(wxColor cl){
  im->setPen(cl);
};

// переопределение виртуальной функции
// рисование
void Line::Draw(){
   im->DrawLine(one,sec);
};

// Реализация

Image::Image( string file):wxImage(wxString(file.c_str(), wxConvUTF8),wxBITMAP_TYPE_PNG){

 

  w = GetWidth();
  h = GetHeight();
 
};


Image::Image(int w, int h, wxColor back):wxImage(w,h){
   wxInitAllImageHandlers();
   wxPoint one(1,1),sec(w-1,h-1);
   wxRect rec(one,sec);
   this->SetRGB(rec, back.Red(),back.Green(),back.Blue());   
};

void Image::setPen(wxColor a){
       pen = a;
};
void Image::setFill(wxColor a){	
   fill = a;
};
void Image::ColorPoint(wxPoint p, wxColor c){
    wxRect rc(p,p);
    this->SetRGB(rc,c.Red(),c.Green(),c.Blue());
};
void Image::FillRec(wxPoint p, wxColor c){
     wxColor place(GetRed(p.x,p.y),GetGreen(p.x,p.y),GetBlue(p.x,p.y));
     wxColor check(GetRed(p.x,p.y - 1),GetGreen(p.x,p.y - 1),GetBlue(p.x,p.y - 1));
     int yh,yl,xl,xp;
     int x,y;
 //    cout << (place != c)<<endl;
     for(y = p.y-1 ; place == check; y--){
          check.Set(GetRed(p.x,y), GetGreen(p.x,y), GetBlue(p.x,y));
        
     };
       yh = y +1;
     check.Set(GetRed(p.x,p.y + 1), GetGreen(p.x,p.y + 1), GetBlue(p.x,p.y + 1));
     for(y = p.y + 1 ; place == check; y++){
          check.Set(GetRed(p.x,y), GetGreen(p.x,y), GetBlue(p.x,y));
     };
       yl = y - 1;
      check.Set(GetRed(p.x - 1,p.y ), GetGreen(p.x - 1,p.y), GetBlue(p.x - 1,p.y));
     for(x = p.x - 1 ; place == check; x--){
          check.Set(GetRed(x,p.y), GetGreen(x,p.y), GetBlue(x,p.y));
     };
       xl = x + 1;
     check.Set(GetRed(p.x + 1,p.y), GetGreen(p.x + 1,p.y), GetBlue(p.x + 1,p.y));
     for( x = p.x + 1 ; place == check; x++){
          check.Set( GetRed(x,p.y), GetGreen(x,p.y), GetBlue(x,p.y));
     };
       xp = x - 1; 
       
};

void Image::DrawRec(wxPoint a, wxPoint b){
	wxRect rec(a, b);
     this->SetRGB(rec, pen.Red(),pen.Green(), pen.Blue());
};

void Image::DrawTri(wxPoint a, wxPoint b, wxPoint c){
	DrawLine(a , b);
	DrawLine(b, c);
	DrawLine(a, c);
};

void Image::DrawLine(wxPoint one, wxPoint sec){
   int b,f;
   if (one.x < sec.x){
      b = one.x;
      f = sec.x;
   }else{
     f = one.x;
     b = sec.x;
   }
   for(int x = b; x < f ; x++){
    int y=((sec.y - one.y )  * x + (sec.x * one.y - one.x * sec.y )) / (sec.x - one.x );
 //    cout<<"x="<<x<<" y="<<y<<endl;
     wxPoint fr(x,y);
     wxRect rec(fr,fr);
     this->SetRGB(rec, pen.Red(), pen.Green(), pen.Blue());
   } 

  if (one.y < sec.y){
      b = one.y;
      f = sec.y;
   }else{
     f = one.y;
     b = sec.y;
   }
  for(int y = b; y < f ; y++){
    int x = ((sec.x - one.x ) * y + (sec.y * one.x - one.y * sec.x )) / (sec.y -  one.y);
 //    cout<<"x="<<x<<" y="<<y<<endl;
     wxPoint fr(x,y);
     wxRect rec(fr,fr);
     this->SetRGB(rec, pen.Red(), pen.Green(), pen.Blue());
   } 
};

void Image::DrawCirc(wxPoint a, int R, Image *im){
	int z1, z2;
	int k1, k2;
	for (int i = a.x - R; i < a.x + R + 1; i ++) {
		z1 = a.y + sqrt(pow(R, 2) - pow(a.x - i, 2));
		z2 = a.y - sqrt(pow(R, 2) - pow(a.x - i, 2));
		im->ColorPoint(wxPoint(i,z1),wxColor(255, 0,0));
		im->ColorPoint(wxPoint(i,z2),wxColor(255, 0,0));
	}
	for (int i = a.y - R; i < a.y + R + 1; i ++) {
		k1 = a.x + sqrt(pow(R, 2) - pow(a.y - i, 2));
		k2 = a.x - sqrt(pow(R, 2) - pow(a.y - i, 2));
		im->ColorPoint(wxPoint(k1,i),wxColor(255, 0,0));
		im->ColorPoint(wxPoint(k2,i),wxColor(255, 0,0));
	}
};

void Image::saveToFile(string file){
  wxString st1(file.c_str(), wxConvUTF8);
  this->SaveFile(st1,wxBITMAP_TYPE_PNG);
};

Image::~Image(){
   wxImage::Destroy();
};

// Пример использования

int main(){

  Image im(600,600,wxColor(255,255,255));
// Создаем Line. передаем адрес картинки
 Line f1(&im);
// установка точек на картинке
  f1.setPoints(wxPoint(10,150),wxPoint(190,300));
// установка цвета
  f1.setColor(wxColor(255,0,255));
// рисование
  f1.Draw();
  
  Rec f2(&im);
  f2.setPoints(wxPoint(30, 30), wxPoint(140, 100));
  f2.setColor(wxColor(255, 255, 0));
  f2.Draw();
  
  Circ f3(&im);
  f3.setPointnRad(wxPoint(300, 300), 60);
  f3.setColor(wxColor(0, 255, 0));
  f3.Draw();
  
  Tri f4(&im);
  f4.setPoints(wxPoint(50, 500), wxPoint(100, 400), wxPoint(200, 600));
  f4.setColor(wxColor(0, 255, 255));
  f4.Draw();
  
  string s="vpic.png";
 im.saveToFile(s); 
}
