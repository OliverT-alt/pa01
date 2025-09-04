#include <iostream> // for use of cin, cout, endl
#include <string> // for use of strings
#include <cmath> // for use of pow(x,y) function
// NO OTHER LIBRARIES ARE ALLOWED!
using namespace std;
// function: disassemble takes in a string representing
// an assembled MIPS instruction as a string
// and returns the instruction itself
//
// This is a limited disassembler: we can safely assume the input is:
// a) legitimate (an actual MIPS instruction)
// b) is ONLY an I-type and ONLY one of: addi, addiu, andi, ori, slti, sltiu
// c) has ONLY registers $a0 thru $a3, $t0 thru $t7, or $s0 thru $s7 in the instruction
//
string disassemble( string hex ) {

    // You want to retrieve all the separate fields of an I-type instruction
   // to help you figure out what the assembly instruction is.
// HINT: Use bitwise masking and bit-shifting to isolate the
// different parts of the hex instruction!
// YOUR CODE GOES HERE!!

    // Convert hex string and extract fields with bit shifts
    long number = stoul(hex, nullptr, 16);
    int opcode = (number >> 26) & 0x3F;
    int rs = (number >> 21) & 0x1F;
    int rt = (number >> 16) & 0x1F;
    int imm = number & 0xFFFF;
    if (imm & 0x8000) { // Check if sign bit is 1
        imm = imm - 0x10000; // extend to 32 bits
    }

    // Convert register numbers to names
    string reg_rt, reg_rs;
    if (rt >= 0 && rt <= 3) reg_rt = "$a" + to_string(rt);
    else if (rt >= 8 && rt <= 15) reg_rt = "$t" + to_string(rt - 8);
    else if (rt >= 16 && rt <= 23) reg_rt = "$s" + to_string(rt - 16);

    if (rs >= 0 && rs <= 3) reg_rs = "$a" + to_string(rs);
    else if (rs >= 8 && rs <= 15) reg_rs = "$t" + to_string(rs - 8);
    else if (rs >= 16 && rs <= 23) reg_rs = "$s" + to_string(rs - 16);

    // Determine instruction based on opcode
    string instr;
    if (opcode == 0x08) instr = "addi";
    else if (opcode == 0x09) instr = "addiu";
    else if (opcode == 0x0C) instr = "andi";
    else if (opcode == 0x0D) instr = "ori";
    else if (opcode == 0x0A) instr = "slti";
    else if (opcode == 0x0B) instr = "sltiu";

    // Build and return the assembly string
    return instr + " " + reg_rt + ", " + reg_rs + ", " + to_string(imm); // remove stub and replace it with correct variable

}

int main() {
// Do NOT change ANY code in main() function!!
// or you will fail this task (get a zero)
string hex, inst;
cout << "Enter your assembled instruction as a hex number: 0x";
cin >> hex;
inst = disassemble( hex );
cout << "Your instruction is:\n" << inst << endl;
return 0;
}
