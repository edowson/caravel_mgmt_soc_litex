/**
 \file
*/
#ifndef FIRMWARE_APIS_C_HEADER_FILE
#define FIRMWARE_APIS_C_HEADER_FILE

#include <defs.h>
#include <stub.c>
#include <uart.h>
#include <irq_vex.h>

#include <gpios.h>
#include <timer0.h>
#include <mgmt_gpio.h>
#include <la.h>
#include <uart_api.h>
#include <irq_api.h>
#include <spi_master.h>
#include <user_space.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
void enable_debug(){
    User_enableIF();
    flash_phy_clk_divisor_write(0);
    // set_debug_reg1(0);
    // set_debug_reg2(0);
    
}
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
/**
 * Enable or disable the housekeeping SPI 
 * This function writes to the housekeeping disenable register inside the housekeeping
 * \note
 * When this register asserted housekeeping SPI can't be used and GPIOs[3] which is CSB can be used as any other Caravel GPIOs
 *  
 * \warning 
 * By default the housekeeping SPI is enabled to use GPIOs[3] freely it should be disabled. 
 * 
 * @param is_enable when 1 (true) housekeeping is active, 0 (false) housekeeping is disabled
 */
void enableHkSpi(bool is_enable){reg_hkspi_disable = !is_enable;}
// debug regs
#ifndef DOXYGEN_SHOULD_SKIP_THIS
void set_debug_reg1(unsigned int data){reg_debug_1 = data;}
void set_debug_reg2(unsigned int data){reg_debug_2 = data;}
unsigned int get_debug_reg1(){return reg_debug_1;}
unsigned int get_debug_reg2(){return reg_debug_2;}
void wait_debug_reg1(unsigned int data){while (get_debug_reg1() != data);}
void wait_debug_reg2(unsigned int data){while (get_debug_reg2() != data);}
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

// user project registers
#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define reg_mprj_userl (*(volatile unsigned int*)0x300FFFF0)
#define reg_mprj_userh (*(volatile unsigned int*)0x300FFFF4)
#define reg_oeb_userl  (*(volatile unsigned int*)0x300FFFEC)
#define reg_oeb_userh  (*(volatile unsigned int*)0x300FFFE8)

// gpio_user 
void set_gpio_user_l(unsigned int data){reg_mprj_userl = data;}
void set_gpio_user_h(unsigned int data){reg_mprj_userh = data;}
unsigned int get_gpio_user_h(){
    return reg_mprj_userh;
}
unsigned int get_gpio_user_l(){return reg_mprj_userl;}
void wait_gpio_user_l(unsigned int data){while (reg_mprj_userl != data);}
void wait_gpio_user_h(unsigned int data){
    while (get_gpio_user_h() != data);    
}

void output_enable_all_gpio_user(char is_enable){
    if (is_enable){
        reg_oeb_userl = 0x0;
        reg_oeb_userh = 0x0;
    }else{
        reg_oeb_userl = 0xFFFFFFFF;
        reg_oeb_userh = 0x3F;
    }

}
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

// 
/**
 * Insert delay 
 * 
 * @param num number of delays steps. step is increment local variable and check it's value
 * 
 * 
 */
void dummyDelay(int num){
    for (volatile int i=0;i < num;i++){
        continue;
    }
}



// debug 
#ifndef DOXYGEN_SHOULD_SKIP_THIS
void mgmt_debug_enable(){reg_wb_enable = reg_wb_enable | 0x10;}
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


#endif // FIRMWARE_APIS_C_HEADER_FILE
