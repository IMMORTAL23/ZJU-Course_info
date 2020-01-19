`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:27:05 12/27/2018
// Design Name:   main
// Module Name:   E:/logic/NeverGiveUp/TestMain.v
// Project Name:  NeverGiveUp
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: main
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module TestMain;

	// Inputs
	reg clk;
	reg SW;
	reg BTN_Y;

	// Outputs
	wire hs;
	wire vs;
	wire [3:0] r;
	wire [3:0] g;
	wire [3:0] b;
	wire BTN_X;

	// Instantiate the Unit Under Test (UUT)
	main uut (
		.clk(clk), 
		.SW(SW), 
		.hs(hs), 
		.vs(vs), 
		.r(r), 
		.g(g), 
		.b(b), 
		.BTN_X(BTN_X), 
		.BTN_Y(BTN_Y)
	);

	initial begin
		SW = 1;

	end
	
	always begin
		clk = 0; #20;
		clk = 1; #20;
	end
      
endmodule

