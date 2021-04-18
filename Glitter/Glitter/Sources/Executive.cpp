// Local Headers
#include "glitter.hpp"
#include "rds.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define INDIVIDUALS_SPAWNED_PER_HOUSE 	2
#define EVENTS_PER_DAY					6
#define EVENTS_TO_LOOKAHEAD				6
#define ADD_OFFICE_PROB					7

long long int Executive::generateID()
{
	static long long int id = -1;
	return ++id;
}

// Shader Sources
const char* vertexSource = R"glsl(
    #version 400 core

    in vec3 position;
    in vec3 color;
    in vec2 texcoord;

    out vec3 Color;
    out vec2 Texcoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;

    void main()
    {
        Color = color;
        Texcoord = texcoord;
        gl_Position = proj * view * model * vec4(position, 1.0);
    }
)glsl";
const char* fragmentSource = R"glsl(
    #version 400 core

    in vec3 Color;
    in vec2 Texcoord;

    out vec4 outColor;

    uniform sampler2D texTex;

    void main()
    {
        vec4 colTex = texture(texTex, Texcoord);
        outColor = vec4(Color, 1.0) * colTex;
    }
)glsl";

GLfloat * createBottomVertices(int xPos, int yPos, GLfloat zheight, int citySize) {
    GLfloat xOff = (GLfloat)xPos/(GLfloat)citySize;
    GLfloat yOff = (float)yPos/(float)citySize;

    GLfloat * v = new GLfloat[6*8];
    ///// BOTTOM
    v[0] = static_cast<GLfloat>(-0.5) + xOff; v[1] = static_cast<GLfloat>(-0.5) + yOff; v[2] = zheight; v[3] =  1.0; v[4] =  1.0; v[5] =  1.0; v[6] =  0.0; v[7] =  0.0; //BLB
    v[8] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[9] = static_cast<GLfloat>(-0.5) + yOff; v[10] = zheight; v[11] =  1.0; v[12] =  1.0; v[13] =  1.0; v[14] =  1.0; v[15] =  0.0; //BLF
    v[16] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[17] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[18] = zheight; v[19] =  1.0; v[20] =  1.0; v[21] =  1.0; v[22] =  1.0; v[23] =  1.0; //BRF
    v[24] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[25] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[26] = zheight; v[27] =  1.0; v[28] =  1.0; v[29] =  1.0; v[30] =  1.0; v[31] =  1.0; //BRF
    v[32] = static_cast<GLfloat>(-0.5) + xOff; v[33] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[34] = zheight; v[35] =  1.0; v[36] =  1.0; v[37] =  1.0; v[38] =  0.0; v[39] =  1.0; //BRB
    v[40] = static_cast<GLfloat>(-0.5) + xOff; v[41] = static_cast<GLfloat>(-0.5) + yOff; v[42] = zheight; v[43] =  1.0; v[44] =  1.0; v[45] =  1.0; v[46] =  0.0; v[47] =  0.0; //BLB
    return v;
};

GLfloat * createCubeVertices(int xPos, int yPos, GLfloat zHeight, int citySize) {
    GLfloat xOff = (GLfloat)xPos/(GLfloat)citySize;
    GLfloat yOff = (float)yPos/(float)citySize;

    GLfloat * v = new GLfloat[36*8];
    ///// BOTTOM
    v[0] = static_cast<GLfloat>(-0.5) + xOff; v[1] = static_cast<GLfloat>(-0.5) + yOff; v[2] = 0.0 + zHeight; v[3] =  1.0; v[4] =  1.0; v[5] =  1.0; v[6] =  0.0; v[7] =  0.0; //BLB
    v[8] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[9] = static_cast<GLfloat>(-0.5) + yOff; v[10] = 0.0 + zHeight; v[11] =  1.0; v[12] =  1.0; v[13] =  1.0; v[14] =  1.0; v[15] =  0.0; //BLF
    v[16] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[17] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[18] = 0.0 + zHeight; v[19] =  1.0; v[20] =  1.0; v[21] =  1.0; v[22] =  1.0; v[23] =  1.0; //BRF
    v[24] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[25] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[26] = 0.0 + zHeight; v[27] =  1.0; v[28] =  1.0; v[29] =  1.0; v[30] =  1.0; v[31] =  1.0; //BRF
    v[32] = static_cast<GLfloat>(-0.5) + xOff; v[33] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[34] = 0.0 + zHeight; v[35] =  1.0; v[36] =  1.0; v[37] =  1.0; v[38] =  0.0; v[39] =  1.0; //BRB
    v[40] = static_cast<GLfloat>(-0.5) + xOff; v[41] = static_cast<GLfloat>(-0.5) + yOff; v[42] = 0.0 + zHeight; v[43] =  1.0; v[44] =  1.0; v[45] =  1.0; v[46] =  0.0; v[47] =  0.0; //BLB
    ///// TOP
    v[48] = static_cast<GLfloat>(-0.5) + xOff; v[49] = static_cast<GLfloat>(-0.5) + yOff; v[50] = 1.0/(GLfloat)citySize + zHeight; v[51] =  1.0; v[52] =  1.0; v[53] =  1.0; v[54] =  0.0; v[55] =  0.0; //TLB
    v[56] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[57] = static_cast<GLfloat>(-0.5) + yOff; v[58] = 1.0/(GLfloat)citySize + zHeight; v[59] =  1.0; v[60] =  1.0; v[61] =  1.0; v[62] =  1.0; v[63] =  0.0; //TLF
    v[64] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[65] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[66] = 1.0/(GLfloat)citySize + zHeight; v[67] =  1.0; v[68] =  1.0; v[69] =  1.0; v[70] =  1.0; v[71] =  1.0; //TRF
    v[72] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[73] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[74] = 1.0/(GLfloat)citySize + zHeight; v[75] =  1.0; v[76] =  1.0; v[77] =  1.0; v[78] =  1.0; v[79] =  1.0; //TRF
    v[80] = static_cast<GLfloat>(-0.5) + xOff; v[81] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[82] = 1.0/(GLfloat)citySize + zHeight; v[83] =  1.0; v[84] =  1.0; v[85] =  1.0; v[86] =  0.0; v[87] =  1.0; //TRB
    v[88] = static_cast<GLfloat>(-0.5) + xOff; v[89] = static_cast<GLfloat>(-0.5) + yOff; v[90] = 1.0/(GLfloat)citySize + zHeight; v[91] =  1.0; v[92] =  1.0; v[93] =  1.0; v[94] =  0.0; v[95] =  0.0; //TLB
    ///// BACK
    v[96] = static_cast<GLfloat>(-0.5) + xOff; v[97] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[98] = 1.0/(GLfloat)citySize + zHeight; v[99] =  1.0; v[100] =  1.0; v[101] =  1.0; v[102] =  1.0; v[103] =  0.0; //TRB
    v[104] = static_cast<GLfloat>(-0.5) + xOff; v[105] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[106] = 0.0 + zHeight; v[107] =  1.0; v[108] =  1.0; v[109] =  1.0; v[110] =  1.0; v[111] =  1.0; //BRB
    v[112] = static_cast<GLfloat>(-0.5) + xOff; v[113] = static_cast<GLfloat>(-0.5) + yOff; v[114] = 0.0 + zHeight; v[115] =  1.0; v[116] =  1.0; v[117] =  1.0; v[118] =  0.0; v[119] =  1.0; //BLB
    v[120] = static_cast<GLfloat>(-0.5) + xOff; v[121] = static_cast<GLfloat>(-0.5) + yOff; v[122] = 0.0 + zHeight; v[123] =  1.0; v[124] =  1.0; v[125] =  1.0; v[126] =  0.0; v[127] =  1.0; //BLB
    v[128] = static_cast<GLfloat>(-0.5) + xOff; v[129] = static_cast<GLfloat>(-0.5) + yOff; v[130] = 1.0/(GLfloat)citySize + zHeight; v[131] =  1.0; v[132] =  1.0; v[133] =  1.0; v[134] =  0.0; v[135] =  0.0; //TLB
    v[136] = static_cast<GLfloat>(-0.5) + xOff; v[137] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[138] = 1.0/(GLfloat)citySize + zHeight; v[139] =  1.0; v[140] =  1.0; v[141] =  1.0; v[142] =  1.0; v[143] =  0.0; //TRB
    ///// FRONT
    v[144] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[145] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[146] = 1.0/(GLfloat)citySize + zHeight; v[147] =  1.0; v[148] =  1.0; v[149] =  1.0; v[150] =  1.0; v[151] =  0.0; //TRF
    v[152] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[153] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[154] = 0.0 + zHeight; v[155] =  1.0; v[156] =  1.0; v[157] =  1.0; v[158] =  1.0; v[159] =  1.0; //BRF
    v[160] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[161] = static_cast<GLfloat>(-0.5) + yOff; v[162] = 0.0 + zHeight; v[163] =  1.0; v[164] =  1.0; v[165] =  1.0; v[166] =  0.0; v[167] =  1.0; //BLF
    v[168] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[169] = static_cast<GLfloat>(-0.5) + yOff; v[170] = 0.0 + zHeight; v[171] =  1.0; v[172] =  1.0; v[173] =  1.0; v[174] =  0.0; v[175] =  1.0; //BLF
    v[176] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[177] = static_cast<GLfloat>(-0.5) + yOff; v[178] = 1.0/(GLfloat)citySize + zHeight; v[179] =  1.0; v[180] =  1.0; v[181] =  1.0; v[182] =  0.0; v[183] =  0.0; //TLF
    v[184] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[185] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[186] = 1.0/(GLfloat)citySize + zHeight; v[187] =  1.0; v[188] =  1.0; v[189] =  1.0; v[190] =  1.0; v[191] =  0.0; //TRF
    ////// LEFT
    v[192] = static_cast<GLfloat>(-0.5) + xOff; v[193] = static_cast<GLfloat>(-0.5) + yOff; v[194] = 0.0 + zHeight; v[195] =  1.0; v[196] =  1.0; v[197] =  1.0; v[198] =  0.0; v[199] =  1.0; //BLB
    v[200] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[201] = static_cast<GLfloat>(-0.5) + yOff; v[202] = 0.0 + zHeight; v[203] =  1.0; v[204] =  1.0; v[205] =  1.0; v[206] =  1.0; v[207] =  1.0; //BLF
    v[208] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[209] = static_cast<GLfloat>(-0.5) + yOff; v[210] = 1.0/(GLfloat)citySize + zHeight; v[211] =  1.0; v[212] =  1.0; v[213] =  1.0; v[214] =  1.0; v[215] =  0.0; //TLF
    v[216] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[217] = static_cast<GLfloat>(-0.5) + yOff; v[218] = 1.0/(GLfloat)citySize + zHeight; v[219] =  1.0; v[220] =  1.0; v[221] =  1.0; v[222] =  1.0; v[223] =  0.0; //TLF
    v[224] = static_cast<GLfloat>(-0.5) + xOff; v[225] = static_cast<GLfloat>(-0.5) + yOff; v[226] = 1.0/(GLfloat)citySize + zHeight; v[227] =  1.0; v[228] =  1.0; v[229] =  1.0; v[230] =  0.0; v[231] =  0.0; //TLB
    v[232] = static_cast<GLfloat>(-0.5) + xOff; v[233] = static_cast<GLfloat>(-0.5) + yOff; v[234] = 0.0 + zHeight; v[235] =  1.0; v[236] =  1.0; v[237] =  1.0; v[238] =  0.0; v[239] =  1.0; //BLB
    ///// RIGHT
    v[240] = static_cast<GLfloat>(-0.5) + xOff; v[241] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[242] = 0.0 + zHeight; v[243] =  1.0; v[244] =  1.0; v[245] =  1.0; v[246] =  0.0; v[247] =  1.0; //BRB
    v[248] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[249] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[250] = 0.0 + zHeight; v[251] =  1.0; v[252] =  1.0; v[253] =  1.0; v[254] =  1.0; v[255] =  1.0; //BRF
    v[256] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[257] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[258] = 1.0/(GLfloat)citySize + zHeight; v[259] =  1.0; v[260] =  1.0; v[261] =  1.0; v[262] =  1.0; v[263] =  0.0; //TRF
    v[264] = static_cast<GLfloat>(-0.5) + xOff + 1.0/(GLfloat)citySize; v[265] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[266] = 1.0/(GLfloat)citySize + zHeight; v[267] =  1.0; v[268] =  1.0; v[269] =  1.0; v[270] =  1.0; v[271] =  0.0; //TRF
    v[272] = static_cast<GLfloat>(-0.5) + xOff; v[273] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[274] = 1.0/(GLfloat)citySize + zHeight; v[275] =  1.0; v[276] =  1.0; v[277] =  1.0; v[278] =  0.0; v[279] =  0.0; //TRB
    v[280] = static_cast<GLfloat>(-0.5) + xOff; v[281] = static_cast<GLfloat>(-0.5) + yOff + 1.0/(GLfloat)citySize; v[282] = 0.0 + zHeight; v[283] =  1.0; v[284] =  1.0; v[285] =  1.0; v[286] =  0.0; v[287] =  1.0; //BRB

    return v;
};

GLfloat * createDroneVertices(int xPos, int yPos, GLfloat zHeight, int citySize, int time, int direction, int speed) {
    GLfloat xOff = (GLfloat)xPos/(GLfloat)citySize;
    GLfloat yOff = (float)yPos/(float)citySize;
	GLfloat xDir, yDir;
	if (direction == -1){ //UP
		xDir = 0.0;
		yDir = -1*time%speed * (1.0/(float)citySize)/(float)speed;
	} else if (direction == 1){ //DOWN
		xDir = 0.0;
		yDir = 1 * time%speed * (1.0/(float)citySize)/(float)speed;
	} else if (direction == -2){ //LEFT
		xDir = -1 * time%speed * (1.0/(float)citySize)/(float)speed;
		yDir = 0.0;
	} else if (direction == 2){ //RIGHT W
		xDir = time%speed * (1.0/(float)citySize)/(float)speed;
		yDir = 0.0;
	} else {
		xDir = 0.0;
		yDir = 0.0;		
	}
    GLfloat * v = new GLfloat[36*8];
    ///// BOTTOM
    v[0] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[1] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[2] = 0.0 + zHeight; v[3] =  1.0; v[4] =  1.0; v[5] =  1.0; v[6] =  0.0; v[7] =  0.0; //BLB
    v[8] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[9] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[10] = 0.0 + zHeight; v[11] =  1.0; v[12] =  1.0; v[13] =  1.0; v[14] =  1.0; v[15] =  0.0; //BLF
    v[16] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[17] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[18] = 0.0 + zHeight; v[19] =  1.0; v[20] =  1.0; v[21] =  1.0; v[22] =  1.0; v[23] =  1.0; //BRF
    v[24] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[25] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[26] = 0.0 + zHeight; v[27] =  1.0; v[28] =  1.0; v[29] =  1.0; v[30] =  1.0; v[31] =  1.0; //BRF
    v[32] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[33] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[34] = 0.0 + zHeight; v[35] =  1.0; v[36] =  1.0; v[37] =  1.0; v[38] =  0.0; v[39] =  1.0; //BRB
    v[40] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[41] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[42] = 0.0 + zHeight; v[43] =  1.0; v[44] =  1.0; v[45] =  1.0; v[46] =  0.0; v[47] =  0.0; //BLB
    ///// TOP
    v[48] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[49] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[50] = 0.5/(GLfloat)citySize + zHeight; v[51] =  1.0; v[52] =  1.0; v[53] =  1.0; v[54] =  0.0; v[55] =  0.0; //TLB
    v[56] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[57] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[58] = 0.5/(GLfloat)citySize + zHeight; v[59] =  1.0; v[60] =  1.0; v[61] =  1.0; v[62] =  1.0; v[63] =  0.0; //TLF
    v[64] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[65] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[66] = 0.5/(GLfloat)citySize + zHeight; v[67] =  1.0; v[68] =  1.0; v[69] =  1.0; v[70] =  1.0; v[71] =  1.0; //TRF
    v[72] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[73] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[74] = 0.5/(GLfloat)citySize + zHeight; v[75] =  1.0; v[76] =  1.0; v[77] =  1.0; v[78] =  1.0; v[79] =  1.0; //TRF
    v[80] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[81] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[82] = 0.5/(GLfloat)citySize + zHeight; v[83] =  1.0; v[84] =  1.0; v[85] =  1.0; v[86] =  0.0; v[87] =  1.0; //TRB
    v[88] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[89] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[90] = 0.5/(GLfloat)citySize + zHeight; v[91] =  1.0; v[92] =  1.0; v[93] =  1.0; v[94] =  0.0; v[95] =  0.0; //TLB
    ///// BACK
    v[96] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[97] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[98] = 0.5/(GLfloat)citySize + zHeight; v[99] =  1.0; v[100] =  1.0; v[101] =  1.0; v[102] =  1.0; v[103] =  0.0; //TRB
    v[104] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[105] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[106] = 0.0 + zHeight; v[107] =  1.0; v[108] =  1.0; v[109] =  1.0; v[110] =  1.0; v[111] =  1.0; //BRB
    v[112] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[113] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[114] = 0.0 + zHeight; v[115] =  1.0; v[116] =  1.0; v[117] =  1.0; v[118] =  0.0; v[119] =  1.0; //BLB
    v[120] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[121] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[122] = 0.0 + zHeight; v[123] =  1.0; v[124] =  1.0; v[125] =  1.0; v[126] =  0.0; v[127] =  1.0; //BLB
    v[128] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[129] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[130] = 0.5/(GLfloat)citySize + zHeight; v[131] =  1.0; v[132] =  1.0; v[133] =  1.0; v[134] =  0.0; v[135] =  0.0; //TLB
    v[136] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[137] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[138] = 0.5/(GLfloat)citySize + zHeight; v[139] =  1.0; v[140] =  1.0; v[141] =  1.0; v[142] =  1.0; v[143] =  0.0; //TRB
    ///// FRONT
    v[144] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[145] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[146] = 0.5/(GLfloat)citySize + zHeight; v[147] =  1.0; v[148] =  1.0; v[149] =  1.0; v[150] =  1.0; v[151] =  0.0; //TRF
    v[152] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[153] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[154] = 0.0 + zHeight; v[155] =  1.0; v[156] =  1.0; v[157] =  1.0; v[158] =  1.0; v[159] =  1.0; //BRF
    v[160] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[161] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[162] = 0.0 + zHeight; v[163] =  1.0; v[164] =  1.0; v[165] =  1.0; v[166] =  0.0; v[167] =  1.0; //BLF
    v[168] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[169] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[170] = 0.0 + zHeight; v[171] =  1.0; v[172] =  1.0; v[173] =  1.0; v[174] =  0.0; v[175] =  1.0; //BLF
    v[176] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[177] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[178] = 0.5/(GLfloat)citySize + zHeight; v[179] =  1.0; v[180] =  1.0; v[181] =  1.0; v[182] =  0.0; v[183] =  0.0; //TLF
    v[184] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[185] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[186] = 0.5/(GLfloat)citySize + zHeight; v[187] =  1.0; v[188] =  1.0; v[189] =  1.0; v[190] =  1.0; v[191] =  0.0; //TRF
    ////// LEFT
    v[192] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[193] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[194] = 0.0 + zHeight; v[195] =  1.0; v[196] =  1.0; v[197] =  1.0; v[198] =  0.0; v[199] =  1.0; //BLB
    v[200] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[201] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[202] = 0.0 + zHeight; v[203] =  1.0; v[204] =  1.0; v[205] =  1.0; v[206] =  1.0; v[207] =  1.0; //BLF
    v[208] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[209] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[210] = 0.5/(GLfloat)citySize + zHeight; v[211] =  1.0; v[212] =  1.0; v[213] =  1.0; v[214] =  1.0; v[215] =  0.0; //TLF
    v[216] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[217] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[218] = 0.5/(GLfloat)citySize + zHeight; v[219] =  1.0; v[220] =  1.0; v[221] =  1.0; v[222] =  1.0; v[223] =  0.0; //TLF
    v[224] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[225] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[226] = 0.5/(GLfloat)citySize + zHeight; v[227] =  1.0; v[228] =  1.0; v[229] =  1.0; v[230] =  0.0; v[231] =  0.0; //TLB
    v[232] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[233] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.2/(GLfloat)citySize; v[234] = 0.0 + zHeight; v[235] =  1.0; v[236] =  1.0; v[237] =  1.0; v[238] =  0.0; v[239] =  1.0; //BLB
    ///// RIGHT
    v[240] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[241] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[242] = 0.0 + zHeight; v[243] =  1.0; v[244] =  1.0; v[245] =  1.0; v[246] =  0.0; v[247] =  1.0; //BRB
    v[248] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[249] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[250] = 0.0 + zHeight; v[251] =  1.0; v[252] =  1.0; v[253] =  1.0; v[254] =  1.0; v[255] =  1.0; //BRF
    v[256] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[257] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[258] = 0.5/(GLfloat)citySize + zHeight; v[259] =  1.0; v[260] =  1.0; v[261] =  1.0; v[262] =  1.0; v[263] =  0.0; //TRF
    v[264] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.8/(GLfloat)citySize; v[265] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[266] = 0.5/(GLfloat)citySize + zHeight; v[267] =  1.0; v[268] =  1.0; v[269] =  1.0; v[270] =  1.0; v[271] =  0.0; //TRF
    v[272] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[273] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[274] = 0.5/(GLfloat)citySize + zHeight; v[275] =  1.0; v[276] =  1.0; v[277] =  1.0; v[278] =  0.0; v[279] =  0.0; //TRB
    v[280] = static_cast<GLfloat>(-0.5) + xOff + xDir + 0.2/(GLfloat)citySize; v[281] = static_cast<GLfloat>(-0.5) + yOff + yDir + 0.8/(GLfloat)citySize; v[282] = 0.0 + zHeight; v[283] =  1.0; v[284] =  1.0; v[285] =  1.0; v[286] =  0.0; v[287] =  1.0; //BRB

    return v;
};

void Executive::run()
{
	//Prompt user for...
	//Simluation duration
	int months;
	std::cout << "How many months should the simulation run for?\n";
	std::cin >> months;

	//Map dimensions
	int mapWidth, mapHeight, blockSize;
	std::cout << "Enter the width (in blocks) of the world followed by the height (ex: 4 5).\n";
	std::cin >> mapWidth >> mapHeight;
	
	//Size of each block
	std::cout << "How wide should each block be?\n";
	std::cin >> blockSize;

	//Create the map itself
	cityMap theMap( mapWidth*blockSize+1, mapHeight*blockSize+1, blockSize, 5, 3 );
	theMap.printMap();	//Show the map for debug purposes
	
	
	//Populate building lists using the map
	FFCs 			= theMap.getFFC();
	offices 		= theMap.getOffices();
	houses 			= theMap.getHouses();
	allBuildings	= theMap.getBuildings();
	
	//Separate storage for buildings that are used for events (only offices and houses)
	std::vector<Building*> eventBuildings;

	for(std::list<Office*>::iterator iter = offices.begin(); iter != offices.end(); iter++)
		eventBuildings.push_back(*iter);

	for(std::list<House*>::iterator iter = houses.begin(); iter != houses.end(); iter++)
		eventBuildings.push_back(*iter);

	//Assign IDs to all buildings
	for(std::list<Building*>::iterator buildIter = allBuildings.begin(); buildIter != allBuildings.end(); buildIter++)
		(*buildIter)->setID(generateID());

	int officeCount = 0;
	int houseCount = 0;

	//Spawn individuals in the houses and generate their agendas
	for(std::list<House*>::iterator houseIter = houses.begin(); houseIter != houses.end(); houseIter++)
	{
		for(int i = 0; i < INDIVIDUALS_SPAWNED_PER_HOUSE; i++)
		{
			Individual * janeDoe = new Individual(*houseIter,generateID());
			peopleList.push_back(janeDoe);
			(*houseIter)->addOccupant(janeDoe);
			
			Agenda * agenda = new Agenda(janeDoe);
			
			//Create a random list of events for this individual's agenda
			for(int j = 0; j < EVENTS_PER_DAY * 30 * months; j++)
			{
				//int inOffice = rand() % 4; irandom_range(0,3);
				int buildingNumber = rand() % ((ADD_OFFICE_PROB*offices.size())+ eventBuildings.size());
				if(buildingNumber >= eventBuildings.size())
				{
					int difference = buildingNumber - eventBuildings.size();
					buildingNumber = buildingNumber % offices.size();//(difference - 1)/ADD_OFFICE_PROB;
				}
				
				if(buildingNumber < offices.size())
					officeCount++;
				else
					houseCount++;
				
				Building* building = eventBuildings[buildingNumber];

				int resourceAmount = rand() % 6 + 1;
				std::list<int> resourceTypes;
				double totalWeight = 0;
				double totalVolume = 0;
				CargoDrone cd(0,0,0);
				double maxVolume = cd.getMaxVolume();
				double maxWeight = cd.getMaxWeight();
				for(int k = 0; k < resourceAmount; k++)
				{
					int resourceType = rand() % TOTAL_RESOURCE_TYPES;
					double theWeight = rTable.getValue(resourceType,WEIGHT_MAX);
					double theVolume = rTable.getValue(resourceType,VOLUME_MAX);
					if(totalWeight + theWeight <= maxWeight
					&& totalVolume + theVolume <= maxVolume)
					{
						totalWeight += theWeight;
						totalVolume += theVolume;
						resourceTypes.push_back(resourceType);
					}
				}
				Event* event = new Event(building,janeDoe,resourceTypes);
				agenda->addEvent(*event);
				eventsCreated++;
			}

			agendas.push_back(agenda);
			//break;	//Remove this to spawn more individuals in a house
		}
		//break;	//Remove this to spawn individuals in multiple houses
	}
	
	std::cout << "Houses, Offices: " << houseCount << ", " << officeCount << std::endl;
	
	std::cout << static_cast<double>(houseCount/houses.size()) << ", " << static_cast<double>(officeCount/offices.size()) << std::endl;
	
	std::cout << offices.size() << ", " << eventBuildings.size() << std::endl;
	
	//Create the AI itself
	/*MainAI theAI( droneList, FFCs );

	//Determine plan for the first week
	for(int i = 0; i < EVENTS_TO_LOOKAHEAD; i++)
	{
	
	}
	*/

	//Graphics Initialization
	// Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "RDS", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        //return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST);

    // Create VAO before binding VBO and element buffers
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create VBO, bind it, copy vertice data
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // Make vbo the active array buffer

    // Create an element array
    //GLuint ebo;
    //glGenBuffers(1, &ebo);
    //GLuint elements[] = {
    //    0, 1, 2,
    //    2, 3, 0
    //};
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create, get source of, and compile Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    // Create, get source of, and compile Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Create a program, attach shaders, link, and use program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor"); // Needed with more than one fragment shader?
    glLinkProgram(shaderProgram); // Changes to shaders within a linked 
                                  // program will not change the actual result 
                                  // until the program has been linked again
    glUseProgram(shaderProgram); // Only one program can be active at a time

    // Get and set uniform color of shader
    // GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
    // glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

    // Format and order of attributes
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE,
        8*sizeof(GLfloat), 0); // Also stores VBO currently bound to GL_ARRAY_BUFFER
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
        8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));  
    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
        8*sizeof(GLfloat), (void*)(6*sizeof(GLfloat)));

    // Load textures
    GLuint tex[13];
    glGenTextures(13, tex);
    //glGenTextures(1, &tex);
    //glBindTexture(GL_TEXTURE_2D, tex);

    int width, height, n;
    unsigned char *image;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/sample2.png", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/bricky.jpeg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);    

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, tex[2]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/orange.jpeg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, tex[3]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/skyscraper.jpeg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, tex[4]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/road.jpg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, tex[5]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/grass.jpg", &width, &height, &n, 0);
	std::cout << "number of channels in image: " << n << std::endl;
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;

    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, tex[6]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/uhaul.jpg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 6);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, tex[7]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/taxi.jpeg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 7);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D, tex[8]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/road2.jpg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 8);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_2D, tex[9]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/intersection.jpg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 9);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, tex[10]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/rooftop.jpeg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 10);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE11);
    glBindTexture(GL_TEXTURE_2D, tex[11]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/rooftop2.jpeg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 11);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glActiveTexture(GL_TEXTURE12);
    glBindTexture(GL_TEXTURE_2D, tex[12]);
    image = stbi_load("/Users/joanjones/Documents/RDS/Glitter/Glitter/Sources/rooftop3.jpeg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 12);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Set up Transformations
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    //printf("%f, %f, %f\n", result.x, result.y, result.z);
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    //glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

    // Set up view and projection
    glm::mat4 view = glm::lookAt(
        glm::vec3(1.2f, 1.2f, 1.2f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(glm::radians(30.0f), 800.0f / 600.0f, 0.1f, 20.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	//Begin simulation loop
	int currentTime = 0;
	int timePerStep = 16;//100;	//milliseconds
	int timeCount = 0;
	int speed = 15;
	int** mapArray = theMap.getMap();
	std::chrono::high_resolution_clock::time_point time1, time2;
	std::chrono::high_resolution_clock::time_point droneStart, droneEnd, eventStart, eventEnd, checkStart, checkEnd;
	auto t_start = std::chrono::high_resolution_clock::now();
	while( currentTime < months*30*24*60 )
	{
		//Get the time at the start of the loop
		time1 = std::chrono::high_resolution_clock::now();


		//Update drone positions
		//droneStart = std::chrono::high_resolution_clock::now();
		if (currentTime%speed == 0){
		moveDrones();
		//droneEnd = std::chrono::high_resolution_clock::now();
		//int droneTime = std::chrono::duration_cast<std::chrono::microseconds>(droneEnd - droneStart).count();
		//std::cout << "Drone time: " << droneTime << " microseconds" << std::endl;

		//Attempt to execute events
		//eventStart = std::chrono::high_resolution_clock::now();
		executeEvents(theMap.getRoadConc());
		//eventEnd = std::chrono::high_resolution_clock::now();
		//int eventTime = std::chrono::duration_cast<std::chrono::milliseconds>(eventEnd - eventStart).count();
		//std::cout << "Event execution: " << eventTime << " milliseconds" << std::endl;

		//Load/unload a passenger when the drone stops
		//checkStart = std::chrono::high_resolution_clock::now();
		checkDrones(theMap.getRoadConc());
		//checkEnd = std::chrono::high_resolution_clock::now();
		//int checkTime = std::chrono::duration_cast<std::chrono::milliseconds>(checkEnd - checkStart).count();
		//std::cout << "Check drones: " << checkTime << " milliseconds" << std::endl;
		}
		//if(!resourceList.empty())
			//std::cout << resourceList.front()->getXPos() << ", " << resourceList.front()->getYPos() << std::endl;

		//Update graphics
		// Rendering Loop
		//std::chrono::high_resolution_clock::time_point timeGraphicsStart = std::chrono::high_resolution_clock::now();
		if (glfwWindowShouldClose(mWindow) == false) {
			if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(mWindow, true);

			// Set the color of the triangle
			//auto t_now = std::chrono::high_resolution_clock::now();
			//float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
			//glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

			// Background Fill Color
			glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			auto t_now = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
			glm::mat4 model = glm::mat4(1.0f);
			/*model = glm::rotate(
				model,
				time * glm::radians(180.0f) / 32,
				glm::vec3(0.0f, 0.0f, 1.0f)
			);*/
			glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

			// Draw a rectangle from the 2 triangles using 6 indices
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//glDrawArrays(GL_TRIANGLES, 0, 36);
			int xSize = theMap.getXSize();

			std::list<PassengerDrone*>::iterator itr = pDroneList.begin();
			*itr++;
			PassengerDrone* first = *itr;
			int direction = first->getMoveList().front().dir;
			/*if (direction == 1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.62f + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.05f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == 2){
				view = glm::lookAt(
					glm::vec3(-0.62f + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.05f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.34f + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.05f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -2){
				view = glm::lookAt(
					glm::vec3(-0.34f + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.05f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else {
				view = glm::lookAt(
					glm::vec3(-0.6f, -0.5f, 0.1f),
					glm::vec3(-0.5f, -0.5f, 0.02f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			}*/

			/*if (direction == 1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.62f + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == 2){
				view = glm::lookAt(
					glm::vec3(-0.62f + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.34f + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -2){
				view = glm::lookAt(
					glm::vec3(-0.34f + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else {
				view = glm::lookAt(
					glm::vec3(-0.6f, -0.5f, 0.1f),
					glm::vec3(-0.5f, -0.5f, 0.02f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			}*/

			/*if (direction == 1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed + 0.001, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == 2){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 0.001, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed + 0.001, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -2){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 0.001, 0.2f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else {
				view = glm::lookAt(
					glm::vec3(-0.6f, -0.5f, 0.1f),
					glm::vec3(-0.5f, -0.5f, 0.02f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			}*/

			if (direction == 1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed + 0.001, 2.0f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == 2){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 0.001, 2.0f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize + 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -1){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed + 0.001, 2.0f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else if (direction == -2){
				view = glm::lookAt(
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize + 0.001, 2.0f),
					glm::vec3(-0.5f + 0.5f/(float)xSize + (float)first->getXPos()/(float)xSize - 1.0f*(float)(currentTime%speed) * (1.0/(float)xSize)/(float)speed, -0.5f + 0.5f/(float)xSize + (float)first->getYPos()/(float)xSize, 0.03f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			} else {
				view = glm::lookAt(
					glm::vec3(-0.6f, -0.5f, 0.1f),
					glm::vec3(-0.5f, -0.5f, 0.02f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				);
			}
			glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

			for (int j = 0; j < xSize; j++)
			{

				for (int i = 0; i<xSize; i++){
					if (mapArray[i][j] == 4){
						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 2);
						GLfloat * cube = createCubeVertices(i, j, 0.0, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 36);

						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 12);
						cube = createBottomVertices(i, j, 1.0/(GLfloat)xSize + 0.001, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 6);
					} else if (mapArray[i][j] == 2){
						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 1);
						GLfloat * cube = createCubeVertices(i, j, 0.0, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 36);
						cube = createCubeVertices(i, j, 1.0/(GLfloat)xSize, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 36);
						cube = createCubeVertices(i, j, 2.0/(GLfloat)xSize, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 36);

						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 10);
						cube = createBottomVertices(i, j, 3.0/(GLfloat)xSize + 0.001, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 6);
					} else if (mapArray[i][j] == 3){
						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 3);
						GLfloat * cube = createCubeVertices(i, j, 0.0, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 36);
						cube = createCubeVertices(i, j, 1.0/(GLfloat)xSize, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 36);

						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 11);
						cube = createBottomVertices(i, j, 2.0/(GLfloat)xSize + 0.001, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 6);
					} else if (mapArray[i][j] == 1){
						if (i%blockSize == 0){
							glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 8);
							GLfloat * cube = createBottomVertices(i, j, 0.0, xSize);
							glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
							delete cube;
							glDrawArrays(GL_TRIANGLES, 0, 6);
						} else {
							glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 4);
							GLfloat * cube = createBottomVertices(i, j, 0.0, xSize);
							glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
							delete cube;
							glDrawArrays(GL_TRIANGLES, 0, 6);
						}
					} else if (mapArray[i][j] == 5){
						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 9);
						GLfloat * cube = createBottomVertices(i, j, 0.0, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 6);						
					} else {
						glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 5);
						GLfloat * cube = createBottomVertices(i, j, 0.0, xSize);
						glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
						delete cube;
						glDrawArrays(GL_TRIANGLES, 0, 6);
					}
				}

			}
			/*std::cout << "Cargo ID list: ";
			for(std::list<CargoDrone*>::iterator it = cDroneList.begin(); it != cDroneList.end(); it++){
				CargoDrone* currentDrone = *it;
				std::cout << currentDrone->getID() << " ";
			}
			std::cout << std::endl;
			std::cout << "Passenger ID list: ";
			for(std::list<PassengerDrone*>::iterator it = pDroneList.begin(); it != pDroneList.end(); it++){
				PassengerDrone* currentDrone = *it;
				std::cout << currentDrone->getID() << " ";
			}
			std::cout << std::endl;*/

			for(std::list<CargoDrone*>::iterator it = cDroneList.begin(); it != cDroneList.end(); it++)
			{
				CargoDrone* currentDrone = *it;
				int xpos = currentDrone->getXPos();
				int ypos = currentDrone->getYPos();
				int direction = currentDrone->getMoveList().front().dir;
				//int direction = 1;
				glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 6);
				GLfloat * drone = createDroneVertices(xpos, ypos, 0.0, xSize, currentTime, direction, speed);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), drone, GL_STATIC_DRAW);
				delete drone;
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			for(std::list<PassengerDrone*>::iterator it = pDroneList.begin(); it != pDroneList.end(); it++)
			{
				PassengerDrone* currentDrone = *it;
				int xpos = currentDrone->getXPos();
				int ypos = currentDrone->getYPos();
				int direction = currentDrone->getMoveList().front().dir;
				//int direction = 1;
				glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 7);
				GLfloat * drone = createDroneVertices(xpos, ypos, 0.0, xSize, currentTime, direction, speed);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), drone, GL_STATIC_DRAW);
				delete drone;
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//glDrawArrays(GL_TRIANGLES, 0, 36);

			// Flip Buffers and Draw
			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}
		//std::chrono::high_resolution_clock::time_point timeGraphicsEnd = std::chrono::high_resolution_clock::now();
		//int graphicsTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeGraphicsEnd - timeGraphicsStart).count();
		//std::cout << "Graphic time: " << graphicsTime << std::endl;
		//droneInformation();

		//Pause the simulation until the next time step
		time2 = std::chrono::high_resolution_clock::now();
		timeCount = std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1).count();
		//std::cout << "Frame time: " << timeCount << std::endl;
		std::this_thread::sleep_for( std::chrono::milliseconds( std::max(timePerStep-timeCount, 0) ) );

		currentTime++;
	}

	//Graphics Termination
	glDeleteTextures(13, tex);
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    //glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();

	std::cout << "Simulation ended\n";
	std::cout << "Events completed: " << eventsCompleted << "/" << eventsCreated << std::endl;
};

void Executive::moveDrones()
{
	for(std::list<Drone*>::iterator droneIter = droneList.begin(); droneIter != droneList.end(); droneIter++)
	{
		(*droneIter)->move();
	}
}

void Executive::checkDrones(int roadConc)
{
	for(std::list<PassengerDrone*>::iterator droneIter = pDroneList.begin(); droneIter != pDroneList.end(); droneIter++)
	{
		PassengerDrone* theDrone = (*droneIter);
		theDrone->deliveryCheck(roadConc);
	}
	for(std::list<CargoDrone*>::iterator droneIter = cDroneList.begin(); droneIter != cDroneList.end(); droneIter++)
	{
		CargoDrone* theDrone = (*droneIter);
		theDrone->deliveryCheck(roadConc);
	}
}

void Executive::executeEvents(int roadConc)
{
	std::chrono::high_resolution_clock::time_point t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12,t13;
	int t = 0;
	int t1t2=0;int t2t3=0;int t3t4=0; int t3t5=0; int t6t7=0;int t6t8=0;int t9t10=0;int t9t11=0;int t1t12=0;int t1t13=0;
	int t1t2c=0;int t2t3c=0;int t3t4c=0;int t3t5c=0;int t6t7c=0;int t6t8c=0;int t9t10c=0;int t9t11c=0;int t1t12c=0;int t1t13c=0;
	for(std::list<Individual*>::iterator indIter = peopleList.begin(); indIter != peopleList.end(); indIter++)
	{
		Individual* person = *indIter;
		t1 = std::chrono::high_resolution_clock::now();
		Agenda* theAgenda = person->getAgenda();
		t13 = std::chrono::high_resolution_clock::now();
		t = std::chrono::duration_cast<std::chrono::microseconds>(t13 - t1).count();
		t1t13 += t;
		t1t13c++;
		if(true/*!theAgenda->getEvents().empty()*/)
		{
			t2 = std::chrono::high_resolution_clock::now();
			t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			t1t2 += t;
			t1t2c++;
			bool personInBuilding = theAgenda->inBuilding();
			std::list<Resource*> foundResources;
			std::list<int> neededTypes;
			bool resourcesInBuilding = theAgenda->canExecuteEvent(foundResources, neededTypes);
			t3 = std::chrono::high_resolution_clock::now();
			t = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
			t2t3 += t;
			t2t3c++;
			//Make sure the individual is in the building
			if(!personInBuilding && person->getPassengerRequest() == nullptr)
			{
				//Not in the building, need a passenger drone
				//std::cout << "(" << person->getID() << ") Event failure, request pDrone\n";
				
				Building* theBuilding = theAgenda->getEvents().front().getBuilding();
				
				//Request the drone
				requestPassengerDrone(theBuilding, person, roadConc);
				t4 = std::chrono::high_resolution_clock::now();
				t = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
				t3t4 += t;
				t3t4c++;
			}
			else {
				t5 = std::chrono::high_resolution_clock::now();
				t = std::chrono::duration_cast<std::chrono::microseconds>(t5 - t3).count();
				t3t5 += t;
				t3t5c++;
			}

			t6 = std::chrono::high_resolution_clock::now();
			//Make sure the needed resources are in the building
			if(personInBuilding && !resourcesInBuilding && person->getCargoRequest() == nullptr)
			{
				//Resources not in building, need a cargo drone
				//std::cout << "(" << person->getID() << ") Event failure, request cDrone\n";
				
				//Spawn some resources at a fulfillment center
				std::list<Resource*> newResources;
				for(std::list<int>::iterator iter = neededTypes.begin(); iter != neededTypes.end(); iter++)
				{
					Resource* r = new Resource(*iter,generateID(),rTable);
					newResources.push_back(r);
					resourceList.push_back(r);
				}
				FFCs.front()->addResources(newResources);
				
				Building* theBuilding = theAgenda->getEvents().front().getBuilding();
				
				//Request the drone
				requestCargoDrone(theBuilding, person, newResources, roadConc);

				t7 = std::chrono::high_resolution_clock::now();
				t = std::chrono::duration_cast<std::chrono::microseconds>(t7 - t6).count();
				t6t7 += t;
				t6t7c++;
			}
			else{
				t8 = std::chrono::high_resolution_clock::now();
				t = std::chrono::duration_cast<std::chrono::microseconds>(t8 - t6).count();
				t6t8 += t;
				t6t8c++;
			}
			t9 = std::chrono::high_resolution_clock::now();			
			//If no requests are needed, execute the event
			if(personInBuilding && resourcesInBuilding)
			{
				theAgenda->executeEvent(foundResources);
				eventsCompleted++;
				//std::cout << "(" << person->getID() << ") Event success; " << eventsCompleted << "/" << eventsCreated << std::endl;
				t10 = std::chrono::high_resolution_clock::now();
				t = std::chrono::duration_cast<std::chrono::microseconds>(t10 - t9).count();
				t9t10 += t;
				t9t10c++;	
			}else{
				t11 = std::chrono::high_resolution_clock::now();
				t = std::chrono::duration_cast<std::chrono::microseconds>(t11 - t9).count();
				t9t11 += t;
				t9t11c++;
			}
	
		}
		else //No more events left to execute
		{
			//Go home
			if(person->getBuilding() != person->getHome() && person->getPassengerRequest() == nullptr)
			{
				requestPassengerDrone(person->getHome(),person,roadConc);
			}
			t12 = std::chrono::high_resolution_clock::now();
			t = std::chrono::duration_cast<std::chrono::microseconds>(t12 - t1).count();
			t1t12 += t;
			t1t12c++;	
		}
	}
	/*if (t1t13c > 0)
		std::cout << "t1->t13: " << t1t13/t1t13c << " (" << t1t13c << ")" << std::endl;
	if (t1t2c > 0)
		std::cout << "t1->t2: " << t1t2/t1t2c << " (" << t1t2c << ")" << std::endl;
	if (t2t3c > 0)	
		std::cout << "t2->t3: " << t2t3/t2t3c << " (" << t2t3c << ")" << std::endl;
	if (t3t4c > 0)
		std::cout << "t3->t4: " << t3t4/t3t4c << " (" << t3t4c << ")" << std::endl;
	if (t3t5c > 0)
		std::cout << "t3->t5: " << t3t5/t3t5c << " (" << t3t5c << ")" << std::endl;
	if (t6t7c > 0)
		std::cout << "t6->t7: " << t6t7/t6t7c << " (" << t6t7c << ")" << std::endl;
	if (t6t8c > 0)
		std::cout << "t6->t8: " << t6t8/t6t8c << " (" << t6t8c << ")" << std::endl;
	if (t9t10c > 0)
		std::cout << "t9->t10: " << t9t10/t9t10c << " (" << t9t10c << ")" << std::endl;
	if (t9t11c > 0)
		std::cout << "t9->t11: " << t9t11/t9t11c << " (" << t9t11c << ")" << std::endl;
	if (t1t12c > 0)
		std::cout << "t1->t12: " << t1t12/t1t12c << " (" << t1t12c << ")" << std::endl;*/
}

PassengerDrone* Executive::findPassengerDrone(Building* where, Individual* who, int & bestIndex1, int & bestIndex2)
{
	PassengerDrone* bestDrone = nullptr;
	for(std::list<PassengerDrone*>::iterator it = pDroneList.begin(); it != pDroneList.end(); it++)
	{	
		PassengerDrone* theDrone = *it;
		//If this drone cannot be full when it comes to pickup
		if(theDrone->getCapacity() > theDrone->getDeliveries().size())
		{
			//Determine if this person's locations are along this drone's path
			int index1 = -1; int index2 = -1;
			index1 = theDrone->posInPath(who->getBuilding()->getXRoad(),who->getBuilding()->getYRoad());
			if(index1 != -1)
				index2 = theDrone->posInPath(where->getXRoad(),where->getYRoad());

			//std::cout << "Person " << who->getID() << "'s move indices: "<< index1 << ", " << index2 << std::endl;
			
			//Determine if this drone is the best match
			if(index2 != -1)	//This drone will pickup and dropoff
			{
				if(bestIndex2 > index2 || bestIndex2 == -1)	//This drone is going to drop off sooner
				{
					bestIndex1 = index1;
					bestIndex2 = index2;
					bestDrone = theDrone;
				}
			}
			else if(index1 != -1)	//This drone will only pickup
			{
				if((bestIndex1 > index1 || bestIndex1 == -1)
				&& bestIndex2 == -1)	//This drone is going to pick up sooner
				{
					bestIndex1 = index1;
					bestDrone = theDrone;
				}
			}
			else	//A whole new set of movements would need to be created
			{
				//So this is more of a last resort than anything
				if(bestIndex1 == -1 && bestIndex2 == -1)
					bestDrone = theDrone;
			}
			
			//Drones that are idle (no deliveries) should take priority
			if(!theDrone->isMoving())
			{
				bestDrone = theDrone;
				break;
			}
		}
	}
	return bestDrone;
}

CargoDrone* Executive::findCargoDrone(Building* where, std::list<Resource*> what, int & bestIndex1, int & bestIndex2)
{
	CargoDrone* bestDrone = nullptr;
	for(std::list<CargoDrone*>::iterator it = cDroneList.begin(); it != cDroneList.end(); it++)
	{	
		CargoDrone* theDrone = *it;
		
		double volume = 0;
		double weight = 0;
		//Determine how much weight and volume will be occupied by this delivery
		std::list<Resource*>::iterator iter;
		for(iter = what.begin(); iter != what.end(); iter++)
		{
			volume += (*iter)->getVolume();
			weight += (*iter)->getWeight();
		}
		
		//Determine how much weight and volume could be taken by the current deliveries
		std::list<Drone::Delivery> deliveries = theDrone->getDeliveries();
		for(std::list<Drone::Delivery>::iterator delivery = deliveries.begin(); delivery != deliveries.end(); delivery++)
		{
			std::list<Resource*> dWhat = (*delivery).what;
			for(iter = dWhat.begin(); iter != dWhat.end(); iter++)
			{
				volume += (*iter)->getVolume();
				weight += (*iter)->getWeight();
			}
		}
		
		//If this drone cannot be full when it comes to pickup
		if(theDrone->getMaxVolume() > volume && theDrone->getMaxWeight() > weight)
		{
			//Determine if the locations are along this drone's path
			int index1 = -1; int index2 = -1;
			index1 = theDrone->posInPath(what.front()->getBuilding()->getXRoad(),what.front()->getBuilding()->getYRoad());
			if(index1 != -1)
				index2 = theDrone->posInPath(where->getXRoad(),where->getYRoad());

			//std::cout << "Resource " << what.front()->getID() << "'s move indices: "<< index1 << ", " << index2 << std::endl;
			
			//Determine if this drone is the best match
			if(index2 != -1)	//This drone will pickup and dropoff
			{
				if(bestIndex2 > index2 || bestIndex2 == -1)	//This drone is going to drop off sooner
				{
					bestIndex1 = index1;
					bestIndex2 = index2;
					bestDrone = theDrone;
				}
			}
			else if(index1 != -1)	//This drone will only pickup
			{
				if((bestIndex1 > index1 || bestIndex1 == -1)
				&& bestIndex2 == -1)	//This drone is going to pick up sooner
				{
					bestIndex1 = index1;
					bestDrone = theDrone;
				}
			}
			else	//A whole new set of movements would need to be created
			{
				//So this is more of a last resort than anything
				if(bestIndex1 == -1 && bestIndex2 == -1)
					bestDrone = theDrone;
			}
			
			//Drones that are idle (no deliveries) should take priority
			if(!theDrone->isMoving())
			{
				bestDrone = theDrone;
				break;
			}
		}
	}
	return bestDrone;
}

void Executive::requestPassengerDrone(Building* where, Individual* who, int roadConc)
{
	int bestIndex1 = -1; int bestIndex2 = -1;
	PassengerDrone* bestDrone = findPassengerDrone(where, who, bestIndex1, bestIndex2);
	
	//A passenger drone was not found, create one
	if(bestDrone == nullptr)
	{
		FulfillmentCenter* theFFC = FFCs.front();
		PassengerDrone* myDrone = new PassengerDrone(theFFC->getXRoad(), theFFC->getYRoad(), generateID());
		pDroneList.push_back(myDrone);
		droneList.push_back(myDrone);
		bestDrone = myDrone;
	}
	
	//Add this person to the drone's delivery list and create the needed movements
	bestDrone->createDelivery(where, who, bestIndex1, bestIndex2, roadConc);

	//std::cout << "Person " << who->getID() << " needs Drone " << bestDrone->getID() << ";\n(" << who->getXPos() << ", " << who->getYPos() << ") -> (" << where->getXPos() << ", " << where->getYPos() << ")\n";
		
	who->setPassengerRequest(bestDrone);
}

void Executive::requestCargoDrone(Building* where, Individual* who, std::list<Resource*> & what, int roadConc)
{
	int bestIndex1 = -1; int bestIndex2 = -1;
	CargoDrone* bestDrone = findCargoDrone(where, what, bestIndex1, bestIndex2);
	
	//A cargo drone was not found, create one
	if(bestDrone == nullptr)
	{
		FulfillmentCenter* theFFC = FFCs.front();
		CargoDrone* myDrone = new CargoDrone(theFFC->getXRoad(), theFFC->getYRoad(), generateID());
		cDroneList.push_back(myDrone);
		droneList.push_back(myDrone);
		bestDrone = myDrone;
	}
	
	//Add this resource list to the drone's delivery list and create the needed movements
	bestDrone->createDelivery(where, who, what, bestIndex1, bestIndex2, roadConc);

	Resource* whatF = what.front();
	//std::cout << "Resource " << whatF->getID() << " needs Drone " << bestDrone->getID() << ";\n(" << whatF->getXPos() << ", " << whatF->getYPos() << ") -> (" << where->getXPos() << ", " << where->getYPos() << ")\n";
	
	who->setCargoRequest(bestDrone);
}
