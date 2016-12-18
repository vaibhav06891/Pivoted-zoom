#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/ml.h>
#include <opencv2/ml/ml.hpp>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace cv;
using namespace std;

Mat zooming(Mat img, int zoom_x, int zoom_y, int scale)
{
	int width = img.size().width;
	int height = img.size().height;

	cv::Mat m1(height, width*scale, CV_8UC3); //3-channel
	m1 = Scalar(0,0,0);  //Scalar.val[0-2] used


//-------------------------------- zooming of image-----------------------------------
	//row operations
	int opB,opG,opR;
	for (int i=0;i<height; i++)
	{
		for (int j=0; j<width ; j++)
		{
			for (int count=0; count<scale;count++)
			{
				m1.at<Vec3b>(i,scale*j+count) = img.at<Vec3b>(i,j);
			}
		}
	}

	cv::Mat m(height*scale, width*scale, CV_8UC3); //3-channel
	m = Scalar(0,0,0);  //Scalar.val[0-2] used

	//column operations
	for (int i=0;i<width*scale; i++)
	{
		for (int j=0; j<height ; j++)
		{
			for (int count=0; count<scale;count++)
			{
				m.at<Vec3b>(scale*j+count,i) = m1.at<Vec3b>(j,i);
			}
		}
	}

//----------------------cropping of appropriate part of image----------------------------------
	if( ( zoom_x*scale - width/2)>0)
	{
		if( (zoom_x*scale + width/2)<width){}
		else
			zoom_x=width/2;
	}
	else
		zoom_x=0;

	if( ( zoom_y*scale - height/2)>0)
		{
			if( (zoom_y*scale + height/2)<height){}
			else
				zoom_y=height/2;
		}
		else
			zoom_y=0;

	Mat zoomed = m(Rect(zoom_x,zoom_y,width,height));
	return zoomed;
}

int main(int argc, char** argv)
{
	String filename = argv[1];
	Mat img = imread(filename,1);
	Mat zoom_image;
	int zoom_x, zoom_y;
	int scale;

	int width = img.size().width;
	int height = img.size().height;
	bool flag=true;

	while(flag)
	{
		cout<<"enter the x cordinate of points where you would like to zoom where maximum x co-ord can be: "<< width<<endl;
		cin>>zoom_x;
		if(zoom_x<width)
			flag=false;
	}
	flag=true;

	while(flag)
	{
		cout<<"enter the y cordinate of points where you would like to zoom where maximum y co-ord can be: "<< height<<endl;
		cin>>zoom_y;
		if(zoom_y<height)
			flag=false;
	}



	cout<<"enter the scale of zooming level for the image"<<endl;
	cin >> scale;

	imshow("Original",img);

	Mat zoomed = zooming(img,zoom_x,zoom_y,scale);
	imshow("cropped zoom", zoomed);
	bool write_success = imwrite("pivoted_zoom.jpg", zoomed);  //---saving image to current directory.
	waitKey(0);
	return 0;
}
