/*******************************************************************************
                                 Menu BKO-x
*******************************************************************************/

#include "General_Definition.h"
#include "LCD1602.h"


void menu_Context(u8 numberMenu)
{

  switch(numberMenu)
  {
    case 0:
          stringLCD1[0]=' ';         stringLCD2[0]=' '; 
          stringLCD1[1]='I';         stringLCD2[1]='<';
          stringLCD1[2]=' ';         stringLCD2[2]='W';
          stringLCD1[3]='=';         stringLCD2[3]='a';
          stringLCD1[4]=' ';         stringLCD2[4]='v';
          stringLCD1[5]=' ';         stringLCD2[5]='e';
          stringLCD1[6]=' ';         stringLCD2[6]=' ';
          stringLCD1[7]=' ';         stringLCD2[7]='=';
          stringLCD1[8]=' ';         stringLCD2[8]=' ';
          stringLCD1[9]=' ';         stringLCD2[9]=' ';
          stringLCD1[10]=' ';        stringLCD2[10]=' ';
          stringLCD1[11]='%';        stringLCD2[11]=' ';
          stringLCD1[12]=' ';        stringLCD2[12]=' ';
          stringLCD1[13]=' ';        stringLCD2[13]=' ';
          stringLCD1[14]=' ';        stringLCD2[14]='A';
          stringLCD1[15]=' ';        stringLCD2[15]='>';

          break;
    case 1:
          stringLCD1[0]='H';         stringLCD2[0]='<'; 
          stringLCD1[1]='V';         stringLCD2[1]=' ';
          stringLCD1[2]=' ';         stringLCD2[2]=' ';
          stringLCD1[3]=' ';         stringLCD2[3]=' ';
          stringLCD1[4]=' ';         stringLCD2[4]=' ';
          stringLCD1[5]=' ';         stringLCD2[5]='>';
          stringLCD1[6]=' ';         stringLCD2[6]=' ';
          stringLCD1[7]='V';         stringLCD2[7]=' ';
          stringLCD1[8]='=';         stringLCD2[8]=' ';
          stringLCD1[9]=' ';         stringLCD2[9]=' ';
          stringLCD1[10]=' ';        stringLCD2[10]='R';
          stringLCD1[11]=' ';        stringLCD2[11]='/';
          stringLCD1[12]=' ';        stringLCD2[12]='T';
          stringLCD1[13]=' ';        stringLCD2[13]=' ';
          stringLCD1[14]=' ';        stringLCD2[14]='o';
          stringLCD1[15]='B';        stringLCD2[15]='k';
          stringLCD1[16]=' ';        stringLCD2[16]=' ';

          break;
    case 2:
          stringLCD1[0]='S';         stringLCD2[0]=' '; 
          stringLCD1[1]='l';         stringLCD2[1]=' ';
          stringLCD1[2]='i';         stringLCD2[2]=' ';
          stringLCD1[3]='t';         stringLCD2[3]=' ';
          stringLCD1[4]=' ';         stringLCD2[4]=' ';
          stringLCD1[5]=' ';         stringLCD2[5]=' ';
          stringLCD1[6]='X';         stringLCD2[6]=' ';
          stringLCD1[7]='=';         stringLCD2[7]=' ';
          stringLCD1[8]=' ';         stringLCD2[8]=' ';
          stringLCD1[9]=' ';         stringLCD2[9]=' ';
          stringLCD1[10]=' ';        stringLCD2[10]='R';
          stringLCD1[11]=' ';        stringLCD2[11]='/';
          stringLCD1[12]=',';        stringLCD2[12]='T';
          stringLCD1[13]=' ';        stringLCD2[13]=' ';
          stringLCD1[14]='m';        stringLCD2[14]='o';
          stringLCD1[15]='m';        stringLCD2[15]='k';
          stringLCD1[16]=' ';        stringLCD2[16]=' ';

          if(spectr.status&SLIT_FAIL)
           {
              stringLCD2[15]='o';
              stringLCD2[14]='n';
           }
           else
           {
              stringLCD2[15]='k';
              stringLCD2[14]='o';
           }
          break;
  case 3:
          stringLCD1[0]='D';         stringLCD2[0]='<'; 
          stringLCD1[1]='e';         stringLCD2[1]=' ';
          stringLCD1[2]='t';         stringLCD2[2]=',';
          stringLCD1[3]='e';         stringLCD2[3]=' ';
          stringLCD1[4]='c';         stringLCD2[4]=' ';
          stringLCD1[5]='t';         stringLCD2[5]=' ';
          stringLCD1[6]='o';         stringLCD2[6]=' ';
          stringLCD1[7]='r';         stringLCD2[7]='V';
          stringLCD1[8]=' ';         stringLCD2[8]='>';
          stringLCD1[9]='l';         stringLCD2[9]=' ';
          stringLCD1[10]='i';        stringLCD2[10]='R';
          stringLCD1[11]='m';        stringLCD2[11]='/';
          stringLCD1[12]='i';        stringLCD2[12]='T';
          stringLCD1[13]='t';        stringLCD2[13]=' ';
          stringLCD1[14]=' ';        stringLCD2[14]='o';
          stringLCD1[15]='1';        stringLCD2[15]='k';
          stringLCD1[16]=' ';        stringLCD2[16]=' ';

          break;
  case 4:
         
          stringLCD1[0]='D';         stringLCD2[0]=' '; 
          stringLCD1[1]='e';         stringLCD2[1]='<';
          stringLCD1[2]='t';         stringLCD2[2]='K';
          stringLCD1[3]='e';         stringLCD2[3]='=';
          stringLCD1[4]='c';         stringLCD2[4]=' ';
          stringLCD1[5]='t';         stringLCD2[5]=' ';
          stringLCD1[6]='o';         stringLCD2[6]=' ';
          stringLCD1[7]='r';         stringLCD2[7]=' ';
          stringLCD1[8]=' ';         stringLCD2[8]=' ';
          stringLCD1[9]=' ';         stringLCD2[9]=' ';
          stringLCD1[10]=' ';        stringLCD2[10]='>';
          stringLCD1[11]=' ';        stringLCD2[11]=' ';
          stringLCD1[12]=' ';        stringLCD2[12]=' ';
          stringLCD1[13]=' ';        stringLCD2[13]=' ';
          stringLCD1[14]=' ';        stringLCD2[14]=' ';
          stringLCD1[15]=' ';        stringLCD2[15]=' ';
          stringLCD1[16]=' ';        stringLCD2[16]=' ';

          break;
  }

}
//
void initMenu(){

}

//
void menu(u8 numberButton,u8 replay){
  
  if(status&IS_CONNECT)
  {
    numberButton=6;
  }

  if(!(status&LCD_BUSY))
    switch(numberButton)
      {
          case 0://left uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu    
                  
                    switch(menuLCD)
                      {
                        case 0:
                              if(spectr.SetWave<=spectr.Wave)
                                  {
                                    if((spectr.Wave-spectr.SetWave)<100)
                                      if(spectr.SetWave>3550)
                                          spectr.SetWave-=50;
                                        else
                                          spectr.SetWave=3500;
                                  }else spectr.SetWave--;
                              
                               switch(typeSourseDetector)
                                {
                                  case 0:
                                    To_string(spectr.integral,0,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],5,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 1:
                                    To_string(spectr.ch1,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 2:
                                    To_string(spectr.ch2,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 3:
                                    To_string(spectr.ch3,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 4:
                                    To_string(spectr.ch4,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 5:
                                    if(spectr.ch1>spectr.ch2)
                                      To_string(spectr.ch1-spectr.ch2,2,spectr.Wave,7);
                                    else
                                      To_string(spectr.ch2-spectr.ch1,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                }
                             
                             
                                
                              break;
                        case 1:
                              if(spectr.SetVoltage>50)
                                   spectr.SetVoltage-=50;
                                 else
                                   spectr.SetVoltage=0;
                          
                               To_string(spectr.Voltage,3,spectr.SetVoltage,5);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,0,32);
                              break;
                        case 2:
                              
                              break;
                        case 3:
                              if(spectr.limit1>10)
                                   spectr.limit1-=10;
                                 else
                                   spectr.limit1=0;
                                 
                              To_string(1,7,spectr.limit1,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 4:
                              if(spectr.limit2>10)
                                   spectr.limit2-=10;
                                 else
                                   spectr.limit2=0;
                                 
                              To_string(2,7,spectr.limit2,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 5:
                              if(spectr.limit3>10)
                                   spectr.limit3-=10;
                                 else
                                   spectr.limit3=0;
                                 
                              To_string(3,7,spectr.limit3,8);
                             writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 6:
                              if(spectr.limit4>10)
                                   spectr.limit4-=10;
                                 else
                                   spectr.limit4=0;
                                 
                              To_string(4,7,spectr.limit4,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 7:
                               if(typeSourseDetector>0)
                                    typeSourseDetector--;
                                   else
                                    typeSourseDetector=5;
                               
                               switch(typeSourseDetector)
                                    {
                                      case 0:
                                            writeLCD(0,"Detector sourse  ",16,0,"<    integral    >",16,0,16);
                                            break;
                                      case 1:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch1       >",16,0,16);
                                            break;
                                      case 2:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch2       >",16,0,16);
                                            break;
                                      case 3:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch3       >",16,0,16);
                                            break;
                                      case 4:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch4       >",16,0,16);
                                            break;
                                      case 5:
                                            writeLCD(0,"Detector sourse  ",16,0,"<     ch1-ch2    >",16,0,16);
                                            break;
                                    }
                             break;
                        case 8:
                             if(spectr.K>2000)
                                spectr.K-=1000;
                              else
                                spectr.K=1000;
                           
                              To_string(spectr.K,100,spectr.K,3);
                              writeLCD(0,&stringLCD1[0],0,4,&stringLCD2[0],6,0,32);
                             break;
                      }
                              
                  break;
          case 1://right  uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu
                  switch(menuLCD)
                      {
                        case 0:
  
                              if(spectr.SetWave>=spectr.Wave)
                                  {
                                    if((spectr.SetWave-spectr.Wave)<100)
                                    {
                                      if(spectr.SetWave<7450)
                                          spectr.SetWave+=50;
                                        else
                                          spectr.SetWave=7500;
                                    }
                                    
                                  }else spectr.SetWave++;
                                    
            
                               switch(typeSourseDetector)
                                {
                                  case 0:
                                    To_string(spectr.integral,0,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],5,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 1:
                                    To_string(spectr.ch1,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 2:
                                    To_string(spectr.ch2,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 3:
                                    To_string(spectr.ch3,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 4:
                                    To_string(spectr.ch4,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 5:
                                    if(spectr.ch1>spectr.ch2)
                                      To_string(spectr.ch1-spectr.ch2,2,spectr.Wave,7);
                                    else
                                      To_string(spectr.ch2-spectr.ch1,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                }
                             
                                
                              break;
                        case 1:
                               if(spectr.SetVoltage<1850)
                                   spectr.SetVoltage+=50;
                                 else
                                   spectr.SetVoltage=1900;
                          
                               To_string(spectr.Voltage,3,spectr.SetVoltage,5);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,0,32);
                              break;
                        case 2:
                             
                              break;
                        case 3:
                              if(spectr.limit1<4990)
                                   spectr.limit1+=10;
                                 else
                                   spectr.limit1+=5000;
                                 
                              To_string(1,7,spectr.limit1,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 4:
                               if(spectr.limit2<4990)
                                   spectr.limit2+=10;
                                 else
                                   spectr.limit2+=5000;
                                 
                              To_string(2,7,spectr.limit2,8);
                             writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 5:
                               if(spectr.limit3<4990)
                                   spectr.limit3+=10;
                                 else
                                   spectr.limit3+=5000;
                                 
                              To_string(3,7,spectr.limit3,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 6:
                               if(spectr.limit4<4990)
                                   spectr.limit4+=10;
                                 else
                                   spectr.limit4+=5000;
                                 
                              To_string(4,7,spectr.limit4,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 7:
                               if(typeSourseDetector<5)
                                    typeSourseDetector++;
                                   else
                                    typeSourseDetector=0;
                               
                               switch(typeSourseDetector)
                                    {
                                      case 0:
                                            writeLCD(0,"Detector sourse  ",16,0,"<    integral    >",16,0,16);
                                            break;
                                      case 1:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch1       >",16,0,16);
                                            break;
                                      case 2:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch2       >",16,0,16);
                                            break;
                                      case 3:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch3       >",16,0,16);
                                            break;
                                      case 4:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch4       >",16,0,16);
                                            break;
                                      case 5:
                                            writeLCD(0,"Detector sourse  ",16,0,"<     ch1-ch2    >",16,0,16);
                                            break;
                                    }
                             break;
                         case 8:
                              if(spectr.K<998000)
                                spectr.K+=1000;
                              else
                                spectr.K=999999;
                           
                              To_string(spectr.K,100,spectr.K,3);
                              writeLCD(0,&stringLCD1[0],0,4,&stringLCD2[0],6,0,32);
                              break;
                      default:
                      
                             break;
                    } 
                 
                  break;
          case 2://up uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu
                    switch(menuLCD)
                      {
                        case 0:
                              menuLCD=8;
                              menu_Context(4);
                              To_string(spectr.K,100,spectr.K,0);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 1:
                              menuLCD=0;
                              menu_Context(0);
                              switch(typeSourseDetector)
                                {
                                  case 0:
                                    To_string(spectr.integral,1,spectr.Wave,1);
                                    break;
                                  case 1:
                                    To_string(spectr.ch1,10,spectr.Wave,1);
                                    break;
                                  case 2:
                                    To_string(spectr.ch2,10,spectr.Wave,1);
                                    break;
                                  case 3:
                                    To_string(spectr.ch3,10,spectr.Wave,1);
                                    break;
                                  case 4:
                                    To_string(spectr.ch4,10,spectr.Wave,1);
                                    break;
                                  case 5:
                                    if(spectr.ch1>spectr.ch2)
                                      To_string(spectr.ch1-spectr.ch2,10,spectr.Wave,1);
                                    else
                                      To_string(spectr.ch2-spectr.ch1,10,spectr.Wave,1);
                                    break;
                                }
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 2:
                              menuLCD=1;
                              menu_Context(1);
                              To_string(spectr.Voltage,3,spectr.SetVoltage,5);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 3:
                              menuLCD=2;
                              menu_Context(2);
                              To_string(spectr.X,5,1,100);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 4:
                              menuLCD=3;//lim1
                              menu_Context(3);
                              To_string(1,7,spectr.limit1,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 5:
                              menuLCD=4;//lim2
                              menu_Context(3);
                              To_string(2,7,spectr.limit2,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 6:
                              menuLCD=5;//lim3
                              menu_Context(3);
                              To_string(3,7,spectr.limit3,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 7:
                              menuLCD=6;//lim4
                              menu_Context(3);
                              To_string(4,7,spectr.limit4,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 8:
                              menuLCD=7;//select sourse detector
                              switch(typeSourseDetector)
                                  {
                                    case 0:
                                          writeLCD(0,"Detector sourse  ",16,0,"<    integral    >",16,0,16);
                                          break;
                                    case 1:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch1       >",16,0,16);
                                          break;
                                    case 2:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch2       >",16,0,16);
                                          break;
                                    case 3:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch3       >",16,0,16);
                                          break;
                                    case 4:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch4       >",16,0,16);
                                          break;
                                    case 5:
                                          writeLCD(0,"Detector sourse  ",16,0,"<     ch1-ch2    >",16,0,16);
                                          break;
                                  }
                              return;
                      }
                    
                break;
          case 3: //down  uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu
              switch(menuLCD)
                      {
                       case 0:
                              menuLCD=1;
                              menu_Context(1);
                              To_string(spectr.Voltage,3,spectr.SetVoltage,5);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 1:
                              menuLCD=2;
                              menu_Context(2);
                              To_string(spectr.X,5,1,100);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 2:
                              menuLCD=3;//lim2
                              menu_Context(3);
                              To_string(1,7,spectr.limit1,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 3:
                              menuLCD=4;//lim2
                              menu_Context(3);
                              To_string(2,7,spectr.limit2,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 4:
                              menuLCD=5;//lim3
                              menu_Context(3);
                              To_string(3,7,spectr.limit3,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 5:
                             menuLCD=6;//lim4
                              menu_Context(3);
                              To_string(4,7,spectr.limit4,8);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 6:
                             menuLCD=7;//select sourse detector
                              switch(typeSourseDetector)
                                  {
                                    case 0:
                                          writeLCD(0,"Detector sourse  ",16,0,"<    integral    >",16,0,16);
                                          break;
                                    case 1:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch1       >",16,0,16);
                                          break;
                                    case 2:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch2       >",16,0,16);
                                          break;
                                    case 3:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch3       >",16,0,16);
                                          break;
                                    case 4:
                                          writeLCD(0,"Detector sourse  ",16,0,"<      ch4       >",16,0,16);
                                          break;
                                    case 5:
                                          writeLCD(0,"Detector sourse  ",16,0,"<     ch1-ch2    >",16,0,16);
                                          break;
                                  }
                              return;
                        case 7:
                              menuLCD=8;
                              menu_Context(4);
                              To_string(spectr.K,100,spectr.K,0);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 8:
                              menuLCD=0;
                              menu_Context(0);
                              switch(typeSourseDetector)
                                {
                                  case 0:
                                    To_string(spectr.integral,1,spectr.Wave,1);
                                    break;
                                  case 1:
                                    To_string(spectr.ch1,10,spectr.Wave,1);
                                    break;
                                  case 2:
                                    To_string(spectr.ch2,10,spectr.Wave,1);
                                    break;
                                  case 3:
                                    To_string(spectr.ch3,10,spectr.Wave,1);
                                    break;
                                  case 4:
                                    To_string(spectr.ch4,10,spectr.Wave,1);
                                    break;
                                  case 5:
                                    if(spectr.ch1>spectr.ch2)
                                      To_string(spectr.ch1-spectr.ch2,10,spectr.Wave,1);
                                    else
                                      To_string(spectr.ch2-spectr.ch1,10,spectr.Wave,1);
                                    break;
                                }
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                      }
                    
                    break;
          case 5: //update//////////////////////////////////////////////////////
                      switch(menuLCD)
                         {
                          case 0:
                               switch(typeSourseDetector)
                                {
                                  case 0:
                                    To_string(spectr.integral,0,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],5,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 1:
                                    To_string(spectr.ch1,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 2:
                                    To_string(spectr.ch2,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 3:
                                    To_string(spectr.ch3,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 4:
                                    To_string(spectr.ch4,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                  case 5:
                                    if(spectr.ch1>spectr.ch2)
                                      To_string(spectr.ch1-spectr.ch2,2,spectr.Wave,7);
                                    else
                                      To_string(spectr.ch2-spectr.ch1,2,spectr.Wave,7);
                                    writeLCD(5,&stringLCD1[0],7,9,&stringLCD2[0],4,0,32);
                                    break;
                                }
                             
                             
                                
                              break;
                        case 1:
                              To_string(spectr.Voltage,3,spectr.SetVoltage,5);
                               writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,0,32);
                              break;
                        case 2:
                              menuLCD=2;
                              menu_Context(2);
                              To_string(spectr.X,5,1,100);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
 /*                    case 3:
                               To_string(1,7,spectr.limit1,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 4:
                              To_string(2,7,spectr.limit2,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 5:
                              To_string(3,7,spectr.limit3,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;
                        case 6:
                              To_string(4,7,spectr.limit4,8);
                              writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                              break;*/
                        case 7:
                               switch(typeSourseDetector)
                                    {
                                      case 0:
                                            writeLCD(0,"Detector sourse  ",16,0,"<    integral    >",16,0,16);
                                            break;
                                      case 1:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch1       >",16,0,16);
                                            break;
                                      case 2:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch2       >",16,0,16);
                                            break;
                                      case 3:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch3       >",16,0,16);
                                            break;
                                      case 4:
                                            writeLCD(0,"Detector sourse  ",16,0,"<      ch4       >",16,0,16);
                                            break;
                                      case 5:
                                            writeLCD(0,"Detector sourse  ",16,0,"<     ch1-ch2    >",16,0,16);
                                            break;
                                    }
                             break;
                        case 8:
                             To_string(spectr.K,100,spectr.K,3);
                             writeLCD(0,&stringLCD1[0],0,4,&stringLCD2[0],6,0,32);
                             break;
                         }
                      break;
            case 6:
                    menuLCD=111; 
                    writeLCD(0,"Computer        ",16,0,"<               >",16,0,16);
              break;
           case 7:
                menuLCD=0;
                menu_Context(0);
                switch(typeSourseDetector)
                  {
                    case 0:
                      To_string(spectr.integral,1,spectr.Wave,1);
                      break;
                    case 1:
                      To_string(spectr.ch1,10,spectr.Wave,1);
                      break;
                    case 2:
                      To_string(spectr.ch2,10,spectr.Wave,1);
                      break;
                    case 3:
                      To_string(spectr.ch3,10,spectr.Wave,1);
                      break;
                    case 4:
                      To_string(spectr.ch4,10,spectr.Wave,1);
                      break;
                    case 5:
                      if(spectr.ch1>spectr.ch2)
                        To_string(spectr.ch1-spectr.ch2,10,spectr.Wave,1);
                      else
                        To_string(spectr.ch2-spectr.ch1,10,spectr.Wave,1);
                      break;
                  }
                writeLCD(0,&stringLCD1[0],16,0,&stringLCD2[0],16,1,32);
                break;
              default:
                break;
      } //uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu
}

