/*
 *  ofInterObj.h
 *  
 *
 *  Created by Exhibits on 1/4/2554.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _UIObj
#define _UIObj

#include "ofShapes.h"
#include "ofNewShapes.h"
#include "../extendedUtils/ofFont.h"

enum ofVariableName {
	OF_X_VAR, OF_Y_VAR, OF_W_VAR, OF_H_VAR
};

class ofInterObj {
protected:
	bool bOver,bPressed;
	double * X, * Y, * W, *H;
public:
	string title;
  ofPoint relPos,relMouse;
	double x,y,w,h;
	ofInterObj(){
		bOver=bPressed=false;
		relPos.x=relPos.y=relMouse.x=relMouse.y=x=y=w=h=0;
	}
	ofInterObj(double xint, double yint, double wid, double hgt){
		bOver=bPressed=0;
		x=xint,y=yint;
		w=wid, h=hgt;
    relPos.x=relPos.y=relMouse.x=relMouse.y=0;
	}
	void bind(double & num,ofVariableName which){
		switch (which) {
			case OF_X_VAR:
				X=&num;
				break;
			case OF_Y_VAR:
				Y=&num;
				break;
			case OF_W_VAR:
				W=&num;
				break;
			case OF_H_VAR:
				H=&num;
				break;
			default:
				break;
		}
	}
	void cSetup(double xint, double yint, double wid, double hgt){
		bOver=bPressed=0;
		x=xint,y=yint;
		w=wid, h=hgt;
	}
	bool over(double xint, double yint){
		return bOver=(xint>x&&xint<x+w&&yint>y&&yint<y+h);
	}
	bool pressed(){ return bPressed; }
	
	void move(double xint, double yint){
		x=xint, y=yint;
	}
	
	void augmentPos(double xint, double yint){
		x+=xint, y+=yint;
	}
	
	void changeSize(double wid, double hgt){
		w=wid, h=hgt;
	}
	void scale(double prct){
		w*=prct, h*=prct;
	}
	void resize(double prctw,double prcth){
		w*=prctw, h*=prcth;
	}
	virtual void setPressed(bool state){
		bPressed=state;
	}
	void registerEvents();
	virtual bool clickDown(int _x,int _y){return false;}
	virtual bool clickUp(int _x, int _y){return false;}
	virtual bool clickUp(){return false;}
	virtual void drag(int _x, int _y){}
	virtual void motion(int _x, int _y){}
	virtual void keyboard(char k){}
	virtual void update(){}
	virtual void draw(int _x, int _y){}
	virtual void setup(){}
	void draw(){
		draw(x,y);
	}
};

vector<ofInterObj *> & interObjects();

class ofInterGroup : public ofInterObj {
	virtual bool clickDown(int _x,int _y){return false;}
	virtual bool clickUp(int _x, int _y){return false;}
	virtual bool clickUp(){return false;}
	virtual void drag(int _x, int _y){}
	virtual void move(int _x, int _y){}
	virtual void keyboard(char k){}
	virtual void update(){}
	virtual void draw(int _x, int _y){}
	void draw(){
		draw(x,y);
	}
};

template <class T>
class ofGroup : public ofInterObj {
  vector<T> objects;
  bool bInHand;
public:
  T & operator[](int i){
    return objects[i];
  }
  unsigned int size(){
    return objects.size(); 
  }
  bool clickDown(int _x,int _y){return false;}
	bool clickUp(int _x, int _y){return false;}
	bool clickUp(){return false;}
	void drag(int _x, int _y){}
	void move(int _x, int _y){}
	void keyboard(char k){}
	void update(){}
	void draw(int _x, int _y){}
};

#endif