`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:44:01 12/27/2018 
// Design Name: 
// Module Name:    barrier 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module barrier(
	input wire [31:0] clk,
	input wire start,
	input wire reset,
	input wire [3:0] barrier_speed,
	output reg [15:0] score,
	output reg [5:0] width,
	output reg [8:0] y,
	output reg [9:0] x_1,
	output reg [9:0] x_2,
	output reg [9:0] x_3,
	output reg [9:0] x_4,
	output reg [9:0] x_5,
	output reg [9:0] x_6,
	output reg [9:0] x_7,
	output reg [9:0] x_8,
	output reg [9:0] x_9,
	output reg [9:0] x_10,
	output reg [6:0] height_1,
	output reg [6:0] height_2,
	output reg [6:0] height_3,
	output reg [6:0] height_4,
	output reg [6:0] height_5,
	output reg [6:0] height_6,
	output reg [6:0] height_7,
	output reg [6:0] height_8,
	output reg [6:0] height_9,
	output reg [6:0] height_10,
	output reg [6:0] left_height
    );
	
	reg [5:0] random_num;
	reg [19:0] cnt;
	
	//初始化十个障碍物的坐标，高度，分数，随机数生成数
	initial begin
		cnt <= 0;
		random_num <= 53;
		score <= 0;
		width <= 40;
		y <= 350;
		x_1 <= 0;
		x_2 <= 64;
		x_3 <= 128;
		x_4 <= 192;
		x_5 <= 256;
		x_6 <= 320;
		x_7 <= 384;
		x_8 <= 448;
		x_9 <= 512;
		x_10 <= 576;
		height_1 <= 10;
		height_2 <= 10;
		height_3 <= 10;
		height_4 <= 10;
		height_5 <= 10;
		height_6 <= 10;
		height_7 <= 10;
		height_8 <= 40;
		height_9 <= 40;
		height_10 <= 40;
		left_height <= 0;
	end

	//随机数生成	
	always @(posedge clk[0])begin
		cnt <= cnt + 1;
		if(cnt == 1000000)begin
			random_num <= random_num + 53;
			cnt <= 0;
		end
	end
	
	always @(posedge clk[20] or negedge reset) begin	
		//响应重置按钮	
		if(reset == 0) begin
			if(start == 0)begin
				score <= 0;
				width <= 40;
				y <= 350;
				x_1 <= 0;
				x_2 <= 64;
				x_3 <= 128;
				x_4 <= 192;
				x_5 <= 256;
				x_6 <= 320;
				x_7 <= 384;
				x_8 <= 448;
				x_9 <= 512;
				x_10 <= 576;
				height_1 <= 10;
				height_2 <= 10;
				height_3 <= 10;
				height_4 <= 10;
				height_5 <= 10;
				height_6 <= 10;
				height_7 <= 10;
				height_8 <= 40;
				height_9 <= 40;
				height_10 <= 40;
				left_height <= 0;
			end
		end
		else begin
			if(start == 1)begin
			//如果游戏正在进行，所有柱子的横坐标左移，形成移动画面
				if(x_1 >= barrier_speed) begin
					x_1 <= x_1 - barrier_speed;
					x_2 <= x_2 - barrier_speed;
					x_3 <= x_3 - barrier_speed;
					x_4 <= x_4 - barrier_speed;
					x_5 <= x_5 - barrier_speed;
					x_6 <= x_6 - barrier_speed;
					x_7 <= x_7 - barrier_speed;
					x_8 <= x_8 - barrier_speed;
					x_9 <= x_9 - barrier_speed;
					x_10 <= x_10 - barrier_speed;
				end
				//如果最左边的柱子达到边界，则交叉赋值，并对最后一个柱子的高度进行随机生成
				else begin
					x_1 <= x_2 - barrier_speed;
					x_2 <= x_3 - barrier_speed;
					x_3 <= x_4 - barrier_speed;
					x_4 <= x_5 - barrier_speed;
					x_5 <= x_6 - barrier_speed;
					x_6 <= x_7 - barrier_speed;
					x_7 <= x_8 - barrier_speed;
					x_8 <= x_9 - barrier_speed;
					x_9 <= x_10 - barrier_speed;
					x_10 <= x_10 + 64 - barrier_speed;
					
					left_height <= height_1;
					height_1 <= height_2;
					height_2 <= height_3;
					height_3 <= height_4;
					height_4 <= height_5;
					height_5 <= height_6;
					height_6 <= height_7;
					height_7 <= height_8;
					height_8 <= height_9;
					height_9 <= height_10;
					
					//根据随机数的值以及先前柱子的高度随机生成新柱子的高度
					if(random_num <= 32 && height_10 == 40 && height_9 != 70)
						height_10 <= 10;
					else if(random_num <= 32 && height_10 == 70)
						height_10 <= 40;
					else if(random_num > 32 && height_10 == 10)
						height_10 <= 40;
					else if(random_num > 32 && height_10 == 40)
						height_10 <= 70;
					else if(height_10 == 10)
						height_10 <= 10;
					else if(height_10 == 40)
						height_10 <= 40;
					else if(height_10 == 70)
						height_10 <= 70;
					else
						height_10 <= 10;
					
					//计算得分
					if(barrier_speed == 4)
						score <= score + 1;
					else if (barrier_speed == 8)
						score <= score + 2;
				end
			end
		end
	end
endmodule
