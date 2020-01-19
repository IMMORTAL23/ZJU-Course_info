`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:24:32 12/27/2018
// Design Name:   bounce
// Module Name:   E:/logic/NeverGiveUp/Test.v
// Project Name:  NeverGiveUp
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: bounce
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Test;

	// Inputs
	reg clk;
	reg btn;

	// Outputs
	wire [9:0] x;
	wire [8:0] y;

	// Instantiate the Unit Under Test (UUT)
	bounce uut (
		.clk(clk), 
		.btn(btn), 
		.x(x), 
		.y(y)
	);

	initial begin
		btn = 0;
	end
	
	always begin
		clk = 0; #20;
		clk = 1; #20;
	end
      
endmodule

