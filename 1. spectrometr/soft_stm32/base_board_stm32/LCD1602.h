

extern void initLCD(void);
extern void LCD(void);
extern u8 SetData(u8 len);
extern void writeLCD(u8 start1,u8* row1,u8 len1,u8 start2,u8* row2,u8 len2,u8 isClear,u8 isUp);
extern void To_string(u32 number1,u8 model1,u32 number2,u8 model2);