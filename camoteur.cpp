#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <fcntl.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>


//g++ camoteur.cpp -o camoteur -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio
/*pour récupérer les test dans test.txt:
     ./cap_test > test.txt
      > ou >> pour écraser garder les test précédent
      */

using namespace cv;


//lecture (read) fonctionnel
typedef struct 
{
	char *namePort;//nom du port
	int fDesc;// numeros du flux

	
}serial_com;

void serial_open( serial_com *sc){
	sc->fDesc = open(sc->namePort,O_RDWR);
}

void serial_close(serial_com *sc){
	close(sc->fDesc);
}


void serial_write(serial_com *sc, char command){
	int size;
	char saisie[1];
	char buffer[127];
	serial_open(sc);
	//while(1){
		size = read(sc->fDesc, buffer, 1);
		strcpy(saisie, &command);
		write(sc->fDesc, &saisie, 1);
	//}
	serial_close(sc);
}

void directionDecisionX(){}

void directionDecisionY(){}




/*void serial_close(serial_com *sp){
	close(sp->fDesc);
}*/

int main (int, char**) {
	time_t timeBegin = time(NULL); //Start counting time in seconds;
	int pid_px,pid_ix, pid_dx, pidX;//pid de la position de l'objet par rapport à la caméra sur l'axe des abcisses
	int pid_py,pid_iy, pid_dy, pidY;//pid de la position de l'objet par rapport à la caméra sur l'axe des ordonnées
	double Kp, Ki, Kd;// Coefficient des régulateur
	//adapter le port série au port correspondant à l'arduino
	/*serial_com scom;
	scom.namePort = "/dev/ttyACM0";*/
	char buffer[50];
	int i,j,count;
	double averagePlace;
	Vec3f pixel;
	//int time;
	//int timePrev = 1;
	//float elapsedTime = 1;
	float time = 0;

    VideoCapture cap(0); // open the default camera, a changer suivant le pc
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame;
    namedWindow("MyCam",1);

    
  
  
    cap.set(CV_CAP_PROP_FRAME_WIDTH,320);  //taille de la fenetre
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,240); //au dela de 320*240

    int xmilieu = 160;
    int ymilieu = 120;
    int x, y, xAver, yAver;

    pid_px=0;
    pid_py=0;

    pid_ix=0;
    pid_iy=0;

    pid_dx=0;
    pid_dy=0;


    Kp = 2;
    Ki = 0;
    Kd = 0;

	MatIterator_<Vec3b> it, end;
    while(1){
    	int n=1;

    	int averagePosx;
    	int averagePosy;

    	int erreurX;
    	int erreurY;
    	int olderreurX = 0;
    	int olderreurY = 0;
    	count = 0, xAver=0, yAver=0;
    	
        if(cap.read(frame)){// get a new frame from camera

            for( it = frame.begin<Vec3b>(), end = frame.end<Vec3b>(); it != end; ++it, i++, count++){
            	//parcours de la fenêtre tel un tableau à une dimension

	              if ((*it)[2]>= 2*(*it)[1] && (*it)[2]>145){ //si le pixel rouge a une valeur 2.5 fois sup aux bleu et vert
	                //on garde l'image en rouge
	                
	                (*it)[0] = 200;//2
	                (*it)[1] = 0;//1
	                (*it)[2] = 140;//1
	                
	                x=count%320;
	                y=count/320;

	                xAver+=x;
	                yAver+=y;

	                n++;
	              	

	              }
	              else{
	              	//tout le reste est changé en noir
	              	/*(*it)[0] = 0;
	              	 (*it)[1] = 0;
	                 (*it)[2] = 0;*/
	              }

            }
           
			/*
            //calcul des coordonné du centre de l'objet rouge
            averagePosx= xAver/n;
            averagePosy= yAver/n;

            //le centre de l'objet rouge doit être au centre de l'image (l'erreur en x et y sera alors nul)
            erreurX = xmilieu - averagePosx;
            erreurY = ymilieu - averagePosy;

            //calcul du régulateur proportionnel
            pid_px =Kp*erreurX;
            pid_py =Kp*erreurY;

            //calcul du regulétaeur intégral
            pid_ix =(Ki*erreurX);
            pid_iy =(Ki*erreurY);

            //calcul du régulateur dérivé
           // pid_dx=Kd*((erreurX - olderreurX)/elapsedTime);//Kd*((error - previous_error)/elapsedTime)
           // pid_dy=Kd*((erreurY - olderreurY)/elapsedTime);

            //calcul du régulateur pid
            pidX = pid_px + pid_ix ;//+ pid_dx;
            pidY = pid_py + pid_iy ;*///+ pid_dy;


            //printf("x=%d\t y=%d\n", averagePosx, averagePosy);

            /*if (erreurX >25){
            	//while(pidX>1){
            		serial_write(&scom, 'f');
            		
            	//}
            	
            }
            if (erreurX<(-25)){
            	//while(pidX<-1){
            		serial_write(&scom, 'm');
            	//}
            }

            if (erreurX >17){
            	//while(pidX>1){
            		serial_write(&scom, 'g');
            		
            	//}
            	
            }
            if (erreurX<(-17)){
            	//while(pidX<-1){
            		serial_write(&scom, 'l');
            	//}
            }

            if (erreurX >10){
            	//while(pidX>1){
            		serial_write(&scom, 'h');//q
            		
            	//}
            	
            }
            if (erreurX<(-10)){
            	//while(pidX<-1){
            		serial_write(&scom, 'k');//d
            	//}
            }

            if (erreurX >5){
            	//while(pidX>1){
            		serial_write(&scom, 'q');
            		
            	//}
            	
            }
            if (erreurX<(-5)){
            	//while(pidX<-1){
            		serial_write(&scom, 'd');
            	//}
            }

           
            //printf("%d ", ymilieu);

            //printf("%d  ", erreurX);
            //printf("%d \n", erreurY);
			
	  		olderreurX = erreurX;
	  		olderreurY = erreurY;*/
	     	//printf("%0f\n", pidX);

	     imshow("MyCam", frame);
        }
       waitKey(10);
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
	

	return 0; 
}