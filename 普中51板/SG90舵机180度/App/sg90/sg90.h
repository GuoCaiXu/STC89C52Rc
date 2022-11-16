# ifndef _sg90_H
# define _sg90_H

# include "public.h"

//PWM 引脚
sbit PWM = P2^1;

//PWM 初始化
void pwm_init(u8 tim_h, u8 tim_l, u8 tim_scale, u8 duty);

//更新占空比
void pwm_set_duty(u8 duty);

# endif