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
   void DrawRec();
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

void Image::DrawRec(){
	wxRect rec(wxPoint(1,1), wxPoint(30,30));
     this->SetRGB(rec, 255, 0, 0);
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
// Создать "пустую" желтую картинку размером 200х200
 Image im(600,600,wxColor(255,255,0));
// имя файла картинки
 string s = "f1.png";
// установить цвет линий - белый
 im.setPen(wxColor(255,0,0));
// нарисовать линию от точки (20,20) до точки (60,20)

im.DrawCirc(wxPoint(400, 400), 30, &im);
 im.DrawLine(wxPoint(300,10),wxPoint(400, 40));
 im.DrawRec();
im.DrawTri(wxPoint(100, 100), wxPoint(100, 200), wxPoint(300, 200));
 
 im.ColorPoint(wxPoint(300,300),wxColor(255, 0,0));

// сохранить картинку в файл
 im.saveToFile(s); 
}
