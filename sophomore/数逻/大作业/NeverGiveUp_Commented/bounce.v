`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:58:26 12/27/2018 
// Design Name: 
// Module Name:    bounce 
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
module bounce(
	input wire clk,
	input wire start,
	input wire reset,
	input wire [3:0] max_speed,
	output reg [9:0] x,
	output reg [8:0] y,
	output reg [3:0] speed,
	output reg direction
    );
	
	//初始化小球坐标以及运动速度和方向
	initial begin
		x <= 10'd276;
		y <= 9'd320;
		speed <= 7;
		direction <= 1;
	end
	
	always @(posedge clk or negedge reset) begin
		//响应重置按钮
		if(reset == 0)begin
			if(start == 0)begin
				x <= 10'd276;
				y <= 9'd320;
				speed <= 7;
				direction <= 1;
			end
		end
		else begin
			//在游戏正在进行的情况下
			if(start == 1) begin
			//以下为模拟小球的斜抛运动，即小球的速度会随时间变化
				if(direction == 1)
					y <= y - speed;
				else
					y <= y + speed;
				//到达顶端则改变运动方向
				if(speed == 0)
					direction <= ~direction;
					
				if(direction == 1 && speed != 0 || speed == 0 && direction == 0)begin
					if(speed == 0)
						speed <= max_speed;
					else
						speed <= speed - 1;
				end 
				else begin
					if(speed == 14 - max_speed)
						speed <= 0;
					else
						speed <= speed + 1;
				end
			end
		end
	end

endmodule
