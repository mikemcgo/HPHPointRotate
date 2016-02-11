//
//  main.cpp
//  Scaling for HPH Airfoil
//
//  Created by Mike McGookey on 11/12/13.
//  Copyright (c) 2013 Mike McGookey. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace std;

void scale(string filename, double scalar, double offsetx,double offsety,double offsetz,double rotateX,double rotateY,double angle);
void rotate_point(double cx,double cy,double angle,double & valueX,double & valueY);

int main()
{
    
	//Declarations
	string filename,rotate;
	double scalar,offsetx,offsety,offsetz,rotateX,rotateY,angle;
	bool run=1;
    
	//File to scale
	cout << "Please enter the filename" << endl;
	cin >> filename;
    
	while(run==1)
	{
        cout << "What scale do you want applied?, Enter 0 to exit" <<endl;
        cout << "Be aware Solidworks defaults to a 1 Meter scale" << endl;
        cin >> scalar;

        if(scalar==0)
		{
			run=0;
            cout << "Exiting\n";
			break;
		}
        cout << "What should the x offset be?" << endl;
        cin >> offsetx;
        cout << "What should the y offset be?" << endl;
        cin >> offsety;
        cout << "What should the z offset be?" << endl;
        cin >> offsetz;

		cout << "Do the points need to be rotated? (y/n)" << endl;
        cin >> rotate;
		
		if(rotate=="y"){
        cout << "What x-coordinate should the curve be rotated around? Give in terms of scaled model" << endl;
        cin >> rotateX;
        cout << "What y-coordinate should the curve be rotated around? Give in terms of scaled model" << endl;
        cin >> rotateY;
        cout << "What angle of rotation is necessary?" << endl;
        cin >> angle;
        }
		else{
			rotateX=0;
			rotateY=0;
			angle=0;
		}

        if(run!=0)
            scale(filename,scalar,offsetx,offsety,offsetz,rotateX,rotateY,angle);
	}
	
}



void scale(string filename, double scalar, double offsetx,double offsety,double offsetz,double rotateX,double rotateY,double angle)
{
    cout << scalar;
    //Variable Creation
	double valueX,valueY;
	string newName;
    string a="Scalar_OffsetX_Y_Z_Angle_";
    string scalestring= std::to_string(scalar).erase(4,4).append("_");
    string xoffset= to_string(offsetx).erase(4,4).append("_");
    string yoffset= to_string(offsety).erase(4,4).append("_");
    string zoffset= to_string(offsetz).erase(4,4).append("_");
    string angleprint = to_string(angle).erase(4,4).append("_");
    
    
    
    //Open input
    ifstream in;
    in.open(filename.c_str());
    if(!in.fail())
    {
        
        //Creating new file name
        newName= a.append(scalestring).append(xoffset).append(yoffset).append(zoffset).append(angleprint).append(filename);
        cout << endl << newName << " created" << endl << endl;
        
        //Create output file
        ofstream out;
        out.open(newName.c_str());
        
        
        //Read in first
        in >> valueX >> valueY;
        
		//cout <<"valueX = " << valueX << " valueY = " << valueY << " out\n";
        
        //Start readin and process loop
        while(!in.fail())
        {
            valueX=valueX*scalar;
            valueY=valueY*scalar;
			//cout <<"valueX = " << valueX << " valueY = " << valueY << " start\n";

            if(angle==0)
                {
					out << (valueX+offsetx) << " " << (valueY+offsety) << " " << offsetz << endl;
                }
            else if(angle!=0)
                {
                    rotate_point(rotateX, rotateY, angle, valueX, valueY);
                    out << valueX+offsetx/100 << " " << valueY+offsety/100 << " " << offsetz << endl;
                }
            in >> valueX >> valueY;
            //cout <<"valueX = " << valueX << " valueY = " << valueY << " in\n";

            
        }
        out.close();
    }
    else
    {
        cout << "File open failed, please exit and restart" << endl << endl;
        
    }
    in.close();
}

  
void rotate_point(double cx,double cy,double angle,double & valueX,double & valueY)
  {
      double pi=acos(-1);
      angle=angle*(pi/180);
      float s = sin(angle);
      float c = cos(angle);
      
      //Translate to original
      
      valueX-=cx;
      valueY-=cy;
      
      
      // rotate point
      float xnew = valueX * c - valueY*s;
      float ynew = valueX * s + valueY*c;
      
      // translate point back:
      valueX = xnew + cx;
      valueY = ynew + cy;
  }
  
