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
    work_m_00000000001127514682_3852973799_init();
    work_m_00000000000432813029_0286164271_init();
    work_m_00000000000541918784_1690108397_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000000541918784_1690108397");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
