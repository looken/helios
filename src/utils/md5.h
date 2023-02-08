#ifndef MD5_H
#define MD5_H

namespace utils {

//将x循环左移n位
#define CYC_SHL_32(x, n) (((x) << (n)) | ((x) >> (32-(n))))

//非线性函数,每组四轮,每轮使用依次一个
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define FF(a ,b ,c ,d ,Mj ,s ,ti ) (a) = (b) + ( CYC_SHL_32(((a) + F((b),(c),(d)) + (Mj) + (ti)), (s)))
#define GG(a ,b ,c ,d ,Mj ,s ,ti ) (a) = (b) + ( CYC_SHL_32(((a) + G((b),(c),(d)) + (Mj) + (ti)), (s)))
#define HH(a ,b ,c ,d ,Mj ,s ,ti ) (a) = (b) + ( CYC_SHL_32(((a) + H((b),(c),(d)) + (Mj) + (ti)), (s)))
#define II(a ,b ,c ,d ,Mj ,s ,ti ) (a) = (b) + ( CYC_SHL_32(((a) + I((b),(c),(d)) + (Mj) + (ti)), (s)))

//第1/4轮的循环左移次数,循环使用
#define FS1 7
#define FS2 12
#define FS3 17
#define FS4 22
//第2/4轮的循环左移次数,循环使用
#define GS1 5
#define GS2 9
#define GS3 14
#define GS4 20
//第3/4轮的循环左移次数,循环使用
#define HS1 4
#define HS2 11
#define HS3 16
#define HS4 23
//第4/4轮的循环左移次数,循环使用
#define IS1 6
#define IS2 10
#define IS3 15
#define IS4 21

//初始序列
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

//链接变量
static unsigned int linka;
static unsigned int linkb;
static unsigned int linkc;
static unsigned int linkd;

//四位二进制序列转换为一个十六进制字符
const char str16[] = "0123456789abcdef";

static void one_group(unsigned int M[])
{
    //临时链接变量
    unsigned int a = linka, b = linkb, c = linkc, d = linkd;

    //第1/4轮,含有16步
    FF(a, b, c, d, M[ 0], FS1, 0xd76aa478);
    FF(d, a, b, c, M[ 1], FS2, 0xe8c7b756);
    FF(c, d, a, b, M[ 2], FS3, 0x242070db);
    FF(b, c, d, a, M[ 3], FS4, 0xc1bdceee);

    FF(a, b, c, d, M[ 4], FS1, 0xf57c0faf);
    FF(d, a, b, c, M[ 5], FS2, 0x4787c62a);
    FF(c, d, a, b, M[ 6], FS3, 0xa8304613);
    FF(b, c, d, a, M[ 7], FS4, 0xfd469501);

    FF(a, b, c, d, M[ 8], FS1, 0x698098d8);
    FF(d, a, b, c, M[ 9], FS2, 0x8b44f7af);
    FF(c, d, a, b, M[10], FS3, 0xffff5bb1);
    FF(b, c, d, a, M[11], FS4, 0x895cd7be);

    FF(a, b, c, d, M[12], FS1, 0x6b901122);
    FF(d, a, b, c, M[13], FS2, 0xfd987193);
    FF(c, d, a, b, M[14], FS3, 0xa679438e);
    FF(b, c, d, a, M[15], FS4, 0x49b40821);

    //第2/4轮,含有16步
    GG(a, b, c, d, M[ 1], GS1, 0xf61e2562);
    GG(d, a, b, c, M[ 6], GS2, 0xc040b340);
    GG(c, d, a, b, M[11], GS3, 0x265e5a51);
    GG(b, c, d, a, M[ 0], GS4, 0xe9b6c7aa);

    GG(a, b, c, d, M[ 5], GS1, 0xd62f105d);
    GG(d, a, b, c, M[10], GS2, 0x02441453);
    GG(c, d, a, b, M[15], GS3, 0xd8a1e681);
    GG(b, c, d, a, M[ 4], GS4, 0xe7d3fbc8);

    GG(a, b, c, d, M[ 9], GS1, 0x21e1cde6);
    GG(d, a, b, c, M[14], GS2, 0xc33707d6);
    GG(c, d, a, b, M[ 3], GS3, 0xf4d50d87);
    GG(b, c, d, a, M[ 8], GS4, 0x455a14ed);

    GG(a, b, c, d, M[13], GS1, 0xa9e3e905);
    GG(d, a, b, c, M[ 2], GS2, 0xfcefa3f8);
    GG(c, d, a, b, M[ 7], GS3, 0x676f02d9);
    GG(b, c, d, a, M[12], GS4, 0x8d2a4c8a);

    //第3/4轮,含有16步
    HH(a, b, c, d, M[ 5], HS1, 0xfffa3942);
    HH(d, a, b, c, M[ 8], HS2, 0x8771f681);
    HH(c, d, a, b, M[11], HS3, 0x6d9d6122);
    HH(b, c, d, a, M[14], HS4, 0xfde5380c);

    HH(a, b, c, d, M[ 1], HS1, 0xa4beea44);
    HH(d, a, b, c, M[ 4], HS2, 0x4bdecfa9);
    HH(c, d, a, b, M[ 7], HS3, 0xf6bb4b60);
    HH(b, c, d, a, M[10], HS4, 0xbebfbc70);

    HH(a, b, c, d, M[13], HS1, 0x289b7ec6);
    HH(d, a, b, c, M[ 0], HS2, 0xeaa127fa);
    HH(c, d, a, b, M[ 3], HS3, 0xd4ef3085);
    HH(b, c, d, a, M[ 6], HS4, 0x04881d05);

    HH(a, b, c, d, M[ 9], HS1, 0xd9d4d039);
    HH(d, a, b, c, M[12], HS2, 0xe6db99e5);
    HH(c, d, a, b, M[15], HS3, 0x1fa27cf8);
    HH(b, c, d, a, M[ 2], HS4, 0xc4ac5665);

    //第4/4轮,含有16步
    II(a, b, c, d, M[ 0], IS1, 0xf4292244);
    II(d, a, b, c, M[ 7], IS2, 0x432aff97);
    II(c, d, a, b, M[14], IS3, 0xab9423a7);
    II(b, c, d, a, M[ 5], IS4, 0xfc93a039);

    II(a, b, c, d, M[12], IS1, 0x655b59c3);
    II(d, a, b, c, M[ 3], IS2, 0x8f0ccc92);
    II(c, d, a, b, M[10], IS3, 0xffeff47d);
    II(b, c, d, a, M[ 1], IS4, 0x85845dd1);

    II(a, b, c, d, M[ 8], IS1, 0x6fa87e4f);
    II(d, a, b, c, M[15], IS2, 0xfe2ce6e0);
    II(c, d, a, b, M[ 6], IS3, 0xa3014314);
    II(b, c, d, a, M[13], IS4, 0x4e0811a1);

    II(a, b, c, d, M[ 4], IS1, 0xf7537e82);
    II(d, a, b, c, M[11], IS2, 0xbd3af235);
    II(c, d, a, b, M[ 2], IS3, 0x2ad7d2bb);
    II(b, c, d, a, M[ 9], IS4, 0xeb86d391);

    linka += a; linkb += b; linkc += c; linkd += d;
}

//对字符串计算MD5.三个形参,表示信息源为字符串,而非文件路径
static void md5(const char* pstr, unsigned long long len_B_, char* md5str)
{
    unsigned long long                  //考虑超长字符串
        len_B = len_B_ - 1,             //当信息源是字符串时,最后一个字节为'\0',为结束标志,不计数,故需减1
        group_num = len_B >> 6;         //不含填充信息的分组数量,可取值0.右移6位,相当于除以64的商
    int mod64Byte = len_B & 0x3F;       //信息的字节数除以64的余数
    unsigned int group[16];             //表示一个分组,共32*16=512 bit,步幅为4字节
    unsigned char* pchar = 
        (unsigned char*)group;          //指向分组的首地址,步幅为1字节.

    //四个链接变量初值
    linka = A; linkb = B; linkc = C; linkd = D;

    //处理不含填充信息的分组,共有group_num个
    for (int i = 0; i < group_num; i++){
        //i << 6:表示i乘以64,为一个分组的字节数,也为分组首地址之间的步幅
        //为减少从数据源大量复制数据的时间,直接指向数据源需要的分组数据,而不进行复制
        one_group((unsigned int*)(pstr + (i << 6)));
    }

    //mod64Byte < 56,意味着含有填充信息的分组只有一组
    if (mod64Byte < 56) {
        for (int i = 0; i < 14; i++)
            group[i] = 0;
        for (int i = 0; i < mod64Byte; i++)
            *(pchar + i) = *(pstr + (group_num<<6)+ i);
        *(pchar + mod64Byte) = 0x80;

        //扩展,原信息的bit数量,64位.
        *((unsigned long long*) & group[14]) = len_B << 3;

        one_group(group);
    } else {//mod64Byte >= 56,意味着含有填充信息的分组有两组
        //初始化倒数第二个分组各bit为0
        for (int i = 0; i < 16; i++) {
            group[i] = 0;
        }

        //倒数第二个分组所需的非填充数据在数据源中的偏移量,单位:字节
        group_num <<= 6;

        //从数据源中截取尾部不足一个分组的数据
        for (int i = 0; i < mod64Byte; i++) {
            *(pchar + i) = *(pstr + group_num + i);
        }

        //该字节的最高位填充1
        *(pchar + mod64Byte) = 0x80;

        //计算倒数第二个分组
        one_group(group);

        //初始化最后一个分组前56个字节各bit为0
        for (int i = 0; i < 14; i++) {
            group[i] = 0;
        }

        //扩展,原信息的bit数量,64位.在内存中小端存放(数据的低字节放在内存的低地址)
        *((unsigned long long*) & group[14]) = len_B << 3;

        //计算最后一个分组
        one_group(group);
    }

    //取得最终MD5的16进制字符串
    for (int i = 0; i < 4; i++) {
        md5str[(i << 1)] = str16[(*((unsigned char*)&linka + i))>>4];
        md5str[(i << 1) +1] = str16[(*((unsigned char*)&linka + i)) & 0x0F ];
        md5str[(i << 1) +8] = str16[(*((unsigned char*)&linkb + i)) >> 4];
        md5str[(i << 1) + 9] = str16[(*((unsigned char*)&linkb + i)) & 0x0F];
        md5str[(i << 1) + 16] = str16[(*((unsigned char*)&linkc + i)) >> 4];
        md5str[(i << 1) + 17] = str16[(*((unsigned char*)&linkc + i)) & 0x0F];
        md5str[(i << 1) + 24] = str16[(*((unsigned char*)&linkd + i)) >> 4];
        md5str[(i << 1) + 25] = str16[(*((unsigned char*)&linkd + i)) & 0x0F];
    }

    //最终MD5字符串结尾标志
    md5str[32] = 0;
}

} // namespace utils

#endif
