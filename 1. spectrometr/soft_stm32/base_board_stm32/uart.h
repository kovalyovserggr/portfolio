 

typedef enum 
{
Run,
Stop,
NameDevice,
}enumNPCommand;

// меод ініціалізаціяї uart1(швидкість 38400 біт/сек, 8 біт в пакеті, 2 стоп біт, без перевірки парності)
extern void init_uart1_(void);

// меод ініціалізаціяї uart1(швидкість 38400 біт/сек, 8 біт в пакеті, 2 стоп біт, без перевірки парності)
extern void init_uart2_(void);


// відправити  дані в порт
extern u8 SendData_Uart1(char* newComand,u8 Len);

// відправити  дані в порт
extern u8 SendData_Uart2(char* newComand,u8 Len);


//Задати напрямок передавання даних через RS485
extern void DirectionTR_Uart1(u8 Dir);

//
extern void USART1_IRQHandler(void);