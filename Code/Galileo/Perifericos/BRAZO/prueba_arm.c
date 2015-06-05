#include "arm_robocol.h"

arm_st prueba_ph(ph_dev* devptr);
arm_st prueba_st(stp_device* devptr);
size_t size=40;
char* line=malloc(size);

int main(int argc, char const *argv[]){

stp_device* stepper;
ph_dev* ph;
uint8_t finished=0;


while(!finished){
printf("Test de funcionamiento de Brazo (URC 2015-ROBOCOL).\n Utilice una de los siguientes comandos:\n"
		"\tstp\t\t\tSeleccionar el stepper que desea mover.\n"
		"\tph\t\t\tSeleccionar el puente h a movilizar.\n"
		"\texit\t\t\tSalir del programa\n");

	printf("Ingrese un comando\n");
	getline(&line,&size,stdin);
	printf("El comando ingresado fue: %s \n",line);
	if (!strcmp(line,"stp\n")){

		while(!finished){
			printf("Ingrese el número del stepper que desea utilizar:\n"
					"\t1\t\t\tMotor encargado de la supinación\n"
					"\t2\t\t\tMotor encargado de elevación de la garra\n"
					"\t3\t\t\tMotor encargado de la apertura de la garra\n"
					"\tbck\t\t\tRegresar al anterior menú.\n");
			printf("Ingrese un comando\n");
			getline(&line,&size,stdin);

			if (!strcmp(line,"1\n")){
				if(arm_get_stp(SUP,stepper)){
					printf("Error en la captura del stp_device con el número %s asociado\n",*line );
				}
				prueba_st(stepper);
			}else if(!strcmp(line,"2\n")){
				if(arm_get_stp(WRIST,stepper)){
					printf("Error en la captura del stp_device con el número %s asociado\n",*line );
				}
				prueba_st(stepper);
			}else if(!strcmp(line,"3\n")){
				if(arm_get_stp(CLAW,stepper)){
					printf("Error en la captura del stp_device con el número %s asociado\n",*line );
				}
				prueba_st(stepper);
			}else if(!strcmp(line,"bck\n")){
				finished=1;
			}else{
				printf("El comando ingresado no es válido. Intente de nuevo\n");
			}

		}
		finished=0;
	}else if(!strcmp(line,"ph\n")){
		while(!finished){
			printf("Ingrese el número del puente H que desea utilizar:\n"
					"\t1\t\t\tPuente H del actuador lineal inferior\n"
					"\t2\t\t\tPuente H del actuador lineal superior\n"
					"\t3\t\t\tMotor encargado del giro del brazo\n"
					"\tbck\t\t\tRegresar al anterior menú.\n");
			printf("Ingrese un comando\n");
			getline(&line,&size,stdin);

			if (!strcmp(line,"1\n")){
				if(arm_get_stp(BACTUATOR,stepper)){
					printf("Error en la captura del stp_device con el número %s asociado\n",*line );
				}
				prueba_ph(ph);
			}else if(!strcmp(line,"2\n")){
				if(arm_get_stp(UACTUATOR,stepper)){
					printf("Error en la captura del stp_device con el número %s asociado\n",*line );
				}
				prueba_ph(ph);
			}else if(!strcmp(line,"3\n")){
				if(arm_get_stp(BMOTOR,stepper)){
					printf("Error en la captura del stp_device con el número %s asociado\n",*line );
				}
				prueba_ph(ph);
			}else if(!strcmp(line,"bck\n")){
				finished=1;
			}else{
				printf("El comando ingresado no es válido. Intente de nuevo\n");
			}

		}
		finished=0;
	}else if(!strcmp(line,"exit\n")){
		finished=1;
	}
}
return 0;
}


arm_st prueba_ph(ph_dev* devptr){
	uint8_t finished=0;
	uint8_t temp, vel,corr,est,debug;

	int buf;

	printf("----------Driver Puente H----------\n");

	if(ph_setEstado(devptr,32)){
		printf("Error en set de Estado a 32(prueba_ph.c)\n");
		perror("Descripción");		
	}
	if(ph_setPWM(devptr,0)){
		printf("Error en set de PWM(prueba_ph.c)\n");
		perror("Descripción");	
	}

	while(!finished){

		printf("Test de funcionamiento de Puente H (URC 2015-ROBOCOL).\n Utilice una de los siguientes comandos:\n" 
		"\t enable\t\t\t-Habilita o deshabilita el puente H. Valores de entrada 1 o 0\n"
		"\t getvel\t-Imprime la velocidad actual del motor\n "
		"\t gettemp\t-Imprime la temperatura actual del motor\n "
		"\t getcorr\t-Imprime la corriente actual que atravieza el motor\n"
		"\t getstate\t \t-Imprime el estado de operación actual del motor\n"
		"\t pwm\t\t-Cambia ciclo útil del PWM. Valor de entrada entre 0 y 255\n"
		"\t dir\t-Cambia la dirección de giro del motor. Valor de entrada 1 o 0\n"
		"\t setvel\t-Cambia la velocidad objetivo del controlador. Valor de entrada entre ------\n"
		"\t setstate\t \t-Cambia el estado de operación del puente H. Valor de entrada entre 16 o 32 TODO: Parser\n"
		"\t kic\t\t-Cambia el valor de KIC. Valor de entrada entre 0 y 255\n"
		"\t kpc\t\t-Cambia el valor de KPC. Valor de entrada entre 0 y 255\n"
		"\t kiv\t\t-Cambia el valor de KIV. Valor de entrada entre 0 y 255\n"
		"\t kpv\t\t-Cambia el valor de KPV. Valor de entrada entre 0 y 255\n"
		"\t sp_vel\t\t\t-Cambia el valor de SP_VELOCIDAD. Valor de entrada entre 0 y 255\n"
		"\t sp_cor\t\t\t-Cambia el valor de SP_CORRIENTE. Valor de entrada entre 0 y 255\n"
		"\t motor\t\t\t-Cambia el motor. Valor de entrada 1 o 2\n"
		"\t debug\t\t\t-Permite rápido envia de CAMBIAR_PWM con un valor de 0x5A\n"
		"\tbck\t\t\tRegresar al anterior menú.\n");


		printf("Ingrese un comando\n");
		getline(&line,&size,stdin);
		printf("El comando ingresado fue: %s \n",line);

		//Mediciones
		if(!strcmp(line,"gettemp\n")){
			ph_getTemperatura(devptr,&temp);
			printf("Temperatura: %d \n",temp);

		}else if(!strcmp(line,"getvel\n")){
			ph_getVelocidad(devptr,&vel);
			printf("Velocidad: %d \n",vel);

		}else if(!strcmp(line,"getcorr\n")){
			ph_getCorriente(devptr,&corr);
			printf("Corriente: %d \n",corr);

		}else if(!strcmp(line,"getstate\n")){
			ph_getEstado(devptr,&est);
			printf("Estado: %d \n",est);
		
		//Setters
		}else if(!strcmp(line,"pwm\n")){
			printf("Ingrese el PWM deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			if(ph_setPWM(devptr,(uint8_t)buf)){
				printf("Error en set de pwm\n");
			}

		}else if(!strcmp(line,"dir\n")){
			printf("Ingrese la direccion deseada ( 1 o 0):\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando direccion a: %d \n",buf);
			ph_setDireccion(devptr,buf);

		}else if(!strcmp(line,"setvel\n")){
			printf("Ingrese la velocidad deseada:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando velocidad a: %d \n",buf);
			ph_setVel(devptr,buf);

		}else if(!strcmp(line,"setstate\n")){
			printf("Ingrese el estado deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando estado a: %d \n",buf);
			ph_setEstado(devptr,buf);

		}else if(!strcmp(line,"kpv\n")){
			printf("Ingrese el KPV deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando KPV a: %d \n",buf);
			ph_setKPV(devptr,buf);

		}else if(!strcmp(line,"kiv\n")){
			printf("Ingrese el KIV deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando KIV a: %d \n",buf);
			ph_setKIV(devptr,buf);

		}else if(!strcmp(line,"kpc\n")){
			printf("Ingrese el KPC deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando KPC a: %d \n",buf);
			ph_setKPC(devptr,buf);

		}else if(!strcmp(line,"kic\n")){
			printf("Ingrese el KIC deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando KIC a: %d \n",buf);
			ph_setKIC(devptr,buf);

		}else if(!strcmp(line,"sp_vel\n")){
			printf("Ingrese el SP_VELOCIDAD deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando SP_VELOCIDAD a: %d \n",buf);
			ph_setVel(devptr,buf);

		}else  if(!strcmp(line,"sp_cor\n")){
			printf("Ingrese el SP_CORRIENTE deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando SP_CORRIENTE a: %d \n",buf);
			ph_setCorriente(devptr,buf);

		}else  if(!strcmp(line,"move\n")){
			printf("Ingrese la posición deseada:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando posición a: %d \n",buf);
			ph_moveToAngle(devptr,buf);

		}else  if(!strcmp(line,"enable\n")){
			printf("Ingrese 1 para activar, 0 para desactivar:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando enable a: %d \n",buf);
			if(buf){
				ph_enable(devptr);
			}else{
				ph_disable(devptr);
			}

		}else if(!strcmp(line,"motor\n")){
			printf("Ingrese 1 para Motor1, 2 para Motor2:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando Motor a: %d \n",buf);
			if(buf==1){
				devptr=&dev1;
				printf("%d\n", (*devptr).pin_in_b);
			}else{
				devptr=&dev2;
				printf("%d\n", (*devptr).pin_in_b);
			}

		}else if(!strcmp(line,"exit\n")){
			printf("Cerrando el programa. Adiós\n");
			break;
		}else if(!strcmp(line,"debug\n")){
			while(getchar()!='q'){
				printf("%c\n",debug);
				ph_setPWM(devptr,debug);
			}
		}else if(!strcmp(line,"bck\n")){
			finished=1;
		}
		printf("--------------------------------------------------------------\n");
	}
	return ARM_OK;
}


arm_st prueba_st(ph_dev* devptr){

int32_t position,status,config=0;
uint8_t step,ocd,tval;
uint8_t alarm,corr,debug;
int32_t buf,buf2;
double fbuf;

debug=0x5A;

printf("----------Driver Stepper----------\n");
// stp_device dev1;
// dev1.pin_cs=PIN7;
// dev1.pin_dir=PIN5;
// dev1.pin_stndby=1;
// dev1.pin_flag=0;
// dev1.exp=EXP2;
// dev1.pin_pwm=3;
// dev1.gear_ratio=15;
// dev1.step=7;
// dev1.period=5000;


(void) signal(SIGINT, emergency_disable);

if(stp_master_disable(devptr)){
	printf("Error en Master Disable inicial\n");
}


if(stp_driver_enable(devptr)){
	printf("Error en driver enable inicial\n" );
}


if(stp_setStepSel(devptr,2)){
	printf("Error en setStepSel inicial\n" );
}

	while(!finished){
		printf("------------------Motor de pasos configurado------------------\n");
		printf("Bienvenido al test de funcionamiento de Stepper(ERC 2015-ROBOCOL).\n Utilice una de los siguientes comandos:\n" 
				"\t master-enable\t\t\t-Habilita el stepper\n"
				"\t en-clk\t\t\t\t-Habilita clk del stepper\n"
				"\t en-driver\t\t\t-Habilita diver del stepper\n"
				"\t en-out\t\t\t\t-Habilita salidas del stepper\n"
				"\t s\t\t\t\t-Deshabilita el stepper\n"
				"\t dis-clk\t\t\t-Deshabilita clk del stepper\n"
				"\t dis-driver\t\t\t-Deshabilita driver del stepper\n"
				"\t dis-out\t\t\t-Deshabilita salidas del stepper\n"
				"\t status\t\t\t\t-Imprime el STATUS register\n "
				"\t getconfig\t\t\t-Imprime el CONFIG register\n "
				"\t getstep\t\t\t-Imprime el estado actual del selector de paso\n"
				"\t getalarm\t\t\t-Imprime el registro de alarmas\n"
				"\t getpos\t\t\t-Imprime el registro posición absoluta\n"
				"\t getocdt\t\t\t-Imprime el Overcurrent Detection Threshold actual\n"
				"\t gettval\t\t\t-Retorna TVAL\n"
				"\t period\t\t\t-Cambia el periodo del step\n"
				"\t dir\t\t\t\t-Cambia la direccion de giro del stepper\n"
				"\t setconfig\t\t\t-Imprime el CONFIG register\n "
				"\t setstep\t\t\t-Asigna un valor al estado actual del selector de paso\n"
				"\t setalarm\t\t\t-Asigna un valor al registro de alarmas\n"
				"\t setpos\t\t\t-Asigna un valor al registro posición absoluta\n"
				"\t setocdt\t\t\t-Asigna un valor al Overcurrent Detection Threshold actual\n"
				"\t settval\t\t\t-Cambia TVAL\n"
				"\t debug\t\t\t\t-Permite rápido envia de getTVAL útil para econtrar fallas en comunicación SPI\n"
				"\tbck\t\t\tRegresar al anterior menú.\n");

		printf("Ingrese un comando\n");
		getline(&line,&size,stdin);
		printf("El comando ingresado fue: %s \n",line);

		//Mediciones
		if(!strcmp(line,"status\n")){
			stp_getStatus(devptr,&status);
			printf("STATUS: %X \n",status);

		}else if(!strcmp(line,"getconfig\n")){
			stp_getConfig(devptr,&config);
			printf("Config: %X \n",config);

		}else if(!strcmp(line,"getalarm\n")){
			stp_getAlarmEn(devptr,&alarm);
			printf("Alarm: %X \n",alarm);

		}else if(!strcmp(line,"getstep\n")){
			stp_getStepSel(devptr,&step);
			printf("Step: %X \n",step);

		}else if(!strcmp(line,"getpos\n")){
			stp_getPosition(devptr,&position);
			printf("Posición: %d \n",position);

		}else if(!strcmp(line,"getocdt\n")){
			stp_getOCDT(devptr,&ocd);
			printf("OCD: %d \n",ocd);
		}else if(!strcmp(line,"gettval\n")){
			stp_getTVAL(devptr,&tval);
			printf("TVAL: %X \n",tval);
		//Setters
		}else if(!strcmp(line,"setstep\n")){
			printf("Ingrese el divisor del paso para paso de 1.8 grados:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando divisor de paso a: %d \n",buf);
			if(stp_setStepSel(devptr,buf)){
				printf("Error en el cambio de divisor de paso.\n");

			}
		}else if(!strcmp(line,"period\n")){
			printf("Ingrese el periodo del paso en ns:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando periodo a: %d \n",buf);
			stp_period(devptr,buf);

		}else if(!strcmp(line,"dir\n")){
			printf("Ingresela dirección: 0 - counterclockwise; 1 - clockwise:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando direccipon a a: %d \n",buf);
			stp_dir(devptr,buf);

		}else if(!strcmp(line,"setpos\n")){
			printf("Ingrese el marcador de la posición actual:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando posición a: %d \n",buf);
			stp_setPosition(devptr,buf);

		}else if(!strcmp(line,"settval\n")){
			printf("Ingrese el TVAL deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando TVAL a: %d \n",buf);
			stp_setTVal(devptr,buf);
		}else if(!strcmp(line,"settonmin\n")){
			printf("Ingrese el TONMIN deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando TONMIN a: %d \n",buf);
			stp_setTOnMin(devptr,buf);

		}else if(!strcmp(line,"settoffmin\n")){
			printf("Ingrese el TOFFMIN deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando TOFFMIN a: %d \n",buf);
			stp_setTOffMin(devptr,buf);

		}else if(!strcmp(line,"setocdt\n")){
			printf("Ingrese el OCDT deseado:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Cambiando OCDT a: %d \n",buf);
			stp_setOCDT(devptr,buf);

		}else if(!strcmp(line,"ratio\n")){
			printf("Ingrese la nueva relación:\n");
			getline(&line,&size,stdin);
			fbuf=atof(line);
			printf("Cambiando relación a: %f \n",fbuf);
			(*devptr).gear_ratio=fbuf;

		}else if(!strcmp(line,"rel\n")){
			printf("Ingrese dirección:\n");
			getline(&line,&size,stdin);
			buf=atoi(line);
			printf("Ingrese grados hexadecimales:\n");
			getline(&line,&size,stdin);
			buf2=atoi(line);
			printf("Cambiando posición a: %d \n",buf);
			stp_moveRelAngle(devptr,buf2,buf);

		}else if(!strcmp(line,"master-enable\n")){
			printf("Habilitando stepper:\n");
			stp_master_enable(devptr);
		}else if(!strcmp(line,"en-clk\n")){
			printf("Habilitando clk del stepper:\n");
			stp_clk_enable(devptr);

		}else if(!strcmp(line,"en-driver\n")){
			printf("Habilitando driver del stepper:\n");
			stp_driver_enable(devptr);
		}else if(!strcmp(line,"en-out\n")){
			printf("Habilitando salidas del stepper:\n");
			stp_output_enable(devptr);

		}else if(!strcmp(line,"master-disable\n")){
			printf("Deshabilitando stepper:\n");
			stp_master_disable(devptr);

		}else if(!strcmp(line,"dis-clk\n")){
			printf("Deshabilitando clk del stepper:\n");
			stp_clk_disable(devptr);

		}else if(!strcmp(line,"dis-driver\n")){
			printf("Deshabilitando driver del stepper:\n");
			stp_driver_disable(devptr);

		}else if(!strcmp(line,"dis-out\n")){
			printf("Deshabilitando salidas del stepper:\n");
			stp_output_disable(devptr);

		}else if(!strcmp(line,"exit\n")){
			printf("Cerrando el programa. Adiós\n");
			stp_returnToZero(devptr);
			stp_master_disable(devptr);
			break;
		}else if(!strcmp(line,"debug\n")){
			while(getchar()!='q'){
				stp_getTVAL(devptr,&tval);
				printf("TVAL: %d \n",tval);
			}
		}else if(!strcmp(line,"s\n")){
			printf("Deshabilitando stepper:\n");
			stp_master_disable(devptr);

		}else if(!strcmp(line,"cero\n")){
			printf("Volviendo a casa:\n");
			stp_returnToZero(devptr);
		}else if(!strcmp(line,"bck\n")){
			finished=1;
		}
		printf("--------------------------------------------------------------\n");
	}

	return ARM_OK;

}

void emergency_disable(int sig){
	stp_master_disable(devptr);
	abort();
}