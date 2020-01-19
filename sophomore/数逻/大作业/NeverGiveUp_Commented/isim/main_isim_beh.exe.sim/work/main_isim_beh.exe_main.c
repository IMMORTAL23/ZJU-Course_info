/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000003266574342_1129804446_init();
    work_m_00000000000897832967_1110640149_init();
    work_m_00000000002104592216_3852973799_init();
    work_m_00000000001854885712_0757712981_init();
    work_m_00000000001421892962_3112508248_init();
    work_m_00000000000268926346_0286164271_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000000268926346_0286164271");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
