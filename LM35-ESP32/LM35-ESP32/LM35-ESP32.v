`timescale 1 ms / 1 ns

module LM35ESP32(
	input clk,
	input ack,
	//input back,
	input [2:0] db,
	output reg [7:0] sseg,
	output reg[5:0] en
);

initial sseg = 8'b11000000;
initial en = 6'b111111;

reg clk_input = 1'b0;
integer clk_input_cnt = 0;

reg clk_sseg = 1'b0;
integer clk_sseg_cnt = 0;

reg [6:0] data = 6'd0;
reg [6:0] saved_data = 6'd0;
integer bit_cnt = 6;

// reg show_flg = 1'b0;
reg sseg_flg = 1'b0;

reg [7:0] mem[0:9];
initial begin
mem[0] = 8'b11000000;
mem[1] = 8'b11111001;
mem[2] = 8'b10100100;
mem[3] = 8'b10110000;
mem[4] = 8'b10011001;
mem[5] = 8'b10010010;
mem[6] = 8'b10000010;
mem[7] = 8'b11111000;
mem[8] = 8'b10000000;
mem[9] = 8'b10010000;
end


/////// Clock Delays:
always @(posedge clk)
begin
  if(clk_input_cnt >= 25500)
	begin
	clk_input_cnt <= 0;
	clk_input <= ~clk_input;
	end
  else
	clk_input_cnt <= clk_input_cnt + 1;
end

always @(posedge clk)
begin
  if(clk_sseg_cnt >= 25500)
	begin
	clk_sseg_cnt <= 0;
	clk_sseg <= ~clk_sseg;
	end
  else
	clk_sseg_cnt <= clk_sseg_cnt + 1;
end

/////// Recieve Data From ESP32 bit by bit
always @(posedge clk_input)
begin
	if(ack == 1)
		begin
			data[bit_cnt - 1] = db[2];			
			data[bit_cnt - 2] = db[1];
			data[bit_cnt - 3] = db[0];

			bit_cnt = bit_cnt - 3;
		
			if(bit_cnt <= 0)
				begin
					saved_data = data;
					data = 0;
					//show_flg = 1;
					bit_cnt = 6;
				end
		end
end


/////// SSEG Display
always @(posedge clk_sseg)
begin
	case(sseg_flg)
		0: begin sseg = mem[(saved_data % 10)]; sseg[7] = 0; en = 6'b111110; end
		1: begin sseg = mem[((saved_data / 10) % 10)]; sseg[7] = 0; en = 6'b111101; end
	endcase
	
	sseg_flg = 1 - sseg_flg;
end
endmodule
