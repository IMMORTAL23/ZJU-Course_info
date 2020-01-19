`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:21:38 12/13/2018 
// Design Name: 
// Module Name:    My74LS161 
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
module My74LS161(
	input wire CR,
	input wire LD,
	input wire CTp,
	input wire CTt,
	input wire CP,
	input wire [3:0] D,
	output reg [3:0] Q,
	output reg CO
    );

always@ (posedge CP or negedge CR) begin
	if (CR == 0) begin
		Q = 4'b0;
	end
	else begin
		if (LD == 0) begin
			Q = D;
		end
		else begin
			if (CTt == 1) begin
				if (CTp == 0) begin
					Q = Q;
				end
				else begin
					Q = Q + 1;
				end
			end
			else begin
				Q = Q;
			end
		end
		CO = Q[0] & Q[1] & Q[2] & Q[3] & CTt;
	end
end

endmodule
