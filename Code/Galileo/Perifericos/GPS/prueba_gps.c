#include "gps_robocol.h"

int main(){

	gps_build("/home/german/GitHub/RobocolERC2015/Code/Galileo/Perifericos/GPS/gps.log");
	gps_start();
	sleep(10);
	printf("Stopping\n");
	gps_stop();

	struct gps_dev datos;
	gps_getData(&datos);

	printf("%f\n",datos.latitude );

	return 0;	
}