/*******************************************************************************
 * GPIO init (STM32F0xx) — табличний варіант
 ******************************************************************************/
#include "General_Definition.h"

//------------------------------ Типи ------------------------------------------
typedef enum { GP_IN = 0, GP_OUT, GP_AF, GP_AN }            GpioMode;   // MODER
typedef enum { NOPULL = 0, PULLUP, PULLDOWN }               GpioPull;   // PUPDR
typedef enum { SPD_LOW = 0, SPD_MED = 1, SPD_HIGH = 3 }     GpioSpeed;  // OSPEEDR
typedef enum { PP = 0, OD }                                 GpioOType;  // OTYPER

typedef struct {
    GPIO_TypeDef *port;
    uint8_t pin;
    uint8_t mode  : 2;
    uint8_t pull  : 2;
    uint8_t speed : 2;
    uint8_t otype : 1;
    uint8_t af    : 4;
} PinCfg;

// Запис поля шириною w біт у позицію pos регістра reg
#define FIELD_SET(reg, pos, w, val) \
    ((reg) = ((reg) & ~(((1UL << (w)) - 1UL) << (pos))) | \
             (((uint32_t)(val) & ((1UL << (w)) - 1UL)) << (pos)))

// Короткі макроси для рядків таблиці
#define OUT_(P, n, pull, spd)   { P, n, GP_OUT, pull, spd,  PP, 0 }
#define IN_(P, n, pull)         { P, n, GP_IN,  pull, SPD_LOW, PP, 0 }
#define AF_(P, n, af, pull)     { P, n, GP_AF,  pull, SPD_HIGH, PP, af }

//------------------------------ Налаштування одного піна ----------------------
void pin_init(const PinCfg *c)
{
    GPIO_TypeDef *X = c->port;
    uint8_t n = c->pin;

    FIELD_SET(X->MODER,         n * 2,       2, c->mode);
    FIELD_SET(X->OTYPER,        n,           1, c->otype);
    FIELD_SET(X->OSPEEDR,       n * 2,       2, c->speed);
    FIELD_SET(X->PUPDR,         n * 2,       2, c->pull);
    FIELD_SET(X->AFR[n >> 3], (n & 7) * 4,   4, c->af);
}

//------------------------------ Таблиця пінів ---------------------------------
static const PinCfg pin_table[] = {
    OUT_(GPIOA,  0, NOPULL,   SPD_MED ),    //
    OUT_(GPIOA,  1, PULLDOWN, SPD_HIGH),    // LED blue
    AF_ (GPIOA,  2, 1, NOPULL),             // UART2 TX
    AF_ (GPIOA,  3, 1, NOPULL),             // UART2 RX
    IN_ (GPIOA,  4, PULLUP),                // right
    IN_ (GPIOA,  5, PULLUP),                // left
    IN_ (GPIOA,  6, PULLUP),                // up
    IN_ (GPIOA,  7, PULLUP),                // down
    OUT_(GPIOA,  8, NOPULL,   SPD_MED ),    // LCD R/W
    AF_ (GPIOA,  9, 1, NOPULL),             // UART1 TX
    AF_ (GPIOA, 10, 1, PULLUP),             // UART1 RX
    OUT_(GPIOA, 11, NOPULL,   SPD_MED ),    // Direct Rx/Tx
    OUT_(GPIOA, 12, NOPULL,   SPD_MED ),    // LCD RS
    // PA13, PA14 — SWD, не чіпаємо
    OUT_(GPIOA, 15, NOPULL,   SPD_HIGH),    // LCD E

    OUT_(GPIOB,  0, PULLUP,   SPD_MED ),    // LCD backlight On/Off
    OUT_(GPIOB,  1, NOPULL,   SPD_MED ),    // LCD DB0
    OUT_(GPIOB,  2, NOPULL,   SPD_MED ),    // LCD DB1
    OUT_(GPIOB,  3, PULLUP,   SPD_MED ),    // StepMotor1
    OUT_(GPIOB,  4, PULLUP,   SPD_MED ),    // StepMotor2
    OUT_(GPIOB,  5, PULLUP,   SPD_MED ),    // StepMotor3
    OUT_(GPIOB,  6, PULLUP,   SPD_MED ),    // StepMotor4
    IN_ (GPIOB,  7, PULLUP),                // KEY1 scanner
    IN_ (GPIOB,  8, PULLUP),                // KEY2 scanner
    IN_ (GPIOB,  9, PULLUP),                // KEY3 scanner
    OUT_(GPIOB, 10, NOPULL,   SPD_MED ),    // LCD DB2
    OUT_(GPIOB, 11, NOPULL,   SPD_MED ),    // LCD DB3
    OUT_(GPIOB, 12, NOPULL,   SPD_MED ),    // LCD DB4
    OUT_(GPIOB, 13, NOPULL,   SPD_MED ),    // LCD DB5
    OUT_(GPIOB, 14, NOPULL,   SPD_MED ),    // LCD DB6
    OUT_(GPIOB, 15, NOPULL,   SPD_MED ),    // LCD DB7

    // OUT_(GPIOF, 0, NOPULL, SPD_MED),     // LED POWER
    // OUT_(GPIOF, 1, NOPULL, SPD_MED),     // LED ANSWER
    // IN_ (GPIOC, 14, NOPULL),             // addr 3
    // IN_ (GPIOC, 15, NOPULL),             // addr 4
};

//------------------------------ Ініціалізація портів --------------------------
void ports_init(void)
{
    for (uint32_t i = 0; i < sizeof(pin_table) / sizeof(pin_table[0]); i++)
    {
        const PinCfg *c = &pin_table[i];

        // Тактування порту: GPIOA..GPIOF -> біти 17..22 RCC_AHBENR (крок 0x400)
        RCC->AHBENR |= 1UL << (17 + ((uint32_t)c->port - GPIOA_BASE) / 0x400);

        if (c->mode == GP_OUT)
            c->port->BRR = 1UL << c->pin;   // низький рівень ДО перемикання на вихід

        pin_init(c);
    }
}