/*******************************************************************************

*******************************************************************************/

// метод налаштування порта A
extern void ports_init(void);

//
extern void MCO_pin_init_(void);

// подавання живлення на BlueTooth
extern void BlueToothPower(u8 On_off); 

// встановлення ключа для BlueTooth
extern void KeySet(u8 KeyBlueTooth);