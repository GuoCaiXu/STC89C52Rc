# ifndef _pwm_H
# define _pwm_H

# include "public.h"

//pwm 管脚
sbit PWM = P2^1;

//pwm 初始化
void pwm_init(u8 tim_h, u8 tim_l, u8 tim_scale, u8 duty);

//传入占空比
void pwm_set_duty_cycle(u8 duty);

# endif