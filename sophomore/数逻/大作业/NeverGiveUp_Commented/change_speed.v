`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    20:41:00 12/28/2018 
// Design Name: 
// Module Name:    change_speed 
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
module change_speed(
	input wire clk,
	input wire direction,
	input wire change,
	input wire start,
	input wire reset,
	input wire collision,
	input wire [3:0] ball_speed,
	input wire [6:0] height_5,
	input wire [6:0] height_6,
	input wire [6:0] height_7,
	output reg [3:0] barrier_speed,
	output reg [3:0] max_speed
    );
	
	//初始化
	initial begin
		max_speed <= 7;
		barrier_speed <= 4;
	end
	
	always @(posedge clk or negedge change or negedge reset)begin
		//游戏重置响应
		if(reset == 0)begin
			if(start == 0 || collision == 1)begin
				max_speed <= 7;
				barrier_speed <= 4;
			end
		end
		else begin
			if(change == 0)begin
				if(start == 1)begin
					//根据后面障碍物的情况控制障碍物的移动速度以及小球的之后的运动情况
					if(ball_speed == 0 && direction == 0 && height_5 >= height_6)
						barrier_speed <= 8;
					else if(ball_speed == 0 && direction == 0)
						barrier_speed <= 4;
						
					if(ball_speed == 0 && direction == 0 && height_5 >= height_6 && height_5 > height_7)
						max_speed <= 5; 
					else if(ball_speed == 0 && direction == 0 && height_6 > height_5)
						max_speed <= 9;
					else if(ball_speed == 0 && direction == 0)
						max_speed <= 7;
				end
			end
			else begin
				//一个运动周期后自动重置障碍物以及小球的运动，以及对应小球下落的运动状态
				if(start == 1)begin
					if(ball_speed == 0 && direction == 0 && height_6 < height_5)begin
						max_speed <= 5;
						barrier_speed <= 4;
					end
					else begin
						if(ball_speed == 0 && direction == 0)begin
							max_speed <= 7;
							barrier_speed <= 4;
						end
					end
				end
			end
		end
	end

endmodule
