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

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "E:/logic/NeverGiveUp/bounce.v";
static unsigned int ng1[] = {276U, 0U};
static unsigned int ng2[] = {320U, 0U};
static int ng3[] = {7, 0};
static int ng4[] = {1, 0};
static int ng5[] = {0, 0};
static int ng6[] = {14, 0};



static void Initial_32_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(32, ng0);

LAB2:    xsi_set_current_line(33, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1928);
    xsi_vlogvar_wait_assign_value(t2, t1, 0, 0, 10, 0LL);
    xsi_set_current_line(34, ng0);
    t1 = ((char*)((ng2)));
    t2 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t2, t1, 0, 0, 9, 0LL);
    xsi_set_current_line(35, ng0);
    t1 = ((char*)((ng3)));
    t2 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t2, t1, 0, 0, 4, 0LL);
    xsi_set_current_line(36, ng0);
    t1 = ((char*)((ng4)));
    t2 = (t0 + 2408);
    xsi_vlogvar_wait_assign_value(t2, t1, 0, 0, 1, 0LL);

LAB1:    return;
}

static void Always_39_1(char *t0)
{
    char t6[8];
    char t30[8];
    char t58[8];
    char t60[8];
    char t64[8];
    char t94[8];
    char t111[8];
    char t127[8];
    char t143[8];
    char t159[8];
    char t167[8];
    char t199[8];
    char t207[8];
    char t245[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    char *t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    char *t45;
    char *t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    char *t52;
    char *t53;
    char *t54;
    char *t55;
    char *t56;
    char *t57;
    char *t59;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    char *t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    char *t76;
    char *t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    unsigned int t83;
    unsigned int t84;
    unsigned int t85;
    int t86;
    int t87;
    unsigned int t88;
    unsigned int t89;
    unsigned int t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    char *t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    char *t101;
    char *t102;
    unsigned int t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    char *t107;
    char *t108;
    char *t109;
    char *t110;
    char *t112;
    char *t113;
    unsigned int t114;
    unsigned int t115;
    unsigned int t116;
    unsigned int t117;
    unsigned int t118;
    unsigned int t119;
    unsigned int t120;
    unsigned int t121;
    unsigned int t122;
    unsigned int t123;
    unsigned int t124;
    unsigned int t125;
    char *t126;
    char *t128;
    unsigned int t129;
    unsigned int t130;
    unsigned int t131;
    unsigned int t132;
    unsigned int t133;
    char *t134;
    char *t135;
    unsigned int t136;
    unsigned int t137;
    unsigned int t138;
    char *t139;
    char *t140;
    char *t141;
    char *t142;
    char *t144;
    char *t145;
    unsigned int t146;
    unsigned int t147;
    unsigned int t148;
    unsigned int t149;
    unsigned int t150;
    unsigned int t151;
    unsigned int t152;
    unsigned int t153;
    unsigned int t154;
    unsigned int t155;
    unsigned int t156;
    unsigned int t157;
    char *t158;
    char *t160;
    unsigned int t161;
    unsigned int t162;
    unsigned int t163;
    unsigned int t164;
    unsigned int t165;
    char *t166;
    unsigned int t168;
    unsigned int t169;
    unsigned int t170;
    char *t171;
    char *t172;
    char *t173;
    unsigned int t174;
    unsigned int t175;
    unsigned int t176;
    unsigned int t177;
    unsigned int t178;
    unsigned int t179;
    unsigned int t180;
    char *t181;
    char *t182;
    unsigned int t183;
    unsigned int t184;
    unsigned int t185;
    unsigned int t186;
    unsigned int t187;
    unsigned int t188;
    unsigned int t189;
    unsigned int t190;
    int t191;
    int t192;
    unsigned int t193;
    unsigned int t194;
    unsigned int t195;
    unsigned int t196;
    unsigned int t197;
    unsigned int t198;
    char *t200;
    unsigned int t201;
    unsigned int t202;
    unsigned int t203;
    unsigned int t204;
    unsigned int t205;
    char *t206;
    unsigned int t208;
    unsigned int t209;
    unsigned int t210;
    char *t211;
    char *t212;
    char *t213;
    unsigned int t214;
    unsigned int t215;
    unsigned int t216;
    unsigned int t217;
    unsigned int t218;
    unsigned int t219;
    unsigned int t220;
    char *t221;
    char *t222;
    unsigned int t223;
    unsigned int t224;
    unsigned int t225;
    int t226;
    unsigned int t227;
    unsigned int t228;
    unsigned int t229;
    int t230;
    unsigned int t231;
    unsigned int t232;
    unsigned int t233;
    unsigned int t234;
    char *t235;
    unsigned int t236;
    unsigned int t237;
    unsigned int t238;
    unsigned int t239;
    unsigned int t240;
    char *t241;
    char *t242;
    char *t243;
    char *t244;
    char *t246;
    char *t247;
    unsigned int t248;
    unsigned int t249;
    unsigned int t250;
    unsigned int t251;
    unsigned int t252;
    unsigned int t253;
    unsigned int t254;
    unsigned int t255;
    unsigned int t256;
    unsigned int t257;
    unsigned int t258;
    unsigned int t259;
    char *t260;
    char *t261;
    unsigned int t262;
    unsigned int t263;
    unsigned int t264;
    unsigned int t265;
    unsigned int t266;
    char *t267;
    char *t268;

LAB0:    t1 = (t0 + 3576U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(39, ng0);
    t2 = (t0 + 3896);
    *((int *)t2) = 1;
    t3 = (t0 + 3608);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(39, ng0);

LAB5:    xsi_set_current_line(40, ng0);
    t4 = (t0 + 1368U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng5)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(48, ng0);

LAB22:    xsi_set_current_line(49, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng4)));
    memset(t6, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t9 = *((unsigned int *)t3);
    t10 = *((unsigned int *)t2);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t4);
    t13 = *((unsigned int *)t5);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB26;

LAB23:    if (t18 != 0)
        goto LAB25;

LAB24:    *((unsigned int *)t6) = 1;

LAB26:    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB27;

LAB28:
LAB29:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(40, ng0);

LAB13:    xsi_set_current_line(41, ng0);
    t28 = (t0 + 1208U);
    t29 = *((char **)t28);
    t28 = ((char*)((ng5)));
    memset(t30, 0, 8);
    t31 = (t29 + 4);
    t32 = (t28 + 4);
    t33 = *((unsigned int *)t29);
    t34 = *((unsigned int *)t28);
    t35 = (t33 ^ t34);
    t36 = *((unsigned int *)t31);
    t37 = *((unsigned int *)t32);
    t38 = (t36 ^ t37);
    t39 = (t35 | t38);
    t40 = *((unsigned int *)t31);
    t41 = *((unsigned int *)t32);
    t42 = (t40 | t41);
    t43 = (~(t42));
    t44 = (t39 & t43);
    if (t44 != 0)
        goto LAB17;

LAB14:    if (t42 != 0)
        goto LAB16;

LAB15:    *((unsigned int *)t30) = 1;

LAB17:    t46 = (t30 + 4);
    t47 = *((unsigned int *)t46);
    t48 = (~(t47));
    t49 = *((unsigned int *)t30);
    t50 = (t49 & t48);
    t51 = (t50 != 0);
    if (t51 > 0)
        goto LAB18;

LAB19:
LAB20:    goto LAB12;

LAB16:    t45 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t45) = 1;
    goto LAB17;

LAB18:    xsi_set_current_line(41, ng0);

LAB21:    xsi_set_current_line(42, ng0);
    t52 = ((char*)((ng1)));
    t53 = (t0 + 1928);
    xsi_vlogvar_wait_assign_value(t53, t52, 0, 0, 10, 0LL);
    xsi_set_current_line(43, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 9, 0LL);
    xsi_set_current_line(44, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 4, 0LL);
    xsi_set_current_line(45, ng0);
    t2 = ((char*)((ng4)));
    t3 = (t0 + 2408);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, 0, 1, 0LL);
    goto LAB20;

LAB25:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB26;

LAB27:    xsi_set_current_line(49, ng0);

LAB30:    xsi_set_current_line(50, ng0);
    t21 = (t0 + 2408);
    t22 = (t21 + 56U);
    t28 = *((char **)t22);
    t29 = ((char*)((ng4)));
    memset(t30, 0, 8);
    t31 = (t28 + 4);
    t32 = (t29 + 4);
    t33 = *((unsigned int *)t28);
    t34 = *((unsigned int *)t29);
    t35 = (t33 ^ t34);
    t36 = *((unsigned int *)t31);
    t37 = *((unsigned int *)t32);
    t38 = (t36 ^ t37);
    t39 = (t35 | t38);
    t40 = *((unsigned int *)t31);
    t41 = *((unsigned int *)t32);
    t42 = (t40 | t41);
    t43 = (~(t42));
    t44 = (t39 & t43);
    if (t44 != 0)
        goto LAB34;

LAB31:    if (t42 != 0)
        goto LAB33;

LAB32:    *((unsigned int *)t30) = 1;

LAB34:    t46 = (t30 + 4);
    t47 = *((unsigned int *)t46);
    t48 = (~(t47));
    t49 = *((unsigned int *)t30);
    t50 = (t49 & t48);
    t51 = (t50 != 0);
    if (t51 > 0)
        goto LAB35;

LAB36:    xsi_set_current_line(53, ng0);
    t2 = (t0 + 2088);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2248);
    t7 = (t5 + 56U);
    t8 = *((char **)t7);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_add(t6, 9, t4, 9, t8, 4);
    t21 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t21, t6, 0, 0, 9, 0LL);

LAB37:    xsi_set_current_line(54, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t6, 0, 8);
    t7 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB41;

LAB38:    if (t18 != 0)
        goto LAB40;

LAB39:    *((unsigned int *)t6) = 1;

LAB41:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB42;

LAB43:
LAB44:    xsi_set_current_line(56, ng0);
    t2 = (t0 + 2408);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t6, 0, 8);
    t7 = (t4 + 4);
    t8 = (t5 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB54;

LAB51:    if (t18 != 0)
        goto LAB53;

LAB52:    *((unsigned int *)t6) = 1;

LAB54:    memset(t30, 0, 8);
    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 & 1U);
    if (t27 != 0)
        goto LAB55;

LAB56:    if (*((unsigned int *)t22) != 0)
        goto LAB57;

LAB58:    t29 = (t30 + 4);
    t33 = *((unsigned int *)t30);
    t34 = *((unsigned int *)t29);
    t35 = (t33 || t34);
    if (t35 > 0)
        goto LAB59;

LAB60:    memcpy(t64, t30, 8);

LAB61:    memset(t94, 0, 8);
    t95 = (t64 + 4);
    t96 = *((unsigned int *)t95);
    t97 = (~(t96));
    t98 = *((unsigned int *)t64);
    t99 = (t98 & t97);
    t100 = (t99 & 1U);
    if (t100 != 0)
        goto LAB73;

LAB74:    if (*((unsigned int *)t95) != 0)
        goto LAB75;

LAB76:    t102 = (t94 + 4);
    t103 = *((unsigned int *)t94);
    t104 = (!(t103));
    t105 = *((unsigned int *)t102);
    t106 = (t104 || t105);
    if (t106 > 0)
        goto LAB77;

LAB78:    memcpy(t207, t94, 8);

LAB79:    t235 = (t207 + 4);
    t236 = *((unsigned int *)t235);
    t237 = (~(t236));
    t238 = *((unsigned int *)t207);
    t239 = (t238 & t237);
    t240 = (t239 != 0);
    if (t240 > 0)
        goto LAB109;

LAB110:    xsi_set_current_line(62, ng0);

LAB120:    xsi_set_current_line(63, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng6)));
    t7 = (t0 + 1528U);
    t8 = *((char **)t7);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 32, t5, 32, t8, 4);
    memset(t30, 0, 8);
    t7 = (t4 + 4);
    t21 = (t6 + 4);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t6);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t21);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t21);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB124;

LAB121:    if (t18 != 0)
        goto LAB123;

LAB122:    *((unsigned int *)t30) = 1;

LAB124:    t28 = (t30 + 4);
    t23 = *((unsigned int *)t28);
    t24 = (~(t23));
    t25 = *((unsigned int *)t30);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB125;

LAB126:    xsi_set_current_line(66, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_add(t6, 32, t4, 4, t5, 32);
    t7 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t7, t6, 0, 0, 4, 0LL);

LAB127:
LAB111:    goto LAB29;

LAB33:    t45 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t45) = 1;
    goto LAB34;

LAB35:    xsi_set_current_line(51, ng0);
    t52 = (t0 + 2088);
    t53 = (t52 + 56U);
    t54 = *((char **)t53);
    t55 = (t0 + 2248);
    t56 = (t55 + 56U);
    t57 = *((char **)t56);
    memset(t58, 0, 8);
    xsi_vlog_unsigned_minus(t58, 9, t54, 9, t57, 4);
    t59 = (t0 + 2088);
    xsi_vlogvar_wait_assign_value(t59, t58, 0, 0, 9, 0LL);
    goto LAB37;

LAB40:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB41;

LAB42:    xsi_set_current_line(55, ng0);
    t28 = (t0 + 2408);
    t29 = (t28 + 56U);
    t31 = *((char **)t29);
    memset(t30, 0, 8);
    t32 = (t31 + 4);
    t33 = *((unsigned int *)t32);
    t34 = (~(t33));
    t35 = *((unsigned int *)t31);
    t36 = (t35 & t34);
    t37 = (t36 & 1U);
    if (t37 != 0)
        goto LAB48;

LAB46:    if (*((unsigned int *)t32) == 0)
        goto LAB45;

LAB47:    t45 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t45) = 1;

LAB48:    t46 = (t30 + 4);
    t52 = (t31 + 4);
    t38 = *((unsigned int *)t31);
    t39 = (~(t38));
    *((unsigned int *)t30) = t39;
    *((unsigned int *)t46) = 0;
    if (*((unsigned int *)t52) != 0)
        goto LAB50;

LAB49:    t44 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t44 & 1U);
    t47 = *((unsigned int *)t46);
    *((unsigned int *)t46) = (t47 & 1U);
    t53 = (t0 + 2408);
    xsi_vlogvar_wait_assign_value(t53, t30, 0, 0, 1, 0LL);
    goto LAB44;

LAB45:    *((unsigned int *)t30) = 1;
    goto LAB48;

LAB50:    t40 = *((unsigned int *)t30);
    t41 = *((unsigned int *)t52);
    *((unsigned int *)t30) = (t40 | t41);
    t42 = *((unsigned int *)t46);
    t43 = *((unsigned int *)t52);
    *((unsigned int *)t46) = (t42 | t43);
    goto LAB49;

LAB53:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB54;

LAB55:    *((unsigned int *)t30) = 1;
    goto LAB58;

LAB57:    t28 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB58;

LAB59:    t31 = (t0 + 2248);
    t32 = (t31 + 56U);
    t45 = *((char **)t32);
    t46 = ((char*)((ng5)));
    memset(t58, 0, 8);
    t52 = (t45 + 4);
    t53 = (t46 + 4);
    t36 = *((unsigned int *)t45);
    t37 = *((unsigned int *)t46);
    t38 = (t36 ^ t37);
    t39 = *((unsigned int *)t52);
    t40 = *((unsigned int *)t53);
    t41 = (t39 ^ t40);
    t42 = (t38 | t41);
    t43 = *((unsigned int *)t52);
    t44 = *((unsigned int *)t53);
    t47 = (t43 | t44);
    t48 = (~(t47));
    t49 = (t42 & t48);
    if (t49 != 0)
        goto LAB63;

LAB62:    if (t47 != 0)
        goto LAB64;

LAB65:    memset(t60, 0, 8);
    t55 = (t58 + 4);
    t50 = *((unsigned int *)t55);
    t51 = (~(t50));
    t61 = *((unsigned int *)t58);
    t62 = (t61 & t51);
    t63 = (t62 & 1U);
    if (t63 != 0)
        goto LAB66;

LAB67:    if (*((unsigned int *)t55) != 0)
        goto LAB68;

LAB69:    t65 = *((unsigned int *)t30);
    t66 = *((unsigned int *)t60);
    t67 = (t65 & t66);
    *((unsigned int *)t64) = t67;
    t57 = (t30 + 4);
    t59 = (t60 + 4);
    t68 = (t64 + 4);
    t69 = *((unsigned int *)t57);
    t70 = *((unsigned int *)t59);
    t71 = (t69 | t70);
    *((unsigned int *)t68) = t71;
    t72 = *((unsigned int *)t68);
    t73 = (t72 != 0);
    if (t73 == 1)
        goto LAB70;

LAB71:
LAB72:    goto LAB61;

LAB63:    *((unsigned int *)t58) = 1;
    goto LAB65;

LAB64:    t54 = (t58 + 4);
    *((unsigned int *)t58) = 1;
    *((unsigned int *)t54) = 1;
    goto LAB65;

LAB66:    *((unsigned int *)t60) = 1;
    goto LAB69;

LAB68:    t56 = (t60 + 4);
    *((unsigned int *)t60) = 1;
    *((unsigned int *)t56) = 1;
    goto LAB69;

LAB70:    t74 = *((unsigned int *)t64);
    t75 = *((unsigned int *)t68);
    *((unsigned int *)t64) = (t74 | t75);
    t76 = (t30 + 4);
    t77 = (t60 + 4);
    t78 = *((unsigned int *)t30);
    t79 = (~(t78));
    t80 = *((unsigned int *)t76);
    t81 = (~(t80));
    t82 = *((unsigned int *)t60);
    t83 = (~(t82));
    t84 = *((unsigned int *)t77);
    t85 = (~(t84));
    t86 = (t79 & t81);
    t87 = (t83 & t85);
    t88 = (~(t86));
    t89 = (~(t87));
    t90 = *((unsigned int *)t68);
    *((unsigned int *)t68) = (t90 & t88);
    t91 = *((unsigned int *)t68);
    *((unsigned int *)t68) = (t91 & t89);
    t92 = *((unsigned int *)t64);
    *((unsigned int *)t64) = (t92 & t88);
    t93 = *((unsigned int *)t64);
    *((unsigned int *)t64) = (t93 & t89);
    goto LAB72;

LAB73:    *((unsigned int *)t94) = 1;
    goto LAB76;

LAB75:    t101 = (t94 + 4);
    *((unsigned int *)t94) = 1;
    *((unsigned int *)t101) = 1;
    goto LAB76;

LAB77:    t107 = (t0 + 2248);
    t108 = (t107 + 56U);
    t109 = *((char **)t108);
    t110 = ((char*)((ng5)));
    memset(t111, 0, 8);
    t112 = (t109 + 4);
    t113 = (t110 + 4);
    t114 = *((unsigned int *)t109);
    t115 = *((unsigned int *)t110);
    t116 = (t114 ^ t115);
    t117 = *((unsigned int *)t112);
    t118 = *((unsigned int *)t113);
    t119 = (t117 ^ t118);
    t120 = (t116 | t119);
    t121 = *((unsigned int *)t112);
    t122 = *((unsigned int *)t113);
    t123 = (t121 | t122);
    t124 = (~(t123));
    t125 = (t120 & t124);
    if (t125 != 0)
        goto LAB83;

LAB80:    if (t123 != 0)
        goto LAB82;

LAB81:    *((unsigned int *)t111) = 1;

LAB83:    memset(t127, 0, 8);
    t128 = (t111 + 4);
    t129 = *((unsigned int *)t128);
    t130 = (~(t129));
    t131 = *((unsigned int *)t111);
    t132 = (t131 & t130);
    t133 = (t132 & 1U);
    if (t133 != 0)
        goto LAB84;

LAB85:    if (*((unsigned int *)t128) != 0)
        goto LAB86;

LAB87:    t135 = (t127 + 4);
    t136 = *((unsigned int *)t127);
    t137 = *((unsigned int *)t135);
    t138 = (t136 || t137);
    if (t138 > 0)
        goto LAB88;

LAB89:    memcpy(t167, t127, 8);

LAB90:    memset(t199, 0, 8);
    t200 = (t167 + 4);
    t201 = *((unsigned int *)t200);
    t202 = (~(t201));
    t203 = *((unsigned int *)t167);
    t204 = (t203 & t202);
    t205 = (t204 & 1U);
    if (t205 != 0)
        goto LAB102;

LAB103:    if (*((unsigned int *)t200) != 0)
        goto LAB104;

LAB105:    t208 = *((unsigned int *)t94);
    t209 = *((unsigned int *)t199);
    t210 = (t208 | t209);
    *((unsigned int *)t207) = t210;
    t211 = (t94 + 4);
    t212 = (t199 + 4);
    t213 = (t207 + 4);
    t214 = *((unsigned int *)t211);
    t215 = *((unsigned int *)t212);
    t216 = (t214 | t215);
    *((unsigned int *)t213) = t216;
    t217 = *((unsigned int *)t213);
    t218 = (t217 != 0);
    if (t218 == 1)
        goto LAB106;

LAB107:
LAB108:    goto LAB79;

LAB82:    t126 = (t111 + 4);
    *((unsigned int *)t111) = 1;
    *((unsigned int *)t126) = 1;
    goto LAB83;

LAB84:    *((unsigned int *)t127) = 1;
    goto LAB87;

LAB86:    t134 = (t127 + 4);
    *((unsigned int *)t127) = 1;
    *((unsigned int *)t134) = 1;
    goto LAB87;

LAB88:    t139 = (t0 + 2408);
    t140 = (t139 + 56U);
    t141 = *((char **)t140);
    t142 = ((char*)((ng5)));
    memset(t143, 0, 8);
    t144 = (t141 + 4);
    t145 = (t142 + 4);
    t146 = *((unsigned int *)t141);
    t147 = *((unsigned int *)t142);
    t148 = (t146 ^ t147);
    t149 = *((unsigned int *)t144);
    t150 = *((unsigned int *)t145);
    t151 = (t149 ^ t150);
    t152 = (t148 | t151);
    t153 = *((unsigned int *)t144);
    t154 = *((unsigned int *)t145);
    t155 = (t153 | t154);
    t156 = (~(t155));
    t157 = (t152 & t156);
    if (t157 != 0)
        goto LAB94;

LAB91:    if (t155 != 0)
        goto LAB93;

LAB92:    *((unsigned int *)t143) = 1;

LAB94:    memset(t159, 0, 8);
    t160 = (t143 + 4);
    t161 = *((unsigned int *)t160);
    t162 = (~(t161));
    t163 = *((unsigned int *)t143);
    t164 = (t163 & t162);
    t165 = (t164 & 1U);
    if (t165 != 0)
        goto LAB95;

LAB96:    if (*((unsigned int *)t160) != 0)
        goto LAB97;

LAB98:    t168 = *((unsigned int *)t127);
    t169 = *((unsigned int *)t159);
    t170 = (t168 & t169);
    *((unsigned int *)t167) = t170;
    t171 = (t127 + 4);
    t172 = (t159 + 4);
    t173 = (t167 + 4);
    t174 = *((unsigned int *)t171);
    t175 = *((unsigned int *)t172);
    t176 = (t174 | t175);
    *((unsigned int *)t173) = t176;
    t177 = *((unsigned int *)t173);
    t178 = (t177 != 0);
    if (t178 == 1)
        goto LAB99;

LAB100:
LAB101:    goto LAB90;

LAB93:    t158 = (t143 + 4);
    *((unsigned int *)t143) = 1;
    *((unsigned int *)t158) = 1;
    goto LAB94;

LAB95:    *((unsigned int *)t159) = 1;
    goto LAB98;

LAB97:    t166 = (t159 + 4);
    *((unsigned int *)t159) = 1;
    *((unsigned int *)t166) = 1;
    goto LAB98;

LAB99:    t179 = *((unsigned int *)t167);
    t180 = *((unsigned int *)t173);
    *((unsigned int *)t167) = (t179 | t180);
    t181 = (t127 + 4);
    t182 = (t159 + 4);
    t183 = *((unsigned int *)t127);
    t184 = (~(t183));
    t185 = *((unsigned int *)t181);
    t186 = (~(t185));
    t187 = *((unsigned int *)t159);
    t188 = (~(t187));
    t189 = *((unsigned int *)t182);
    t190 = (~(t189));
    t191 = (t184 & t186);
    t192 = (t188 & t190);
    t193 = (~(t191));
    t194 = (~(t192));
    t195 = *((unsigned int *)t173);
    *((unsigned int *)t173) = (t195 & t193);
    t196 = *((unsigned int *)t173);
    *((unsigned int *)t173) = (t196 & t194);
    t197 = *((unsigned int *)t167);
    *((unsigned int *)t167) = (t197 & t193);
    t198 = *((unsigned int *)t167);
    *((unsigned int *)t167) = (t198 & t194);
    goto LAB101;

LAB102:    *((unsigned int *)t199) = 1;
    goto LAB105;

LAB104:    t206 = (t199 + 4);
    *((unsigned int *)t199) = 1;
    *((unsigned int *)t206) = 1;
    goto LAB105;

LAB106:    t219 = *((unsigned int *)t207);
    t220 = *((unsigned int *)t213);
    *((unsigned int *)t207) = (t219 | t220);
    t221 = (t94 + 4);
    t222 = (t199 + 4);
    t223 = *((unsigned int *)t221);
    t224 = (~(t223));
    t225 = *((unsigned int *)t94);
    t226 = (t225 & t224);
    t227 = *((unsigned int *)t222);
    t228 = (~(t227));
    t229 = *((unsigned int *)t199);
    t230 = (t229 & t228);
    t231 = (~(t226));
    t232 = (~(t230));
    t233 = *((unsigned int *)t213);
    *((unsigned int *)t213) = (t233 & t231);
    t234 = *((unsigned int *)t213);
    *((unsigned int *)t213) = (t234 & t232);
    goto LAB108;

LAB109:    xsi_set_current_line(56, ng0);

LAB112:    xsi_set_current_line(57, ng0);
    t241 = (t0 + 2248);
    t242 = (t241 + 56U);
    t243 = *((char **)t242);
    t244 = ((char*)((ng5)));
    memset(t245, 0, 8);
    t246 = (t243 + 4);
    t247 = (t244 + 4);
    t248 = *((unsigned int *)t243);
    t249 = *((unsigned int *)t244);
    t250 = (t248 ^ t249);
    t251 = *((unsigned int *)t246);
    t252 = *((unsigned int *)t247);
    t253 = (t251 ^ t252);
    t254 = (t250 | t253);
    t255 = *((unsigned int *)t246);
    t256 = *((unsigned int *)t247);
    t257 = (t255 | t256);
    t258 = (~(t257));
    t259 = (t254 & t258);
    if (t259 != 0)
        goto LAB116;

LAB113:    if (t257 != 0)
        goto LAB115;

LAB114:    *((unsigned int *)t245) = 1;

LAB116:    t261 = (t245 + 4);
    t262 = *((unsigned int *)t261);
    t263 = (~(t262));
    t264 = *((unsigned int *)t245);
    t265 = (t264 & t263);
    t266 = (t265 != 0);
    if (t266 > 0)
        goto LAB117;

LAB118:    xsi_set_current_line(60, ng0);
    t2 = (t0 + 2248);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng4)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 32, t4, 4, t5, 32);
    t7 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t7, t6, 0, 0, 4, 0LL);

LAB119:    goto LAB111;

LAB115:    t260 = (t245 + 4);
    *((unsigned int *)t245) = 1;
    *((unsigned int *)t260) = 1;
    goto LAB116;

LAB117:    xsi_set_current_line(58, ng0);
    t267 = (t0 + 1528U);
    t268 = *((char **)t267);
    t267 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t267, t268, 0, 0, 4, 0LL);
    goto LAB119;

LAB123:    t22 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t22) = 1;
    goto LAB124;

LAB125:    xsi_set_current_line(64, ng0);
    t29 = ((char*)((ng5)));
    t31 = (t0 + 2248);
    xsi_vlogvar_wait_assign_value(t31, t29, 0, 0, 4, 0LL);
    goto LAB127;

}


extern void work_m_00000000002104592216_3852973799_init()
{
	static char *pe[] = {(void *)Initial_32_0,(void *)Always_39_1};
	xsi_register_didat("work_m_00000000002104592216_3852973799", "isim/main_isim_beh.exe.sim/work/m_00000000002104592216_3852973799.didat");
	xsi_register_executes(pe);
}
