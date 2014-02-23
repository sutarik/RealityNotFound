#include "Aruco/arucothread.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Aruco/arucocore.h"
#include <QFileInfo>
#include <QDebug>

using namespace ArucoModul;

ArucoThread::ArucoThread(void)
{
	cancel=false;
}

ArucoThread::~ArucoThread(void)
{
}



void ArucoThread::run()
{
	// this code will be changed soon
	cv::Mat frame;
	CvCapture *capture;
	QMatrix4x4 mat;
	QString filename = "../share/3dsoftviz/config/camera.yml";

	// this must do camera singleton
	capture = cvCreateCameraCapture(1);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 640);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 480);

	QFileInfo file(filename);
	if( ! file.exists() ){
		qDebug() << "File " << file.absoluteFilePath() << " does Not exist!";
	}
	ArucoCore aCore(filename);


	//while(!cancel) {
	for(int i=0; i<50; i++ ) {
		// doing aruco work in loop
		// get image from camera
		// add image to aruco and get matrix
		// emit matrix


		frame = cvQueryFrame(capture);
		mat = aCore.getDetectedMatrix(frame);

		// test print of matrix if changed
		QString str;
		str = QString::number(mat.data()[0],'g' ,1  );
		str += " " +  QString::number(mat.data()[1], 'g', 2);
		str += " " +  QString::number(mat.data()[2], 'g', 3);
		qDebug() << i << ": " << str;
		msleep(200);

	}
	cvReleaseCapture( &capture );

}


void ArucoThread::setCancel(bool set){
	this->cancel=set;
}

void ArucoThread::pause()
{
	this->cancel=true;
}

