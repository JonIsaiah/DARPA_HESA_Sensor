/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include<main.h>



#define numberOfTests 100
int i = 0; //for loop increment variable
   
char buf[200]; //just to hold text values in for writing to UART

int16_t CAX, CAY, CAZ; //current acceleration values
int16_t CGX, CGY, CGZ; //current gyroscope values
int16_t CT;            //current temperature
   
float   AXoff, AYoff, AZoff; //accelerometer offset values
float   GXoff, GYoff, GZoff; //gyroscope offset values

float   AX, AY, AZ; //acceleration floats
float   GX, GY, GZ; //gyroscope floats

float  Gx_integrated, Gy_integrated, Gz_integrated;

struct Vector current_Gvector;

float roll = 0.0;
float pitch = 0.0;

float rolld = 0.00;
float pitchd = 0.00;

float filtered_combo_roll = 0.0;
float filtered_combo_pitch = 0.0;



//Function Declarations

uint16 fiveMicroSeconds_count = 0;
CY_ISR(TIMER_ISR){
    fiveMicroSeconds_count++;
}



int main()
{
    /* Start the components */
	InitializeSystem();
    



    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */

        
        MPU6050_getMotion6t(&CAX, &CAY, &CAZ, &CGX, &CGY, &CGZ, &CT);
        AX = ((float)CAX-AXoff)/16384.00;
        AY = ((float)CAY-AYoff)/16384.00; //16384 is just 32768/2 to get our 1G value
        AZ = ((float)-CAZ-(AZoff-16384))/16384.00; //remove 1G before dividing              FIX TO MAINTAIN RIGHT HANDED COORDINATES

        GX = ((float)CGX-GXoff)/131.07; //131.07 is just 32768/250 to get us our 1deg/sec value
        GY = ((float)CGY-GYoff)/131.07;
        GZ = ((float)CGZ-GZoff)/131.07;
        

        
        current_Gvector.x = AX;
        current_Gvector.y = AY;
        current_Gvector.z = AZ;
        //current_Gvector = normalizeVector(current_Gvector);   THIS LINE FUCKS SHIT UP

         roll = atan2f(current_Gvector.y, -current_Gvector.z);
         pitch =atan2f(-current_Gvector.x, sqrtf(current_Gvector.y*current_Gvector.y + current_Gvector.z*current_Gvector.z));

        
         rolld = roll * 180/M_PI;
         pitchd = pitch * 180/M_PI;

         filtered_combo_roll = (0.9800 * (filtered_combo_roll+(GX * fiveMicroSeconds_count*.000005))) + (.02000 * rolld);
         filtered_combo_pitch = (0.9800 * (filtered_combo_pitch+(GY * fiveMicroSeconds_count*.000005))) + (.02000 * pitchd);
         fiveMicroSeconds_count =0;

         //DUMMY YAW INSERTED
         sprintf(buf, "p%.3fr%.3fy%.3fe", filtered_combo_pitch, filtered_combo_roll, 17.400);
         SERIAL_UartPutString(buf);
         
        

        

         


    }
}



void InitializeSystem(void)
{
	/* Enable Global Interrupt Mask */
	CyGlobalIntEnable;		
    isr_1_StartEx(TIMER_ISR);
    
    /* Change SCL and SDA pins drive mode to Resistive Pull Up */
    I2C_bus_scl_SetDriveMode(I2C_bus_scl_DM_RES_UP);
    I2C_bus_sda_SetDriveMode(I2C_bus_sda_DM_RES_UP);
    
    I2C_bus_Start();
    CyDelay(150);
    
    SERIAL_Start();
    
    MPU6050_init();
	MPU6050_initialize();
    
    calibrateMPU();
	

    
    
    Timer_1_Start();
    
    
}




void calibrateMPU(){
    
    for(i=0; i<numberOfTests; i++)
    {

    
      MPU6050_getMotion6t(&CAX, &CAY, &CAZ, &CGX, &CGY, &CGZ, &CT);
      AXoff += CAX;
      AYoff += CAY;
      AZoff += CAZ;
      GXoff += CGX;
      GYoff += CGY;
      GZoff += CGZ;
      
      CyDelay(25);
    }
    
    AXoff = AXoff/numberOfTests;
    AYoff = AYoff/numberOfTests;
    AZoff = AZoff/numberOfTests;  //SWITCH Z AXIS DIRECTION TO MAINTAIN RIGHT HANDED COORDINATE SYSTEM
    GXoff = GXoff/numberOfTests;
    GYoff = GYoff/numberOfTests;
    GZoff = GZoff/numberOfTests;
    
}




struct Vector normalizeVector(struct Vector v1){
 v1.mag = sqrtf( powf(v1.x, 2) + powf(v1.y, 2) + powf(v1.z, 2) );
 v1.x = v1.x/v1.mag;
 v1.y = v1.y/v1.mag;
 v1.z = v1.z/v1.mag;
 v1.mag = sqrtf( powf(v1.x, 2) + powf(v1.y, 2) + powf(v1.z, 2) );
 return v1;  
}





/* [] END OF FILE */
