#include <wx/wx.h>
#include <wx/image.h>
#include <fstream>
#include <iostream>
#include <string.h>
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
// рисование линии по двум точкам
   void DrawLine(wxPoint one, wxPoint sec);
// установить цвет линий
   void setPen(wxColor a);
// установить цвет заливки
   void setFill(wxColor a);
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
  
     wxRect rec(wxPoint(100,100), wxPoint(50,50));
     this->SetRGB(rec, c.Red(), c.Green(), c.Blue()); 

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
 im.setPen(wxColor(255,255,255));
// нарисовать линию от точки (20,20) до точки (60,20)
 im.DrawLine(wxPoint(20,20),wxPoint(60,20));
 im.DrawLine(wxPoint(20,20),wxPoint(20,60));
 im.DrawLine(wxPoint(20,60),wxPoint(60,60));
 im.DrawLine(wxPoint(60,20),wxPoint(60,60));
 
// Закрасить прямоугольник, в котором точка  (30,30)
 im.FillRec(wxPoint(30,30), wxColor(255,0,0));
// Закрасть одну точку внутри прямоугольника
 im.ColorPoint(wxPoint(40,40),wxColor(0,255,0));
// нарисовать "косую" линию
 im.DrawLine(wxPoint(20,20),wxPoint(30,60));
// сохранить картинку в файл
 im.saveToFile(s); 
}
