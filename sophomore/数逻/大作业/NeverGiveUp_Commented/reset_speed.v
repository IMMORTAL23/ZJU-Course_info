`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:35:06 01/03/2019 
// Design Name: 
// Module Name:    reset_speed 
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
module reset_speed(
	input wire clk,
	input wire cnt,
	output reg barrier_speed
    );

	always@(posedge clk)begin
		if(cnt == 0)
			barrier_speed <= 4;
	end
	
endmodule
