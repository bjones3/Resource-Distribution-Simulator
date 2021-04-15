// Local Headers
#include "glitter.hpp"
#include "rds.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

// Custom Headers
#include <iostream>
#include <algorithm>
#include <chrono>

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
const char* fragmentSourceHouse = R"glsl(
    #version 400 core

    in vec3 Color;
    in vec2 Texcoord;

    out vec4 outColor;

    uniform sampler2D texHouse;

    void main()
    {
        vec4 colHouse = texture(texHouse, Texcoord);
        outColor = vec4(Color, 1.0) * colHouse;
    }
)glsl";
const char* fragmentSourceFulfillmentCenter = R"glsl(
    #version 400 core

    in vec3 Color;
    in vec2 Texcoord;

    out vec4 outColor;

    uniform sampler2D texFulfillmentCenter;

    void main()
    {
        vec4 colFulfillmentCenter = texture(texFulfillmentCenter, Texcoord);
        outColor = vec4(Color, 1.0) * colFulfillmentCenter;
    }
)glsl";
const char* fragmentSourceOffice = R"glsl(
    #version 400 core

    in vec3 Color;
    in vec2 Texcoord;

    out vec4 outColor;

    uniform sampler2D texOffice;

    void main()
    {
        vec4 colOffice = texture(texOffice, Texcoord);
        outColor = vec4(Color, 1.0) * colOffice;
    }
)glsl";
const char* fragmentSourceStreet = R"glsl(
    #version 400 core

    in vec3 Color;
    in vec2 Texcoord;

    out vec4 outColor;

    uniform sampler2D texStreet;

    void main()
    {
        vec4 colStreet = texture(texStreet, Texcoord);
        outColor = vec4(Color, 1.0) * colStreet;
    }
)glsl";
const char* fragmentSourceGrass = R"glsl(
    #version 400 core

    in vec3 Color;
    in vec2 Texcoord;

    out vec4 outColor;

    uniform sampler2D texGrass;

    void main()
    {
        vec4 colGrass = texture(texGrass, Texcoord);
        outColor = vec4(Color, 1.0) * colGrass;
    }
)glsl";

GLfloat * createBottomVertices(int xPos, int yPos, int citySize) {
    GLfloat xOff = (GLfloat)xPos/(GLfloat)citySize;
    GLfloat yOff = (float)yPos/(float)citySize;

    GLfloat * v = new GLfloat[6*8];
    ///// BOTTOM
    v[0] = static_cast<GLfloat>(-0.5) + xOff; v[1] = static_cast<GLfloat>(-0.5) + yOff; v[2] = 0.0; v[3] =  1.0; v[4] =  1.0; v[5] =  1.0; v[6] =  0.0; v[7] =  0.0; //BLB
    v[8] = static_cast<GLfloat>(-0.48) + xOff; v[9] = static_cast<GLfloat>(-0.5) + yOff; v[10] = 0.0; v[11] =  1.0; v[12] =  1.0; v[13] =  1.0; v[14] =  1.0; v[15] =  0.0; //BLF
    v[16] = static_cast<GLfloat>(-0.48) + xOff; v[17] = static_cast<GLfloat>(-0.48) + yOff; v[18] = 0.0; v[19] =  1.0; v[20] =  1.0; v[21] =  1.0; v[22] =  1.0; v[23] =  1.0; //BRF
    v[24] = static_cast<GLfloat>(-0.48) + xOff; v[25] = static_cast<GLfloat>(-0.48) + yOff; v[26] = 0.0; v[27] =  1.0; v[28] =  1.0; v[29] =  1.0; v[30] =  1.0; v[31] =  1.0; //BRF
    v[32] = static_cast<GLfloat>(-0.5) + xOff; v[33] = static_cast<GLfloat>(-0.48) + yOff; v[34] = 0.0; v[35] =  1.0; v[36] =  1.0; v[37] =  1.0; v[38] =  0.0; v[39] =  1.0; //BRB
    v[40] = static_cast<GLfloat>(-0.5) + xOff; v[41] = static_cast<GLfloat>(-0.5) + yOff; v[42] = 0.0; v[43] =  1.0; v[44] =  1.0; v[45] =  1.0; v[46] =  0.0; v[47] =  0.0; //BLB
    return v;
};

GLfloat * createCubeVertices(int xPos, int yPos, GLfloat zHeight, int citySize) {
    GLfloat xOff = (GLfloat)xPos/(GLfloat)citySize;
    GLfloat yOff = (float)yPos/(float)citySize;

    GLfloat * v = new GLfloat[36*8];
    ///// BOTTOM
    v[0] = static_cast<GLfloat>(-0.5) + xOff; v[1] = static_cast<GLfloat>(-0.5) + yOff; v[2] = 0.0 + zHeight; v[3] =  1.0; v[4] =  1.0; v[5] =  1.0; v[6] =  0.0; v[7] =  0.0; //BLB
    v[8] = static_cast<GLfloat>(-0.48) + xOff; v[9] = static_cast<GLfloat>(-0.5) + yOff; v[10] = 0.0 + zHeight; v[11] =  1.0; v[12] =  1.0; v[13] =  1.0; v[14] =  1.0; v[15] =  0.0; //BLF
    v[16] = static_cast<GLfloat>(-0.48) + xOff; v[17] = static_cast<GLfloat>(-0.48) + yOff; v[18] = 0.0 + zHeight; v[19] =  1.0; v[20] =  1.0; v[21] =  1.0; v[22] =  1.0; v[23] =  1.0; //BRF
    v[24] = static_cast<GLfloat>(-0.48) + xOff; v[25] = static_cast<GLfloat>(-0.48) + yOff; v[26] = 0.0 + zHeight; v[27] =  1.0; v[28] =  1.0; v[29] =  1.0; v[30] =  1.0; v[31] =  1.0; //BRF
    v[32] = static_cast<GLfloat>(-0.5) + xOff; v[33] = static_cast<GLfloat>(-0.48) + yOff; v[34] = 0.0 + zHeight; v[35] =  1.0; v[36] =  1.0; v[37] =  1.0; v[38] =  0.0; v[39] =  1.0; //BRB
    v[40] = static_cast<GLfloat>(-0.5) + xOff; v[41] = static_cast<GLfloat>(-0.5) + yOff; v[42] = 0.0 + zHeight; v[43] =  1.0; v[44] =  1.0; v[45] =  1.0; v[46] =  0.0; v[47] =  0.0; //BLB
    ///// TOP
    v[48] = static_cast<GLfloat>(-0.5) + xOff; v[49] = static_cast<GLfloat>(-0.5) + yOff; v[50] = 0.02 + zHeight; v[51] =  1.0; v[52] =  1.0; v[53] =  1.0; v[54] =  0.0; v[55] =  0.0; //TLB
    v[56] = static_cast<GLfloat>(-0.48) + xOff; v[57] = static_cast<GLfloat>(-0.5) + yOff; v[58] = 0.02 + zHeight; v[59] =  1.0; v[60] =  1.0; v[61] =  1.0; v[62] =  1.0; v[63] =  0.0; //TLF
    v[64] = static_cast<GLfloat>(-0.48) + xOff; v[65] = static_cast<GLfloat>(-0.48) + yOff; v[66] = 0.02 + zHeight; v[67] =  1.0; v[68] =  1.0; v[69] =  1.0; v[70] =  1.0; v[71] =  1.0; //TRF
    v[72] = static_cast<GLfloat>(-0.48) + xOff; v[73] = static_cast<GLfloat>(-0.48) + yOff; v[74] = 0.02 + zHeight; v[75] =  1.0; v[76] =  1.0; v[77] =  1.0; v[78] =  1.0; v[79] =  1.0; //TRF
    v[80] = static_cast<GLfloat>(-0.5) + xOff; v[81] = static_cast<GLfloat>(-0.48) + yOff; v[82] = 0.02 + zHeight; v[83] =  1.0; v[84] =  1.0; v[85] =  1.0; v[86] =  0.0; v[87] =  1.0; //TRB
    v[88] = static_cast<GLfloat>(-0.5) + xOff; v[89] = static_cast<GLfloat>(-0.5) + yOff; v[90] = 0.02 + zHeight; v[91] =  1.0; v[92] =  1.0; v[93] =  1.0; v[94] =  0.0; v[95] =  0.0; //TLB
    ///// BACK
    v[96] = static_cast<GLfloat>(-0.5) + xOff; v[97] = static_cast<GLfloat>(-0.48) + yOff; v[98] = 0.02 + zHeight; v[99] =  1.0; v[100] =  1.0; v[101] =  1.0; v[102] =  1.0; v[103] =  0.0; //TRB
    v[104] = static_cast<GLfloat>(-0.5) + xOff; v[105] = static_cast<GLfloat>(-0.48) + yOff; v[106] = 0.0 + zHeight; v[107] =  1.0; v[108] =  1.0; v[109] =  1.0; v[110] =  1.0; v[111] =  1.0; //BRB
    v[112] = static_cast<GLfloat>(-0.5) + xOff; v[113] = static_cast<GLfloat>(-0.5) + yOff; v[114] = 0.0 + zHeight; v[115] =  1.0; v[116] =  1.0; v[117] =  1.0; v[118] =  0.0; v[119] =  1.0; //BLB
    v[120] = static_cast<GLfloat>(-0.5) + xOff; v[121] = static_cast<GLfloat>(-0.5) + yOff; v[122] = 0.0 + zHeight; v[123] =  1.0; v[124] =  1.0; v[125] =  1.0; v[126] =  0.0; v[127] =  1.0; //BLB
    v[128] = static_cast<GLfloat>(-0.5) + xOff; v[129] = static_cast<GLfloat>(-0.5) + yOff; v[130] = 0.02 + zHeight; v[131] =  1.0; v[132] =  1.0; v[133] =  1.0; v[134] =  0.0; v[135] =  0.0; //TLB
    v[136] = static_cast<GLfloat>(-0.5) + xOff; v[137] = static_cast<GLfloat>(-0.48) + yOff; v[138] = 0.02 + zHeight; v[139] =  1.0; v[140] =  1.0; v[141] =  1.0; v[142] =  1.0; v[143] =  0.0; //TRB
    ///// FRONT
    v[144] = static_cast<GLfloat>(-0.48) + xOff; v[145] = static_cast<GLfloat>(-0.48) + yOff; v[146] = 0.02 + zHeight; v[147] =  1.0; v[148] =  1.0; v[149] =  1.0; v[150] =  1.0; v[151] =  0.0; //TRF
    v[152] = static_cast<GLfloat>(-0.48) + xOff; v[153] = static_cast<GLfloat>(-0.48) + yOff; v[154] = 0.0 + zHeight; v[155] =  1.0; v[156] =  1.0; v[157] =  1.0; v[158] =  1.0; v[159] =  1.0; //BRF
    v[160] = static_cast<GLfloat>(-0.48) + xOff; v[161] = static_cast<GLfloat>(-0.5) + yOff; v[162] = 0.0 + zHeight; v[163] =  1.0; v[164] =  1.0; v[165] =  1.0; v[166] =  0.0; v[167] =  1.0; //BLF
    v[168] = static_cast<GLfloat>(-0.48) + xOff; v[169] = static_cast<GLfloat>(-0.5) + yOff; v[170] = 0.0 + zHeight; v[171] =  1.0; v[172] =  1.0; v[173] =  1.0; v[174] =  0.0; v[175] =  1.0; //BLF
    v[176] = static_cast<GLfloat>(-0.48) + xOff; v[177] = static_cast<GLfloat>(-0.5) + yOff; v[178] = 0.02 + zHeight; v[179] =  1.0; v[180] =  1.0; v[181] =  1.0; v[182] =  0.0; v[183] =  0.0; //TLF
    v[184] = static_cast<GLfloat>(-0.48) + xOff; v[185] = static_cast<GLfloat>(-0.48) + yOff; v[186] = 0.02 + zHeight; v[187] =  1.0; v[188] =  1.0; v[189] =  1.0; v[190] =  1.0; v[191] =  0.0; //TRF
    ////// LEFT
    v[192] = static_cast<GLfloat>(-0.5) + xOff; v[193] = static_cast<GLfloat>(-0.5) + yOff; v[194] = 0.0 + zHeight; v[195] =  1.0; v[196] =  1.0; v[197] =  1.0; v[198] =  0.0; v[199] =  1.0; //BLB
    v[200] = static_cast<GLfloat>(-0.48) + xOff; v[201] = static_cast<GLfloat>(-0.5) + yOff; v[202] = 0.0 + zHeight; v[203] =  1.0; v[204] =  1.0; v[205] =  1.0; v[206] =  1.0; v[207] =  1.0; //BLF
    v[208] = static_cast<GLfloat>(-0.48) + xOff; v[209] = static_cast<GLfloat>(-0.5) + yOff; v[210] = 0.02 + zHeight; v[211] =  1.0; v[212] =  1.0; v[213] =  1.0; v[214] =  1.0; v[215] =  0.0; //TLF
    v[216] = static_cast<GLfloat>(-0.48) + xOff; v[217] = static_cast<GLfloat>(-0.5) + yOff; v[218] = 0.02 + zHeight; v[219] =  1.0; v[220] =  1.0; v[221] =  1.0; v[222] =  1.0; v[223] =  0.0; //TLF
    v[224] = static_cast<GLfloat>(-0.5) + xOff; v[225] = static_cast<GLfloat>(-0.5) + yOff; v[226] = 0.02 + zHeight; v[227] =  1.0; v[228] =  1.0; v[229] =  1.0; v[230] =  0.0; v[231] =  0.0; //TLB
    v[232] = static_cast<GLfloat>(-0.5) + xOff; v[233] = static_cast<GLfloat>(-0.5) + yOff; v[234] = 0.0 + zHeight; v[235] =  1.0; v[236] =  1.0; v[237] =  1.0; v[238] =  0.0; v[239] =  1.0; //BLB
    ///// RIGHT
    v[240] = static_cast<GLfloat>(-0.5) + xOff; v[241] = static_cast<GLfloat>(-0.48) + yOff; v[242] = 0.0 + zHeight; v[243] =  1.0; v[244] =  1.0; v[245] =  1.0; v[246] =  0.0; v[247] =  1.0; //BRB
    v[248] = static_cast<GLfloat>(-0.48) + xOff; v[249] = static_cast<GLfloat>(-0.48) + yOff; v[250] = 0.0 + zHeight; v[251] =  1.0; v[252] =  1.0; v[253] =  1.0; v[254] =  1.0; v[255] =  1.0; //BRF
    v[256] = static_cast<GLfloat>(-0.48) + xOff; v[257] = static_cast<GLfloat>(-0.48) + yOff; v[258] = 0.02 + zHeight; v[259] =  1.0; v[260] =  1.0; v[261] =  1.0; v[262] =  1.0; v[263] =  0.0; //TRF
    v[264] = static_cast<GLfloat>(-0.48) + xOff; v[265] = static_cast<GLfloat>(-0.48) + yOff; v[266] = 0.02 + zHeight; v[267] =  1.0; v[268] =  1.0; v[269] =  1.0; v[270] =  1.0; v[271] =  0.0; //TRF
    v[272] = static_cast<GLfloat>(-0.5) + xOff; v[273] = static_cast<GLfloat>(-0.48) + yOff; v[274] = 0.02 + zHeight; v[275] =  1.0; v[276] =  1.0; v[277] =  1.0; v[278] =  0.0; v[279] =  0.0; //TRB
    v[280] = static_cast<GLfloat>(-0.5) + xOff; v[281] = static_cast<GLfloat>(-0.48) + yOff; v[282] = 0.0 + zHeight; v[283] =  1.0; v[284] =  1.0; v[285] =  1.0; v[286] =  0.0; v[287] =  1.0; //BRB

    return v;
};

GLfloat * createDroneVertices(int xPos, int yPos, GLfloat zHeight, int citySize) {
    GLfloat xOff = (GLfloat)xPos/(GLfloat)citySize;
    GLfloat yOff = (float)yPos/(float)citySize;

    GLfloat * v = new GLfloat[36*8];
    ///// BOTTOM
    v[0] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[1] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[2] = 0.0 + zHeight; v[3] =  1.0; v[4] =  1.0; v[5] =  1.0; v[6] =  0.0; v[7] =  0.0; //BLB
    v[8] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[9] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[10] = 0.0 + zHeight; v[11] =  1.0; v[12] =  1.0; v[13] =  1.0; v[14] =  1.0; v[15] =  0.0; //BLF
    v[16] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[17] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[18] = 0.0 + zHeight; v[19] =  1.0; v[20] =  1.0; v[21] =  1.0; v[22] =  1.0; v[23] =  1.0; //BRF
    v[24] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[25] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[26] = 0.0 + zHeight; v[27] =  1.0; v[28] =  1.0; v[29] =  1.0; v[30] =  1.0; v[31] =  1.0; //BRF
    v[32] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[33] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[34] = 0.0 + zHeight; v[35] =  1.0; v[36] =  1.0; v[37] =  1.0; v[38] =  0.0; v[39] =  1.0; //BRB
    v[40] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[41] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[42] = 0.0 + zHeight; v[43] =  1.0; v[44] =  1.0; v[45] =  1.0; v[46] =  0.0; v[47] =  0.0; //BLB
    ///// TOP
    v[48] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[49] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[50] = 0.01 + zHeight; v[51] =  1.0; v[52] =  1.0; v[53] =  1.0; v[54] =  0.0; v[55] =  0.0; //TLB
    v[56] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[57] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[58] = 0.01 + zHeight; v[59] =  1.0; v[60] =  1.0; v[61] =  1.0; v[62] =  1.0; v[63] =  0.0; //TLF
    v[64] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[65] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[66] = 0.01 + zHeight; v[67] =  1.0; v[68] =  1.0; v[69] =  1.0; v[70] =  1.0; v[71] =  1.0; //TRF
    v[72] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[73] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[74] = 0.01 + zHeight; v[75] =  1.0; v[76] =  1.0; v[77] =  1.0; v[78] =  1.0; v[79] =  1.0; //TRF
    v[80] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[81] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[82] = 0.01 + zHeight; v[83] =  1.0; v[84] =  1.0; v[85] =  1.0; v[86] =  0.0; v[87] =  1.0; //TRB
    v[88] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[89] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[90] = 0.01 + zHeight; v[91] =  1.0; v[92] =  1.0; v[93] =  1.0; v[94] =  0.0; v[95] =  0.0; //TLB
    ///// BACK
    v[96] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[97] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[98] = 0.01 + zHeight; v[99] =  1.0; v[100] =  1.0; v[101] =  1.0; v[102] =  1.0; v[103] =  0.0; //TRB
    v[104] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[105] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[106] = 0.0 + zHeight; v[107] =  1.0; v[108] =  1.0; v[109] =  1.0; v[110] =  1.0; v[111] =  1.0; //BRB
    v[112] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[113] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[114] = 0.0 + zHeight; v[115] =  1.0; v[116] =  1.0; v[117] =  1.0; v[118] =  0.0; v[119] =  1.0; //BLB
    v[120] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[121] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[122] = 0.0 + zHeight; v[123] =  1.0; v[124] =  1.0; v[125] =  1.0; v[126] =  0.0; v[127] =  1.0; //BLB
    v[128] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[129] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[130] = 0.01 + zHeight; v[131] =  1.0; v[132] =  1.0; v[133] =  1.0; v[134] =  0.0; v[135] =  0.0; //TLB
    v[136] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[137] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[138] = 0.01 + zHeight; v[139] =  1.0; v[140] =  1.0; v[141] =  1.0; v[142] =  1.0; v[143] =  0.0; //TRB
    ///// FRONT
    v[144] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[145] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[146] = 0.01 + zHeight; v[147] =  1.0; v[148] =  1.0; v[149] =  1.0; v[150] =  1.0; v[151] =  0.0; //TRF
    v[152] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[153] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[154] = 0.0 + zHeight; v[155] =  1.0; v[156] =  1.0; v[157] =  1.0; v[158] =  1.0; v[159] =  1.0; //BRF
    v[160] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[161] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[162] = 0.0 + zHeight; v[163] =  1.0; v[164] =  1.0; v[165] =  1.0; v[166] =  0.0; v[167] =  1.0; //BLF
    v[168] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[169] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[170] = 0.0 + zHeight; v[171] =  1.0; v[172] =  1.0; v[173] =  1.0; v[174] =  0.0; v[175] =  1.0; //BLF
    v[176] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[177] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[178] = 0.01 + zHeight; v[179] =  1.0; v[180] =  1.0; v[181] =  1.0; v[182] =  0.0; v[183] =  0.0; //TLF
    v[184] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[185] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[186] = 0.01 + zHeight; v[187] =  1.0; v[188] =  1.0; v[189] =  1.0; v[190] =  1.0; v[191] =  0.0; //TRF
    ////// LEFT
    v[192] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[193] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[194] = 0.0 + zHeight; v[195] =  1.0; v[196] =  1.0; v[197] =  1.0; v[198] =  0.0; v[199] =  1.0; //BLB
    v[200] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[201] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[202] = 0.0 + zHeight; v[203] =  1.0; v[204] =  1.0; v[205] =  1.0; v[206] =  1.0; v[207] =  1.0; //BLF
    v[208] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[209] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[210] = 0.01 + zHeight; v[211] =  1.0; v[212] =  1.0; v[213] =  1.0; v[214] =  1.0; v[215] =  0.0; //TLF
    v[216] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[217] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[218] = 0.01 + zHeight; v[219] =  1.0; v[220] =  1.0; v[221] =  1.0; v[222] =  1.0; v[223] =  0.0; //TLF
    v[224] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[225] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[226] = 0.01 + zHeight; v[227] =  1.0; v[228] =  1.0; v[229] =  1.0; v[230] =  0.0; v[231] =  0.0; //TLB
    v[232] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[233] = static_cast<GLfloat>(-0.5 + 0.004) + yOff; v[234] = 0.0 + zHeight; v[235] =  1.0; v[236] =  1.0; v[237] =  1.0; v[238] =  0.0; v[239] =  1.0; //BLB
    ///// RIGHT
    v[240] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[241] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[242] = 0.0 + zHeight; v[243] =  1.0; v[244] =  1.0; v[245] =  1.0; v[246] =  0.0; v[247] =  1.0; //BRB
    v[248] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[249] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[250] = 0.0 + zHeight; v[251] =  1.0; v[252] =  1.0; v[253] =  1.0; v[254] =  1.0; v[255] =  1.0; //BRF
    v[256] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[257] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[258] = 0.01 + zHeight; v[259] =  1.0; v[260] =  1.0; v[261] =  1.0; v[262] =  1.0; v[263] =  0.0; //TRF
    v[264] = static_cast<GLfloat>(-0.48 - 0.004) + xOff; v[265] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[266] = 0.01 + zHeight; v[267] =  1.0; v[268] =  1.0; v[269] =  1.0; v[270] =  1.0; v[271] =  0.0; //TRF
    v[272] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[273] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[274] = 0.01 + zHeight; v[275] =  1.0; v[276] =  1.0; v[277] =  1.0; v[278] =  0.0; v[279] =  0.0; //TRB
    v[280] = static_cast<GLfloat>(-0.5 + 0.004) + xOff; v[281] = static_cast<GLfloat>(-0.48 - 0.004) + yOff; v[282] = 0.0 + zHeight; v[283] =  1.0; v[284] =  1.0; v[285] =  1.0; v[286] =  0.0; v[287] =  1.0; //BRB

    return v;
};

int map[][51] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 1, 4, 4, 4, 4, 4, 4, 3, 3, 3, 1, 4, 4, 4, 4, 2, 2, 2, 2, 4, 1, 4, 4, 4, 3, 3, 3, 4, 4, 4, 1, 4, 4, 4, 3, 3, 3, 4, 4, 4, 1},
    {1, 2, 2, 2, 2, 3, 3, 3, 0, 4, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 3, 3, 3, 0, 4, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 4, 4, 4, 4, 4, 1, 4, 4, 4, 3, 3, 3, 4, 4, 4, 1, 4, 4, 4, 4, 2, 2, 2, 2, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 2, 2, 2, 2, 4, 1, 4, 4, 4, 4, 4, 4, 3, 3, 3, 1, 4, 4, 4, 4, 4, 4, 3, 3, 3, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 1, 4, 4, 4, 4, 4, 4, 3, 3, 3, 1, 4, 4, 4, 4, 2, 2, 2, 2, 4, 1, 4, 4, 4, 3, 3, 3, 4, 4, 4, 1, 4, 4, 4, 3, 3, 3, 4, 4, 4, 1},
    {1, 2, 2, 2, 2, 3, 3, 3, 0, 4, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 3, 3, 3, 0, 4, 1, 4, 0, 0, 0, 0, 0, 3, 3, 3, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 4, 4, 4, 4, 4, 1, 4, 4, 4, 3, 3, 3, 4, 4, 4, 1, 4, 4, 4, 4, 2, 2, 2, 2, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 4, 4, 4, 4, 4, 4, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 3, 3, 3, 0, 0, 4, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 2, 2, 2, 2, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 2, 2, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 4, 1, 3, 3, 3, 0, 0, 0, 0, 0, 4, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc, char * argv[]) {
    Executive ex;
	ex.run();
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
        return EXIT_FAILURE;
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
    GLuint tex[6];
    glGenTextures(6, tex);
    //glGenTextures(1, &tex);
    //glBindTexture(GL_TEXTURE_2D, tex);

    int width, height, n;
    unsigned char *image;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    image = stbi_load("/Users/joanjones/Documents/EECS582/Glitter/Glitter/Sources/sample2.png", &width, &height, &n, 0);
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
    image = stbi_load("/Users/joanjones/Documents/EECS582/Glitter/Glitter/Sources/brick.jpg", &width, &height, &n, 0);
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
    image = stbi_load("/Users/joanjones/Documents/EECS582/Glitter/Glitter/Sources/house.jpg", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, tex[3]);
    image = stbi_load("/Users/joanjones/Documents/EECS582/Glitter/Glitter/Sources/board.jpg", &width, &height, &n, 0);
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
    image = stbi_load("/Users/joanjones/Documents/EECS582/Glitter/Glitter/Sources/road.jpg", &width, &height, &n, 0);
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
    image = stbi_load("/Users/joanjones/Documents/EECS582/Glitter/Glitter/Sources/sample.png", &width, &height, &n, 0);
    if (image == NULL){
        #define STBI_FAILURE_USERMSG
        std::cout << stbi_failure_reason() << std::endl;
        std::cout << "number of channels in image: " << n << std::endl;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
              GL_UNSIGNED_BYTE, image);
    stbi_image_free(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 5);
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

    glm::mat4 proj = glm::perspective(glm::radians(30.0f), 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    auto t_start = std::chrono::high_resolution_clock::now();
    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
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
        model = glm::rotate(
            model,
            /*time **/ glm::radians(00.0f),
            glm::vec3(0.0f, 0.0f, 1.0f)
        );
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

        // Draw a rectangle from the 2 triangles using 6 indices
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        for (int j = 0; j < 51; j++)
        {

            for (int i = 0; i<51; i++){
                if (map[i][j] == 4){
                    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 2);
                    GLfloat * cube = createCubeVertices(i, j, 0.0, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                glDrawArrays(GL_TRIANGLES, 0, 36);
                } else if (map[i][j] == 2){
                    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 1);
                    GLfloat * cube = createCubeVertices(i, j, 0.0, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    cube = createCubeVertices(i, j, 0.02, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    cube = createCubeVertices(i, j, 0.04, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                } else if (map[i][j] == 3){
                    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 3);
                    GLfloat * cube = createCubeVertices(i, j, 0.0, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                    cube = createCubeVertices(i, j, 0.02, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                glDrawArrays(GL_TRIANGLES, 0, 36);
                } else if (map[i][j] == 1){
                    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 4);
                    GLfloat * cube = createBottomVertices(i, j, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                } else {
                    glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 0);
                    GLfloat * cube = createBottomVertices(i, j, 51);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[6*8]), cube, GL_STATIC_DRAW);
                    delete cube;
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                }
            }
            
        }

        glUniform1i(glGetUniformLocation(shaderProgram, "texTex"), 5);
        GLfloat * drone = createDroneVertices(50, 40, 0.0, 51);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat[36*8]), drone, GL_STATIC_DRAW);
        delete drone;
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   

    //glDeleteTextures(1, &tex);
    glDeleteTextures(2, tex);
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    //glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
    return EXIT_SUCCESS;
}
