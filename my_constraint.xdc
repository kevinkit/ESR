###################
# TIMING CONTRAINTS
###################

# define system clock and period
create_clock -period 10.000 -name clk_in1 -waveform {0.000 5.000} [get_ports clk_in1]


#################
# PIN CONSTRAINTS
#################

# CLK source 100 MHz
set_property PACKAGE_PIN Y9 [get_ports clk_in1]
set_property IOSTANDARD LVCMOS33 [get_ports clk_in1]

# Reset button - BTNC
set_property PACKAGE_PIN P16 [get_ports reset]
set_property IOSTANDARD LVCMOS33 [get_ports reset]
