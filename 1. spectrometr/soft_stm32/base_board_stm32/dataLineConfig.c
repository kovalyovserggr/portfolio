/*******************************************************************************

*******************************************************************************/
#include "General_Definition.h"


/******************************************************************************/
void initLines(void)
{
  ReadFromFlesh();
  
  u32 tempData1, tempData2, tempData3;
  for(int i=0; i<20; i++)
  {
    tempData1 = bufferFromFlesh[i];
    masConfigXW[i*2] = (u16)(tempData1);
    masConfigXW[i*2+1] = (u16)(tempData1>>16);
     
    tempData2 = bufferFromFlesh[i+20];
    masConfigWI_FEU[i*2] = (u16)(tempData2);
    masConfigWI_FEU[i*2+1] = (u16)(tempData2>>16);
    
    if(i<10)
    {
      tempData3 = bufferFromFlesh[i+40];
      masConfigWF[i*2] = (u16)(tempData3);
      masConfigWF[i*2+1] = (u16)(tempData3>>16);
    }
  }
}

void saveLines(void)
{

  for(int i=0; i<20; i++)
  {
    bufferFromFlesh[i] = masConfigXW[i*2] + ((((u32) masConfigXW[i*2+1])<<16)& 0xFFFF0000); 
    bufferFromFlesh[i+20] = masConfigWI_FEU[i*2] + ((((u32) masConfigWI_FEU[i*2+1])<<16)& 0xFFFF0000); 
    if(i<10)
      bufferFromFlesh[i+40] = masConfigWF[i*2] + ((((u32) masConfigWF[i*2+1])<<16)& 0xFFFF0000);
  }
 
  
  SaveToFlesh();

}


u16 ABB()
{
  u16 temperaturaB=spectr.temperatura, WaveB = spectr.Wave , Kgray=spectr.Kgray;
  /*
  корекція  сигналу з урахуванням закономірностей випромінювання абсолютно чорного тіла
  */
  return 1;
}

void calculationSignalFromDetector()
{
    long double W1=3500;
    long double W2=7500;
    long double I1=0;
    long double I2=1000;
    long double I=0;
    long double W=3500;
    u16 wave = spectr.Wave;
    u8 f=0;
    u16 I_feu=0;  
    
      for(int i=0;i<21;i++)
        {
          if((i==0)&&(wave < masConfigWI_FEU[i]))
            {
              W1 = 3500;
              I1 = 0;
              
              W2 = masConfigWI_FEU[i+20];
              I2 = masConfigWI_FEU[i];
              
              W = W2;
              I = I2;
              
              if(I1>I2)
                  f=1;
            }
          else if(i==20)
            {
              if(wave > masConfigWI_FEU[i-1])
              {
                W1 = W;
                I1 = I;
                
                W2 = 7500;
                I2 = 20000;
                
                if(I1>I2)
                    f = 1;
              }
            }
          else if((masConfigWI_FEU[i-1] <= wave)&&(wave <= masConfigWI_FEU[i]))
            {
                I1 = masConfigWI_FEU[i-1];
                W1 = masConfigWI_FEU[i+20-1];
                
                I2 = masConfigWI_FEU[i];
                W2 = masConfigWI_FEU[i+20];
               
                I = I2;
                W = W2;
                
                if(I1>I2)
                  f=1;
            }
          else if(masConfigWI_FEU[i] < 20001)
            {
                W = masConfigWI_FEU[i+20];
                I = masConfigWI_FEU[i];
            }
        }
      
      if(f)
            I_feu = ((W1-W2)*(I2 - wave))/(I2-I1)+W2;
         else
            I_feu = ((W2-W1)*(wave - I1))/(I2-I1)+W1;
   
  
}


u16 Position(u16 wave)
{
     long double W3=3500;
     long double W4=7500;
     long double W=0;
     long double X1=0;
     long double X2=20000;
     long double X=0;
     u8 f=0;
     u16 newX=0;

       for(int i=20;i<41;i++) 
       {
         if((i==20)&&(wave<masConfigXW[i]))
          {
            W3=3500;
            X1=0;
            
            W4=masConfigXW[i];
            X2=masConfigXW[i-20];
            
            W = W4;
            X = X2;
            
            if(X1>X2)
                f=1;
          }
          else if(i==40)
          {
            if(wave>=W)
              {
                 W3=W;
                 X1=X;
                 
                 W4=7500;
                 X2=20000;
                 
                if(X1>X2)
                   f=1;
              }
              
          }else if((masConfigXW[i-1]<=wave)&&(wave<=masConfigXW[i]))
          {
              W3  =masConfigXW[i-1];
              X1 = masConfigXW[i-20-1];
              
              W4 = masConfigXW[i];
              X2 = masConfigXW[i-20];

              W = W4;
              X = X2;
              
              if(X1>X2)
                f=1;
              
          }else if(masConfigXW[i] < 7500)
          {
              W = masConfigXW[i];
              X = masConfigXW[i-20];
          }
       }
       
       if(f)
            newX= ((W4-wave)*(X1-X2)) / (W4 - W3) +X2;
         else
            newX = ((wave-W3)*(X2-X1)) / (W4 - W3) +X1;
 
   return  newX;
}

u16 X_Calculation(u16 wave)
{
     long double W3=3500;
     long double W4=7500;
     long double W=0;
     long double F1=0;
     long double F2=110;
     long double F=0;
     u8 f=0;
     u16 newX=0;
     
     if(spectr.status&SLIT_AUTO)
     {
       for(int i=0;i<11;i++) 
       {
         if((i==0)&&(wave<masConfigWF[i]))
          {
            F1=0;
            W3=3500;
           
            F2=masConfigWF[i+10];
            W4=masConfigWF[i];
            
            F = F2;
            W = W4;
            
            if(F1>F2)
                f=1;
          }
          else if(i==10)
          {
            if(wave>=W)
              {
                 W3=W;
                 F1=F;
                 
                 W4=7500;
                 F2=110;
                 
                if(F1>F2)
                   f=1;
              }
              
          }else if((masConfigWF[i-1]<=wave)&&(wave<=masConfigWF[i]))
          {
              W3  =masConfigWF[i-1];
              F1 = masConfigWF[i+10-1];
              
              W4 = masConfigWF[i];
              F2 = masConfigWF[i+10];
              
              W = W4;
              F = F2;
              
              if(F1>F2)
                f=1;
              
          }else if(masConfigWF[i] < 7500)
          {
              W = masConfigWF[i];
              F = masConfigWF[i+10];
          }
       }
       
       if(f)
            newX= ((W4-wave)*(F1-F2)) / (W4 - W3) +F2;
         else
            newX = ((wave-W3)*(F2-F1)) / (W4 - W3) +F1;
     }
     else
       newX = spectr.SetX; 
     
#warning  

  return newX;
}

u16 wave_Calculation(u16 coordinate)
{
      long double W1=3500;
      long double W2=7500;
      long double X1=0;
      long double X2=20000;
      long double X=0;
      long double W=3500;
      u8 f=0;
      u16 newWave=0;
      
      for(int i=0;i<21;i++)
        {
          if((i==0)&&(coordinate<masConfigXW[i]))
            {
              W1=3500;
              X1=0;
              
              W2=masConfigXW[i+20];
              X2=masConfigXW[i];
              
              W = W2;
              X = X2;
              
              if(X1>X2)
                  f=1;
            }
          else if((i==20)&&(coordinate>masConfigXW[i-1]))
            {
              W1=W;
              X1=X;
              
              W2=7500;
              X2=20000;
              
              if(X1>X2)
                  f=1;
            }
          else if((masConfigXW[i-1]<=coordinate)&&(coordinate<=masConfigXW[i]))
            {
                X1 = masConfigXW[i-1];
                W1 = masConfigXW[i+20-1];
                
                X2 = masConfigXW[i];
                W2 = masConfigXW[i+20];
               
                X = X2;
                W = W2;
                
                if(X1>X2)
                  f=1;
            }
          else if(masConfigXW[i] < 20001)
            {
                W = masConfigXW[i+20];
                X = masConfigXW[i];
            }
        }
      
      if(f)
            newWave= ((W1-W2)*(X2-coordinate))/(X2-X1)+W2;
         else
            newWave =((W2-W1)*(coordinate-X1))/(X2-X1)+W1;
      
    return newWave+1;
}